cmake_minimum_required(VERSION 3.6)
enable_language(CXX)

set(sources 
    src/MarkdownParser.cpp
    src/AstConverter.cpp
    src/Ast2HtmlCompiler.cpp
    src/SimpleMethod.cpp
    src/less20functions.cpp
)

add_library(
    md2h
    STATIC
    ${sources}    
)
