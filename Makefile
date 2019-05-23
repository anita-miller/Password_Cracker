CC     = gcc
CFLAGS = -Wall
EXE    = crack
OBJ    = main.o crack.o sha256.o crack_one_argument_helper_functions.o crack_zero_argument_helper_functions.o

# Default Target, so "$ make" or "$ make all" will do this
all: $(EXE)

# Create the executable
$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ)

# Other Dependencies
sha256.o: helper_functions/sha256.h helper_functions/sha256.c
	$(CC) $(CFLAGS) -c helper_functions/sha256.c

crack.o: crack.h crack.c
	$(CC) $(CFLAGS) -c crack.c

crack_one_argument_helper_functions.o: helper_functions/crack_one_argument_helper_functions.h  helper_functions/crack_one_argument_helper_functions.c
	$(CC) $(CFLAGS) -c helper_functions/crack_one_argument_helper_functions.c

crack_zero_argument_helper_functions.o: helper_functions/crack_zero_argument_helper_functions.h  helper_functions/crack_zero_argument_helper_functions.c
	$(CC) $(CFLAGS) -c helper_functions/crack_zero_argument_helper_functions.c
	
# "clean" and "all" don't actually create files called "clean" and "all"
# and are thus "Phony Targets"
.PHONY: clean all

# Run "$ make clean" to remove the object and executable files
clean:
	rm -f $(OBJ) $(EXE)
