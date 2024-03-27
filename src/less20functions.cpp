#include "../inc/less20functions.hpp"

namespace m2h
{
    #if __cplusplus <= 201703L
    bool contains(JsonObj obj, String key){
        return obj.find(key) != obj.end();
    }
    #endif
    
    #if __cplusplus <= 201703L
    bool starts_with(const String& str, String prefix){
        return str.rfind(prefix, 0) == 0;
    }
    bool ends_with(const String& str, String prefix){
        return str.size() >= prefix.size() && str.find(prefix, str.size() - prefix.size()) != std::string::npos;
    }
    #endif
}
