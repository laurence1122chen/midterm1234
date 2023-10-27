CC = gcc
CFLAG = -std=c11 -O2 -Wall
TARGET = q1
SRCS = q1.c
OBJS = q1.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAG) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

CC = gcc
CFLAG = -std=c11 -O2 -Wall
TARGET = q2
SRCS = q2.c
OBJS = q2.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAG) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
