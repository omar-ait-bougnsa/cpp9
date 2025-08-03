
#include "BitcoinExchange.hpp"

void	BitcoinExchange::parse_data_line(std::string line, std::map<int, double> &Map)
{
	size_t		pos;
	int 		date;
	double		value;
	pos = line.find(',');
	std::string str = line.substr(0, pos);
	std::string value_str = line.substr(pos + 1).c_str();
	std::string *newstr = split(str, '-');
	year 	= atoi(newstr[0].c_str());
	month 	= atoi(newstr[1].c_str());
	day		= atoi(newstr[2].c_str());
	date = year * 10000 + month * 100 + day;
	value = std::strtold(value_str.c_str(),NULL);
	Map[date] = value;
	delete[] newstr;
}

int	is_intger(std::string str)
{
	int			i;
	char const	*s; 

	i = 0;
	s = str.c_str();
	if (str.empty())
		return (0);
	while (s[i])
	{
		if (!isdigit(str[i]))
		{
			return (0);
		}
		i++;
	}
	return (1);
}

void  BitcoinExchange::processData(std::ifstream &file)
{
	std::ifstream 	fileData("data.csv");
	std::string 	line;
	std::map<int, double> Map;
	if (!fileData.is_open())
	{
		std::cout << "can't open file data.csv" << std::endl;
		return ;
	}
	std::getline(fileData, line);
	while (std::getline(fileData, line))
	{
		parse_data_line(line, Map);
	}
	std::getline(file, line);
	if (line != "date | value")
	{
		std::cout << "error: first line must 'date | value'\n";
		return ;
	}
	while (std::getline(file, line))
	{
		parsing_line(line,Map);
	}
}
int	main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Error: could not open file.\n";
		return (0);
	}
	BitcoinExchange obj;
	std::ifstream file(av[1]);
	if (!file.is_open())
	{
		std::cout << "can't open file\n";
		return 0;
	}
	obj.processData(file);
}