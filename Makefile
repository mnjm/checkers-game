Checkers_Game: Objects.h Events.h
	g++ Main.cpp -o Checkers_Game -lglut -lGL -lGLU

clean:
	rm -f Checkers_Game
