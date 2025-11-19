/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:39:22 by hbousset          #+#    #+#             */
/*   Updated: 2025/11/19 14:34:15 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <stdexcept>

class BitcoinExchange
{
	private:
		std::map<std::string, float> _database;

		void		loadDatabase(const std::string &filename);
		bool		isValidDate(const std::string &date);
		std::string	trim(const std::string &str);
		float		getExchangeRate(const std::string &date);
		void		processLine(const std::string &line);

	public:
		BitcoinExchange();
		BitcoinExchange(std::string data);
		BitcoinExchange(const BitcoinExchange &other);
		BitcoinExchange& operator=(const BitcoinExchange &other);
		~BitcoinExchange();

		void processFile(const std::string &filename);
};
