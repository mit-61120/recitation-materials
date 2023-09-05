CXX := g++ -std=c++17
FLAGS := -Wno-attributes -Isrc -Iinclude -I.

BUILD_DIR := build
SRC_DIR := src
ANTLR_DEP := lexer
DEPS := MITScript.cpp utils.cpp lib/libantlr4-runtime.a

SRC := AST.cpp Visitor.cpp Parser.cpp CFG.cpp CFGBuilder.cpp compile.cpp
# turn all .cpp files into bin/*.o files
OBJ := $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SRC))

# build bin/*.o files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(SRC_DIR)/%.h $(ANTLR_DEP)
	@mkdir -p $(@D)
	$(CXX) $(FLAGS) $< -c -o $@
# $< = first dependency
# $@ = build name

main: main.cpp $(OBJ) $(ANTLR_DEP) $(DEPS)
		$(CXX) $(FLAGS) main.cpp $(OBJ) $(DEPS) -o $@
# $^ = all dependencies

.PHONY: clean

clean:
		rm -rf main $(BUILD_DIR)

.PHONY: lexer

lexer: MITScript.g.intermediate
	@# Empty recipe

.INTERMEDIATE: MITScript.g.intermediate

MITScript.g.intermediate: MITScript.g
	java -Xmx500M -cp "bin/antlr-4.7.2-complete.jar:${CLASSPATH}" org.antlr.v4.Tool -Dlanguage=Cpp MITScript.g
