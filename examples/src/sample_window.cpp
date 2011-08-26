
#include <AoTK/aotk.h>

AoTK::Window* window;

float a = 0.5;

void display(){
	GLERRORS();
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);


	glBegin(GL_TRIANGLES);
	glColor3f(1,0,0);glVertex3f(-a,a,-3);
	glColor3f(0,1,0);glVertex3f(a,a,-3);
	glColor3f(0,0,1);glVertex3f(0,-a,-3);
	glEnd();
}

void keyDown(AoTK::KEY key){
    if(key == AoTK::KEY::F){
        window->toggleFullscreen();
    }if(key == AoTK::KEY::ESC){
        window->stop();
    }
}

void scroll(int i){
	a *= 1.0 + (0.1 * i);
	window->redraw();
}

void resize(int w,int h){
	std::cout << "Resize to : "<< w << " " << h << std::endl;
    glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glLoadMatrixf(AoTK::Math::Matrix4x4<float>::perspectiveProjection(45,
                                                                      float(w)/h,
                                                                      0.1,
                                                                      10).toOpenGLMatrix()._1d);
	glMatrixMode(GL_MODELVIEW);
	window->redraw();
}

int main(int argc , char * argv[]){
	AoTK::init();
	window = AoTK::Window::createWindow(600,600,"SampleWindow");
	
	window->setDisplayFunction(display);
	window->addResizeListener(resize);
	window->addScrollListener(scroll);
	window->addKeyDownListener(keyDown);
	window->redraw();


	glClearColor(0,0,0,1);
	glDisable(GL_DEPTH_TEST);
	
	
	window->resizeEvent();

	auto d = AoTK::getDevices();
	auto i = AoTK::getNumberOfDevices();
	for(unsigned int a = 0;a<i;a++){
		std::cout << "Device 1: " << d[a] << std::endl;
    }
        
	
	window->start();


	return 0;
}
