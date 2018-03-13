#include "parallel.h"
#include "msg.h"

#include <functional>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

class Parallel
{
public:
    Parallel(uint32_t num_workers) {

        // give workers an empty task
        m_task = [](uint32_t) {};
        m_accept_work = true;
        m_num_workers = num_workers;

        // set work available status
        for (uint32_t worker_id = 0; worker_id < num_workers-1; worker_id++) {
            m_work_available.emplace_back(true);
        }

        // create worker threads
        for (uint32_t worker_id = 0; worker_id < num_workers-1; worker_id++) {
            m_workers.emplace_back(std::thread(&Parallel::do_work, this, worker_id));
        }

        // wait for workers to finish task to make sure they're ready
        wait();
    }

    ~Parallel() {
        // wait for all workers to finish their current work
        wait();

        // exit worker main loops
        m_accept_work = false;
        for (auto&& workAvailable : m_work_available) {
            workAvailable = true;
        }
        m_signal_work.notify_all();

        // join worker threads to make sure they have finished
        for (auto& thread : m_workers) {
            thread.join();
        }

        // destroy all worker threads
        m_workers.clear();
    }

    void run(std::function<void(uint32_t)>&& task) {
        // don't allow more tasks if workers are stopping
        if (!m_accept_work) {
            throw std::runtime_error("Workers are exiting and no longer accept work");
        }

        // prepare task for workers and send signal so they start working
        m_task = task;

        {
            std::unique_lock<std::mutex> ul(m_signal_mutex);
            for (auto&& workAvailable : m_work_available) {
                workAvailable = true;
            }
        }

        m_signal_work.notify_all();
        m_task(m_num_workers-1);

        // wait for all workers to finish
        wait();
    }

private:
    std::function<void(uint32_t)> m_task;
    std::vector<std::thread> m_workers;
    std::mutex m_signal_mutex;
    std::condition_variable m_signal_work;
    std::condition_variable m_signal_done;
    std::vector<bool> m_work_available;
    bool m_accept_work;
    uint32_t m_num_workers;

    void do_work(int32_t worker_id) {

        while (m_accept_work) {

            // switch to async mode and run task
            if (m_accept_work) {
                m_task(worker_id);
            }

			{
				std::unique_lock<std::mutex> ul(m_signal_mutex);

				// task is done, update number of active workers
				// and signal main thread
				m_work_available[worker_id] = false;

				m_signal_done.notify_one();
			}

#ifdef ANDROID
			//Busy loop wait for a bit to keep cores awake
			bool workAvailable = false;
			int count = 0;
			while (!workAvailable && count++ < 10000) {
				std::unique_lock<std::mutex> ul(m_signal_mutex);
				workAvailable = m_work_available[worker_id];
				std::this_thread::yield();
			}
#endif

            // go idle and wait for more work
			std::unique_lock<std::mutex> ul(m_signal_mutex);
            m_signal_work.wait(ul, [worker_id, this]{
                bool workAvailable = m_work_available[worker_id];
                return workAvailable;
            });
        }
    }

    void wait() {

#ifdef ANDROID
		//Busy loop wait for a bit to keep cores awake
		bool waitingForWorkDone = true;
		int count = 0;
		while (waitingForWorkDone && count++ < 10000) {

			waitingForWorkDone = false;

			std::unique_lock<std::mutex> ul(m_signal_mutex);
			for (unsigned int index = 0; index < m_work_available.size() && !waitingForWorkDone; ++index) {
				waitingForWorkDone = m_work_available[index];
			}

			std::this_thread::yield();
		}
#endif

		//Switch to idle waiting
        std::unique_lock<std::mutex> ul(m_signal_mutex);
        m_signal_done.wait(ul, [this]{

            for (auto workAvailable : m_work_available) {
                if(workAvailable) return false;
            }
            return true;
        });
    }

    void operator=(const Parallel&) = delete;
    Parallel(const Parallel&) = delete;
};

// C interface for the Parallel class
static std::unique_ptr<Parallel> parallel;
static uint32_t worker_num;

void parallel_init(uint32_t num)
{
    // auto-select number of workers based on the number of cores
    if (num == 0) {
        num = std::thread::hardware_concurrency();
    }

    parallel = std::make_unique<Parallel>(num);

    worker_num = num;
}

void parallel_run(void task(uint32_t))
{
    parallel->run(task);
}

uint32_t parallel_worker_num()
{
    return worker_num;
}

void parallel_close()
{
    parallel.reset();
}
