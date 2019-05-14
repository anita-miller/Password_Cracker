CC     = gcc
CFLAGS = -Wall
EXE    = crack
OBJ    = crack.o sha256.o

# Default Target, so "$ make" or "$ make all" will do this
all: $(EXE)

# Create the executable
$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ)

# Other Dependencies
sha256.o: sha256.h sha256.c
	$(CC) $(CFLAGS) -c ha256.c

# "clean" and "all" don't actually create files called "clean" and "all"
# and are thus "Phony Targets"
.PHONY: clean all

# Run "$ make clean" to remove the object and executable files
clean:
	rm -f $(OBJ) $(EXE)
