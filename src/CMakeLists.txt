cmake_minimum_required(VERSION 3.6)
enable_language(CXX)

set(sources 
    MarkdownParser.cpp
)

foreach(source ${sources})
    message(${source})
endforeach()


add_library(
    md2h_src
    STATIC
    ${sources}    
)
