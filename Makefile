# Três ações:
# all => somente compila.
# exec => compila E executa.
# clean => remove o executável.

COMPILER = g++
FLAGS = -std=c++17 -Wall

SRC = src
DIST = dist
SOURCES = $(wildcard $(SRC)/*.cpp)

# Detecta o sistema operacional
ifeq ($(OS),Windows_NT)
    EXE = $(DIST)/main.exe
    MKDIR = mkdir
    RMDIR = rmdir /s /q
    RM = del /s /q
    EXEC_CMD = $(EXE)
    CHECK_DIR = if not exist "$(DIST)" $(MKDIR) "$(DIST)"
    CLEAN_CMD = if exist "$(DIST)" $(RMDIR) "$(DIST)"
else
    EXE = $(DIST)/main
    MKDIR = mkdir -p
    RMDIR = rm -rf
    RM = rm -f
    EXEC_CMD = ./$(EXE)
    CHECK_DIR = if [ ! -d "$(DIST)" ]; then $(MKDIR) "$(DIST)"; fi
    CLEAN_CMD = if [ -d "$(DIST)" ]; then $(RMDIR) "$(DIST)"; fi
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