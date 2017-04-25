ROOT_PATH=$(shell pwd)
CLIENT_PATH=$(ROOT_PATH)/client
SERVER_PATH=$(ROOT_PATH)/server
CONF_PATH=$(ROOT_PATH)/conf
LOG_PATH=$(ROOT_PATH)/log
COMM_PATH=$(ROOT_PATH)/comm
WINDOW=$(ROOT_PATH)/window
LIB_PATH=$(ROOT_PATH)/lib
DATA_POOL_PATH=$(ROOT_PATH)/data_pool
CC=g++
INCLUDE=-I$(SERVER_PATH) -I$(DATA_POOL_PATH) -I$(LOG_PATH)
lib=-lpthread

CLIENT_BIN=udpclient
SERVER_BIN=udpserver

CLIENT_SRC=$(shell ls  $(CLIENT_PATH) $(LOG_PATH)| egrep  '*.cpp')  
SERVER_SRC=$(shell ls  $(SERVER_PATH) $(DATA_POOL_PATH) $(LOG_PATH) | egrep "*.cpp")

CLIENT_OBJ=$(shell echo $(CLIENT_SRC) | sed 's/.cpp/.o/g')
SERVER_OBJ=$(shell echo $(SERVER_SRC) | sed 's/.cpp/.o/g')

.PHONY:all
all:$(CLIENT_BIN) $(SERVER_BIN)

$(CLIENT_BIN):$(CLIENT_OBJ)
	@echo "Linking [$<] to [$@]..."
	$(CC) -o $@ $^ $(INCLUDE)
	@echo "Linking CLIENT done..."
	
%.o:$(CLIENT_PATH)/%.cpp
	$(CC) -c $< $(INCLUDE)
$(SERVER_BIN):$(SERVER_OBJ)
	@echo "Linking [$<] to [$@]..."
	$(CC) -o $@ $^ $(lib)
	@echo "Linking Server done..."
%.o:$(SERVER_PATH)/%.cpp
	$(CC) -c $< $(INCLUDE)

%.o:$(DATA_POOL_PATH)/%.cpp
	$(CC) -c $< 
%.o:$(LOG_PATH)/%.cpp
	$(CC) -c $< 

.PHONY:clean
clean:
	rm -f $(SERVER_BIN) $(SERVER_OBJ) $(CLIENT_BIN) $(CLIENT_OBJ)

.PHONY:debug
debug:
	@echo $(SERVER_SRC)
	@echo $(CLIENT_SRC)
	@echo "--------------------------------"
	@echo $(SERVER_OBJ)
	@echo $(CLIENT_OBJ)
	@echo "--------------------------------"
