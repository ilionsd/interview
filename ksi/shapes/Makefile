
CXXFLAGS = -g -Wall -std=c++11 
LDFLAGS = -g -lstdc++

OBJS = bin/main.o bin/cylinder.o bin/cuboid.o bin/cube.o bin/pyramid.o


bin/shapes : $(OBJS)
	g++ $(LDFLAGS) -o bin/shapes $(OBJS)

bin/main.o : src/main.cpp 
	g++ -c $(CXXFLAGS) -o bin/main.o src/main.cpp

bin/cylinder.o : lib/cylinder.cpp lib/cylinder.hpp lib/shape.hpp include/cloning.hpp
	g++ -c $(CXXFLAGS) -o bin/cylinder.o lib/cylinder.cpp 

bin/cuboid.o : lib/cuboid.cpp lib/cuboid.hpp lib/shape.hpp include/cloning.hpp
	g++ -c $(CXXFLAGS) -o bin/cuboid.o lib/cuboid.cpp 

bin/cube.o : lib/cube.cpp lib/cube.hpp lib/shape.hpp include/cloning.hpp
	g++ -c $(CXXFLAGS) -o bin/cube.o lib/cube.cpp 

bin/pyramid.o : lib/pyramid.cpp lib/pyramid.hpp lib/shape.hpp include/cloning.hpp
	g++ -c $(CXXFLAGS) -o bin/pyramid.o lib/pyramid.cpp
	


clean:
	rm -f $(OBJS) bin/shapes

