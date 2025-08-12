CC:=gcc
.Phony: clean all build

SRC_DIR:= ./src .
INC_DIR:= ./inc
OBJ_DIR:= ./obj

CFLAG:= -I$(INC_DIR)

SRC_FILES:=$(foreach src,$(SRC_DIR),$(wildcard $(src)/*.c))
INC_FILES:=$(foreach inc,$(INC_DIR),$(wildcard $(inc)/*.h))
OBJ_FILES := $(patsubst %.c,$(OBJ_DIR)/%.o,$(notdir $(SRC_FILES)))


vpath %.c $(SRC_DIR)

$(OBJ_DIR)/%.o: %.c $(INC_FILES)
	$(CC) -c $<  -o $@ $(CFLAG)

build: $(OBJ_FILES)
	$(CC) -o ./bin/main.exe $^ 
all:
	./bin/main.exe
clean:
	rm -f ./obj/*.o ./bin/*.exe
print-%:
	@echo $($(subst print-,,$@))