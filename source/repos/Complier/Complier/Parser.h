#pragma once
#ifndef _PARSER_H_
#define _PARSER_H_
#include<iostream>
#include<string>
#include<fstream>
#include"Lexer.h"
#include<map>
using namespace std;
class Parser {
    Lexer* lexer;
    Token* c;

    void move() {
        Token* t = c;
        c = lexer->scan();
        if (t!=nullptr)delete t;
    }
    void error() {
        
        cout << "error!\n"; c->show();
        exit(-1);
    }
    void stmts();
    void stmt();

    void expr();
    void term();
    void t();
    void fac();
    void e();

    bool end() {
        return c->getTAG() == TAG::ENDSIGN;
    }
    void program();
    void fork_program();

    void const_ills();
    void const_identify();
    void var_ills();
    void process_head();
    void process_ills();

    void condition();
    void conditionStmt();
    void becomeStmt();
    void processStmt();
    void loopStmt();
    void multiStmt();
public:
    void start() {
        program();
    }
    Parser(char* buf, int size) {
        lexer = new Lexer(buf, size);
    }
    ~Parser()
    {
        delete lexer;
    }
};
void Parser::program() {
    cout << "program->fork_program .\n";
    move();
    fork_program();
    if (!end()) {
        cout << "finish wrong!\n";
    }
    else cout << "finish\n";
}
void Parser::fork_program() {
    cout << "fork_program->";
    if (c->getTAG() == TAG::CONST) {
        cout << "const_ills";
        const_ills();
    }
    while(c->getTAG() <= TAG::FLOAT && c->getTAG() >= TAG::INT) {
        cout << " var_ills";
        var_ills();     
    }
    if (c->getTAG() == TAG::PROCEDURE) {
        cout << " process_ills";
        process_ills();
    }
    cout << " stmts\n";
    stmts();
}
void Parser::const_identify() {
    if (c->getTAG() == TAG::IDENTIFIER) {
        cout << "const_identify->id=number";
        move();
    }
    else
    {
        error();
    }
    if (c->getTAG() == TAG::BECOMES)move(); else error();
    if (c->getTAG() == TAG::NUM || c->getTAG() == TAG::REAL) {
        move();
    }
    else error();
}
void Parser::const_ills() {
    if (c->getTAG() == TAG::CONST) {
        cout << "const_ills->const_identify+"; move();
    }
    else error();
    const_identify();
    while (c->getTAG() == TAG::SYMBOLS && static_cast<Word*>(c)->getch() == ',') {
         move();
        const_identify();
    }
    if (c->getTAG() == TAG::SYMBOLS && static_cast<Word*>(c)->getch() == ';') { move(); cout << endl; }
    else error();

}
void Parser::var_ills() {
    if (c->getTAG() <= TAG::FLOAT && c->getTAG() >= TAG::INT) {
        cout << "var_ills->"; c->show(); cout << " id\n";
        move();
    }
    else error();
    if (c->getTAG() == TAG::IDENTIFIER)move(); else error();
    while (c->getTAG() == TAG::SYMBOLS && static_cast<Word*>(c)->getch() == ',') {
        cout << "var_ills->id\n"; move();
        if (c->getTAG() == TAG::IDENTIFIER)move(); else error();
    }
    if (c->getTAG() == TAG::SYMBOLS && static_cast<Word*>(c)->getch() == ';')move(); else error();
}
void Parser::process_ills() {
    cout << "process_ills->process_head fork_program ;\n";
    process_head();
    fork_program();
    if (c->getTAG() == TAG::SYMBOLS && static_cast<Word*>(c)->getch() == '$') {
        move();
    }
    else error();
}
void Parser::process_head() {
    if (c->getTAG() == TAG::PROCEDURE) {
        cout << "process_head->procedure id ;\n";
        move();
    }
    else error();
    if (c->getTAG() == TAG::IDENTIFIER)move(); else error();
    if (c->getTAG() == TAG::SYMBOLS && static_cast<Word*>(c)->getch() == ';')move();
    else error();
}
void Parser::stmts() {
    cout << "stmts->stmt \n";
    stmt();
    while (c->getTAG() == TAG::SYMBOLS && static_cast<Word*>(c)->getch() == ';') {
            move();
            cout << "stmts->; stmt\n";
            stmt(); 
        }
    
}
void Parser::multiStmt() {
    if (c->getTAG() == TAG::BEGIN) {
        cout << "multiStmt->begin stmts end\n";
        move();
    }
    stmts();
    if (c->getTAG() == TAG::END) {
        move();
    }
    else error();

}
void Parser::loopStmt() {
    if (c->getTAG() == TAG::WHILE) {
        cout << "loopStmt->while condition do stmt\n";
        move();
    }
    condition();
    if (c->getTAG() == TAG::DO) {
        move();
    }
    else error();
    stmt();
}
void Parser::processStmt() {
    if (c->getTAG() == TAG::CALL) {
        cout << "processStmt->call id\n";
        move();
    }
    else error();
    if (c->getTAG() == TAG::IDENTIFIER)move();
    else error();
}
void Parser::conditionStmt() {
    if (c->getTAG() == TAG::IF) {
        cout << "conditionStmt->if condition then stmt\n";
        move();
    }
    else error();
    condition();
    if (c->getTAG() == TAG::THEN)move();
    //在语句之前,已经move了
    else error();
    stmt();
}
void Parser::becomeStmt() {
    if (c->getTAG() == TAG::IDENTIFIER) {
        cout << "becomeStmt->id=expr\n";
        move();
    }
    else
    {
        error();
    }
    if (c->getTAG() == TAG::BECOMES)move(); else error();
    expr();
}
void Parser::stmt() {
    switch (c->getTAG())
    {
    case TAG::IF:
        cout << "stmt->conditionStmt\n";
        conditionStmt();
        break;
    case TAG::IDENTIFIER:
        cout << "stmt->becomeStmt\n";
        becomeStmt();
        break;
    case TAG::CALL:
        cout << "stmt->processStmt\n";
        processStmt();
        break;
    case TAG::WHILE:
        cout << "stmt->loopStmt\n";
        loopStmt();
        break;
    case TAG::BEGIN:
        cout << "stmt->multiStmt\n";
        multiStmt();
        break;
    default:
        cout << "stmt_error!\n";
            error();
    }
}
void Parser::expr() {
    cout << "expr->term e\n";
    term();
    e();
}
void Parser::term() {
    cout << "term->fac t\n";
    fac();
    t();
}
void Parser::t() {

    if (c->getTAG() == TAG::SYMBOLS && (static_cast<Word*>(c)->getch() == '*' || static_cast<Word*>(c)->getch() == '/')) {
        cout << "t->" << static_cast<Word*>(c)->getch() << " fac\n";
        move();
        fac();
    }
    else cout << "t->null" << endl;
}
void Parser::fac() {
    if (static_cast<Word*>(c)->getch() == '(') {
        cout << "fac->(expr)\n";
        move();
        expr();
        if (static_cast<Word*>(c)->getch() != ')') {
            error();
        }
        else move();
    }
    else if (c->getTAG() == TAG::NUM || c->getTAG() == TAG::REAL) {
        cout << "fac->number\n";
        move();
    }
    else if (c->getTAG() == TAG::IDENTIFIER) {
        cout << "fac->id\n";
        move();
    }

    else {
        error();
    }
}
void Parser::e() {
    if (c->getTAG() == TAG::SYMBOLS && (static_cast<Word*>(c)->getch() == '+' || static_cast<Word*>(c)->getch() == '-')) {
        cout << "e->" << static_cast<Word*>(c)->getch() << " term\n";
        move();
        term();
    }
    else {

        cout << "e->null\n";
    }
}
void Parser::condition() //条件
{
    cout << "expr relate expr\n";
    expr();
    if (c->getTAG() <= TAG::EQ && c->getTAG() > TAG::BECOMES||c->getTAG()==TAG::NE) {
        cout << "relate-> "; c->show(); cout << endl;
        move();
    }
    else {
        error();
    }
    expr();
}
#endif // !_PARSER_H_
