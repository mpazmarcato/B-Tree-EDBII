# Três ações:
# all => somente compila.
# exec => compila E executa.
# clean => remove o executável.

COMPILER = g++
FLAGS = -std=c++17 -Wall -g

SRC = src
SOURCES = $(wildcard $(SRC)/*.cpp)

# Detecta o sistema operacional
ifeq ($(OS),Windows_NT)
    EXE = $(SRC)/main.exe
    MKDIR = mkdir
    RMDIR = rmdir /s /q
    RM = del /s /q
    EXEC_CMD = $(EXE)
    CHECK_DIR = if not exist "$(SRC)" $(MKDIR) "$(SRC)"
    CLEAN_CMD = if exist "$(EXE)" $(RM) "$(EXE)"
else
    EXE = $(SRC)/main
    MKDIR = mkdir -p
    RMDIR = rm -rf
    RM = rm -f
    EXEC_CMD = ./$(EXE)
    CHECK_DIR = if [ ! -d "$(SRC)" ]; then $(MKDIR) "$(SRC)"; fi
    CLEAN_CMD = if [ -f "$(EXE)" ]; then $(RM) "$(EXE)"; fi
endif

all: $(EXE)

$(EXE): $(SOURCES)
	@$(CHECK_DIR)
	$(COMPILER) $(FLAGS) -o $@ $^

exec: $(EXE)
	@$(EXEC_CMD)

clean:
	@$(CLEAN_CMD)

.PHONY: all exec clean
