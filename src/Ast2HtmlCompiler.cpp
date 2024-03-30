#include "../inc/Constants.hpp"
#include "../inc/Ast2HtmlCompiler.hpp"
#include "../inc/less20functions.hpp"

namespace m2h
{
    void Ast2HtmlCompiler::compile(){
        std::ostringstream oss;
        auto children = this->m_htmlAst[KeyType::Children].get<JsonArray>();
        for(auto child : children){
            this->readAst(oss, child);   
        }
        
        this->m_html = oss.str();
    }

    void Ast2HtmlCompiler::readAst(std::ostringstream& oss, JsonValue value){
        auto obj = value.get<JsonObj>();
        #if __cplusplus > 201703L
        if(obj.contains(KeyType::Children)){
        #else
        if(contains(obj, KeyType::Children)){
        #endif
            // std::cout << obj[KeyType::Tag].get<String>() << std::endl;
            oss << "<";
            oss << obj[KeyType::Tag].get<String>();
            oss << ">";
            auto children = obj[KeyType::Children].get<JsonArray>();
            // std::cout << std::boolalpha << obj[KeyType::Children].is<JsonArray>() << std::endl;
            for(auto child : children){
                this->readAst(oss, child);
            }
            oss << "</";
            oss << obj[KeyType::Tag].get<String>();
            oss << ">\n";
        }
        else if(obj[KeyType::Tag].get<String>() == HtmlTag::Br){
            oss << "<br>";
        }
        else{
            // std::cout << "こっちも来てるぜ！！！" << std::endl;
            String str = obj[KeyType::Value].get<String>();
            this->replaceSpecial(str);
            String tag = obj[KeyType::Tag].get<String>();
            if(tag != HtmlTag::None){
                oss << "<";
                oss << tag;
                oss << ">";
            }
            oss << str;
            if(tag != HtmlTag::None){
                oss << "</";
                oss << tag;
                oss << ">";
            }
        }
    }
    void Ast2HtmlCompiler::replaceSpecial(String& str){
        str = this->replaceAll(str, "&", "&amp;");
        str = this->replaceAll(str, "<", "&lt;");
        str = this->replaceAll(str, ">", "&gt;");
    }
    std::string Ast2HtmlCompiler::replaceAll(std::string str, const std::string& from, const std::string& to) {
        size_t start_pos = 0;
        while((start_pos = str.find(from, start_pos)) != std::string::npos) {
            str.replace(start_pos, from.length(), to);
            start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
        }
        return str;
}

}
