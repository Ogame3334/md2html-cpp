#pragma once

#include "Structures.hpp"

namespace m2h
{
    namespace ObjType
    {
        static const String Root = "root";
        static const String Text = "text";
        static const String Ln = "ln";
        static const String Paragraph = "paragraph";
        static const String Heading = "heading";
        static const String SubHeading = "subheading";
        static const String SubSubHeading = "subsubheading";
        static const String InlineCode = "inlinecode";
        static const String Code = "code";
        static const String Element = "element";
    }
    namespace KeyType
    {
        static const String Type = "type";
        static const String Children = "children";
        static const String Value = "value";
        static const String Style = "style";
        static const String CodeLang = "codelang";
        static const String Tag = "tag";
    }
    namespace TextStyle
    {
        static const String Plane = "plane";
        static const String Bold = "bold";
    }
    namespace HtmlTag
    {
        static const String None = "none";
        static const String Div = "div";
        static const String P = "p";
        static const String H1 = "h1";
        static const String H2 = "h2";
        static const String H3 = "h3";
        static const String Code = "code";
        static const String Pre = "pre";
        static const String Br = "br";
        static const String B = "b";
    }
}
