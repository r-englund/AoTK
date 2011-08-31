
#include "tests.h"


using namespace AoTK;
using namespace AoTK::IMG;

int testScreens(){
    int fails = 0;
    auto w = AoTK::Window::createWindow(600,600,"Testing Screens");
    w->setDisplayFunction([](){});
    w->redraw();
    w->start();
    return fails;
}

int testRotate(){
    int fails = 0;
	
    auto img1 = Image<uint8_t>::random(4,4,1);
    auto img2 = img1.rotate(90).rotate(90).rotate(90).rotate(90);
    auto img3 = img1.rotate(180).rotate(180);    
	auto img4 = img1.rotate(270).rotate(90);    
	auto img5 = img1.rotate(90).rotate(270);    
	auto img6 = img1.rotate(90).rotate(-90);    
	auto img7 = img1;


	fails += my_assert_false(img7 != img1,"auto img7 = img1 directly followed by img7 != img1 evaluates to true");
	fails += my_assert_true(img7 == img1,"auto img7 = img1 directly followed by img7 == img1 evaluates to false");
	
	for(int x = 0;x<4;x++)for(int y = 0;y<4;y++){
		if(img1.getPixel(x,y) != img2.getPixel(x,y)){
			fails++;
			std::cerr << "Rotate 4x90 doesnt create the same image" << std::endl;
			break;		
		}
	}for(int x = 0;x<4;x++)for(int y = 0;y<4;y++){
		if(img1.getPixel(x,y) != img3.getPixel(x,y)){
			fails++;
			std::cerr << "Rotate 180 + 180 doesnt create the same image" << std::endl;
			break;		
		}
	}for(int x = 0;x<4;x++)for(int y = 0;y<4;y++){
		if(img1.getPixel(x,y) != img4.getPixel(x,y)){
			fails++;
			std::cerr << "Rotate 270 + 90 doesnt create the same image" << std::endl;
			break;		
		}
	}for(int x = 0;x<4;x++)for(int y = 0;y<4;y++){
		if(img1.getPixel(x,y) != img5.getPixel(x,y)){
			fails++;
			std::cerr << "Rotate 90 + 270 doesnt create the same image" << std::endl;
			break;		
		}
	}for(int x = 0;x<4;x++)for(int y = 0;y<4;y++){
		if(img1.getPixel(x,y) != img6.getPixel(x,y)){
			fails++;
			std::cerr << "Rotate +90 followed by -90 doesnt create the same image" << std::endl;
			break;		
		}
	}
	

	return fails;
}

int main(int argc,char ** argv){
    AoTK::init();
	int fails = 0;
	fails += testRotate();
	fails += testScreens();
	return fails;
}
