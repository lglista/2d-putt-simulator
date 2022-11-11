SRC_DIR := ./src
OBJ_DIR := ./obj
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
LDFLAGS := -lsfml-graphics -lsfml-window -lsfml-system -lpthread
CPPFLAGS := ...
CXXFLAGS := ...

simulate.exe: $(OBJ_FILES)
	g++ simulate.cpp $(LDFLAGS) -o $@ $^

editor.exe: $(OBJ_FILES)
	g++ editor.cpp $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ -c -nostartfiles -o $@ $<

clean_simulate:
	rm simulate.exe

clean_editor:
	rm editor.exe
