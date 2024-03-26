#include "../inc/Constants.hpp"
#include "../inc/AstConverter.hpp"

namespace m2h
{
    void AstConverter::convert(){
        this->m_htmlAst.emplace(KeyType::Type, ObjType::Root);
        this->m_htmlAst.emplace(KeyType::Tag, HtmlTag::Div);
        JsonArray rootChildren;

        auto mdAstChildren = this->m_mdAst["children"].get<JsonArray>();
        for(auto iter = mdAstChildren.cbegin(); iter != mdAstChildren.cend(); ++iter){
            // JsonObj childObj;
            auto elem = (*iter).get<JsonObj>();
            // childObj.emplace(KeyType::Type, ObjType::Element);
            // childObj.emplace(KeyType::Tag, this->typeConvert(elem[KeyType::Type].get<String>()));
            // childObj.emplace(KeyType::Children, elem[KeyType::Children].get<JsonArray>());
            JsonObj obj = this->convertElements(elem);
            rootChildren.push_back(JsonValue{obj});
        }

        this->m_htmlAst.emplace(KeyType::Children, rootChildren);
    }
    String AstConverter::typeConvert(String type){
        String result;
        if(type == ObjType::Heading){
            result = HtmlTag::H1;
        }
        else if(type == ObjType::SubHeading){
            result = HtmlTag::H2;
        }
        else if(type == ObjType::SubSubHeading){
            result = HtmlTag::H3;
        }
        else if(type == ObjType::Paragraph){
            result = HtmlTag::P;
        }
        else if(type == ObjType::InlineCode){
            result = HtmlTag::Code;
        }
        else if(type == ObjType::Code){
            result = HtmlTag::Code;
        }
        else{
            result = "";
        }
        return result;
    }
    JsonObj AstConverter::convertElements(JsonObj& _obj){
        JsonObj obj;
        JsonArray children;
        obj[KeyType::Type] = JsonValue{ObjType::Element};
        obj[KeyType::Tag] = JsonValue{this->typeConvert(_obj[KeyType::Type].get<String>())};
        if(_obj.contains(KeyType::Children)){
            auto array = _obj[KeyType::Children].get<JsonArray>();
            for(auto iter = array.begin(); iter != array.end(); ++iter){
                children.push_back(
                    JsonValue{this->convertElements((*iter).get<JsonObj>())}
                );
            }
        }
        else{
            JsonObj childObj;
            if(_obj[KeyType::Type].get<String>() == ObjType::InlineCode){
                childObj.emplace(KeyType::Type, ObjType::Element);
                childObj.emplace(KeyType::Tag, HtmlTag::Code);
                childObj.emplace(KeyType::Style, TextStyle::Plane);
                childObj.emplace(KeyType::Value, _obj[KeyType::Value].get<String>());
            }
            else{
                childObj.emplace(KeyType::Type, ObjType::Element);
                if(_obj[KeyType::Style].get<String>() == TextStyle::Plane){
                    childObj.emplace(KeyType::Tag, HtmlTag::None);
                }
                else if(_obj[KeyType::Style].get<String>() == TextStyle::Bold){
                    childObj.emplace(KeyType::Tag, HtmlTag::B);
                }
                childObj.emplace(KeyType::Style, TextStyle::Plane);
                childObj.emplace(KeyType::Value, _obj[KeyType::Value].get<String>());

            }
            return childObj;
        }
        // _obj[KeyType::Type] = JsonValue{this->typeConvert(_obj[KeyType::Type].get<String>())};
        obj.emplace(KeyType::Children, children);
        if(_obj[KeyType::Type].get<String>() == ObjType::Code){
            JsonObj parentObj;
            JsonArray parentArray;
            parentArray.push_back(JsonValue{obj});
            parentObj.emplace(KeyType::Type, ObjType::Element);
            parentObj.emplace(KeyType::Tag, HtmlTag::Pre);
            parentObj.emplace(KeyType::Children, parentArray);
            return parentObj;
        }
        else{
            return obj;
        }
    }
}
