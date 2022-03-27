%option c++

%{
    #include "parser.tab.hh"
    int yyFlexLexer::yywrap ()
    {
        return 1;
    }
%}

WS          [ \t\v\n]+
DIGIT       [0-9]
DIGIT1      [1-9]
COMMA       [,]

%%

{WS}                // skip blanks and tabs
{COMMA}             { return yy::parser::token_type::COMMA; }
"--"                { return yy::parser::token_type::LINE; }
{DIGIT1}{DIGIT}*    { return yy::parser::token_type::NUMBER; }
.                   { return -yy::parser::token_type::LEXERR; }

%%
