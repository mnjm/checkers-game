Checkers_Game: include/Objects.h include/Events.h
	g++ src/Main.cpp -o Checkers_Game -Iinclude -lglut -lGL -lGLU

clean:
	rm -f Checkers_Game
