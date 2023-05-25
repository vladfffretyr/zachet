#include <iostream>
#include <stack>
#include <map>
#include <algorithm>
#include <vector>
#include <string>
#include <cctype>
using namespace std;

//создаем ОПЗ (обратную польскую запись из строки)
string RPN(string str);
//вычисление результата
float Calculation(float a, float b, float c, float d, float e, string str);
void StackPrint(stack<float> stack);

int main()
{
	string str = "a/(b-c)*(d+e)";
	float a = 8.6f;
	float b = 2.4f;
	float c = 5.1f;
	float d = 0.3f;
	float e = 7.9f;

	cout << str << endl;

	float result = Calculation(a, b, c, d, e, str);
	cout << "------------------------------------------------\n";
	cout << "Answer: " << result << endl;

	return 0;
}

void StackPrint(stack<float> stack)
{
	cout << "Stack print: ";
	do
	{
		cout << stack.top() << " ";
		stack.pop();
	} while (!stack.empty());
	cout << endl;
}
string RPN(string str)
{
	//строка, где будет храниться итоговая строка
	string srpn;

	//удаление пробелов в строке
	string::size_type ind;
	while ((ind = str.find(' ')) != string::npos)
	{
		str.erase(ind, 1);
	}

	//учет отрицательных чисел
	for (int i = 0; i < str.size(); i++)
	{
		if ((str[i] == '+' || str[i] == '-') && (0 == i || (!isalnum(str[i - 1]) && str[i - 1] != '.' && str[i - 1] != ')')))
		{
			auto it = find_if(str.begin() + i + 1, str.end(), [](char const c) {return !isalnum(c); });
			str.insert(it, ')');
			str.insert(i, "(");
		}
	}

	//карта веса символов
	map<char, size_t> map;
	map.insert(make_pair('*', 3));
	map.insert(make_pair('/', 3));
	map.insert(make_pair('+', 2));
	map.insert(make_pair('-', 2));
	map.insert(make_pair('(', 1));

	//стек для работы с опз
	stack<char> stack;
	//формирование строки в опз
	for (auto c : str)
	{
		if (!isalnum(c) && ('.' != c))
		{
			srpn += ' ';
			if (')' == c)
			{
				while (stack.top() != '(')
				{
					srpn += stack.top();
					stack.pop();
					srpn += ' ';
				}
				stack.pop();
			}
			else if ('(' == c)
			{
				stack.push(c);
			}
			else if (stack.empty() || (map[stack.top()] < map[c]))
			{
				stack.push(c);
			}
			else
			{
				do
				{
					srpn += stack.top();
					srpn += ' ';
					stack.pop();
				} while (!(stack.empty() || (map[stack.top()] < map[c])));
				stack.push(c);
			}
		}
		else
		{
			srpn += c;
		}
	}

	//добавление остатка стека в результирующую строку
	while (!stack.empty())
	{
		srpn += stack.top();
		srpn += ' ';
		stack.pop();
	}

	//удаление лишних пробелов
	vector<int> index;
	int count = 0;
	for (size_t i = 0; i < srpn.size() - 1; i++)
	{
		if (srpn[i] == ' ' && srpn[i + 1] == ' ')
			index.push_back(i + 1);
	}
	for (int i = index.size() - 1; i >= 0; i--)
	{
		srpn.erase(index[i], 1);
	}
	if (srpn[0] == ' ') srpn.erase(0, 1);

	return srpn;
}
float Calculation(float a, float b, float c, float d, float e, string str)
{
	str = RPN(str);
	stack<float> stack;
	cout << "Converted string: " << str << endl;
	cout << "------------------------------------------------\n";

	while (str != "")
	{
		//ASCII, 97 => a 101 => e
		if (str[0] == ' ') str.erase(0, 1);
		else if (str[0] >= 97 && str[0] <= 101)
		{
			char symb = str[0];
			str.erase(0, 1);
			switch (symb)
			{
			case 'a': stack.push(a); break;
			case 'b': stack.push(b); break;
			case 'c': stack.push(c); break;
			case 'd': stack.push(d); break;
			case 'e': stack.push(e); break;
			default: cout << "Can't found variable like this: " << str[0] << endl; return 0;
				break;
			}
		}
		else
		{
			StackPrint(stack);
			cout << "Future operator: " << str[0] << endl;
			float numbers[2];

			for (int i = 0; i < 2; i++)
			{
				numbers[i] = stack.top();
				stack.pop();
			}

			char symbol = str[0];
			str.erase(0, 1);
			switch (symbol)
			{
			case '+': stack.push(numbers[1] + numbers[0]); break;
			case '-': stack.push(numbers[1] - numbers[0]); break;
			case '/': stack.push(numbers[1] / numbers[0]); break;
			case '*': stack.push(numbers[1] * numbers[0]); break;
			default: cout << "Can't find operand like this:break; " << str[0] << endl;
			}
		}
	}
	return stack.top();
}