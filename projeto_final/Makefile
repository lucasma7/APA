CXX = g++
CXXFLAGS = -O3 -Wall -std=c++17 -Isrc

SRC_DIR = src
OBJ_DIR = obj

# Encontra todos os .cpp e converte para .o
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

OUT = gcp_solver

all: $(OUT)

$(OUT): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(OUT)

# Regra para compilar e executar diretamente
run: all
	@mkdir -p results
	./$(OUT)