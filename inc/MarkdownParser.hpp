#pragma once

#include "Structures.hpp"
#include "Constants.hpp"

namespace m2h
{
class MarkdownParser{
public:
    void set(String markdown_source){
        this->m_markdown = markdown_source;
    }
    void parse();
    String serialize() const{
        return JsonValue{this->m_ast}.serialize();
    }
    JsonObj getMdAst() const { return this->m_ast; } 
private:
    String m_markdown;
    JsonObj m_ast;

    bool judgeLineFeature(String& ObjType, String sentence, String& contentSentence) const;
    JsonObj createNode(String objType, JsonValue value) const;
    JsonObj createContext(String context, String objType = ObjType::Text, String textStyle = TextStyle::Plane) const;
    JsonArray readContent(String content) const;
    // JsonArray parsePair(String::const_iterator begin, String::const_iterator end) const;
};


}
