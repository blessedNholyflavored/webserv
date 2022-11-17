#include "server.hpp"
#include "inc.hpp"

// int	ft_in_charset1(char const c,  std::string &charset)
// {
// 	int	i_charset;

// 	i_charset = 0;
// 	while (charset[i_charset])
// 	{
// 		if (c == charset[i_charset++])
// 			return 0;
// 	}
// 	return 1;
// }

int check_int(std::string str)
{
	if (str.empty() || ((!isdigit(str[0])) && str[0] != '-' && str[0] != '+'))
		return 0;
	char *p;
	strtol(str.c_str(), &p, 10);
	return (*p == 0);
}

// std::string ft_split( std::string str,  std::string charset)
// {
// 	std::string res;
// 	std::string 	tmp;
// 	size_t			i;

// 	i = 0;
// 	while (i < str.length())
// 	{
// 		while (i < str.length() && ft_in_charset1(str[i], charset))
// 			i++;
// 		if (i < str.length())
// 		{
// 			tmp = "";
// 			while (i < str.length() && !ft_in_charset1(str[i], charset))
// 				tmp += str[i++];
// 			res.push_back(tmp);
// 		}
// 	}
// 	return res;
// }


Server *parser_le_server(std::string res[], size_t *nbligne, int j)
{
	//ft_split(configfile, WHITESPACES);
	if (res[j].compare("{"))
		return NULL;
	std::cout <<"{" <<std::endl;
	//Server *server = new Server();
	//std::string it = res[j].begin() + *nbligne;
	// if (it == res.end())
	// 	return NULL;
	// it++;
	// (*nbligne)++;
	// while (it != res.end())
	// {
	// 	std::string ligne = ft_split(*it, WHITESPACES);
	// 	if (!ligne.size() || !ligne[0].size())
	// 	{
	// 		it++;
	// 		(*nbligne)++;
	// 		continue;
	// 	}
	// 	if (ligne[0][0] == '#')
	// 	{
	// 		it++;
	// 		(*nbligne)++;
	// 		continue;
	// 	}
		if (res[j][0] != '}')
			std::cout <<"\t" << res[j][0] << ":" << std::endl;
		// if (res[j][0] == '}')
		// {
		// 	// (*nbligne)++;
		// 	break;
		// }
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
		if (res[j] == "max_client_body_size")
		{
			if (res[j].size() != 2)
				std::cerr << "manque un argument de taille" << std::endl;
			if (!check_int(res[j]))
				std::cerr << "mauvais int de taille " << std::endl;
				
		}
		(void)nbligne;
	return (NULL);
		//return server;
}