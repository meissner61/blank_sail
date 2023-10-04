output_dir := ./bin
executable := $(output_dir)/main.out
debug_executable := $(output_dir)/debug.out

.PHONY: all clean run debug

all: build

build: $(output_dir) $(executable)

$(output_dir):
	mkdir -p $(output_dir)

$(executable): src/*.cpp
	g++ -Wall -Wextra -std=c++17 -I/usr/include/SDL2 src/*.cpp -lSDL2 -o $(executable)

run: $(executable)
	./$(executable)

clean:
	rm -rf $(output_dir)

debug: $(output_dir) $(debug_executable)

$(debug_executable): src/*.cpp
	g++ -g -Wall -Wextra -std=c++17 -I/usr/include/SDL2 src/*.cpp -lSDL2 -o $(debug_executable)
