# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <cstdlib>
# include <unistd.h>
#include <vector>
# define WHITESPACES "; \t"
#include "server.hpp"
#include "inc.hpp"
int	ft_in_charset1(char const c, const std::string &charset)
{
	int	i_charset;

	i_charset = 0;
	while (charset[i_charset])
	{
		if (c == charset[i_charset++])
			return 0;
	}
	return 1;
}


std::vector<std::string> ft_split(const std::string &str, const std::string &charset)
{
	std::vector<std::string> res;
	std::string 	tmp;
	size_t			i;

	i = 0;
	while (i < str.length())
	{
		while (i < str.length() && ft_in_charset1(str[i], charset))
			i++;
		if (i < str.length())
		{
			tmp = "";
			while (i < str.length() && !ft_in_charset1(str[i], charset))
				tmp += str[i++];
			res.push_back(tmp);
		}
	}
	return res;
}

std::string get_file(const std::string &file)
{
	std::ifstream fichier(file.c_str());
	std::string contenu((std::istreambuf_iterator<char>(fichier)), std::istreambuf_iterator<char>());
	fichier.close();
	return contenu;
}

int parser(char *str)
{
	const std::vector<std::string> configfile = ft_split(get_file(str), "\n");
	if (!configfile.size())
	{
		std::cerr << "Config file is empty " << std::endl;
		exit(1);
	}
	size_t nbline = 0;
	while(nbline < configfile.size())
	{
		std::vector<std::string> line = ft_split(configfile[nbline], WHITESPACES);
		if (line[0] == "server")
		{
			/*Server *server = */parser_le_server(configfile, &nbline);
		}
		
	}
	return (0);
}

int    main(int ac, char **av)
{
   
	if (!parser(av[1]))
	{
		std::cerr << "ya un pb mec" << std::endl;
        return (0);
	}
    return (0);
}