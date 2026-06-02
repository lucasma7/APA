CXX = g++
CXXFLAGS = -O3 -march=native -mtune=native -std=c++17 -Wall

SRC = $(wildcard *.cpp) $(wildcard src/*.cpp)
OUT = mochila_solver
OUT_DIR = output

all: release

release:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

debug:
	$(CXX) -g -O0 -std=c++17 $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)
	rm -rf $(OUT_DIR)

run_all: release
	@mkdir -p $(OUT_DIR)
	@echo "Criando relatorio em $(OUT_DIR)/resultados_mochila.txt..."
	@echo "Problema: Mochila Inteira (0-1) - Programacao Dinamica" > $(OUT_DIR)/resultados_mochila.txt
	@echo "Instância - solucao (tempo)" >> $(OUT_DIR)/resultados_mochila.txt
	@for file in input/*.txt; do \
		if [ -f "$$file" ]; then \
			nome=$$(basename "$$file" .txt); \
			resultado=$$(./$(OUT) < "$$file"); \
			echo "$$nome - $$resultado" >> $(OUT_DIR)/resultados_mochila.txt; \
			echo "Processado: $$nome"; \
		fi \
	done