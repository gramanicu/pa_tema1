# Copyright 2020 Grama Nicolae

.PHONY: gitignore clean memory beauty run
.SILENT: beauty clean memory gitignore

# Compiles the programs
build:
	@g++ gard.cpp -o gard
	@g++ bani.cpp -o bani
	@g++ bomboane.cpp -o bomboane

# Executes the first binary
run-p1: bani
	./bani

# Executes the second binary
run-p2: gard
	./gard

# Executes the third binary
run-p3: bomboane
	./bomboane

# Deletes the binary and object files
clean:
	rm -f gard bani bomboane README cpp.errors java.errors 322CA_GramaNicolae_Tema1.zip

# Automatic coding style, in my personal style
beauty:
	clang-format -i -style=file *.cpp

readme:
	cp Readme.md README

# Creates an archive of the project
pack: clean readme beauty
	zip -FSr 322CA_GramaNicolae_Tema1.zip README gard.cpp bani.cpp bomboane.cpp Makefile
	rm -f README
 
