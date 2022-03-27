#pragma once

#include <FlexLexer.h>
#include "parser.tab.hh"
#include <vector>

namespace yy
{
    enum lexem_type
    {
        COMMA = 1,
        LINE  = 2,
        NUMBER = 3
    };

    class Driver final
    {
        FlexLexer* lexer = new yyFlexLexer;

        public:

        std::vector <int> edges_info_;
        std::vector <std::pair <int, int>> data_;

        std::vector <std::string> errors;

        public:

        ~Driver () { delete lexer; }

        parser::token_type yylex(parser::semantic_type *yylval)
        {
            parser::token_type tt = static_cast<parser::token_type>(lexer->yylex());

            switch (tt)
            {
                case yy::parser::token_type::COMMA:
                    yylval->build <lexem_type>() = lexem_type::COMMA;
                    break;
                
                case yy::parser::token_type::LINE:
                    yylval->build <lexem_type>() = lexem_type::LINE;
                    break;

                case yy::parser::token_type::NUMBER:
                    yylval->build <int>() = std::stoi (lexer->YYText());
                    break;

                case yy::parser::token_type::LEXERR:
                    errors.push_back (std::string("unrecognized symbol: ") + lexer->YYText());
            }

            return tt;
        }

        void parse ()
        {
            parser parser(this);
            parser.parse ();

            if (errors.size())
                throw errors;
        }

        void push_data (int n1, int n2, int n3)
        {
            data_.emplace_back (n1, n2);
            edges_info_.push_back (n3);
        }
    };
}