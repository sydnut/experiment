#pragma once
#ifndef _TOKEN_H_
#define _TOKEN_H_
#include<string>
#include"TAG.h"
using namespace std;
class Token {
public:
	int tag;
	void virtual show() { cout << 1; };
	Token(const int num) { tag = num; }
	int getTAG() {
		return tag;
	}
};
class Num :public Token {
public:
	int num;
	Num(const int n) :Token(TAG::NUM) {
		num = n;
	}
	void show()override {
		cout << num;
	}
};
class Real :public Token {
public:
	double num;
	Real(const double n) :Token(TAG::REAL) { num = n; }
	void show()override {
		cout << num;
	}
};
class Word :public Token {
public:
	string s;
	char c;
	Word(const string& str, int n) :Token(n) {
		s = str;
	}
	
	Word(char c) :Token(TAG::SYMBOLS) {
		this->c = c;
	}
	void show() override {
		if (tag != TAG::SYMBOLS)cout << s;
		else cout << c;
	}
	char getch() {
		return c;
	}
};
#endif // !_TOKEN_H_