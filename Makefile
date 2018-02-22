all: main

main: ray.o object.o sphere.o triangle.o cylinder.o light.o world.o camera.o main.o
	g++ -o main main.o ray.o object.o sphere.o triangle.o cylinder.o light.o world.o camera.o -L/usr/local/lib -lPNGwriter -lpng -lz

main.o: main.cpp params.h
	g++ -O3 -c main.cpp -DNO_FREETYPE -I/home/nalin/Sourceballs/eigen-eigen-5a0156e40feb

ray.o: ray.cpp ray.h
	g++ -O3 -c ray.cpp -I/home/nalin/Sourceballs/eigen-eigen-5a0156e40feb

object.o: object.cpp object.h
	g++ -O3 -c object.cpp -I/home/nalin/Sourceballs/eigen-eigen-5a0156e40feb

sphere.o: sphere.cpp sphere.h object.o
	g++ -O3 -c sphere.cpp -I/home/nalin/Sourceballs/eigen-eigen-5a0156e40feb

triangle.o: triangle.cpp triangle.h object.o
	g++ -O3 -c triangle.cpp -I/home/nalin/Sourceballs/eigen-eigen-5a0156e40feb

cylinder.o: cylinder.cpp cylinder.h object.o
	g++ -O3 -c cylinder.cpp -I/home/nalin/Sourceballs/eigen-eigen-5a0156e40feb

light.o: light.cpp light.h
	g++ -O3 -c light.cpp -I/home/nalin/Sourceballs/eigen-eigen-5a0156e40feb

world.o: world.cpp world.h
	g++ -O3 -c world.cpp -I/home/nalin/Sourceballs/eigen-eigen-5a0156e40feb

camera.o: camera.cpp camera.h params.h
	g++ -O3 -c camera.cpp -DNO_FREETYPE -I/home/nalin/Sourceballs/eigen-eigen-5a0156e40feb