# Executable names:
EXE = roadmap
TEST = test

# Add all object files needed for compiling:
EXE_OBJ = main.o
OBJS = main.o Graph.o AStarSearch.o BFS.o 

# Use the cs225 makefile template:
include cs225/make/cs225.mk