#Used compiler
CC = g++

SRCDIR := src
OBJDIR := build

MAIN = $(addprefix $(SRCDIR)/, main.cpp )
SOURCES = $(addprefix $(SRCDIR)/, glad.c shader.cpp)

#Path to aditional files needed to compile
INCLUDE_PATHS = -Iinclude

#Path to libraries needed to compile
LIBRARY_PATHS = -Llibs

#Aditional compile options
COMPILER_FLAGS =

#Specifies which libraries we're linking
LINKER_FLAGS = -lglfw3 -lOpenGL32 

#Executable name
EXE_NAME = bin\demo

#This is the target that compiles our executable
all : main 

main: $(OBJECTS)
	$(CC) $(MAIN) $(SOURCES) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(EXE_NAME)