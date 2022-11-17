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

static std::string res[4096];

bool	ft_in_charset(char c, std::string &charset)
{
	int	i_charset;

	i_charset = 0;
	while (charset[i_charset])
	{
		if (c == charset[i_charset++])
			return true;
	}
	return false;
}

void ft_split1(std::string str, std::string charset)
{
	std::string res[4096];
	std::string tmp("");
	size_t			i;
	size_t j = 0;
	i = 0;
	while (i < str.length())
	{
		while (i < str.length() && ft_in_charset(str[i], charset))
			i++;
		if (i < str.length())
		{
			while (i < str.length() && !ft_in_charset(str[i], charset))
				tmp += str[i++];
			res[j] = tmp;
			j++;
		}
	}
}

std::string get_file( std::string file)
{
	std::ifstream fichier(file.c_str());
	std::string contenu((std::istreambuf_iterator<char>(fichier)), std::istreambuf_iterator<char>());
	fichier.close();
	return contenu;
}

int parser(std::string str)
{
	int	j = 0;
	get_file(str);
	if (!str.size())
	{
		std::cerr << "Config file is empty " << std::endl;
		exit(1);
	}
	size_t nbline = 0;
	while(nbline < str.size())
	{
		ft_split1(str, ": \t");
		if (res[0] == "server")
		{
		/*Server *server = */parser_le_server(res, &nbline, j);
		}
		j++;
		nbline++;
	}
	return (0);
}

int    parsExt(char *str)
{
    std::string cpy(str);

    if (cpy.length() > 5 && !cpy.compare(cpy.length() - 5, 5, ".conf"))
        return (1);
    return (0);
}

int    main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "Need a .conf file" << std::endl;
        return (0);
    }
    if (!parsExt(av[1]))
    {
        std::cerr << "Bad extension file" << std::endl;
        return (0);
    }
	if (!parser(av[1]))
	{
		std::cerr << "ya un pb mec" << std::endl;
        return (0);
	}
    printf("%s\n", av[1]);
    return (0);
}