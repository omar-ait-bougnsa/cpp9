
#include "BitcoinExchange.hpp"

void	parse_data_line(std::string line, std::map<int, double> &Map)
{
	size_t		pos;
	int 		date;
	double		value;

	pos = line.find(',');
	std::string str = line.substr(0, pos);
	std::string *newstr = split(str, '-');
	date = atoi(newstr[0].c_str()) * 10000 + atoi(newstr[1].c_str()) * 100 + atoi(newstr[2].c_str());
	value = std::atof(line.substr(pos + 1).c_str());
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

void	processData(std::ifstream &file)
{
	std::ifstream data("data.csv");
	std::string line;
	BitcoinExchange obj;
	std::map<int, double> Map;
	if (!data.is_open())
	{
		std::cout << "can't open file data.csv" << std::endl;
		return ;
	}
	std::getline(data, line);
	while (std::getline(data, line))
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
		obj.parsing_line(line,Map);
	}
}
int	main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Error: could not open file.\n";
		return (0);
	}
	std::ifstream file(av[1]);
	if (!file.is_open())
	{
		std::cout << "can't open file\n";
		return 0;
	}
	processData(file);
}