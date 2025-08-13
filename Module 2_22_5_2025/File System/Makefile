CC:=gcc
.Phony: clean build

CFLAGS := -I.

%.o: %.c filesat.h
	$(CC) $(CFLAGS) -c $<  -o $@ 

build: main.o filesat.o
	$(CC) -o filesat.exe $^ 
	

clean:
	rm -f *.o *.exe
