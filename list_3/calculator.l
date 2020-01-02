%{
#include <iostream>
#include <cstdlib>
#include "calculator.tab.h"

extern "C" int yylex();
%}

%x COMMENT

%%
^#  BEGIN(COMMENT);
\\\n    ;
[ \t]+  ;
<COMMENT>
{
    .|\\\n  ;
    \n  BEGIN(INITIAL);
}

\+  return PLUS;
\-  return MINUS;
\*  return MULT;
\/  return DIV;
\%  return MOD;
\^  return POW;
[0-9]+  { yylval = atoi(yytext);
          return NUM; }
\(  return LBRACKET;
\)  return RBRACKET;
\n  return NEWLINE;
.   ;
%%
