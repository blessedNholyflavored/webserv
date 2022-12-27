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
#include "functions.h"



std::string res[4096];

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
	std::string tmp("");
	size_t i = 0;
	static size_t j;
	while (i < str.length())
	{
		while (i < str.length() && ft_in_charset(str[i], charset))
			i++;
		if (i < str.length())
		{
			while (i < str.length() && !ft_in_charset(str[i], charset))
				tmp += str[i++];
			res[j] = tmp;
			tmp = "";
		}
	j++;
	}
}

std::string get_file( std::string file)
{
	std::ifstream fichier(file.c_str());
	std::string contenu((std::istreambuf_iterator<char>(fichier)), std::istreambuf_iterator<char>());
	fichier.close();
	return contenu;
}


int    parsExt(char *str)
{
    std::string cpy(str);

    if (cpy.length() > 5 && !cpy.compare(cpy.length() - 5, 5, ".conf"))
        return (1);
    return (0);
}

void	addCGI(Server server)
{
	ft_lstadd_back(&server.lst, ft_lstnew(NULL, NULL, (char *)"SERVER_SOFTWARE=Webserv/1.0"));
	ft_lstadd_back(&server.lst, ft_lstnew(NULL, NULL, (char *)"SERVER_NAME=localhost"));
	ft_lstadd_back(&server.lst, ft_lstnew(NULL, NULL, (char *)"GATEWAY_INTERFACE=CGI/1.1"));
	ft_lstadd_back(&server.lst, ft_lstnew(NULL, NULL, (char *)"SERVER_PROTOCOL=HTPP/1.1"));
	ft_lstadd_back(&server.lst, ft_lstnew(NULL, NULL, (char *)"QUERY_STRING=test=querystring"));
	ft_lstadd_back(&server.lst, ft_lstnew(NULL, NULL, (char *)"SERVER_PORT=9001"));
	ft_lstadd_back(&server.lst, ft_lstnew(NULL, NULL, (char *)"REQUEST_METHOD=POST"));
	ft_lstadd_back(&server.lst, ft_lstnew(NULL, NULL, (char *)"CONTENT_TYPE=application/x-www-form-urlencoded;charset=utf-8"));
	ft_lstadd_back(&server.lst, ft_lstnew(NULL, NULL, (char *)"PATH_INFO=./reponse.php"));
	ft_lstadd_back(&server.lst, ft_lstnew(NULL, NULL, (char *)"PATH_TRANSLATED=./reponse.php"));
	ft_lstadd_back(&server.lst, ft_lstnew(NULL, NULL, (char *)"PATH_NAME=./reponse.php"));
	ft_lstadd_back(&server.lst, ft_lstnew(NULL, NULL, (char *)"SCRIPT_NAME=./reponse.php"));
	ft_lstadd_back(&server.lst, ft_lstnew(NULL, NULL, (char *)"SCRIPT_FILENAME=./reponse.php"));
	ft_lstadd_back(&server.lst, ft_lstnew(NULL, NULL, (char *)"REDIRECT_STATUS=200"));
	ft_lstadd_back(&server.lst, ft_lstnew(NULL, NULL, (char *)"HTTP_ACCEPT=*/*"));
	ft_lstadd_back(&server.lst, ft_lstnew(NULL, NULL, (char *)"HTTP_ACCEPT_LANGUAGE=en-US,en"));
	ft_lstadd_back(&server.lst, ft_lstnew(NULL, NULL, (char *)"HTTP_REFERER="));
}

int    main(int ac, char **av, char **env)
{
	Server server;
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
    if (!(server.parser(av[1])))
	{
		std::cerr << "ya un pb mec" << std::endl;
        return (0);
	}
	server.lst = init_lst(env, server.lst);
	addCGI(server);
	StartServer(server);
	
    return (0);
}
