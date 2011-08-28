#ifndef AOTK_H
#define AOTK_H

#include "window_handler.h"
#include "math.h"
#include "image.h"
#include "shader.h"
#include "fbo.h"
#include "geometry.h"
#include "mesh.h"


namespace AoTK{
	void init();

	extern AoTK::Math::Vector4<int> *devices;
	extern int number_of_devices;

	AoTK::Math::Vector4<int> *getDevices();
	unsigned int getNumberOfDevices();
	void initDevices();
	
	void getAllError(std::string file, int line);

    
};

#endif
