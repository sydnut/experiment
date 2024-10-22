#pragma once
#ifndef _LEXER_H_
#define _LEXER_H_
#include<string>
#include"Token.h"
#include<map>
#include"TAG.h"
using namespace std;
class Lexer {

	void reserve(Word word) {
		hashmap[word.s] = word;
	}
	void getch() {
		if (len < size)
			peek = data[len++];
		else peek = ' ';
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
		printf("%2d", line);
		reserve(Word("void", TAG::VOID)); reserve(Word("main", TAG::MAIN)); reserve(Word("if", TAG::IF)); reserve(Word("then", TAG::THEN)); reserve(Word("break", TAG::BREAK));
		reserve(Word("int", TAG::INT)); reserve(Word("char", TAG::CHAR)); reserve(Word("float", TAG::FLOAT)); reserve(Word("include", TAG::INCLUDE)); reserve(Word("for", TAG::FOR));
		reserve(Word("while", TAG::WHILE)); reserve(Word("printf", TAG::PRINTF)); reserve(Word("scanf", TAG::SCANF)); reserve(Word("begin", TAG::BEGIN)); reserve(Word("end", TAG::END));
	}
	void scan() {
		for (; len < size; getch()) {
			if (peek == ' ' || peek == '\t') {
				if (len > 1024)break;//×î´óÈÝÁ¿
				continue;
			}
			if (peek == '\r'&&getch('\n'))printf("\n%2d ", ++line);
			else break;
		}
		if (len > size)return;
		switch (peek)
		{
		case'=':
			if (getch('=')) {
				Word("==", TAG::EQ).show(); return;
			}
			else {
				Word("=", TAG::BECOMES).show(); return;
			}; break;
		case'!':
			if (getch('=')) {
				Word("!=", TAG::NE).show(); return;
			}
			else {
				Word("!", TAG::SYMBOLS).show(); return;
			} break;
		case'>':
		{
			if (getch('=')) {
				Word(">=", TAG::RQ).show(); return;
			}
			else {
				Word(">", TAG::RN).show(); return;
			} break;
		}
		case'<':
			if (getch('=')) {
				Word("<=", TAG::LQ).show(); return;
			}
			else {
				Word("<", TAG::LN).show(); return;
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
			if (peek != '.') { Num(sum).show(); return; }
			else {
				getch();
				int d = 10;
				double real = sum;
				do {
					real = (double)(real * 10 + peek - '0') / (double)d;
					d *= 10;
					getch();
				} while (isdigit(peek));
				Real(real).show();
				return;
			}
		}
		if ((peek <= 'z' && peek >= 'a') || (peek <= 'Z' && peek >= 'A') || peek == '_') {
			string s;
			do {
				s.push_back(peek);
				getch();
			} while ((peek <= 'z' && peek >= 'a') || (peek <= 'Z' && peek >= 'A') || peek == '_' || isdigit(peek));
			if (hashmap.find(s) == hashmap.end()) { hashmap[s] = Word(s, TAG::IDENTIFIER); }hashmap[s].show(); return;
		}
		if (peek == '-') {
			if (isdigit(peek)) {
				int sum = 0;
				do {
					sum += sum * 10 + peek - '0';
					getch();
				} while (isdigit(peek));
				if (peek != '.') { Num(sum * -1).show(); return; }
				else {
					double real = sum;
					do {
						real = (real * 10 + peek - '0') / 10.0;
						getch();
					} while (isdigit(peek));
					Real(real * -1).show(); return;
				}
			}
		}
		Word(peek).show();
		peek = ' ';

		return;
	}
};

#endif

