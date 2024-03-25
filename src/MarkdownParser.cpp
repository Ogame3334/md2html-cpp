#include "../inc/MarkdownParser.hpp"
#include <sstream>

namespace m2h
{
    void MarkdownParser::parse(){
        this->m_ast.emplace(std::make_pair("type", ObjType::Root));
        JsonArray rootChildren;
        std::stringstream ss(this->m_markdown);
        String line;
        std::vector<String> lines;

        JsonObj childObj;
        JsonArray childChildren;
        while(std::getline(ss, line, '\n')){
            lines.push_back(line);
        }
        for(auto lines_iter = lines.cbegin(); lines_iter != lines.cend(); ++lines_iter){
            line = *lines_iter;
            String buf = "";
            auto iter = line.cbegin();
            String objType = "";
            if(String content = ""; this->judgeLineFeature(objType, line, content)){
                if(childChildren.empty()){
                    auto temp = this->readContent(content);
                    childChildren.insert(childChildren.end(), temp.begin(), temp.end());
                }
                else{
                    --lines_iter;
                    objType = ObjType::Paragraph;
                }
            }
            else{
                auto temp = this->readContent(line);
                childChildren.insert(childChildren.end(), temp.begin(), temp.end());
                if(not (lines_iter == lines.cend() - 1))
                    continue;
            }
            childObj.emplace(KeyType::Type, objType);
            childObj.emplace(KeyType::Children, childChildren);
            rootChildren.push_back(JsonValue{childObj});
            childObj.clear();
            childChildren.clear();
        }
        this->m_ast.emplace(std::make_pair("children", rootChildren));
    }
    JsonArray MarkdownParser::readContent(String content) const{
        bool shouldLn = false;
        JsonArray children;
        String buf = "";
        if(content.ends_with("  ")){
            shouldLn = true;
            content.erase(content.size() - 2, 2);
        }
        for(auto iter = content.cbegin(); iter != content.cend(); ++iter){
            if((*iter) == '`'){
                ++iter;
                if(buf != ""){
                    children.push_back(JsonValue{
                        this->createContext(buf)
                    });
                    buf = "";
                }
                for(;iter != content.cend(); ++iter){
                    if((*iter) == '`'){
                        ++iter;
                        children.push_back(JsonValue{
                            this->createContext(buf, ObjType::InlineCode)
                        });
                        buf = "";
                        break;
                    }
                    buf += *iter;
                }
            }
            if((*iter) == '*' and (*(iter + 1) == '*')){
                ++iter;
                ++iter;
                if(buf != ""){
                    children.push_back(JsonValue{
                        this->createContext(buf)
                    });
                    buf = "";
                }
                for(;iter != content.cend(); ++iter){
                    if((*iter) == '*' and (*(iter + 1) == '*')){
                        ++iter;
                        ++iter;
                        children.push_back(JsonValue{
                            this->createContext(buf, ObjType::Text, TextStyle::Bold)
                        });
                        buf = "";
                        break;
                    }
                    buf += *iter;
                }
            }
            buf += *iter;
        }
        if(buf != ""){
            children.push_back(JsonValue{
                this->createContext(buf)
            });
        }
        if(shouldLn){
            children.push_back(JsonValue{
                this->createContext("", ObjType::Ln)
            });
        }
        return children;
    }
    bool MarkdownParser::judgeLineFeature(String& objType, String sentence, String& contentSentence) const{
        bool flag = false;
        if(String prefix = "# "; sentence.starts_with(prefix)){
            objType = ObjType::Heading;
            flag = true;
            contentSentence = sentence;
            contentSentence.erase(0, prefix.size());
        }
        else if(String prefix = "## "; sentence.starts_with(prefix)){
            objType = ObjType::SubHeading;
            flag = true;
            contentSentence = sentence;
            contentSentence.erase(0, prefix.size());
        }
        else if(String prefix = "### "; sentence.starts_with(prefix)){
            objType = ObjType::SubSubHeading;
            flag = true;
            contentSentence = sentence;
            contentSentence.erase(0, prefix.size());
        }
        else{
            objType = ObjType::Paragraph;
        }
        return flag;
    }
    JsonObj MarkdownParser::createNode(String objType, JsonValue value) const {
        JsonObj obj;
        JsonArray children;
        children.push_back(value);
        obj.emplace(KeyType::Type, objType);
        obj.emplace(KeyType::Children, children);
        return obj;
    }
    JsonObj MarkdownParser::createContext(String context, String objType, String textStyle) const {
        JsonObj obj;
        obj.emplace(KeyType::Type, objType);
        obj.emplace(KeyType::Value, context);
        obj.emplace(KeyType::Style, textStyle);
        return obj;
    }
    // JsonArray MarkdownParser::parsePair(
    //     String::const_iterator iter, 
    //     String::const_iterator end, 
    //     String objType
    // ) const{
    //     String buf;
    //     JsonArray children;
    //     if((*iter) == '*' and (*(iter + 1) == '*')){
    //             ++iter;
    //             ++iter;
    //             if(buf != ""){
    //                 children.push_back(JsonValue{
    //                     this->createContext(buf)
    //                 });
    //                 buf = "";
    //             }
    //             for(;iter != end; ++iter){
    //                 if((*iter) == '*' and (*(iter + 1) == '*')){
    //                     ++iter;
    //                     ++iter;
    //                     children.push_back(JsonValue{
    //                         this->createContext(buf, ObjType::Text, TextStyle::Bold)
    //                     });
    //                     buf = "";
    //                     break;
    //                 }
    //                 buf += *iter;
    //             }
    //         }
    // }
}