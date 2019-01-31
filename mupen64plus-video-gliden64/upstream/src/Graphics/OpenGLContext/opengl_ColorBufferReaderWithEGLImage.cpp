#if defined(EGL) && defined(OS_ANDROID)

#include <GBI.h>
#include <Graphics/Context.h>
#include "opengl_ColorBufferReaderWithEGLImage.h"

using namespace opengl;
using namespace graphics;

ColorBufferReaderWithEGLImage::ColorBufferReaderWithEGLImage(CachedTexture *_pTexture, CachedBindTexture *_bindTexture)
	: graphics::ColorBufferReader(_pTexture)
	, m_bindTexture(_bindTexture)
	, m_image(0)
	, m_bufferLocked(false)
{
	m_glEGLImageTargetTexture2DOES = (PFNGLEGLIMAGETARGETTEXTURE2DOESPROC)eglGetProcAddress("glEGLImageTargetTexture2DOES");
	_initBuffers();
}


ColorBufferReaderWithEGLImage::~ColorBufferReaderWithEGLImage()
{
}


void ColorBufferReaderWithEGLImage::_initBuffers()
{
	// Also AHARDWAREBUFFER_USAGE_GPU_COLOR_OUTPUT
	AHardwareBuffer_Desc bufferDesc{m_pTexture->realWidth, m_pTexture->realHeight,
		1, AHARDWAREBUFFER_FORMAT_R8G8B8A8_UNORM,
		AHARDWAREBUFFER_USAGE_CPU_READ_OFTEN | AHARDWAREBUFFER_USAGE_GPU_SAMPLED_IMAGE,
		0,0};
	AHardwareBuffer_allocate(&bufferDesc, &m_hardwareBuffer);
	//m_window.reallocate(m_pTexture->realWidth, m_pTexture->realHeight,
	//	HAL_PIXEL_FORMAT_RGBA_8888, GRALLOC_USAGE_SW_WRITE_OFTEN | GRALLOC_USAGE_HW_TEXTURE);
	EGLint eglImgAttrs[] = { EGL_IMAGE_PRESERVED_KHR, EGL_TRUE, EGL_NONE, EGL_NONE };

	EGLClientBuffer clientBuffer = eglGetNativeClientBufferANDROID(m_hardwareBuffer);

	if(m_image == 0)
	{
		m_image = eglCreateImageKHR(eglGetDisplay(EGL_DEFAULT_DISPLAY), EGL_NO_CONTEXT,
			EGL_NATIVE_BUFFER_ANDROID, clientBuffer, eglImgAttrs);
	}
}


const u8 * ColorBufferReaderWithEGLImage::_readPixels(const ReadColorBufferParams& _params, u32& _heightOffset,
	u32& _stride)
{
	GLenum format = GLenum(_params.colorFormat);
	GLenum type = GLenum(_params.colorType);

	void* gpuData = nullptr;

	if (!_params.sync) {
		m_bindTexture->bind(graphics::Parameter(0), graphics::Parameter(GL_TEXTURE_2D), m_pTexture->name);
		m_glEGLImageTargetTexture2DOES(GL_TEXTURE_2D, m_image);
		m_bindTexture->bind(graphics::Parameter(0), graphics::Parameter(GL_TEXTURE_2D), ObjectHandle());

		//m_window.lock(GRALLOC_USAGE_SW_READ_OFTEN, &gpuData);
		AHardwareBuffer_lock(m_hardwareBuffer, AHARDWAREBUFFER_USAGE_CPU_READ_OFTEN, -1, nullptr, &gpuData);
		m_bufferLocked = true;
		_heightOffset = static_cast<u32>(_params.y0);
		_stride = m_pTexture->realWidth;
	} else {
		gpuData = m_pixelData.data();
		glReadPixels(_params.x0, _params.y0, _params.width, _params.height, format, type, gpuData);
		_heightOffset = 0;
		_stride = m_pTexture->realWidth;
	}

	return reinterpret_cast<u8*>(gpuData);
}

void ColorBufferReaderWithEGLImage::cleanUp()
{
	if (m_bufferLocked) {
		//m_window.unlock();
		AHardwareBuffer_unlock(m_hardwareBuffer, NULL);
		m_bufferLocked = false;
	}
}

#endif // EGL
