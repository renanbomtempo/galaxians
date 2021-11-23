#Used compiler
CC = g++

# Directories
SRCDIR := src/
ENGINESRCDIR := $(SRCDIR)moxxi/
GAMESRCDIR := $(SRCDIR)space-invaders/
OBJDIR := build/

# Files list
ENGINESRCS = $(addprefix $(ENGINESRCDIR),  renderer.cpp transform.cpp component.cpp mesh.cpp gameobject.cpp object.cpp vec2.cpp vec3.cpp shader.cpp scene.cpp core.cpp)
GAMESRCS = $(addprefix $(GAMESRCDIR), main.cpp player.cpp )
GLAD = $(SRCDIR)glad/glad.c

#Path to aditional files needed to compile
INCLUDE_PATHS = -Iinclude

#Path to libraries needed to compile
LIBRARY_PATHS = -Llibs

#Aditional compile options
COMPILER_FLAGS =

#Specifies which libraries we're linking
LINKER_FLAGS = -lglfw3 -lOpenGL32 

#Executable name
EXE_NAME = bin/demo

all : main 

main: 
	$(CC) $(GLAD) $(ENGINESRCS) $(GAMESRCS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(EXE_NAME)
