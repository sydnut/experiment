#pragma once
#ifndef _LEXER_H_
#define _LEXER_H_
#include<string>
#include"Token.h"
#include<map>
#include"TAG.h"
using namespace std;
class Lexer {

	void reserve(Word&& word) {
		hashmap.insert(make_pair(word.s, word));
	}
	void getch() {
		if (len < size)
			peek = data[len++];
	}
	bool getch(char c) {
		getch();
		if (peek == c) {
			peek = ' ';
			return 1;
		}
		else return 0;
	}
	int size;
	char peek;
	int line;
	char* data;
	map<string, Word>hashmap;
public:
	int len;
	//void£¬main£¬if£¬then£¬break£¬int£¬Char£¬float£¬include£¬for£¬while£¬printf, scanf £¬begin,end,
	Lexer(char* c, int sa) {
		hashmap.clear();
		size = sa;
		peek = ' ';
		line = 1;
		data = c;
		len = 0;
		//printf("%2d", line);
		  reserve(Word("if", TAG::IF)); reserve(Word("then", TAG::THEN)); reserve(Word("break", TAG::BREAK)); reserve(Word("procedure", TAG::PROCEDURE));
		reserve(Word("int", TAG::INT)); reserve(Word("char", TAG::CHAR)); reserve(Word("float", TAG::FLOAT)); reserve(Word("for", TAG::FOR));
		reserve(Word("while", TAG::WHILE)); reserve(Word("begin", TAG::BEGIN)); reserve(Word("end", TAG::END)); reserve(Word("call", TAG::CALL));
		reserve(Word("const", TAG::CONST)); reserve(Word("do", TAG::DO));
	}
	Token* scan() {
		for (; len < size; getch()) {
			if (peek == ' ' || peek == '\t') {
				if (len > 1024)break;//×î´óÈÝÁ¿
				continue;
			}
			if ((peek == '\r' && getch('\n'))||peek=='\n') {//printf("\n%2d ", ++line);
			}
			else break;
		}
		switch (peek)
		{
		case'=':
			if (getch('=')) {
				return new Word("==", TAG::EQ);
			}
			else {
				return new Word("=", TAG::BECOMES); 
			}; break;
		case'!':
			if (getch('=')) {
				return new Word("!=", TAG::NE); 
			}
			else {
				return new Word("!", TAG::SYMBOLS); 
			} break;
		case'>':
		{
			if (getch('=')) {
				return new Word(">=", TAG::RQ); 
			}
			else {
				return new Word(">", TAG::RN); 
			} break;
		}
		case'<':
			if (getch('=')) {
				return new Word("<=", TAG::LQ);
			}
			else {
				return new Word("<", TAG::LN); 
			} break;
		default:
			break;
		}
		if (isdigit(peek)) {
			int sum = 0;
			do {
				sum += sum * 10 + peek - '0';
				getch();
			} while (isdigit(peek));
			if (peek != '.') { return new Num(sum);  }
			else {
				getch();
				int d = 10;
				double real = sum;
				do {
					real = (double)(real * 10 + peek - '0') / (double)d;
					d *= 10;
					getch();
				} while (isdigit(peek));
				return new Real(real);
				
			}
		}
		if (isalpha(peek)|| peek == '_') {
			string s;
			do {
				s.push_back(peek);
				getch();
			} while (isalpha(peek) || peek == '_' || isdigit(peek));
			if (hashmap.find(s) == hashmap.end()) { reserve(Word(s, TAG::IDENTIFIER)); }return new Word(s,hashmap.find(s)->second.getTAG()) ;
		}
		if (peek == '.')return new Word(".", TAG::ENDSIGN);
		char t = peek; peek = ' ';
		return new Word(t);
		
		


	}
};

#endif