CXX = g++
CXXFLAGS = -O3 -march=native -mtune=native -flto -funroll-loops -DNDEBUG -std=c++17 -Wall

SRC = src/main.cpp src/sort_algorithms.cpp
OUT = sort_algorithms
OUTPUT_PATH = output/*

all: release

release:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

debug:
	$(CXX) -g -O0 -std=c++17 $(SRC) -o $(OUT)

run:
	@if [ -z "$(FILE)" ]; then \
		echo "Uso: make run FILE=input/arquivo.in [ALG=merge|quick]"; \
	else \
		./$(OUT) $(FILE) $(ALG); \
	fi

run_all:
	@for file in input/*; do \
		echo "Executando $$file"; \
		./$(OUT) $$file; \
	done

clean:
	rm -f $(OUT) && rm -rf $(OUTPUT_PATH)