# $(wildcard *.cpp /xxx/xxx/*.cpp): get all .cpp files from the current directory and dir "/xxx/xxx/"
SRCS := $(wildcard *.cpp) $(wildcard src/*.cpp) $(wildcard src/**/*.cpp)
# $(patsubst %.cpp,%.o,$(SRCS)): substitute all ".cpp" file name strings to ".o" file name strings
OBJS := $(wildcard *.o)

TARGET := DEBUG
CC := g++
CFLAGS := -Wall -g

default: 
	g++ -c $(SRCS) -I SFML-2.5.1/include
	g++ $(OBJS) -o build/sfml-app -L SFML-2.5.1//lib -lsfml-graphics -lsfml-window -lsfml-system
	./build/sfml-app