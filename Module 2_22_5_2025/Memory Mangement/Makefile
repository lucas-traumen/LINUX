CC:=gcc
.Phony: clean all build

CFLAGS := -g -O0 -I.

%.o: %.c memory_lab.h
	$(CC) $(CFLAGS) -c $<  -o $@ 

build: main.o memory_lab.o
	$(CC) -o memory_lab.exe $^ 
gdb_stack:
	gdb --args ./memory_lab stack_overflow
gdb_leak:
	gdb --args ./memory_lab memory_leak
gdb_out:
	gdb --args ./memory_lab out_of_memory
clean:
	rm -f *.o *.exe
