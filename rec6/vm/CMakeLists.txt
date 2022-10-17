project(rec6)

cmake_minimum_required(VERSION 3.18)
set(CMAKE_CXX_STANDARD 17)

include_directories(. src)
add_compile_options(-Wno-attributes)

# generate the grammar cpp file
add_custom_command(
        OUTPUT ${CMAKE_CURRENT_LIST_DIR}/MITScript.cpp
        COMMAND java -Xmx500M -cp "bin/antlr-4.7.2-complete.jar:${CLASSPATH}" org.antlr.v4.Tool -Dlanguage=Cpp MITScript.g
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
        DEPENDS MITScript.g
)

# Grammar library
add_library(MITScriptGrammar MITScript.cpp)
target_link_libraries(MITScriptGrammar ${CMAKE_CURRENT_LIST_DIR}/lib/libantlr4-runtime.a)
target_include_directories(MITScriptGrammar PUBLIC include)

##################################################

add_executable(main main.cpp
        utils.cpp

        src/AST.cpp
        src/Visitor.cpp
        src/Parser.cpp
        src/CFG.cpp
        src/CFGBuilder.cpp
        src/compile.cpp
        )

target_link_libraries(main MITScriptGrammar)


