all: shaders

clean:
	rm *.o shaders

gl.o: gl.cpp gl.h
	g++ $(FLAGS) -c gl.cpp

main.o: main.cpp
	g++ $(FLAGS) -c main.cpp

obj.o: obj.cpp obj.h
	g++ $(FLAGS) -c obj.cpp

shaders: gl.o main.o obj.o
	g++ $(FLAGS) -o shaders gl.o main.o obj.o -lGL -lSDL2