INCLUDE = 
LIBS = -lpthread
LIBRARY = 
CFLAGS = -g -s -O2 -fpermissive
SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp, %.o, $(SRCS))

TARGET = main

%.o : %.cpp
	g++ -o $@ $< -c $(BASES) $(INCLUDE) $(LIBS) $(LIBRARY) $(CFLAGS)

$(TARGET): $(OBJS)
	g++ -o $@ $^ $(BASES) $(INCLUDE) $(LIBS) $(LIBRARY) $(CFLAGS)
clean:
	rm -rf *.o $(TARGET)
