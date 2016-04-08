default: test

main: main.o shaders.o
	gcc main.o shaders.o -lGL -lglfw -lglut -lGLEW -o main

main.o: main.c shaders.h
	gcc -c -o main.o main.c

# What I did here:
# `ld -r -b binary -o OUT_FILE.o BINARY_SOURCE_FILES` converts binary data
# into a format that linked with a program. Run objdump -t OUT_FILE.o
# to see what symbols can be accessed.
shader_source_files := $(wildcard *.glsl)
shaders.o: $(shader_source_files)
	ld -r -b binary -o shaders.o $(shader_source_files)
	@echo shader.o contains: $(shader_source_files)

test: main
	./main
