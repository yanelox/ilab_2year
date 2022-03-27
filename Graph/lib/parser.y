%language "c++"

%skeleton "lalr1.cc"
%defines
%define api.value.type variant
%param {yy::Driver* driver}

%code requires
{
    namespace yy { class Driver; }
}

%code
{
    #include <tuple>
    #include "driver.h"
    namespace yy
    {
        parser::token_type yylex(parser::semantic_type* yylval, Driver* driver);
    }
}

%token
    COMMA   ","
    LINE    "--"
    <int> NUMBER
    LEXERR
;

%nterm
    EXPR
;

%start program

%%

program: EXPR program               {}
        | %empty                    {}

;

EXPR: NUMBER LINE NUMBER COMMA NUMBER { driver->push_data ($1, $3, $5); }

%%

namespace yy
{
    parser::token_type yylex(parser::semantic_type* yylval, Driver* driver)
    {
        return driver->yylex(yylval);
    }

    void parser::error(const std::string& err) {}
}