# Check for OS Type
UNAME_S := $(shell uname -s)

# Linux
ifeq ($(UNAME_S), Linux)
CC=g++
LIBS= -lglut -lGLEW -lGL -lassimp -lSDL2 `Magick++-config --cppflags --cxxflags --ldflags --libs`
# Mac
else
	CC=clang++
  LIBS=  -framework OpenGL -framework GLUT -framework Cocoa -lGLEW -stdlib=libc++ `Magick++-config --cppflags --cxxflags --ldflags --libs`
endif

# Paths, use this to set Include directories, or library directories; uncomment in all: if used
#PATHI=-I/usr/local/include/ 
#PATHL=-L/usr/local/lib/

#Compiler Flags
CXXFLAGS=-g -Wall -std=c++0x

all: ../build/Assignment6

../build/Assignment6: ../src/main.cpp camera.o engine.o graphics.o object.o shader.o window.o texture.o
	$(CC) $(CXXFLAGS) ../src/main.cpp camera.o engine.o graphics.o object.o shader.o window.o texture.o -o ../build/Assignment6 $(LIBS)

camera.o: ../src/camera.cpp ../src/camera.h
	$(CC) $(CXXFLAGS) -c ../src/camera.cpp ../src/camera.h $(LIBS)

engine.o: ../src/engine.cpp ../src/engine.h
	$(CC) $(CXXFLAGS) -c ../src/engine.cpp ../src/engine.h $(LIBS)

graphics.o: ../src/graphics.cpp ../src/graphics.h
	$(CC) $(CXXFLAGS) -c ../src/graphics.cpp ../src/graphics.h $(LIBS)

object.o: ../src/object.cpp ../src/object.h
	$(CC) $(CXXFLAGS) -c ../src/object.cpp ../src/object.h $(LIBS)

shader.o: ../src/shader.cpp ../src/shader.h
	$(CC) $(CXXFLAGS) -c ../src/shader.cpp ../src/shader.h $(LIBS)

window.o: ../src/window.cpp ../src/window.h
	$(CC) $(CXXFLAGS) -c ../src/window.cpp ../src/window.h $(LIBS)

texture.o: ../src/texture.cpp ../src/texture.h
	$(CC) $(CXXFLAGS) -c ../src/texture.cpp ../src/texture.h $(LIBS)

clean:
	-@if rm *.o Assignment6 2>/dev/null || true; then echo "Main Removed"; else echo "No Main"; fi
