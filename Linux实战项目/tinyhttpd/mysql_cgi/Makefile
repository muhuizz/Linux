ROOT_PATH=$(shell pwd)
INCLUDE_PATH=-I$(ROOT_PATH)/../lib/include
LIB_PATH=-L$(ROOT_PATH)/../lib/lib
lib=-lmysqlclient -lpthread -ldl -lrt
cc=g++
#FLAG=-static
debug=-D_DEBUG
.PHONY:all
all:cgi_insert cgi_select cgi_delete cgi_modify
cgi_insert:cgi_insert.cpp mysql_api.cpp
	$(cc) -o $@ $^ $(INCLUDE_PATH) $(LIB_PATH) $(lib) $(FLAG)
cgi_select:cgi_select.cpp mysql_api.cpp
	$(cc) -o $@ $^ $(INCLUDE_PATH) $(LIB_PATH) $(lib) $(FLAG)
cgi_delete:cgi_delete.cpp mysql_api.cpp
	$(cc) -o $@ $^ $(INCLUDE_PATH) $(LIB_PATH) $(lib) $(FLAG)
cgi_modify:cgi_modify.cpp mysql_api.cpp
	$(cc) -o $@ $^ $(INCLUDE_PATH) $(LIB_PATH) $(lib) $(FLAG)
ENV:
	@export LD_LIBRARY_PATH=/home/muhui/code/httpd/lib/lib
#mysql_api: mysql_api.cpp 
#	$(cc) -o $@ $^ $(INCLUDE_PATH) $(LIB_PATH) $(lib) $(FLAG) $(debug)

.PHONY:clean
clean:
	rm -f cgi_insert cgi_select cgi_delete cgi_modify
#	rm -f mysql_api
