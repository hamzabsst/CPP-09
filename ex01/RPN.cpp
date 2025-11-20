/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 14:25:55 by hbousset          #+#    #+#             */
/*   Updated: 2025/11/20 22:05:29 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

static void performOperation(std::list<int>& stack, char op)
{
	if (stack.size() < 2)
		throw std::runtime_error("error: something went wrong in your equation twin!");

	int b = stack.back();
	stack.pop_back();
	int a = stack.back();
	stack.pop_back();

	int result;
	switch (op)
	{
		case '+':
			result = a + b;
			break;
		case '-':
			result = a - b;
			break;
		case '*':
			result = a * b;
			break;
		case '/':
			if (b == 0)
				throw std::runtime_error("error: what did you thought when you were dividing by 0?");
			result = a / b;
			break;
		default:
			throw std::runtime_error("error: i mean get smarter or whatever");
	}
	stack.push_back(result);
}

void	RPN(std::string input)
{
	std::list<int> stack;

	for (size_t i = 0; i < input.length(); i++)
	{
		char c = input[i];

		if (c == ' ')
			continue;

		if (isdigit(c))
		{
			if (i + 1 < input.length() && isdigit(input[i + 1]))
				throw std::runtime_error("error: problem in formating the equation!");
			stack.push_back(c - '0');
		}
		else if (c == '+' || c == '-' || c == '*' || c == '/')
		{
			performOperation(stack, c);
		}
		else
		{
			throw std::runtime_error("error: expected an operator ngl twin!");
		}
	}

	if (stack.size() != 1)
		throw std::runtime_error("error: invalid equation ngl twin!");

	std::cout << stack.back() << std::endl;
}
