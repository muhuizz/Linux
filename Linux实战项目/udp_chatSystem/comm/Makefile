INCLUDE=-I/home/muhui/code/chat_system/lib/include/
LIB=-L/home/muhui/code/chat_system/lib/lib/
lib=-ljsoncpp
object:dataType.cpp jsonApi.cpp
	g++ -o $@ $^ $(INCLUDE) $(LIB) $(lib)

.PHONY:clean
clean:
	rm -f object
