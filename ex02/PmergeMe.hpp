/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 22:52:28 by hbousset          #+#    #+#             */
/*   Updated: 2025/11/21 16:14:11 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <sstream>
#include <sys/time.h>
#include <algorithm>
#include <exception>

class PmergeMe
{
	private:
		std::vector<int>	_vector;
		std::deque<int>		_deque;

		void 				sortVector();
		std::vector<int>	mergeInsertSortVector(std::vector<int>& vec);

		void				sortDeque();
		std::deque<int>		mergeInsertSortDeque(std::deque<int>& deq);


	public:
		PmergeMe();
		PmergeMe(const PmergeMe& other);
		PmergeMe& operator=(const PmergeMe& other);
		~PmergeMe();

		void	parseInput(int ac, char** av);
		void 	execute();
		void	displayBefore() const;
		void	displayAfter() const;
};
