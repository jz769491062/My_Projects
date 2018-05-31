#pragma once
#include "CalculatorImp.h"
using namespace std;

stack<char> opers;  //操作符  
queue<char> suffix;  //后缀表达式  
stack<double> solution;  //计算后缀表达式

bool is_paren(char c)
{
	if (c == '(' || c == ')')
		return true;
	else return false;
}

//符号优先级
int getPrio(char c)
{
	switch (c)
	{
	case '+':
	case '-':
		return 0;
		break;
	case '*':
	case '/':
		return 1;
		break;
	case '(':
	case ')':
		return -1;
		break;
	case 'L':
	case 'R':
	case 'P':
	case 'E':
		return 2;
		break;
	//Get rid of warning message
	default:
		return -999;
		break;
	}
}

void check(char c, stack<char>& opers, queue<char>& suffix)
{	//不判定逗号的优先
	if (c == ',')return;
	if (opers.empty())
	{
		opers.push(c);
		return;
	}

	if (is_paren(c))
	{
		if (c == '(')
			opers.push(c);
		else
		{
			//弹出所有元素直到遇到左括号  
			while (opers.top() != '(')
			{
				char ch = opers.top();
				suffix.push(ch);
				opers.pop();
			}
			//当遇到左括号时，弹出但不加入后缀表达式）  
			opers.pop();
		}
	}
	else//如果不是括号  
	{
		//取出栈顶元素，与当前符号进行优先性比较  
		char symbol = opers.top();

		if (getPrio(c) <= getPrio(symbol))
		{
			//如果c的优先性<=栈顶符号,进后缀
			opers.pop();
			suffix.push(symbol);
			//递归check,比较当前符号c与下一个栈顶符号的优先性
			check(c, opers, suffix);
		}
		else
		{
			opers.push(c);
		}
	}
}
void allocate(string& expression, stack<char>& opers, queue<char>& suffix)
{
	while (!expression.empty())
	{
		char c = expression.front();
		expression.erase(expression.begin());
		if ((c >= '0'&&c <= '9') || c == '.')
		{
			suffix.push(c);
			if (!expression.empty())
			{
				char temp = expression.front();
				expression.erase(expression.begin());
				while ((temp >= '0'&&temp <= '9') || temp == '.')
				{
					suffix.push(temp);
					if (!expression.empty())
					{
						temp = expression.front();
						expression.erase(expression.begin());
					}
					else break;
				}
				suffix.push(',');
				check(temp, opers, suffix);
			}
			else suffix.push(',');
		}
		else
		{
			//用check函数，针对不同情况作出不同操作
			check(c, opers, suffix);
		}
	}
	//如果输入结束，将opers的元素全部加入后缀表达式中
	while (!opers.empty())
	{
		char c = opers.top();
		suffix.push(c);
		opers.pop();
	}
}

//计算后缀
void calc(queue<char>& suffix, stack<double>& solution)
{
	string numstr; //储存数字
	while (!suffix.empty())
	{
		char c = suffix.front();
		suffix.pop();
		//如果是数，进栈
		if ((c >= '0'&&c <= '9') || c == '.')
		{
			numstr.append(1, c);
		}
		else if (c == ',')
		{
			double numb = stod(numstr);
			solution.push(numb);
			numstr.clear();
		}
		else  //如果是运算符
		{
			double op1;
			if (solution.empty()) op1 = 0;
			else
			{
				op1 = solution.top();
				solution.pop();
			}
			double op2;
			if (solution.empty()) op2 = 0;
			else
			{
				op2 = solution.top();
				solution.pop();
			}
			switch (c)
			{
			case '+':
				solution.push(op2 + op1);
				break;
			case '-':
				solution.push(op2 - op1);
				break;
			case '*':
				solution.push(op2*op1);
				break;
			case '/':
				solution.push(op2 / op1);
				break;
			case 'L'://100log10 = 100L10
				solution.push((log(op2) / log(op1)));
				break;
			case 'R'://27R3=27^(1/3)
				solution.push(pow(op2, 1 / op1));
				break;
			case 'P'://2^3 = 2P3
				solution.push(pow(op2, op1));
				break;
			case 'E'://e^2=E2
				solution.push(exp(op1));//op1 or op2?
				break;
			}
		}
	}
}

double Calculate(string &str)
{
	allocate(str, opers, suffix);
	calc(suffix, solution);
	return solution.top();
}