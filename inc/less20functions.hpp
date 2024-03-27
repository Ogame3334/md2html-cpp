#pragma once

#include "Structures.hpp"

namespace m2h
{
    #if __cplusplus <= 201703L
    bool contains(JsonObj obj, String key);
    #endif
    
    #if __cplusplus <= 201703L
    bool starts_with(const String& str, String prefix);
    bool ends_with(const String& str, String prefix);
    #endif
}
