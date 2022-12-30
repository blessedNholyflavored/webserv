#include "server.hpp"
#include "inc.hpp"
#include "location.hpp"

Server::Server() //: max_client_body_size(4096), listen_fd(0)
{
	port = 0;
	autoindex = false;
}

Server::~Server()
{
	
}

// void	Server::transfer_location(Location location)
// {
// 	this->location.push_back(location);
// }

size_t countEndl(std::string content){
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

// int	checkEndofserver(std::string str)
// {
// 	int j = 0;
// 	for (int i = 0; str[i]; i++)
// 	{
// 		if (str[i] == '}')
// 		{
// 			j++;
// 			return 0;
// 		}
// 	}
// 	return (1);
// }

bool Server::autoindexed() const
{
	return this->autoindex;
}

int Server::parser(std::string str)
{
	int	j = 0;
	std::string content;
	content = get_file(str);
	if (!content.length())
	{
		std::cerr << "Config file is empty " << std::endl;
		exit(1);
	}
	ft_split1(content, "\n");
	size_t nbline = 0;
	while(!res[j].empty()){
		res[j] = remove_charset(res[j]);
		j++;
	}
	j = 0;
	int y = 0;
	int z = 0;
	size_t it;
	while(nbline <= countEndl(content))
	{
		if (res[0] == "server {")
		{
			this->parser_le_server(res, nbline, j);
		}
		std::string tmp(res[j]);
		if ((it = tmp.find("{") != std::string::npos))
		{
			if (tmp.find("server") < it || tmp.find("location") <= it)
			{
				z++;
			}
			else
			{
				std::cerr << "check tes }}}}} cest le bordel" << std::endl;
				exit(1);
			}
		}
		if ((tmp.find("}") != std::string::npos))
		{
			y++;
		}
	j++;
	nbline++;
	}
	if (z != y)
	{
		std::cerr << "check tes }}}}} cest le bordel" << std::endl;
		exit(1);
	}
	return 1;
}

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

std::vector<std::string> ft_split(std::string str, std::string deli)
{
	std::vector<std::string> res;

		int start = 0;
        int end = str.find(deli);
        int     i = 0;
        while (end != -1)
        {
                res.push_back(str.substr(start, end - start));
                start = end + deli.size();
                end = str.find(deli, start);
                i++;
        }
        res.push_back(str.substr(start, end - start));
		return (res);
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


int Server::parser_le_server(std::string res[], size_t nbligne, int j)
{
	//std::cout << res[j] << std::endl;
	if (res[j].find("location") != std::string::npos)
	{
		Location *tmp;

		tmp = new Location;
		tmp->parser_la_location(j);
		this->location.push_back(*tmp);
	}
	else if (res[j].find("server_name") != std::string::npos)
	{
		if (static_cast<std::string>(&res[j][13]).size() < 2)
			{
				std::cerr << "expecting at least 1 argument after 'server_name' "<< std::endl;
			}
		this->name_server = (res[j].c_str() + 13);
	}
	else if (res[j].find("autoindex") != std::string::npos)
	{
		if (static_cast<std::string>(&res[j][10]).size() < 2)
			{
				std::cerr << "expecting at least 1 argument after 'autoindex' "<< std::endl;
			}
		if (res[j].find("on") != std::string::npos && res[j].find("off") == std::string::npos) 
		{
			this->autoindex = 1;
		}
		else
		{
			this->autoindex = 0;
		}
	}
	else if (res[j].find("listen") != std::string::npos)
	{
		if (static_cast<std::string>(&res[j][7]).size() == 1) 
			std::cerr << "expecting one argument after listen"<< std::endl;
		std::string tmp(&res[j][7]);
		std::vector<std::string> listen = ft_split(tmp, ":");
		if (listen.size() != 1 && listen.size() != 2)
			std::cerr << "il faut port ou adress:port apres le listen" << std::endl;
		std::string address;
		std::string port;
		address = tmp;
		if (listen.size() == 1)
		{
			address = "0.0.0.0";
			port = listen[0];
		}
		else
			port = listen[1];
		if (address == "localhost")
			address = "127.0.0.1";
		this->ip = listen[0]; 
		std::string test = ltrim(port);
		if (check_int1(test))
			std::cerr << "port should be an int" << std::endl;
		this->port = ft_atoi(port.c_str());
		this->nbport.push_back(this->port);
	}
	else if (res[j].find("error_page") != std::string::npos)
	{
		std::string tmp(&res[j][11]);
		std::vector<std::string> error_page_tmp = ft_split(tmp, " ");
		if (error_page_tmp.size() != 3)
			std::cerr << "expecting two arguments after error_page"<< std::endl;
		else
		{
			this->error_name.push_back(error_page_tmp[1]);
			this->error_page.push_back(error_page_tmp[2]);
		}	
	}
	else if (res[j].find("cgi") != std::string::npos)
	{
		std::string tmp(&res[j][4]);
		std::vector<std::string> cgi = ft_split(tmp, " ");
		if (cgi.size() != 3)
			std::cerr << "expecting two arguments after cgi"<< std::endl;
		else 
		{
			this->cgi_exec.push_back(cgi[1]);
			this->cgi_address.push_back(cgi[2]);
		}
	}
	else if (res[j].find("index") != std::string::npos && res[j].find("autoindex") == std::string::npos)
	{
		if (static_cast<std::string>(&res[j][6]).size() < 3)
		{
			std::cerr << "expecting one argument after index"<< std::endl;
		}
		std::string tmp(res[j].c_str() + 6);
		this->index.push_back(tmp);
	}
	else if (res[j].find("root") != std::string::npos)
	{
		if (static_cast<std::string>(&res[j][6]).size() == 1)
			std::cerr << "expecting one argument after root"<< std::endl;
		std::string tmp(&res[j][6]);
		if (tmp.size() > 0 && tmp[0] == '/')
			tmp = tmp.substr(1);
		if (tmp.size() > 1 && tmp[tmp.size() - 1] == '/')
			tmp.resize(tmp.size() - 1);
		this->root = (tmp.c_str());
		// nginx garde le root qui a le plus long prefixe et lattribue
		std::cout << "root " <<  root << std::endl;
	}
	else if (res[j].find("max_client_body_size") != std::string::npos) 
	{
		std::string tmp(&res[j][22]);
		std::vector<std::string> max_body_size = ft_split(tmp, " ");
		if(max_body_size.size() != 1)
			std::cerr << "expecting one argument after max_client_body_size" << std::endl;
		else if (check_int1(max_body_size[0]))
			std::cerr << "mauvais int de taille " << std::endl;
		this->max_client_body_size = tmp;
	}
	(void)nbligne;
	return (0);
}
