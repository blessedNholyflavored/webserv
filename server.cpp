/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhamlac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:00:47 by lkhamlac          #+#    #+#             */
/*   Updated: 2023/01/11 14:01:00 by lkhamlac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/server.hpp"
#include "includes/inc.hpp"
#include "includes/location.hpp"

Server::Server()
{
	port = 0;
	autoindex = false;
}

Server::~Server()
{

}

void	Server::parsLoc(int i){
	int indexline = 0;
	for (int count = -1; count < i; count++){
		if (res[indexline] == "server {")
			count++;
		if (count < i)
			indexline++;
	}
	while (res[indexline].find("}") == std::string::npos){
		if (res[indexline].find("location") != std::string::npos)
		{
			Location tmp;
			indexline = tmp.parser_la_location(indexline);
			this->loc = tmp;
			location.push_back(tmp);
		}
		indexline++;
	}
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
			if(this->parser_le_server(res, nbline, j, countEndl(content)))
				return(0);
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
	if (this->root.empty())
	{	
		std::cerr << "there should be a root" << std::endl;
		exit (1);
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


int Server::parser_le_server(std::string res[], size_t nbligne, int j, int max)
{
	static int f;
	if (!(res[j].find("location") != std::string::npos))
	{
		if (j == max && !f)
			return (1);
	}
	else
		f = 9;
	int h = j;
	int floc = 0;
	while (h >= 0)
	{
		if (res[h].find("server") != std::string::npos)
			break ;
		if (res[h].find("location") != std::string::npos)
		{
			floc = 1;
			break ;
		}
		h--;
	}
	if (res[j].find("server_name") != std::string::npos)
	{
		if (static_cast<std::string>(&res[j][13]).size() < 2)
		{
			std::cerr << "expecting at least 1 argument after 'server_name' "<< std::endl;
			return (1);
		}
		this->name_server = (res[j].c_str() + 13);
		this->vectorname_server.push_back(this->name_server);
	}
	else if (res[j].find("autoindex") != std::string::npos)
	{
		if (static_cast<std::string>(&res[j][10]).size() < 2)
		{
			std::cerr << "expecting at least 1 argument after 'autoindex' "<< std::endl;
			return (1);
		}
		if (res[j].find("on") != std::string::npos && res[j].find("off") == std::string::npos) 
		{
			this->autoindex = 1;
			this->vectorauto.push_back(this->autoindex);
		}
		else
		{
			this->autoindex = 0;
			this->vectorauto.push_back(this->autoindex);
		}
	}
	else if (res[j].find("listen") != std::string::npos)
	{
		if (static_cast<std::string>(&res[j][7]).size() == 1) 
		{
			std::cerr << "expecting one argument after listen"<< std::endl;
			return (1);
		}
		std::string tmp(&res[j][7]);
		std::vector<std::string> listen = ft_split(tmp, ":");
		if (listen.size() != 1 && listen.size() != 2)
		{
			std::cerr << "need port or address after listen" << std::endl;
			return (1);
		}
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
		{
			std::cerr << "port should be an int" << std::endl;
			return (1);
		}
		if(test.length() != 4)
		{
			std::cerr << "port should be 4 digits only" << std::endl;
			return (1);
		}
		this->port = ft_atoi(port.c_str());
		this->nbport.push_back(this->port);
	}
	else if (res[j].find("error_page") != std::string::npos)
	{
		std::string tmp(&res[j][11]);
		std::vector<std::string> error_page_tmp = ft_split(tmp, " ");
		if (error_page_tmp.size() != 3)
		{
			std::cerr << "expecting two arguments after error_page"<< std::endl;
			return (1);
		}
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
		{
			std::cerr << "expecting two arguments after cgi"<< std::endl;
			return (1);
		}
		else 
		{
			this->cgi_exec.push_back(cgi[1]);
			this->cgi_address.push_back(cgi[2]);
		}
	}
	else if (res[j].find("index") != std::string::npos && res[j].find("autoindex") == std::string::npos && !floc)
	{
		if (static_cast<std::string>(&res[j][6]).size() < 3)
		{
			std::cerr << "expecting one argument after index"<< std::endl;
			return (1);
		}
		this->nom_index = res[j].c_str() + 6;
		this->index.push_back(nom_index);
	}
	else if (res[j].find("root") != std::string::npos && !floc)
	{
		if (static_cast<std::string>(&res[j][6]).size() <= 0)
		{
			std::cerr << "expecting one argument after root"<< std::endl;
			return (1);
		}
		std::string tmp(&res[j][6]);
		this->root = (tmp.c_str());
		this->vectorroot.push_back(this->root);		
	}
	else if (!(res[j].find("root")))
	{
		std::cerr << "there should be a root" << std::endl;
		exit(1);
	}
	else if (res[j].find("max_client_body_size") != std::string::npos) 
	{
		std::string tmp(&res[j][22]);
		std::vector<std::string> max_body_size = ft_split(tmp, " ");
		if(max_body_size.size() != 1)
		{
			std::cerr << "expecting one argument after max_client_body_size" << std::endl;
			return (1);
		}
		else if (check_int1(max_body_size[0]))
			std::cerr << "Bad size it seems" << std::endl;
		this->max_client_body_size = tmp;
	}
	(void)nbligne;
	return (0);
}
