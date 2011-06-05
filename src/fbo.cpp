#include <AoTK/fbo.h>

namespace AoTK{
namespace GPU{
FBO::FBO(){
    isInit = false;
    _numAttachemnts = 0;
    _w = 0;
    _h = 0;
}

FBO::~FBO(){
    if(isInit){
        glDeleteFramebuffers(1,&_fbo);
    }
}
void FBO::init(){
    if(isInit)
        return;
    isInit = true;
    glGenFramebuffers(1, &_fbo);GLERRORS();

    glGenTextures(1, &_depthtex);GLERRORS();
    glBindTexture(GL_TEXTURE_2D, _depthtex);GLERRORS();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);GLERRORS();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);GLERRORS();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);GLERRORS();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);GLERRORS();

    glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);GLERRORS();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);GLERRORS();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);GLERRORS();

    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, _w, _h, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);GLERRORS();

    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);GLERRORS();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _depthtex, 0);GLERRORS();GLERRORS();

    std::cout << GL_FRAMEBUFFER << std::endl;
    std::cout << GL_DEPTH_ATTACHMENT_EXT << std::endl;
    std::cout << GL_TEXTURE_2D << std::endl;
    std::cout << _depthtex << std::endl;
    std::cout << "asdf"<< std::endl;
//    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, _fbo);GLERRORS();
//    glGenRenderbuffers(1, &_depth);
//
//    glBindRenderbuffer(GL_RENDERBUFFER, _depth);
//    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, _w, _h);
//
//    glFramebufferRenderbuffer(GL_FRAMEBUFFER,
//                              GL_DEPTH_ATTACHMENT,
//                              GL_RENDERBUFFER,
//                              _depthtex);

    unbind();GLERRORS();
}

void FBO::setSize(uint16_t w,uint16_t h){
    _w = w;
    _h = h;
    std::cout << "Change setSize in " << __FILE__ << ":" << __LINE__ << " to update sizes of attachments" << std::endl;
}

uint8_t FBO::createAttachment(){
    if(!isInit)
        init();
    uint8_t index = _numAttachemnts++;
    attachment.push_back(0);

    glGenTextures(1, &attachment[index]);
    glBindTexture(GL_TEXTURE_2D, attachment[index]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16, _w, _h, 0, GL_RGBA, GL_FLOAT, 0);
    bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0+index, GL_TEXTURE_2D, attachment[index], 0);

    fboerror();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    unbind();

    return index;


}

GLuint FBO::getTexture(uint8_t attatchemntID){return attachment[attatchemntID];}
GLuint FBO::getDepthTexture(){return _depthtex;}

void FBO::bind(uint8_t attatchemntID){
    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
    glDrawBuffer(GL_COLOR_ATTACHMENT0 + attatchemntID);
}

void FBO::clear(uint8_t attatchemntID){
    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
    glDrawBuffer(GL_COLOR_ATTACHMENT0 + attatchemntID);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void FBO::clear(uint8_t* attatchemntIDs,uint8_t num_attachemnts){
    for(int i = 0;i<num_attachemnts;i++){
        clear(attatchemntIDs[i]);
    }
}
void FBO::bind(uint8_t* attatchemntIDs,uint8_t num_attachemnts){
    GLenum * mrt = new GLenum[num_attachemnts];
    for(int i = 0; i<num_attachemnts;i++)
        mrt[i] = GL_COLOR_ATTACHMENT0_EXT + attatchemntIDs[i];
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, _fbo);
    glDrawBuffers(num_attachemnts,mrt);
    delete mrt;
}
void FBO::unbind(){
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
    glDrawBuffer(GL_BACK);
}


void FBO::render(uint8_t attatchemntID)
{
	glPushAttrib(GL_VIEWPORT_BIT);
    glViewport(0, 0, _w, _h);
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glColor4f(1.f, 1.f, 1.f, 1.f);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, 1, 1, 0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glBindTexture(GL_TEXTURE_2D, attachment[attatchemntID]);
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
}
};
};
