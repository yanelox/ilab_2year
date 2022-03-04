%option c++

%{
%}

WS          [ \t\v\n]+
DIGIT       [0-9]
DIGIT1      [1-9]
COMMA       [,]

%%

{WS}                // skip blanks and tabs
{COMMA}             {return -3;}
"--"                {return -1;}
{DIGIT1}{DIGIT}*    {return atoi (yytext);}
.                   {return -4;}

%%
