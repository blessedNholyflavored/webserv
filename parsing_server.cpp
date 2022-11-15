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

int check_int(const std::string &str)
{
	if (str.empty() || ((!isdigit(str[0])) && str[0] != '-' && str[0] != '+'))
		return 0;
	char *p;
	strtol(str.c_str(), &p, 10);
	return (*p == 0);
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

Server *parser_le_server(const std::vector<std::string> configfile, size_t *nbligne)
{
	std::vector<std::string> ligne = ft_split(configfile[0], WHITESPACES);
	if (ligne[1] != "{")
		return NULL;
	std::cout <<"{" <<std::endl;
	Server *server = new Server();
	std::vector<std::string>::const_iterator it = configfile.begin() + *nbligne;
	if (it == configfile.end())
		return NULL;
	it++;
	(*nbligne)++;
	while (it != configfile.end())
	{
		std::vector<std::string> ligne = ft_split(*it, WHITESPACES);
		if (!ligne.size() || !ligne[0].size())
		{
			it++;
			(*nbligne)++;
			continue;
		}
		if (ligne[0][0] == '#')
		{
			it++;
			(*nbligne)++;
			continue;
		}
		else if (ligne[0] != "}")
			std::cout <<"\t" << ligne[0] << ":" << std::endl;
		if (ligne[0] == "}")
		{
			// (*nbligne)++;
			break;
		}
		// else if (ligne[0] == "location")
		// {

		// }
		// else if (line[0] == "server_name")
		// {

		// }
		// else if (line[0] == "listen")
		// {

		// }
		// else if (line[0] == "index")
		// {
			
		// }
		// else if (line[0] == "root")
		// {

		// }
		else if (ligne[0] == "max_client_body_size")
		{
			if (ligne.size() != 2)
				std::cerr << "manque un argument de taille" << std::endl;
			if (!check_int(ligne[1]))
				std::cerr << "mauvais int de taille " << std::endl;
				
		}
	}
		return server;
}