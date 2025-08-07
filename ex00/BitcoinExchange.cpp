#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
 
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
	day = other.day;
    month = other.month;
    year = other.year;
    Bitcoin = other.Bitcoin;
    date_input = other.date_input;
    Map  =  other.Map;
}

BitcoinExchange BitcoinExchange::operator=(const BitcoinExchange &other)
{
	day = other.day;
    month = other.month;
    year = other.year;
    Bitcoin = other.Bitcoin;
    date_input = other.date_input;
    Map =  other.Map;
	return *this;
}
BitcoinExchange::~BitcoinExchange()
{

}

std::string BitcoinExchange::parseDate(std::string dataStr)
{
    int maxDay;
	int i = 0;
    
	std::stringstream ss(dataStr);

	while (std::getline(ss, dataStr, '-'))
	{
		if (dataStr.empty() || !is_intger(dataStr))
			throw std::logic_error("Error: date must be 'Year-Month-Day' and must be integer");
		if (i == 0)
		{
			if (dataStr.size() != 4)
				throw std::logic_error ("Error: must just betwen (1000 to 9999) in year");
			year = atoi(dataStr.c_str());
		}
		else if (i == 1)
		{
			if (dataStr.size() != 2)
				throw std::logic_error("Error: Month must be two digits (01, 12)");
			month = atoi(dataStr.c_str());
		}
		else if (i == 2)
		{
			if(dataStr.size() != 2)
				throw std::logic_error("Error: Day must be two digits (01, 31)");
			day = atoi(dataStr.c_str());
		}
		i++;
	}
	if (i != 3)
		throw std::logic_error("Error: date must be 'Year-Month-Day'");
    if (month > 12)
		throw std::logic_error("Error: mounth must (1,12)");
	if (month == 2)
	{
		maxDay = 28;
		if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
			maxDay = 29;
	}
	else if (month == 4 || month == 6 || month == 11 || month == 9)
	{
		maxDay = 30;
	}
	else
		maxDay = 31;
	if (day > maxDay)
		throw std::logic_error("Error: Invalid day, this month does not have that many days");
	return dataStr;
} 

void BitcoinExchange::validate_bitcoin_value(std::string str)
{
    char *pos;
    Bitcoin = std::strtold(str.c_str(), &pos);
    if (pos[0] != '\0')
        throw std::logic_error("Error: Bitcoin must integer");
    if(Bitcoin < 0)
        throw std::logic_error("Error: Bitcoin must a positive number.");
    if (Bitcoin > 1000)
        throw std::logic_error("Error: Bitcoin too large a number.");
}

void removSpace(std::string &dateStr)
{
	size_t start = dateStr.find_first_not_of("\r\t ");
	size_t end = dateStr.find_last_not_of("\r\t ");
	if (start == std::string::npos || end == std::string::npos)
		dateStr = "";
	else
		dateStr = dateStr.substr(start, end - start + 1);
}

void BitcoinExchange::parsing_line(std::string line)
{
	std::string dateStr;
	std::string BitcoinStr;
    try
    {

    	size_t pos = line.find ('|');
		if (pos == std::string::npos)
		 	throw std::logic_error ("bad input => "+ line);
    	dateStr = line.substr(0,pos);
    	BitcoinStr = line.substr(pos +1);
		if (dateStr[dateStr.size() - 1] != ' ' || BitcoinStr[0] != ' ')
			throw std::logic_error ("Error: bad input => " + line);
    	removSpace(dateStr);
		removSpace(BitcoinStr);
		if (dateStr.empty() || BitcoinStr.empty())
			throw std::logic_error("Error: bad input => " + line + " must 'Year-Month-Day | value'");
		parseDate(dateStr);
    	validate_bitcoin_value(BitcoinStr);
		std::map<std::string, double>::iterator it = Map.lower_bound(dateStr);
		if (it == Map.begin() && it->first > dateStr)
		{
			std::cout << "Error: " + dateStr + " => doesn't have Bitcoin" << std::endl;
			return;
		}
		else if (it == Map.end() || it->first > dateStr)
		      it--;
		std::cout << dateStr << " => " << BitcoinStr << " = " << it->second * Bitcoin << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}