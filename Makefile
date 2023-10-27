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

all:q1 q2    
q1:q1.o 
  gcc -std=c11 -O2 -Wall q1.o -o q1 

q1.o:q1.c
  gcc -c q1.c -o q1.o

q2:q2.o 
  gcc -std=c11 -O2 -Wall q2.o -o q2 

q2.o:q2.c
  gcc -c q2.c -o q2.o
