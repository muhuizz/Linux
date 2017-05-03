INCLUDE=-I/home/muhui/code/chat_system/lib/include/
LIB=-L/home/muhui/code/chat_system/lib/lib/
lib=-ljsoncpp
FLAGS=-D_DEBUG_ -D_FAST_
object:dataType.cpp jsonApi.cpp
	g++ -o $@ $^ $(INCLUDE) $(LIB) $(lib) $(FLAGS)

.PHONY:clean
clean:
	rm -f object
