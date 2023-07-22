LIBS:=-Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system

all: pong

main.o: main.cpp GameObject.h Paddle.h Ball.h
	g++ -Isrc/include -c main.cpp

GameObject.o: GameObject.h
	g++ -Isrc/include -c "GameObject.cpp" -o GameObject.o

Paddle.o: Paddle.cpp Paddle.h
	g++ -Isrc/include -c "Paddle.cpp" -o Paddle.o

vector.o: VectorMath.cpp VectorMath.h
	g++ -Isrc/include -c "VectorMath.cpp" -o vector.o

Ball.o: Ball.cpp Ball.h VectorMath.h
	g++ -Isrc/include -c "Ball.cpp" -o Ball.o


pong: main.o GameObject.o Paddle.o Ball.o vector.o
	g++ -o pong main.o GameObject.o Paddle.o Ball.o vector.o $(LIBS)