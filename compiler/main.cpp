#include <vector>
#include <iostream>
#include <fstream>
#include "ast.hpp"
#include "asm.hpp"
#include "code_gen.hpp"
#include "symbols.hpp"

extern int yyparse();
extern int errors;
extern FILE *yyin;

ast::Node *root;
Symbols symbols;
CodeGen generator;


int main(int argc, char* argv[]) {
    if(argc == 3) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            std::cerr << "No such file: " << argv[1] << std::endl;
            return 1;
        }
        int syntaxInvalid = yyparse();
        if(syntaxInvalid || errors > 0) {
            std::cerr << "Error compiling file: " << errors << " syntax errors found" << std::endl;
            return 1;
        } else {
            if (root != NULL) {
                std::ofstream resultfile;
                resultfile.open(argv[2]);

                bool result = generator.generate_to(resultfile, root);
                resultfile.close();
                if (result) {
                    std::cerr << "Compilation successful" << std::endl;
                }
                return !result;
            }
        }
    } else {
        std::cout << "Program usage:\n\tcompiler Input_File Output_File" << std::endl;
        return 0;
    }
}