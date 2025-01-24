# Três ações:
# all => somente compila.
# exec => compila E executa.
# clean => remove o executável.

COMPILER = g++
FLAGS = -std=c++17 -Wall

SRC = src
DIST = dist
SOURCES = $(wildcard $(SRC)/*.cpp)
EXE = $(DIST)/main.exe

all: $(EXE)

$(EXE): $(SOURCES)
	@if not exist "$(DIST)" mkdir "$(DIST)"
	$(COMPILER) $(FLAGS) -o $@ $^

exec: $(EXE) 
	$(EXE) 

clean:
	@if exist "$(DIST)" del /s /q "$(DIST)\*" 

.PHONY: all exec clean
