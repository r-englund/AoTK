#ifndef FBO_H
#define FBO_H

#include <AoTK/aotk.h>

namespace AoTK{
class FBO
{
public:
	FBO(void);
	~FBO(void);
	void create(int width, int height);
	void bind();
	void unbind();
	void clear();
	void render();
	GLuint getTex();
private:
	GLuint fboId, colorId, depthId, w, h;
	void fboerror();
};
};





#endif
