#include "includes/server.hpp"
#include "includes/inc.hpp"
#include "includes/functions.h"

std::string	intToString(int i)
{
	std::string res;
	std::stringstream recup;
	recup << i;
	recup >> res;
	return res;
}

int	checkBuffBoundary2(char *buff)
{
	std::string all = buff;

	std::size_t found = all.find("------WebKitFormBoundary");
	if (found != std::string::npos)
		return (found);
	return (0);
}

int	checkBuffBoundary(std::string buff)
{
	int i = 0;
	char **recup = ft_split(buff.c_str(), '\r');

	while (recup[i])
	{
		std::string cmp = recup[i] + 1;
		if (cmp.compare(0, 24, "------WebKitFormBoundary") == 0)
		{
			freeTab2(recup);
			return 0;
		}
		i++;
	}
	freeTab2(recup);
	return (1);
}