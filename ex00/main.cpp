
#include "BitcoinExchange.hpp"

int	BitcoinExchange::parse_data_line(std::string line)
{
	size_t		pos;
	double		value;
	std::string str;
	pos = line.find(',');
	if (pos == std::string::npos)
	{
		std::cout << "Error: bad dataDB => " << line << std::endl;
		return 0;
	}
	std::string dateStr = line.substr(0, pos);
	std::string value_str = line.substr(pos + 1).c_str();
	
	std::stringstream ss(dateStr);
	if (dateStr.empty() || value_str.empty())
	{
		std::cout << "Error: bad dataDB => " << line << std::endl;
		return 0;
	}
	try
	{
		parseDate(dateStr);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return 0;
	}
	value = std::strtod(value_str.c_str(), NULL);
	Map[dateStr] = value;
	return 1;
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

int  BitcoinExchange::parsing_date(std::string datafile)
{
	std::string 	line;
	std::ifstream 	fileData(datafile.c_str());
	if (!fileData.is_open())
	{
		std::cout << "can't open file data.csv" << std::endl;
		return 0;
	}
	std::getline(fileData, line);
	while (std::getline(fileData, line))
	{
		if (parse_data_line(line) == 0)
			return 0;
	}
	return (1);
}

void  BitcoinExchange::processData(std::ifstream &file)
{
	std::string 	line;

	if (parsing_date("data.csv") == 0)
		return ;
	
	std::getline(file, line);
	if (line != "date | value")
	{
		std::cout << "error: first line must 'date | value'\n";
		return ;
	}
	while (std::getline(file, line))
	{
		parsing_line(line);
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