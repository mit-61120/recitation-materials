CXX := g++ -std=c++20
FLAGS := -Wno-attributes

BUILD_DIR := bin

SRC := AST.cpp PrettyPrinter.cpp
# turn all .cpp files into bin/*.o files
OBJ := $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SRC))

# build bin/*.o files
$(BUILD_DIR)/%.o: %.cpp %.h
	@mkdir -p $(@D)
	$(CXX) $(FLAGS) $< -c -o $@
# $< = first dependency
# $@ = build name

main: main.cpp $(OBJ)
		$(CXX) $(FLAGS) $^ -o $@
# $^ = all dependencies

.PHONY: clean

clean:
		rm -rf main $(BUILD_DIR)
