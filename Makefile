CC = g++
CFLAGS = -Wall -Werror -std=c++11

TARGET = loadbalancer.exe

OBJS = main.o WebServer.o LoadBalancer.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp LoadBalancer.h WebServer.h Request.h
	$(CC) $(CFLAGS) -c main.cpp

WebServer.o: WebServer.cpp WebServer.h Request.h
	$(CC) $(CFLAGS) -c WebServer.cpp

LoadBalancer.o: LoadBalancer.cpp LoadBalancer.h WebServer.h Request.h
	$(CC) $(CFLAGS) -c LoadBalancer.cpp

clean:
	del /Q *.o $(TARGET)