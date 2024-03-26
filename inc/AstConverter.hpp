#pragma once

#include "../inc/Structures.hpp"

namespace m2h
{
    class AstConverter{
    public:
        JsonObj getMdAst() const { return this->m_mdAst; }
        JsonObj getHtmlAst() const { return this->m_htmlAst; }

        void set(JsonObj mdAst){
            this->m_mdAst = mdAst;
        }
        void convert();
    private:
        JsonObj m_mdAst;
        JsonObj m_htmlAst;

        String typeConvert(String type);
        JsonObj convertElements(JsonObj& obj);
    };
}
