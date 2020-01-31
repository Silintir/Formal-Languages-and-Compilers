%{
    bool doc_mode = false;
%}

%x STRING
%x MULTI_LINE
%x ONE_LINE
%x MULTI_LINE_DOC
%x ONE_LINE_DOC

%%

\"          {ECHO; BEGIN(STRING);}
<STRING>{
    \"      {ECHO; BEGIN(INITIAL);}        
    .       ECHO;
}

\/\/\/|\/\/!        {   
                        if (!doc_mode) {
                            ECHO;
                        }
                        BEGIN(ONE_LINE_DOC);
                    }
<ONE_LINE_DOC>{
    .       {
                if (!doc_mode) {
                    ECHO;
                } else {
                    putchar(' ');
                }
            }
    \n      {ECHO; BEGIN(INITIAL);}
}

\/(\\\n)*\/                {BEGIN(ONE_LINE);}
<ONE_LINE>{
    \\\n            ;
    .               ;
    \n              {ECHO; BEGIN(INITIAL);}
}

\/\*\*|\/\*!        {
                        if (!doc_mode) {
                            ECHO;
                        }
                        BEGIN(MULTI_LINE_DOC);
                    }

<MULTI_LINE_DOC>{
    .       {
                if (!doc_mode) {
                    ECHO;
                } else {
                    putchar(' ');
                }
            }
    \*\/    {
                if (!doc_mode) {
                    ECHO;
                }
                BEGIN(INITIAL);
            }
}

\/\*            {putchar(' '); BEGIN(MULTI_LINE);}
<MULTI_LINE>{
    .       ;
    \*\/    {
                BEGIN(INITIAL);
            }
}

%%

int yywrap(void) {
    return 1;
}

int main(int argc, char** argv) {
    if (argc > 1) {
        doc_mode = true;
    }
    yylex();
}
