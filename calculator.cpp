#include <iostream>
#include <string>
#include <stack>
#include <stdlib.h>
#include <vector>
using namespace std;

string token = "{}()[]+-*/";
vector<string> st;
string formula;

int order(string op) {
	if (op == "(") return 0;
	if (op == "+" || op == "-") return 1;
	if (op == "*" || op == "/") return 2;
	else return 3;
}

int errorcheck() {
	int c1 = 0, c2 = 0, c3 = 0;
	int d1 = 0, d2 = 0, d3 = 0;
	for (int i = 0; i < formula.length(); i++) {
		if (formula[i] == '{') {
			c1++;
			formula[i] = '(';
		}
		else if (formula[i] == '(')
			c2++;
		else if (formula[i] == '[') {
			c3++;
			formula[i] = '(';
		}
		if (formula[i] == '}')
		{
			d1++;
			formula[i] = ')';
		}
		else if (formula[i] == ')')
			d2++;
		else if (formula[i] == ']')
		{
			d3++;
			formula[i] = ')';
		}
	}
	if ((d1 + d2 + d3) != (c1 + c2 + c3))
		return -1;
	else if (d1 != c1)
		return -1;
	else if (d2 != c2)
		return -1;
	else if (d3 != c3)
		return -1;

	return 1;
}

void tokenizer(string str) {
	string temp = "";
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '(' || str[i] == ')' || str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') {
			if (temp == "") {
				string temp2 = "";
				temp2 += str[i];
				st.push_back(temp2);
			}
			else {
				st.push_back(temp);
				temp = "";
				string temp2 = "";
				temp2 += str[i];
				st.push_back(temp2);
			}
		}
		else
			temp += str[i];
		if (i == str.length() - 1 && temp != "")
			st.push_back(temp);
	}

}
string calc(string formula) {
	stack<string> postfix;
	stack<string> oper;
	int status = 0;
	tokenizer(formula);
	int index = 0;
	while (index < st.size()) {
		string str = st.at(index);
		if (str.compare("+") == 0 || str.compare("-") == 0 || str.compare("*") == 0 || str.compare("/") == 0) {
			if (oper.empty()) {
				oper.push(str);
			}
			else {
				if (order(oper.top()) >= order(str)) {
					postfix.push(oper.top());
					oper.pop();
					oper.push(str);
				}
				else {
					oper.push(str);
				}
			}
		}
		else if (str.compare("(") == 0) {
			oper.push(str);
		}
		else if (str.compare(")") == 0) {
			while (!(oper.top().compare("(") == 0)) {
				postfix.push(oper.top());
				oper.pop();
			}
			oper.pop();
		}
		else {
			postfix.push(str);
		}
		index++;
	}

	st.clear();

	while (!oper.empty()) {
		postfix.push(oper.top());
		oper.pop();
	}

	int size = postfix.size();

	for (int i = 0; i < size; i++) {
		oper.push(postfix.top());
		postfix.pop();
	}

	postfix = oper;
	stack<string> temp;

	for (int i = 0; i < size; i++) {
		string s = "";
		if (postfix.top() != "")
			s = postfix.top();
		else {
			continue;
		}
		if (s.compare("+") == 0) {
			double num1 = stod(temp.top());
			temp.pop();
			double num2 = stod(temp.top());
			temp.pop();
			temp.push(to_string(num2 + num1));
		}
		else if (s.compare("-") == 0) {
			double num1 = stod(temp.top());
			temp.pop();
			double num2 = stod(temp.top());
			temp.pop();
			temp.push(to_string(num2 - num1));
		}
		else if (s.compare("*") == 0) {
			double num1 = stod(temp.top());
			temp.pop();
			double num2 = stod(temp.top());
			temp.pop();
			temp.push(to_string(num2 * num1));
		}
		else if (s.compare("/") == 0) {
			double num1 = stod(temp.top());
			temp.pop();
			double num2 = stod(temp.top());
			temp.pop();
			if (num1 == 0) {
				return "Error!: divide by zero";
			}
			temp.push(to_string(num2 / num1));
		}
		else {
			temp.push(s);
		}
		postfix.pop();
	}
	return temp.top();
}

int main(void) {
	while (1) {
		cin >> formula;
		if (formula == "EOI")
			break;
		if (errorcheck() == 1) {
			cout << fixed; cout.precision(3);
			if (calc(formula).compare("Error!: divide by zero") != 0)
				cout << stod(calc(formula)) << endl;
			else
				cout << calc(formula) << endl;
		}
		else
			cout << "Error!: unbalanced parentheses" << endl;
	}

	system("pause");
	return 0;
}