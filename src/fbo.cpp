

#include <AoTK/aotk.h>

namespace AoTK{
FBO::FBO(void)
{
}

FBO::~FBO(void)
{
    glDeleteFramebuffersEXT(1, &fboId);
    glDeleteTextures(1, &colorId);
}

void FBO::create(int width, int height)
{
	w = width;
	h = height;
	// Create an FBO
	glGenFramebuffers(1, &fboId);

    getAllError(__FILE__,__LINE__);
	// Create color texture
	glGenTextures(1, &colorId);

    getAllError(__FILE__,__LINE__);
	glBindTexture(GL_TEXTURE_2D, colorId);

    getAllError(__FILE__,__LINE__);
    /* for completeness */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    getAllError(__FILE__,__LINE__);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    getAllError(__FILE__,__LINE__);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

    getAllError(__FILE__,__LINE__);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    getAllError(__FILE__,__LINE__);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

    getAllError(__FILE__,__LINE__);

    bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorId, 0);



    getAllError(__FILE__,__LINE__);
    // depth
    glGenRenderbuffers(1, &depthId);

    getAllError(__FILE__,__LINE__);
    glBindRenderbuffer(GL_RENDERBUFFER, depthId);

    getAllError(__FILE__,__LINE__);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24,
                    w, h);

    getAllError(__FILE__,__LINE__);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER,
                    GL_DEPTH_ATTACHMENT,
                    GL_RENDERBUFFER,
                    depthId);

    getAllError(__FILE__,__LINE__);
	fboerror();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    unbind();
}

void FBO::bind()
{
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fboId);
}

void FBO::unbind()
{
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

void FBO::clear()
{
	bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	unbind();
}

GLuint FBO::getTex()
{
	return colorId;
}

void FBO::render()
{
	glPushAttrib(GL_VIEWPORT_BIT);
    glViewport(0, 0, w, h);
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glColor4f(1.f, 1.f, 1.f, 1.f);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, 1, 1, 0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glBindTexture(GL_TEXTURE_2D, colorId);
	glBegin(GL_QUADS);
	glTexCoord2f(0.f, 1.f); glVertex2f(0.0f, 0.f);
	glTexCoord2f(0.f, 0.f); glVertex2f(0.0f, 1.0f);
	glTexCoord2f(1.f, 0.f); glVertex2f(1.0f, 1.0f);
	glTexCoord2f(1.f, 1.f); glVertex2f(1.0f, 0.f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glPopMatrix();
	glPopAttrib();
}

void FBO::fboerror()
{

    getAllError(__FILE__,__LINE__);
	switch(glCheckFramebufferStatus(GL_FRAMEBUFFER))
	{
	case GL_FRAMEBUFFER_COMPLETE_EXT:
		printf("FRAMEBUFFER_COMPLETE\n");
		break;
	case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT:
		printf("FRAMEBUFFER_INCOMPLETE_ATTACHMENT\n");
		break;
	case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
		printf("FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT\n");
		break;
	case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
		printf("FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT\n");
		break;
	case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
		printf("FRAMEBUFFER_INCOMPLETE_FORMATS_EXT\n");
		break;
	case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:
		printf("FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT\n");
		break;
	case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:
		printf("FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT\n");
		break;
	case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
		printf("FRAMEBUFFER_UNSUPPORTED\n");
		break;
	default:
		printf("paws\n");
		break;
	}

    getAllError(__FILE__,__LINE__);
}
};


