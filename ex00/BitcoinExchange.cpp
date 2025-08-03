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
		throw std::logic_error("Error: valide date must be 'Year-Month-Day' ");
    if (!is_intger(date[0]) || !is_intger(date[1]) || !is_intger(date[2]))
		throw std::logic_error("Error: valide line must be 'Year-Month-Day | value' ");
	if (date[1].size() != 2 || date[2].size() != 2)
		throw std::logic_error("Error: month and day must two character");
    if (date[1].size() != 2 || date[2].size() != 2)
		throw std::logic_error("Error: month and day must two character");
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
		throw std::logic_error("Error: this day is not in this month.");
    date_number = year * 10000 + month * 100 + day;
}
void BitcoinExchange::validate_bitcoin_value(std::string str)
{
    char *pos;
    Bitcoin = std::strtold(str.c_str(), &pos);
    if (pos[0] != '\0')
        throw std::logic_error("Error: Bitcoin must integer");
    if(Bitcoin < 0)
        throw std::logic_error("Error: not a positive number.");
    if (Bitcoin > 1000)
        throw std::logic_error("Error: too large a number.");
}

void BitcoinExchange::parsing_line(std::string line,std::map<int, double> Map)
{
    try
    {
    size_t pos = line.find ('|');
    std::string str = line.substr(0,pos);
	size_t lenth = str.length() - 1;
    line.erase(0,pos + 1);
    if (str[lenth] != ' ' || line[0] != ' ')
		throw std::logic_error("Error: valide line must be 'Year-Month-Day | value' ");
	line.erase(0,1);
	str.erase(str.size() - 1, 1);
    date = split(str,'-');
    parsing_date();
    validate_bitcoin_value(line);
    std::map<int, double>::iterator it = Map.begin();
	while (it != Map.end())
	{
		if (it->first == date_number)
		{
			std::cout << str << " => " << line << " = " << it->second * Bitcoin << std::endl;
			break ;
		}
		else if (it->first > date_number)
		{
			it--;
			if (it == Map.begin())
				std::cout << "Error: this date doesn't have Bitcoin" << std::endl;
			else
				std::cout << str << " => " << line << " = " << it->second * Bitcoin << std::endl;
			break ;
		}
				it++;
	}
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}