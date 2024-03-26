#pragma once

#include <sstream>
#include "Structures.hpp"

namespace m2h
{
    class Ast2HtmlCompiler{
    public:
        void set(JsonObj obj){ this->m_htmlAst = obj; }
        void compile();
        String getHtml() const { return this->m_html; }
    private:
        JsonObj m_htmlAst;
        String m_html;

        void readAst(std::ostringstream& oss, JsonValue value);
        void replaceSpecial(String& str);
        std::string replaceAll(std::string str, const std::string& from, const std::string& to);
    };
}
