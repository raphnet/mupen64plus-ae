#pragma once
#ifdef EGL
#include <Graphics/ColorBufferReader.h>
#include "opengl_CachedFunctions.h"

#include <android/hardware_buffer.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>

typedef void (APIENTRYP PFNGLEGLIMAGETARGETTEXTURE2DOESPROC) (GLenum target, EGLImageKHR image);

namespace opengl {

class ColorBufferReaderWithEGLImage : public graphics::ColorBufferReader
{
public:
	ColorBufferReaderWithEGLImage(CachedTexture * _pTexture,
								  CachedBindTexture * _bindTexture);
	~ColorBufferReaderWithEGLImage();

	const u8 * _readPixels(const ReadColorBufferParams& _params, u32& _heightOffset, u32& _stride) override;

	void cleanUp() override;

private:
	void _initBuffers();

	CachedBindTexture * m_bindTexture;
	AHardwareBuffer* m_hardwareBuffer;
	EGLImageKHR m_image;
	PFNGLEGLIMAGETARGETTEXTURE2DOESPROC m_glEGLImageTargetTexture2DOES;
	bool m_bufferLocked;
};

}

#endif //EGL
