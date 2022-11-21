#include "server.hpp"
#include "inc.hpp"

int check_int(std::string str)
{
	int i = 0;
	while(str[i])
	{
		if (str[i] == ';')
			{
				str.erase(i, 1);
			}
		i++;
	}	
	if (str.empty() || ((!isdigit(str[0])) && str[0] != '-' && str[0] != '+'))
		return 0;
	char *p;
	strtol(str.c_str(), &p, 10);
	return (*p == 0);
}

