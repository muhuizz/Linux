FLAGS=-D_DEBUG_

window:window.cpp
	g++ -o $@ $^ -lncurses -lpthread $(FLAGS)
.PHONY:clean
clean:
	rm -f window
