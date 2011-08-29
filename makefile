
OBJS = glew.o fbo.o math.o shader.o Image_BMP.o Image_GL.o Image_JSON.o Image_double.o Image_float.o Image_uint8.o mesh.o window.o window_unix.o window_win.o aotk_win.o aotk_unix.o
ODIR = obj
OBJPATH = $(patsubst %,$(ODIR)/%,$(OBJS))

OS = unkown

ifeq ($(shell uname) , Linux)
    OS = Linux
endif
ifeq ($(shell uname -o) , Msys)
    OS = Windows
endif
ifeq ($(shell uname) , MINGW32_NT-6.0)
    OS = Windows
endif



ifeq ($(OS) , Linux)
	CPP = g++
	CC = gcc
	GL = /user/include
	LFLAGS =  -L /usr/lib/mesa -L . -lAoTK -lGL -lXext -lXau -lXdmcp -lxcb -lX11 -lXxf86vm
	CFLAGS = -Wall -std=c++0x -I ./include -I $(GL)	
	RM = rm -f
	AR = ar -cr
	OUT = out
	CHMOD = chmod 755
endif
ifeq ($(OS) , Windows)
	PATH = C:\MinGW\bin
	CPP = $(PATH)\mingw32-g++.exe
	CC = $(PATH)\mingw32-gcc.exe
	LFLAGS =  -L C:\MinGW\lib -lopengl32 -L . -lAoTK -lkernel32 -luser32 -lgdi32  -lopengl32 -lglu32 -lglaux -lkernel32 -luser32 -lgdi32 -lwinspool -lcomdlg32 -ladvapi32 -lshell32 -lole32 -loleaut32 -luuid -lodbc32 -lodbccp32
	GL = C:\MinGW\include
	CFLAGS = -Wall -std=c++0x -I .\include -I $(GL)	
	AR = $(PATH)\ar cr 
	RM = rm -f
	OUT = exe
	CHMOD = echo
endif


all : libAoTK

libAoTK : $(OBJPATH)
	$(AR) libAoTK.a $(OBJPATH)

$(ODIR)/glew.o : 
	$(CC) -g -I ./include -I $(GL) -w -c src/externals/glew.c -o $(ODIR)/glew.o

$(ODIR)/fbo.o : src/fbo.cpp
	$(CPP) $(CFLAGS) -c $< -o $(ODIR)/fbo.o 

$(ODIR)/math.o : src/math.cpp
	$(CPP) $(CFLAGS) -c $< -o $(ODIR)/math.o 

$(ODIR)/shader.o : src/shader.cpp
	$(CPP) $(CFLAGS) -c $< -o $(ODIR)/shader.o 

$(ODIR)/Image_BMP.o : src/img/Image_BMP.cpp
	$(CPP) $(CFLAGS) -c $< -o $(ODIR)/Image_BMP.o 

$(ODIR)/Image_GL.o : src/img/Image_GL.cpp
	$(CPP) $(CFLAGS) -c $< -o $(ODIR)/Image_GL.o 

$(ODIR)/Image_JSON.o : src/img/Image_JSON.cpp
	$(CPP) $(CFLAGS) -c $< -o $(ODIR)/Image_JSON.o 

$(ODIR)/Image_double.o : src/img/Image_double.cpp
	$(CPP) $(CFLAGS) -c $< -o $(ODIR)/Image_double.o 

$(ODIR)/Image_float.o : src/img/Image_float.cpp
	$(CPP) $(CFLAGS) -c $< -o $(ODIR)/Image_float.o 

$(ODIR)/Image_uint8.o : src/img/Image_uint8.cpp
	$(CPP) $(CFLAGS) -c $< -o $(ODIR)/Image_uint8.o 

$(ODIR)/mesh.o : src/mesh/mesh.cpp
	$(CPP) $(CFLAGS) -c $< -o $(ODIR)/mesh.o 

$(ODIR)/window.o : src/window/window.cpp
	$(CPP) $(CFLAGS) -c $< -o $(ODIR)/window.o 

$(ODIR)/window_unix.o : src/window/window_unix.cpp
	$(CPP) $(CFLAGS) -c $< -o $(ODIR)/window_unix.o 

$(ODIR)/window_win.o : src/window/window_win.cpp
	$(CPP) $(CFLAGS) -c $< -o $(ODIR)/window_win.o 

$(ODIR)/aotk_win.o : src/aotk_win.cpp
	$(CPP) $(CFLAGS) -c $< -o $(ODIR)/aotk_win.o 

$(ODIR)/aotk_unix.o : src/aotk_unix.cpp
	$(CPP) $(CFLAGS) -c $< -o $(ODIR)/aotk_unix.o 


TEST_SRC_DIR = test/src
TEST_OUT_DIR = test/exec
TESTS = img math

tests : libAoTK $(TESTS) 
	$(CHMOD) $(TEST_OUT_DIR)/*

$(TESTS) : 
	$(CPP) $(CFLAGS) $(TEST_SRC_DIR)/$@.cpp $(LFLAGS) -o $(TEST_OUT_DIR)/$@.$(OUT)

withtest : tests
	./run_tests

EX_SRC_DIR = examples/src
EX_OUT_DIR = examples
EXS = sample_window

examples : libAoTK $(EXS) 
	$(CHMOD) $(EX_OUT_DIR)/*

$(EXS) : 
	$(CPP) $(CFLAGS) $(EX_SRC_DIR)/$@.cpp $(LFLAGS) -o $(EX_OUT_DIR)/$@.$(OUT)


clean : 
	$(RM) obj/*


