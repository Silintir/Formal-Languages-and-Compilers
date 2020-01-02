%{
    int lines, words;
%}
%option yylineno
%%

^[ \t]+         {} 
[ \t]+          {printf(" ");}
([ \t]*\r?\n)+  {printf("\n"); lines++;}
    /*
^(?:[\t ]*(?:\r?\n|\r))+ {}
    */
[^ \t\n]+       {ECHO; words++;}

%%

int yywrap(void) {
    return 1;
}

int main(void) {

    extern int lines, words;
    extern int yylex();

    yylex();

    printf("\nlines - %d. words - %d", lines, words);
    return 0;
} 
