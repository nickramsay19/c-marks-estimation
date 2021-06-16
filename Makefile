# cpp-template/Makefile
# All source files should have compilation rules.
# All intermediary builds should be directed to the build directory.
# The final resulting executable should reside in the root directory.

# variables
COMPILER = gcc
FLAGS = -l argp

all: dist/main 

# Produce the final executable
# Include all required object files
dist/main: dist build/main.o build/Assessment.o build/Subject.o build/Estimation.o build/SubjectsFile.o build/Interface.o build/ArgumentParser.o
	 ${COMPILER} ${FLAGS} -o dist/main build/main.o build/Assessment.o build/Subject.o build/Estimation.o build/SubjectsFile.o build/Interface.o build/ArgumentParser.o

dist:
	mkdir dist

# Build an object file for main
build/main.o: src/main.c
	 $(COMPILER) $(FLAGS) -o build/main.o -c src/main.c

# Add object file compilation rules here
build/Assessment.o: src/Assessment.c
	$(COMPILER) $(FLAGS) -o build/Assessment.o -c src/Assessment.c

build/Subject.o: src/Subject.c
	$(COMPILER) $(FLAGS) -o build/Subject.o -c src/Subject.c

build/Estimation.o: src/Estimation.c
	$(COMPILER) $(FLAGS) -o build/Estimation.o -c src/Estimation.c

build/SubjectsFile.o: src/SubjectsFile.c
	$(COMPILER) $(FLAGS) -o build/SubjectsFile.o -c src/SubjectsFile.c

build/Interface.o: src/Interface.c
	$(COMPILER) $(FLAGS) -o build/Interface.o -c src/Interface.c

build/ArgumentParser.o: src/ArgumentParser.c
	$(COMPILER) -o build/ArgumentParser.o -c src/ArgumentParser.c

# add all build files including ./main to the clean command
clean:
	 rm dist/main build/main.o build/Assessment.o build/Subject.o build/Estimation.o build/SubjectsFile.o build/Interface.o ArgumentParser.o
