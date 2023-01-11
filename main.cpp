/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhamlac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:33:16 by lkhamlac          #+#    #+#             */
/*   Updated: 2023/01/11 15:33:17 by lkhamlac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <cstdlib>
# include <unistd.h>
#include <vector>
# define WHITESPACES "; \t"
#include "includes/server.hpp"
#include "includes/inc.hpp"
#include "includes/functions.h"

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

std::vector<char *>	addCGI(Server server)
{
	server.vectorenv.push_back((char *)("SERVER_SOFTWARE=Webserv/1.0"));
	server.vectorenv.push_back((char *)("SERVER_NAME=localhost"));
	server.vectorenv.push_back((char *)("GATEWAY_INTERFACE=CGI/1.1"));
	server.vectorenv.push_back((char *)("SERVER_PROTOCOL=HTPP/1.1"));
	server.vectorenv.push_back((char *)("SERVER_PORT=9000"));
	server.vectorenv.push_back((char *)("CONTENT_TYPE=application/x-www-form-urlencoded;charset=utf-8"));
	server.vectorenv.push_back((char *)("REDIRECT_STATUS=200"));
	server.vectorenv.push_back((char *)("HTTP_ACCEPT=*/*"));
	server.vectorenv.push_back((char *)("HTTP_ACCEPT_LANGUAGE=en-US,en"));
	server.vectorenv.push_back((char *)("HTTP_REFERER="));
	return server.vectorenv;
}

std::vector<char *>	addCGIcpy(Server server)
{
	server.vectorenvcpy.push_back((char *)("SERVER_SOFTWARE=Webserv/1.0"));
	server.vectorenvcpy.push_back((char *)("SERVER_NAME=localhost"));
	server.vectorenvcpy.push_back((char *)("GATEWAY_INTERFACE=CGI/1.1"));
	server.vectorenvcpy.push_back((char *)("SERVER_PROTOCOL=HTPP/1.1"));
	server.vectorenvcpy.push_back((char *)("SERVER_PORT=9000"));
	server.vectorenvcpy.push_back((char *)("CONTENT_TYPE=application/x-www-form-urlencoded;charset=utf-8"));
	server.vectorenvcpy.push_back((char *)("REDIRECT_STATUS=200"));
	server.vectorenvcpy.push_back((char *)("HTTP_ACCEPT=*/*"));
	server.vectorenvcpy.push_back((char *)("HTTP_ACCEPT_LANGUAGE=en-US,en"));
	server.vectorenvcpy.push_back((char *)("HTTP_REFERER="));
	return (server.vectorenvcpy);
}

std::vector<char *>	init_vectorenv(char **env, std::vector<char *> vec)
{
	int i = 0;
	while (env[i])
	{       
		vec.push_back(env[i]);
		i++;
	}
	vec.push_back((char *)NULL);
	return vec;

}

std::string recupCWD(char **env, std::string cwd)
{
	int i = 0;
	while (env[i])
	{
		if (strncmp(env[i], "PWD=", 4) == 0)
		{
			std::string ret(env[i] + 4);
			return ret;
		}       
		i++;
	}
	return cwd;
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
		std::cerr << "Parsing error in cong file" << std::endl;
        return (0);
	}
    	server.cwd = recupCWD(env, server.cwd);
    	server.vectorenv = init_vectorenv(env, server.vectorenv);
    	server.vectorenvcpy = init_vectorenv(env, server.vectorenvcpy);
		server.vectorenv = addCGI(server);
		server.vectorenvcpy = addCGIcpy(server);
		StartServer(server);
	
    return (0);
}
