#include <cmath>
#include <sstream>
#include <vector>
#include "stringCalc.h"

using namespace std;

enum TokenType { Number, MinusOrPlus, OtherOperator, LB, RB, Other };

bool isNumber(const char in)
{
	return (isdigit(in) || (in == '.'));
}

bool isMinusOrPlus(const char in)
{
	switch (in)
	{
	case '-':
	case '+':
		return true;
	default:
		return false;
	}
}

bool isOtherOperator(const char in)
{
	switch (in)
	{
	case '/':
	case '*':
	case '^':
		return true;
	default:
		return false;
	}
}

TokenType getTokenType(const char in)
{
	if (isNumber(in))
	{
		return Number;
	}
	if (isMinusOrPlus(in))
	{
		return MinusOrPlus;
	}
	if (isOtherOperator(in))
	{
		return OtherOperator;
	}
	if (in == '(')
	{
		return LB;
	}
	if (in == ')')
	{
		return RB;
	}
	return Other;
}

void calcRes(vector<double>& out, const char oper)
{
	if (out.size() < 2) throw string("Output stack too short");

	const double b = out.back();
	out.pop_back();
	const double in = out.back();
	out.pop_back();

	switch (oper)
	{
	case '+':
		out.push_back(in + b);
		break;
	case '-':
		out.push_back(in - b);
		break;
	case '*':
		out.push_back(in * b);
		break;
	case '/':
		out.push_back(in / b);
		break;
	case '^':
		out.push_back(pow(in, b));
		break;
	default:
		out.push_back(-1);
	}
}

int precedence(const char in)
{
	switch (in)
	{
	case '-':
	case '+':
		return 1;
	case '/':
	case '*':
		return 2;
	case '^':
		return 3;
	default:
		return -1;
	}
}

void handleOperatorToken(vector<double>& out, vector<char>& oper, const char operatorToken)
{
	if (oper.size() > 0)
	{
		if ((precedence(oper.back()) >= precedence(operatorToken)))
		{
			calcRes(out, oper.back());
			oper.pop_back();
		}
		oper.push_back(operatorToken);
	}
	else
	{
		oper.push_back(operatorToken);
	}
}

string stringCalc(string in)
{
	vector<double> out;
	vector<char> oper;

	string::iterator prevIter = in.begin();

	std::ostringstream outStream;
	outStream.precision(15);

	try
	{
		for (string::iterator inIter = in.begin(); inIter != in.end(); ++inIter)
		{
			if (getTokenType(*inIter) == Number)
			{
				if (getTokenType(*prevIter) == RB)
				{
					handleOperatorToken(out, oper, '*');
				}

				if (getTokenType(*prevIter) != Number) prevIter = inIter;

				if (inIter == in.end() - 1)
				{
					if (inIter - prevIter >= 307) throw string("Too many digits");
					out.push_back(stod(string(prevIter, inIter + 1)));
				}
			}
			else
			{
				if (getTokenType(*prevIter) == Number)
				{
					if (inIter - prevIter >= 308) throw string("Too many digits");
					out.push_back(stod(string(prevIter, inIter)));
				}

				if (getTokenType(*inIter) == MinusOrPlus)
				{
					if (getTokenType(*prevIter) == Number || getTokenType(*prevIter) == RB)
					{
						handleOperatorToken(out, oper, *inIter);
					}
					else if (getTokenType(*prevIter == MinusOrPlus))
					{
						switch (*inIter)
						{
						case '-':
							out.push_back(-1.0);
							break;
						case'+':
							out.push_back(1.0);
							break;
						default:;
						}
						handleOperatorToken(out, oper, '*');
					}
				}
				else if (getTokenType(*inIter) == OtherOperator)
				{
					handleOperatorToken(out, oper, *inIter);
				}
				else if (getTokenType(*inIter) == LB)
				{
					if (getTokenType(*prevIter) == RB || getTokenType(*prevIter) == Number)
					{
						handleOperatorToken(out, oper, '*');
					}
					oper.push_back(*inIter);
				}
				else if (getTokenType(*inIter) == RB)
				{
					if (oper.size() == 0) throw string("Operator stack empty");
					while (getTokenType(oper.back()) != LB)
					{
						calcRes(out, oper.back());
						oper.pop_back();
						if (oper.size() == 0) throw string("Operator stack empty");
					}
					oper.pop_back();
				}
				else
				{
					throw string("Invalid character");
				}

				prevIter = inIter;
			}
		}

		while (oper.size() > 0)
		{
			if (out.size() == 0) throw string("Output stack empty");
			calcRes(out, oper.back());
			oper.pop_back();
		}

		if (out.size() == 0) throw string("Output stack empty");
		outStream << out.back();
	}
	catch (string& err)
	{
		outStream << err;
		if (out.size() != 0) outStream << ": " << out.back();
	}
	return outStream.str();
}