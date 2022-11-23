#include "server.hpp"
#include "inc.hpp"

int check_int(std::string str)
{
	if (str.empty() || ((!isdigit(str[0])) && str[0] != '-' && str[0] != '+'))
		return 0;
	char *p;
	strtol(str.c_str(), &p, 10);
	return (*p == 0);
}

