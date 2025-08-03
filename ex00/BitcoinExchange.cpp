#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
 
}

std::string *split(std::string line, char target)
{
	int i = 0;
	size_t pos = 0;
    int less = 0;
	std::string *str = new std::string[5];
	while (i < 5)
	{
		pos = line.find (target);
		if (pos == std::string::npos)
        {
            str[i] = line.substr (0,line.length());
			break;
        }
        if (line[pos] == '-')
            less++;
		str[i] = line.substr (0,pos);
		line.erase(0,pos + 1);
		i++;
	}
    if (less != 2)
    {
        delete[] str;
        throw std::logic_error("Error: valide line must be 'Year-Month-Day | value'");
    }
	i = 0;
    while (str[i].empty())
	{
		std::cout <<"date = " <<  str[i].empty() <<std::endl;
		i++;
	}
    return str;
}

int	lenth(std::string *str)
{
	int	i;

	i = 0;
	while (!str[i].empty())
	{
		i++;
	}
	return (i);
}

void BitcoinExchange::parsing_date()
{
    int maxDay;
    if (lenth(date) != 3)
		throw std::logic_error("Error: date must be 'Year-Month-Day' ");
    if (!is_intger(date[0]) || !is_intger(date[1]) || !is_intger(date[2]))
		throw std::logic_error("Error: date must be 'Year-Month-Day'");
    if (date[1].size() != 2 || date[2].size() != 2)
		throw std::logic_error("Error: Month and day must be two digite (02,12)");
    year = atoi(date[0].c_str());
    month = atoi(date[1].c_str());
    day = atoi(date[2].c_str());
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
    date_input = year * 10000 + month * 100 + day;
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

void BitcoinExchange::parsing_line(std::string line,std::map<int, double> Map)
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
		size_t lenth = dateStr.length() - 1;
    	if (dateStr[lenth] != ' ' || BitcoinStr[0] != ' ')
			throw std::logic_error("Error: valide line must be 'Year-Month-Day | value' ");
		BitcoinStr.erase(0,1);
		dateStr.erase(dateStr.size() - 1, 1);
    	date = split(dateStr,'-');
    	parsing_date();
    	validate_bitcoin_value(BitcoinStr);
    	std::map<int, double>::iterator it = Map.begin();
		while (it != Map.end())
		{
			if (it->first == date_input)
			{
				std::cout << dateStr << " => " << BitcoinStr << " = " << it->second * Bitcoin << std::endl;
				return;
			}
			else if (it == Map.begin() && it->first > date_input)
			{
				std::cout << "Error: "+ dateStr +" => doesn't have Bitcoin" << std::endl;
				return;
			}
			else if (it->first > date_input)
			{
				it--;
				std::cout << dateStr << " => " << BitcoinStr << " = " << it->second * Bitcoin << std::endl;
				return;
			}
			it++;
		}
		it--;
		std::cout << dateStr << " => " << BitcoinStr << " = " << it->second * Bitcoin << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}