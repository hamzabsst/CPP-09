/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 22:52:20 by hbousset          #+#    #+#             */
/*   Updated: 2025/11/21 16:12:01 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe& other)
{
	*this = other;
}
PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
	{
		_vector = other._vector;
		_deque = other._deque;
	}
	return *this;
}
PmergeMe::~PmergeMe() {}

void PmergeMe::parseInput(int ac, char** av)
{
	if (ac < 2)
		throw std::runtime_error("Error");

	for (int i = 1; i < ac; i++)
	{
		std::string arg = av[i];

		if (arg.empty())
			throw std::runtime_error("Error");
		for (size_t j = 0; j < arg.length(); j++)
		{
			if (!isdigit(arg[j]))
				throw std::runtime_error("Error");
		}

		std::stringstream ss(arg);
		long num;
		ss >> num;
		if (num <= 0 || num > 2147483647)
			throw std::runtime_error("Error");
		_vector.push_back(static_cast<int>(num));
		_deque.push_back(static_cast<int>(num));
	}
}

void PmergeMe::displayBefore() const
{
	std::cout << "Before: ";
	for (size_t i = 0; i < _vector.size(); i++)
	{
		std::cout << _vector[i] << " ";
	}
	std::cout << std::endl;
}

void PmergeMe::displayAfter() const
{
	std::cout << "\nAfter:  ";
	for (size_t i = 0; i < _vector.size(); i++)
	{
		std::cout << _vector[i] << " ";
	}
	std::cout << std::endl;
}

std::vector<int> PmergeMe::mergeInsertSortVector(std::vector<int>& vec)
{
	if (vec.size() <= 1)
		return vec;

	std::vector<int> larger, smaller;
	int straggler = -1;
	bool hasStraggler = (vec.size() % 2 != 0);

	for (size_t i = 0; i + 1 < vec.size(); i += 2)
	{
		if (vec[i] > vec[i + 1])
		{
			larger.push_back(vec[i]);
			smaller.push_back(vec[i + 1]);
		}
		else
		{
			larger.push_back(vec[i + 1]);
			smaller.push_back(vec[i]);
		}
	}
	if (hasStraggler)
		straggler = vec[vec.size() - 1];

	std::vector<int> sorted = mergeInsertSortVector(larger);

	for (size_t i = 0; i < smaller.size(); i++)
		sorted.insert(std::lower_bound(sorted.begin(), sorted.end(), smaller[i]), smaller[i]);

	if (hasStraggler)
		sorted.insert(std::lower_bound(sorted.begin(), sorted.end(), straggler), straggler);

	return sorted;
}

std::deque<int> PmergeMe::mergeInsertSortDeque(std::deque<int>& deq)
{
	if (deq.size() <= 1)
		return deq;

	std::deque<int> larger, smaller;
	int straggler = -1;
	bool hasStraggler = (deq.size() % 2 != 0);

	for (size_t i = 0; i + 1 < deq.size(); i += 2)
	{
		if (deq[i] > deq[i + 1])
		{
			larger.push_back(deq[i]);
			smaller.push_back(deq[i + 1]);
		}
		else
		{
			larger.push_back(deq[i + 1]);
			smaller.push_back(deq[i]);
		}
	}
	if (hasStraggler)
		straggler = deq[deq.size() - 1];

	std::deque<int> sorted = mergeInsertSortDeque(larger);

	for (size_t i = 0; i < smaller.size(); i++)
		sorted.insert(std::lower_bound(sorted.begin(), sorted.end(), smaller[i]), smaller[i]);

	if (hasStraggler)
		sorted.insert(std::lower_bound(sorted.begin(), sorted.end(), straggler), straggler);

	return sorted;
}

void PmergeMe::sortVector()
{
	_vector = mergeInsertSortVector(_vector);
}
void PmergeMe::sortDeque()
{
	_deque = mergeInsertSortDeque(_deque);
}

void PmergeMe::execute()
{
	struct timeval start, end;

	gettimeofday(&start, NULL);
	sortVector();
	gettimeofday(&end, NULL);
	double vectorTime = (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec;

	gettimeofday(&start, NULL);
	sortDeque();
	gettimeofday(&end, NULL);
	double dequeTime = (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec;

	std::cout << "\nTime to process a range of " << _vector.size() << " elements with std::vector : " << vectorTime << " us" << std::endl;
	std::cout << "Time to process a range of " << _deque.size() << " elements with std::deque : " << dequeTime << " us" << std::endl;
}
