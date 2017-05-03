ROOT_PATH=$(shell pwd)
CLIENT_PATH=$(ROOT_PATH)/client
SERVER_PATH=$(ROOT_PATH)/server
CONF_PATH=$(ROOT_PATH)/conf
LOG_PATH=$(ROOT_PATH)/log
COMM_PATH=$(ROOT_PATH)/comm
WINDOW_PATH=$(ROOT_PATH)/windows
LIB_PATH=$(ROOT_PATH)/lib
DATA_POOL_PATH=$(ROOT_PATH)/data_pool
CC=g++

INCLUDE= -I$(DATA_POOL_PATH) -I$(LOG_PATH) -I$(COMM_PATH) -I$(LIB_PATH)/include -I$(WINDOW_PATH) 
lib=-lpthread -ljsoncpp 
JSON_LIB=-L$(LIB_PATH)/lib
#COMP=-static
FLAGS=-D_FAST_
CLIENT_BIN=udpclient
SERVER_BIN=udpserver

CLIENT_SRC=$(shell ls  $(CLIENT_PATH) $(LOG_PATH) $(COMM_PATH) $(WINDOW_PATH)| egrep  '*.cpp')  
SERVER_SRC=$(shell ls  $(SERVER_PATH) $(DATA_POOL_PATH) $(LOG_PATH) $(COMM_PATH) | egrep "*.cpp")

CLIENT_OBJ=$(shell echo $(CLIENT_SRC) | sed 's/.cpp/.o/g')
SERVER_OBJ=$(shell echo $(SERVER_SRC) | sed 's/.cpp/.o/g')

.PHONY:all
all:$(SERVER_BIN) $(CLIENT_BIN)

$(SERVER_BIN):$(SERVER_OBJ)
	@echo "Linking [$<] to [$@]..."
	$(CC) -o $@ $^ $(lib) $(COMP) $(JSON_LIB)
	@echo "Linking Server done..."
%.o:$(SERVER_PATH)/%.cpp
	$(CC) -c $< $(INCLUDE) 

$(CLIENT_BIN):$(CLIENT_OBJ)
	@echo "Linking [$<] to [$@]..."
	$(CC) -o $@ $^ $(COMP) $(JSON_LIB) $(lib)  -lncurses 
	@echo "Linking CLIENT done..."
%.o:$(CLIENT_PATH)/%.cpp
	$(CC) -c $< $(INCLUDE)

%.o:$(DATA_POOL_PATH)/%.cpp
	$(CC) -c $< $(lib) 
%.o:$(LOG_PATH)/%.cpp
	$(CC) -c $< 
%.o:$(COMM_PATH)/%.cpp
	$(CC) -c $< $(INCLUDE) $(FLAGS)
%.o:$(WINDOW_PATH)/%.cpp
	$(CC) -c $< 

.PHONY:output
output:
	mkdir -p output/log
	cp $(SERVER_BIN) output
	cp $(CLIENT_BIN) output
	cp -rf $(CONF_PATH) output
	cp server_ctl.sh output
	cp client_ctl.sh output

.PHONY:clean
clean:
	rm -rf $(SERVER_BIN) $(SERVER_OBJ) $(CLIENT_BIN) $(CLIENT_OBJ) output

.PHONY:debug
debug:
	@echo $(SERVER_SRC)
	@echo $(CLIENT_SRC)
	@echo "--------------------------------"
	@echo $(SERVER_OBJ)
	@echo $(CLIENT_OBJ)
	@echo "--------------------------------"
