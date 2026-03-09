CC = gcc
TARGET = mt1
#The * is to give a list of all possible files in the directory.
CFILES = $(wildcard *.c)
# % pattern matches all of the files that has a .c.
# patsubst transforms all of the .c values into whatever.o and turns it into an executable that has all of the c files within the directory.
# $(patsubst PATTERN,REPLACEMENT,TEXT)
OBJS = $(patsubst %.c, %.o, $(CFILES))

#-g supplies the debugging information, -Wall gets all of the warnings and -Werror turns warnings into errors. -pednatic-errors take all of the Strict ISO C standards and turns them into errors.
CFLAGS = -g -Wall  -pedantic-errors

LDLIBS =
LDFLAGS =

.PHONY: all clean
all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@ $(LDLIBS)
%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
clean:
	rm -f $(OBJS) $(TARGET) $(TARGET).exe
