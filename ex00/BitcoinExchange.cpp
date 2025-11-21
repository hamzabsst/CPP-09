/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset <hbousset@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:39:36 by hbousset          #+#    #+#             */
/*   Updated: 2025/11/20 23:14:18 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
	loadDatabase("data.csv");
}

BitcoinExchange::BitcoinExchange(std::string data)
{
	loadDatabase(data);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
	*this = other;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
	{
		_database = other._database;
	}
	return *this;
}

BitcoinExchange::~BitcoinExchange(){}

void BitcoinExchange::loadDatabase(const std::string &filename)
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
		throw std::runtime_error("could not open database file.");

	std::string line;
	std::getline(file, line);

	while (std::getline(file, line))
	{
		std::istringstream ss(line);
		std::string date;
		float price;

		if (std::getline(ss, date, ',') && ss >> price)
		{
			_database[date] = price;
		}
	}
	file.close();
}

std::string BitcoinExchange::trim(const std::string &str)
{
	size_t start = str.find_first_not_of(" \t");
	size_t end = str.find_last_not_of(" \t");
	if (start == std::string::npos)
		return "";
	return str.substr(start, end - start + 1);
}

bool BitcoinExchange::isValidDate(const std::string &date)
{
	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		return false;

	for (size_t i = 0; i < date.length(); i++)
		if (i != 4 && i != 7 && !isdigit(date[i]))
			return false;

	std::istringstream ss(date);
	int year, month, day;
	char dash1, dash2;
	ss >> year >> dash1 >> month >> dash2 >> day;

	if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31)
		return false;

	if (month == 2)
	{
		if (day > 29) return false;
	}
	else if (month == 4 || month == 6 || month == 9 || month == 11)
		if (day > 30)
			return false;
	return true;
}

float BitcoinExchange::getExchangeRate(const std::string &date)
{
	std::map<std::string, float>::iterator it = _database.lower_bound(date);

	if (it != _database.end() && it->first == date)
		return it->second;
	if (it == _database.begin())
		return -1;
	--it;
	return it->second;
}

void BitcoinExchange::processLine(const std::string &line)
{
	size_t pipePos = line.find('|');
	if (pipePos == std::string::npos)
	{
		std::cerr << "Error: bad input " << line << std::endl;
		return;
	}

	std::string date = trim(line.substr(0, pipePos));
	std::string valueStr = trim(line.substr(pipePos + 1));

	if (!isValidDate(date))
	{
		std::cerr << "Error: bad input " << date << std::endl;
		return;
	}

	std::istringstream ss(valueStr);
	float value;
	if (!(ss >> value) || !ss.eof())
	{
		std::cerr << "Error: bad input " << valueStr << std::endl;
		return;
	}

	if (value < 0)
	{
		std::cerr << "Error: not a positive number." << std::endl;
		return;
	}
	if (value > 1000)
	{
		std::cerr << "Error: too large a number." << std::endl;
		return;
	}

	float rate = getExchangeRate(date);
	if (rate < 0)
	{
		std::cerr << "Error: no exchange rate available." << std::endl;
		return;
	}

	std::cout << date << " => " << value << " = " << (value * rate) << std::endl;
}

void BitcoinExchange::processFile(const std::string &filename)
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return;
	}

	std::string line;
	std::getline(file, line);

	while (std::getline(file, line))
		processLine(line);

	file.close();
}
