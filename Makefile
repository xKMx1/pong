# all: complie link

# complie:
# 	g++ -Isrc/include -c main.cpp

# link:
# 	g++ main.o -o Pong -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system

LIBS:=-Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system

all: pong

main.o: main.cpp GameObject.h Paddle.h Ball.h
	g++ -Isrc/include -c main.cpp

GameObject.o: GameObject.cpp
	g++ -Isrc/include -c "GameObject.cpp" -o GameObject.o

GameObject.cpp: GameObject.h

Paddle.o: Paddle.cpp
	g++ -Isrc/include -c "Paddle.cpp" -o Paddle.o

Paddle.cpp: Paddle.h

Ball.o: Ball.cpp
	g++ -Isrc/include -c "Ball.cpp" -o Ball.o

Ball.cpp: Ball.h

pong: main.o GameObject.o Paddle.o Ball.o
	g++ -o pong main.o GameObject.o Paddle.o Ball.o $(LIBS)