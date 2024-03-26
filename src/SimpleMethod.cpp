#include "../inc/SimpleMethod.hpp"
#include "../inc/MarkdownParser.hpp"
#include "../inc/AstConverter.hpp"
#include "../inc/Ast2HtmlCompiler.hpp"

namespace m2h
{
    String md2html(const String& str){
        MarkdownParser parser;
        AstConverter converter;
        Ast2HtmlCompiler compiler;

        parser.set(str);
        parser.parse();
        converter.set(parser.getMdAst());
        converter.convert();
        compiler.set(converter.getHtmlAst());
        compiler.compile();
        return compiler.getHtml();
    }
}
