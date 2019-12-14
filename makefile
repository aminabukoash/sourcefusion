$(shell mkdir -p bin)
$(shell mkdir -p build)
CC=g++
CFLAGS=-std=c++17
INCLUDES=
ifeq ($(OS),Windows_NT)
       INCLUDES=-I"inc" -I"C:\cygwin64\usr\include"
else
       UNAME_S := $(shell uname -s)
       ifeq ($(UNAME_S),Darwin)
       		INCLUDES=-I"inc" -I/usr/local/Cellar/gsl/2.6/include
       endif
endif


LFLAGS=
ifeq ($(OS),Windows_NT)
       LFLAGS=-LC:\cygwin64\lib
else
       UNAME_S := $(shell uname -s)
       ifeq ($(UNAME_S),Darwin)
       		LFLAGS=-L/usr/local/Cellar/gsl/2.6/lib
       endif
endif

LIBS=-lgsl -lgslcblas -lm
TARGET=FusedOutput

default :$(TARGET)

$(TARGET): sensor_fusion.o sensor_fusion_common.o fusion_algorithm.o sensor_fusion_implementation.o
	$(CC) $(CFLAGS) $(LFLAGS) -o bin/$(TARGET) build/sensor_fusion.o build/sensor_fusion_common.o build/fusion_algorithm.o build/sensor_fusion_implementation.o $(LIBS)

sensor_fusion.o :src/sensor_fusion.cpp
	$(CC) -c $(CFLAGS) $(INCLUDES) src/sensor_fusion.cpp -o build/sensor_fusion.o

sensor_fusion_common.o : src/sensor_fusion_common.cpp
	$(CC) -c $(CFLAGS) $(INCLUDES) src/sensor_fusion_common.cpp -o build/sensor_fusion_common.o

fusion_algorithm.o : src/fusion_algorithm.cpp
	$(CC) -c $(CFLAGS) $(INCLUDES) src/fusion_algorithm.cpp -o build/fusion_algorithm.o

sensor_fusion_implementation.o : src/sensor_fusion_implementation.cpp
	$(CC) -c $(CFLAGS) $(INCLUDES) src/sensor_fusion_implementation.cpp -o build/sensor_fusion_implementation.o


#CLEAN COMMANDS
clean:
	rm -f bin/* build/*