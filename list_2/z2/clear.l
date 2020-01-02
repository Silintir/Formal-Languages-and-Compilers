%{
    #include<vector>
    #include<string>
    #include<iostream>

    std::vector<std::string> comm;      // buffer for comment
    bool err = false;                   // error flag for comment
    bool dat = false;
%}


%x TAG
%x COM
%x DAT

%% 
    /* anything in tag */
\<      {ECHO; BEGIN(TAG);}
<TAG>{
    \".*\"   ECHO;
    .   ECHO;
    \n  ECHO;
    .>  {ECHO; BEGIN(INITIAL);}
}

    /* cdata */
\<!\[CDATA\[   {ECHO; BEGIN(DAT); dat = true;}
<DAT>{
    .        {ECHO;}
    \]\]\>      {ECHO; BEGIN(INITIAL); dat = false;}
}
    /* comment */
\<!--       {BEGIN(COM); comm.emplace_back(yytext);}
<COM>{
    --      {err = true; comm.emplace_back(yytext);}
    \<!--      {comm.emplace_back(yytext);}
    .|\n    {comm.emplace_back(yytext);}
    --\>    {
                comm.emplace_back(yytext);
                if (err || dat) {
                    for (auto s : comm) {
                        std::cout << s;
                    }
                    err = false;
                }
                comm.clear();
                BEGIN(INITIAL);
            }
}

%%

int yywrap(void) {
    return 1;
}

int main(void) {
    yylex(); 
    return 0;
}
