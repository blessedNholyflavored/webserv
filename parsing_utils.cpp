#include "includes/server.hpp"
#include "includes/inc.hpp"

int check_int(std::string str)
{
	if (str.empty() || ((!isdigit(str[0])) && str[0] != '-' && str[0] != '+'))
		return 0;
	char *p;
	strtol(str.c_str(), &p, 10);
	return (*p == 0);
}

int check_int1(std::string str)
{
	if (str.empty() || ((!isdigit(str[0])) || str[0] == '-' || str[0] == '+'))
		return 1;
	return 0;
}   


std::string ltrim(std::string &s)
{
	size_t start = s.find_first_not_of(" ");
	return (start == std::string::npos) ? "" : s.substr(start);
}

size_t countEndl(std::string content)
{
	int nbEndl = 0;
	for (int i = 0; content[i]; i++)
	{
		if (content[i] == '\n')
			nbEndl++;
	}
	return nbEndl;
}

std::string remove_charset(std::string res)
{
	int i = 0;
	while(res[i])
	{
		if (res[i] == ';')
		{
			((res.erase(i, 1)));
		}
		i++;
	}
	return res;
}