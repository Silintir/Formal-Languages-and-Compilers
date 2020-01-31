%{
    #include<stack>
    #include<string>
    #include<iostream>
    #include<cmath>

    std::stack<int> stack;
    bool err;
    
    void reset_stack() {
        while (!stack.empty()) {
            stack.pop();
        }
    }
%}

%x ERR

%%

-?(0[0-9]+)          {
                         std::cerr << "\033[1;31m[ERROR]: Unexpected symbol: \"" << yytext << "\"\033[m" << std::endl;
                         reset_stack();
                         BEGIN(ERR);
                     } 

-?(0|[1-9][0-9]*)         {stack.push(std::stoi(yytext));}            

\+                  {
                        if (stack.size() >= 2) {
                            int x = stack.top();
                            stack.pop();
                            int y = stack.top();
                            stack.pop();
                            stack.push(y + x);
                        } else {
                            err = true;
                            reset_stack();
                            BEGIN(INITIAL);
                        }
                    }
\-                  {
                        if (stack.size() >= 2) {
                            int x = stack.top();
                            stack.pop();
                            int y = stack.top();
                            stack.pop();
                            stack.push(y - x);
                        } else {
                            err = true;
                            reset_stack();
                        }   
                    }
\*                  {
                        if (stack.size() >= 2) {
                            int x = stack.top();
                            stack.pop();
                            int y = stack.top();
                            stack.pop();
                            stack.push(y * x);
                        } else {
                            err = true;
                            reset_stack();
                        }
                    }
\/                  {
                        if (stack.size() >= 2) {
                            int x = stack.top();
                            stack.pop();
                            if (x == 0) {
                                reset_stack();
                                std::cerr << "\033[1;31m[ERROR]: Division by 0 not premitted!\n\033[m";
                                BEGIN(ERR);
                            } else {
                                int y = stack.top();
                                stack.pop();
                                stack.push(y / x);
                            }
                        } else {
                            err = true;
                            reset_stack();
                        }
                    }
\%                  {
                        if (stack.size() >= 2) {
                            int x = stack.top();
                            stack.pop();
                            if (x == 0) {
                                reset_stack();
                                std::cerr << "\033[1;31m[ERROR]: Division by 0 not premitted!\n\033[m";
                                BEGIN(ERR);
                            } else {
                              int y = stack.top();
                              stack.pop();
                              stack.push(y % x);
                            }
                        } else {
                            err = true;
                            reset_stack();
                        }
                    }
\^                  {
                        if (stack.size() >= 2) {
                            int x = stack.top();
                            stack.pop();
                            int y = stack.top();
                            stack.pop();
                            stack.push(std::pow(y, x));
                        } else {
                            err = true;
                            reset_stack();
                        }
                    }

[ \t]               ;

\n                  {
                        if (stack.size() > 1) {
                            std::cerr << "\033[1;31m[ERROR]: Too few operators\n\033[m";
                        } else {
                            if (err) {
                                std::cerr << "\033[1;31m[ERROR]: Too few arguments\n\033[m";
                            } else {
                                std::cout << "\033[1;32mResult: " << stack.top() << "\033[m" << std::endl;
                                stack.pop();
                            }
                        }
                        reset_stack();
                        err = false;
                        BEGIN(INITIAL);
                    }

.                   {
                        std::cerr << "\033[1;31m[ERROR]: Unexpected symbol: \"" << yytext << "\"\033[m" << std::endl;
                        reset_stack();
                        err = false;
                        BEGIN(ERR);
                    }
<ERR>{
    .               ;
    \n              {
                        BEGIN(INITIAL);
                        err = false;
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
