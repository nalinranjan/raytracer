CXX=g++
CC=g++
# LDFLAGS=-O3
LDLIBS=-L/usr/local/lib -lPNGwriter -lpng -lz -lpthread
CXXFLAGS=-O3 -std=c++0x -pthread -DNO_FREETYPE -isystem /home/nalin/Sourceballs/eigen-eigen-5a0156e40feb -Wall -Wextra -pedantic

SRCS=ray.cpp triangletex.cpp checkerboard.cpp PerlinNoise.cpp checkerboardnoisy.cpp trytexture.cpp imgtexture.cpp illumination.cpp phongblinn.cpp intersect.cpp aabb.cpp tinyply.cpp object.cpp sphere.cpp triangle.cpp kdnode.cpp light.cpp tone_ward.cpp tone_reinhard.cpp tone_adaptive_log.cpp world.cpp camera.cpp main.cpp
OBJS=$(subst .cpp,.o,$(SRCS))
OBJECTS=sphere triangle
MODELS=phongblinn
TEXTURES=checkerboard checkerboardnoisy trytexture imgtexture

all: main

main: $(OBJS)

main.o: main.cpp params.h
camera.o: camera.cpp camera.h params.h
world.o: world.cpp world.h params.h
kdnode.o: kdnode.cpp kdnode.h params.h
tone_ward.o: tone_ward.cpp tone_ward.h params.h
tone_reinhard.o: tone_reinhard.cpp tone_reinhard.h params.h
tone_adaptive_log.o: tone_adaptive_log.cpp tone_adaptive_log.h params.h

$(addsuffix .o,$(OBJECTS)): %.o: %.cpp %.h object.o
$(addsuffix .o,$(MODELS)): %.o: %.cpp %.h illumination.o
$(addsuffix .o,$(TEXTURES)): %.o: %.cpp %.h triangletex.o

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	$(RM) main $(OBJS)