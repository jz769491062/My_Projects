#pragma once
#include "CalculatorImp.h"
using namespace std;

stack<char> opers;  //������  
queue<char> suffix;  //��׺���ʽ  
stack<double> solution;  //�����׺���ʽ

bool is_paren(char c)
{
	if (c == '(' || c == ')')
		return true;
	else return false;
}

//�������ȼ�
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
{	//���ж����ŵ�����
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
			//��������Ԫ��ֱ������������  
			while (opers.top() != '(')
			{
				char ch = opers.top();
				suffix.push(ch);
				opers.pop();
			}
			//������������ʱ���������������׺���ʽ��  
			opers.pop();
		}
	}
	else//�����������  
	{
		//ȡ��ջ��Ԫ�أ��뵱ǰ���Ž��������ԱȽ�  
		char symbol = opers.top();

		if (getPrio(c) <= getPrio(symbol))
		{
			//���c��������<=ջ������,����׺
			opers.pop();
			suffix.push(symbol);
			//�ݹ�check,�Ƚϵ�ǰ����c����һ��ջ�����ŵ�������
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
			//��check��������Բ�ͬ���������ͬ����
			check(c, opers, suffix);
		}
	}
	//��������������opers��Ԫ��ȫ�������׺���ʽ��
	while (!opers.empty())
	{
		char c = opers.top();
		suffix.push(c);
		opers.pop();
	}
}

//�����׺
void calc(queue<char>& suffix, stack<double>& solution)
{
	string numstr; //��������
	while (!suffix.empty())
	{
		char c = suffix.front();
		suffix.pop();
		//�����������ջ
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
		else  //����������
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