#pragma once

#include "../thirdparty-lib/picojson.hpp"
#include <string>

namespace m2h
{
    using JsonValue = picojson::value;
    using JsonObj = picojson::object;
    using JsonArray = picojson::array;

#ifdef MD2H_USING_UTF16
    using Char = char16_t;
#else
    using Char = char;
#endif

    using String = std::basic_string<Char>;
}
