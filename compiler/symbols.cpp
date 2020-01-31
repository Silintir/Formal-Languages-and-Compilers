#include <unordered_map>
#include <vector>
#include <string>
#include <sstream>
#include <typeinfo>
#include "ast.hpp"
#include "symbols.hpp"

extern int errors;
extern void yyerror(const char *msg);
extern int yynerrs, yylineno;


void error(std::string msg, int64_t loc) {
    std::cerr << "Error: near line " << loc << ": " << msg << std::endl;
    errors++;
}

bool Symbols::declare(ast::Identifier *identifier) {
    if(table.find(identifier->name) != table.end()){
        return false;
    }
    else {
        Symbol var;
        if (identifier->type() == 0) {
            var = Symbol(identifier->name, identifier->line, offset);
        } else if (identifier->type() == 1){
            ast::ConstArray* decl_array = ((ast::ConstArray*)identifier);
            var = Symbol(identifier->name, identifier->line, (decl_array->index_e - decl_array->index_b)+3, offset,
            decl_array->index_e, decl_array->index_b);
        }
        offset += var.size;
        //std::cout << identifier->name <<  " " << var.offset_id << std::endl;
        table[identifier->name] = var;
        return true;
    }
}

bool Symbols::declare_iterator(ast::Identifier *iterator) {
    if(table.find(iterator->name) != table.end() && !table[iterator->name].not_in_scope){
        return false;
    } else {
        Symbol var;
        var = Symbol(iterator->name, iterator->line, for_offset);
        for_offset += var.size;
        table[iterator->name] = var;
        table[iterator->name].not_in_scope = false;
        return true;
    }
}

void Symbols::alloc_for_control(int64_t for_count) {
    for_offset = offset;
    offset += for_count*2;
}

Symbol Symbols::get_symbol(std::string name) {
    if(table.find(name) != table.end()) {
        return table[name];
    }
    return Symbol();
}

bool Symbols::undeclare_iter(std::string name) {
    if(table.find(name) == table.end()) {
        return true;
    }
    table[name].not_in_scope = true;
    return true;
}

bool Symbols::undeclare(std::string name) {
        if(table.find(name) == table.end()) {
        return true;
    }
    table.erase(name);
    return true;
}

bool Symbols::is_initialized(ast::Identifier *identifier) {
    if(table.find(identifier->name) == table.end()) {
        return false;
    }
    if(table[identifier->name].not_in_scope == true){
        return false;
    } 

    return table[identifier->name].is_initialized;
}

bool Symbols::set_initialized(ast::Identifier *identifier) {
    if(table.find(identifier->name) == table.end()) {
        return false;
    } else {
        table[identifier->name].is_initialized = true;
        return true;
    }
}

bool Symbols::is_iterator(ast::Identifier *identifier) {
    if(table.find(identifier->name) == table.end()) {
        return false;
    }
    return table[identifier->name].iterator;
}

void Symbols::set_iterator(ast::Identifier *identifier) {
    if(table.find(identifier->name) == table.end()) {
        return;
    }
    table[identifier->name].iterator = true;
}

void Symbols::set_array(ast::Identifier *identifier) {
    if(table.find(identifier->name) == table.end()) {
        return;
    } else {
        table[identifier->name].is_array = true;
        // treat all arrays as initialized
        table[identifier->name].is_initialized = true;
    }
}

