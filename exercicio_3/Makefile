CXX = g++
CXXFLAGS = -O3 -march=native -mtune=native -std=c++17 -Wall


SRC = $(wildcard *.cpp) $(wildcard src/*.cpp)
OUT = mst_solver
OUT_DIR = output

all: release

release:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

debug:
	$(CXX) -g -O0 -std=c++17 $(SRC) -o $(OUT)

clean:
	rm -f $(OUT) 
	rm -f $(OUT_DIR)/resultados.txt

# Roda apenas um arquivo fixo para testes rápidos
run: release
	./$(OUT) < input/dij10.txt

# Roda todas as instâncias .txt da pasta input e salva no arquivo final
run_all: release
	@mkdir -p $(OUT_DIR)
	@echo "Preparando execucao em lote..."
	@> $(OUT_DIR)/resultados.txt
	@for file in input/*.txt; do \
		if [ -f "$$file" ]; then \
			echo "Processando instancia: $$file"; \
			echo "-------------------------------" >> $(OUT_DIR)/resultados.txt; \
			echo "Instancia: $$file" >> $(OUT_DIR)/resultados.txt; \
			./$(OUT) < $$file >> $(OUT_DIR)/resultados.txt; \
			echo "" >> $(OUT_DIR)/resultados.txt; \
		fi \
	done
	@echo "\nConcluido! Todos os resultados foram salvos em $(OUT_DIR)/resultados.txt"