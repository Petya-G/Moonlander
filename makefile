#OBJS specifies which files to compile as part of the project
OBJS = main.c geometry.c lander.c level.c sdlstuff.c text.c score.c debugmalloc.h

#CC specifies which compiler we're using
CC = gcc

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS =

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -Bstatic -lSDL2 -lSDL2_gfx -lm -Bdynamic

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = Moonlander

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)