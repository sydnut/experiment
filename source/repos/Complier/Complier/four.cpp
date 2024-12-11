#include<iostream>
#include<string>
#include<vector>
#include<stack>
using std::cout;
class Par {
	char c;
	char var;
	int tag;
	std::stack<char>sk;
	std::stack<int> elseptr;
	struct four
	{
		int id;
		char v1;
		std::string op;
		char v2;
		char ans;
	};
	std::vector<four>res;
	void error() {
		cout << "error!\n"; exit(-1);
	}
	void getch() {
		std::cin >> c;
	}
	void expr();
	void term();
	void t();
	void e();
	void fac();
	void stmt();
	void condition();
	void becomeStmt();
	void conditionStmt();
public:

	void start() {
		tag = 1;
		var = 'A';		getch();
		conditionStmt();
		if (c == '.')return;
	}
	void out() {
		for(auto& i:res) {
			cout << i.id << " (" << i.op << "," << i.v1 << "," << i.v2 << "," << i.ans << ")\n";
		}
	}

};
void Par::stmt() {
	if (c == 'i')conditionStmt();
	else becomeStmt();


}
void Par::conditionStmt() {
	if (c == 'i') {
		getch();
		if (c == 'f') {
			getch();
			condition();
			std::string op;
			op.push_back('j');
			res.push_back({ tag++,'_',op,'_','0'});
			elseptr.push( res.size() - 1);
		}
		else error();
	}
	else error();
	if (c == 't') {
		getch(); getch(); getch(); getch();


		stmt();
	}
	if (c == 'e') {
		res[elseptr.top()].ans = (char)(tag + '0');
		elseptr.pop();
		getch(); getch(); getch(); getch();
		stmt();
	}


}
void Par::becomeStmt() {
	if (isalpha(c)) {
		char v1, v2;
		v1 = c;
		std::string op;
		getch();
		op.push_back(c);
		getch();
		expr();
		v2 = sk.top();
		sk.pop();
		res.push_back({ tag++,v2,op,'_',v1});
	}
	else error();
}
void Par::condition() {
	expr();
	char v1 = sk.top();
	sk.pop();
	std::string op; op.push_back('j'); op.push_back(c);
	getch();
	expr();
	char v2 = sk.top();
	sk.pop();
	res.push_back({ tag++,v1,op,v2,(char)('0' + tag + 1) });
}
void Par::expr() {

	term();
	e();
}
void Par::term() {

	fac();
	t();
}
void Par::fac() {
	if (!isdigit(c) && c == '(') {

		getch();
		expr();
		if (c != ')')error();
		else getch();


	}
	else
	{
		sk.push(c);

		getch();
	}
}
void Par::e() {
	if (c == '+' || c == '-') {

		char v1, v2, v3; std::string op; op.push_back(c);
		v1 = sk.top(); sk.pop();
		getch();
		term();
		v2 = sk.top(); sk.pop();
		v3 = var++;
		sk.push(v3);
		res.push_back({ tag++,v1,op,v2,v3 });



	}

}
void Par::t() {
	if (c == '*' || c == '/') {

		char v1, v2, v3; std::string op; op.push_back(c);
		v1 = sk.top(); sk.pop();
		getch();
		fac();
		v2 = sk.top(); sk.pop();
		v3 = var++;
		sk.push(v3);
		res.push_back({ tag++,v1,op,v2,v3 });



	}

}
int main() {
	Par* p = new Par();
	p->start();
	p->out();

}