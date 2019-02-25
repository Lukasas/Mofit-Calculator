#include "logic.h"
std::vector<Node> InfixToPostfix(std::vector<Node> & tokens);
double calculate(std::vector<Node> & tokens);
std::string Make_Calculation(std::string & input)
{
	std::vector<Node> tokens;
	std::string buffer = "";

	for(size_t i = 0; i < input.length(); i++)
	{
		char c = input[i];

		if (c == ' ')
			continue;

		if (isdigit(c) || c == '.' || c == ',')
		{
			buffer += c;
			continue;
		}

		if (buffer.length() > 0)
		{
			tokens.push_back(Node(0, buffer));
			buffer = "";
		}

		switch (c)
		{
			case '+':
			case '-':
			case '*':
			case '/':
				buffer += c;
				tokens.push_back(Node(1, buffer));
				buffer = "";
			break;
			case '(':
				buffer += c;
				tokens.push_back(Node(2, buffer));
				buffer = "";
			break;
			case ')':
				buffer += c;
				tokens.push_back(Node(2, buffer));
				buffer = "";
			break;

			default:
				// TODO: ERROR HERE !
			break;
		}
	}

	if (buffer.length() > 0)
	{
		tokens.push_back(Node(0, buffer));
		buffer = "";
	}

	tokens = InfixToPostfix(tokens);

	double result = 0;

	result = calculate(tokens);

	std::ostringstream strs;
	strs << result;
	return strs.str();
}

 int precedence(std::string & op)
 {
	if (op.compare("/") == 0 || op.compare("*") == 0 )
	 	return 3;
	else if (op.compare("+") == 0 || op.compare("+") == 0)
		return 2;
	else if (op.compare("(") == 0)
		return 1;
	return 0;
 }

std::vector<Node> InfixToPostfix(std::vector<Node> & tokens)
{

	std::vector<Node> help;
	std::vector<Node> fin;

	Node token;

	for(size_t i = 0; i < tokens.size(); i++)
	{
		token = tokens[i];

		if (token.type == 0)
		{
			fin.push_back(token);
		}
		else if(token.type == 2)
		{
			if (token.value.compare("(") == 0)
			{
				help.push_back(token);
			}
			else
			{
				if (help.size() == 0) // Mispaired brackets
					throw 1;
				while (help.back().value.compare("(") != 0)
				{
					fin.push_back(help.back());
					help.pop_back();
					if (help.size() == 0)
						throw 1;
				}
				if (help.size() == 0)
				{
					throw 1; // error
				}
				help.pop_back();
			}
		}
		else
		{
			while (help.size() > 0 && precedence(help.back().value) >= precedence(token.value))
			{
				fin.push_back(help.back());
				help.pop_back();
			}
			help.push_back(token);
		}
	}

	while (help.size() > 0)
	{
		fin.push_back(help.back());
		help.pop_back();
	}

	return fin;
}

double evaluate(double operand1, std::string & opera, double operand2)
{
	if (opera.compare("+") == 0)
	{
		return operand2 + operand1;
	}
	else if (opera.compare("-") == 0)
	{
		return operand2 - operand1;
	}
	else if (opera.compare("*") == 0)
	{
		return operand2 * operand1;
	}
	else if (opera.compare("/") == 0)
	{
		return operand2 / operand1;
	}
	return 0.0/0.0;
}

double calculate(std::vector<Node> & tokens)
{
	Node token;
	std::vector<double> stack;
	double val, temp1, temp2;

	for(size_t i = 0; i < tokens.size(); i++)
	{
		token = tokens[i];
		if (token.type == 0)
		{
			val = strtod(token.value.c_str(), NULL);
			stack.push_back(val);
		}
		else
		{
			if (stack.size() == 0)
				throw 2; // CALL ERROR
			temp1 = stack.back();
			stack.pop_back();

			if (stack.size() == 0)
				throw 2; // CALL ERROR
			temp2 = stack.back();
			stack.pop_back();
			stack.push_back(evaluate(temp1, token.value, temp2));
		}
	}
	if (stack.size() > 0)
		return stack.back();
	return 0;
}