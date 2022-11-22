#include "server.hpp"
#include "inc.hpp"

Server::Server() //: max_client_body_size(4096), listen_fd(0)
{
	max_client_body_size = 0;
	port = 0;
	// root = NULL;
	// name_server = NULL;
}

Server::~Server()
{
	// std::cout << "KILLING SERVER" << std::cout;
	// //close(listen_fd);
	// std::cout << "bye" << std::cout;
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
	size_t nbline = 0;
	while(nbline < content.size())
	{
		ft_split1(content, "\n");
		if (res[0] == "server {")
		{
			this->parser_le_server(res, &nbline, j);
		}
		j++;
		nbline++;
	}
	return 0;
}

std::string c_trop_complik(std::string res)
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


// std::vector<std::string> ft_split(const std::string &str, const std::string &charset)
// {
// 	std::vector<std::string> res;
// 	std::string 	tmp;
// 	size_t			i;

// 	i = 0;
// 	std::cout << str << std::endl;
// 	while (i < str.length())
// 	{
// 		while (i < str.length() && ft_in_charset1(str[i], charset))
// 			i++;
// 		if (i < str.length())
// 		{
// 			tmp = "";
// 			while (i < str.length() && !ft_in_charset1(str[i], charset))
// 				tmp += str[i++];
// 			std::cout << "tmp" << str[i] << std::endl;
// 			res.push_back(tmp);
// 		}
// 	}
// 	return res;
// }

std::vector<std::string> ft_split(std::string str, std::string deli)
{
	std::vector<std::string> res;

		int start = 0;
        int end = str.find(deli);
        int     i = 0;
        while (end != -1)
        {
                //std::cout << "IN SPLIT: " << str.substr(start, end - start) << std::endl;
                res.push_back(str.substr(start, end - start));
                start = end + deli.size();
                end = str.find(deli, start);
                i++;
        }
        res.push_back(str.substr(start, end - start));
		return (res);
}

int Server::parser_le_server(std::string res[], size_t *nbligne, int j)
{
	// static int count = 0;
	res[j] = c_trop_complik(res[j]);
		// if (res[j][0] != '}')
		// 	std::cout <<"\t" << res[j][0] << ":" << std::endl;
		// if (res[j][0] == '}')
		// {
		// 	// (*nbligne)++;
		// 	break;
		// }
		//if (!res[j].compare(0, 9, "\tlocation"))
		// if (static_cast<std::string>(&res[j][9]).size() != 3)
		// {
		// 	std::cerr << "il faut deux arguments apres location mec "<< std::endl;
		// }
		if (!res[j].compare(0, 12, "\tserver_name"))
		{
			if (static_cast<std::string>(&res[j][13]).size() < 2)
				{
					std::cerr << "expecting at least 1 argument after 'server_name' "<< std::endl;
					//exit(1);
				}
			this->name_server = (res[j].c_str() + 13);
		}
		// else if (!res[j].compare(0, 7, "\tlisten"))
		// {
			
		// 	if (static_cast<std::string>(&res[j][7]).size() == 1) // empty
		// 		std::cerr << "expecting one argument after listen"<< std::endl;
		// 	std::string tmp;
		// 	tmp = (static_cast<std::string>(&res[j][7]));
		// 	std::vector<std::string> listen = ft_split(tmp, ":");
		// 	if (listen.size() != 1 && listen.size() != 2)
		// 		std::cerr << "il faut port ou adress:port apres le listen" << std::endl;
		// 	std::string address;
		// 	std::string port;
		// 	address = tmp[0];
		// 	if (listen.size() == 1)
		// 	{
		// 		address = "0.0.0.0";
		// 		port = listen[0];
		// 	}
		// 	else
		// 		port = listen[1];
		// 	if (address == "localhost")
		// 		address = "127.0.0.1";
		// 	this->ip = address;
		// 	if (!check_int(port))
		// 		std::cerr << "port should be an int" << std::endl;
		// 	this->port = atoi(port.c_str());
		// }
		else if (!res[j].compare(0, 11, "\terror_page"))
		{
			std::string tmp;
			tmp = (static_cast<std::string>(&res[j][11]));
			
			std::vector<std::string> error_page_tmp = ft_split(tmp, " ");
			if (error_page_tmp.size() != 3)
				std::cerr << "expecting two arguments after error_page"<< std::endl;
			else 
			{
				this->error_name.push_back(error_page_tmp[1]);
				this->error_page.push_back(error_page_tmp[2]);
			}
			// 	std::cout << "name1:" << error_name[0] << std::endl;
			// 	std::cout << "page1:" << error_page[0] << std::endl;
			// if (error_page.size() > 1)
			// {
			// 	std::cout << "name2:" << error_name[1] << std::endl;
			// 	std::cout << "page2:" << error_page[1] << std::endl;
			// }	
		}
		else if (!res[j].compare(0, 4, "\tcgi"))
		{
			std::string tmp;
			tmp = (static_cast<std::string>(&res[j][4]));
			std::vector<std::string> cgi = ft_split(tmp, " ");
			if (cgi.size() != 3)
				std::cerr << "expecting two arguments after cgi"<< std::endl;
			else 
			{
				this->cgi_exec.push_back(cgi[1]);
				this->cgi_address.push_back(cgi[2]);
			}
		}
		else if (!res[j].compare(0, 6, "\tindex"))
		{
			if (static_cast<std::string>(&res[j][6]).size() < 3) // empty
			{
				std::cerr << "expecting one argument after index"<< std::endl;
			}
			this->index =  (res[j].c_str() + 6);
		}
		else if (!res[j].compare(0, 5, "\troot"))
		{
			if (static_cast<std::string>(&res[j][6]).size() == 1) // empty
				std::cerr << "expecting one argument after root"<< std::endl;
			std::string tmp = (static_cast<std::string>(&res[j][6]));
			if (tmp.size() > 0 && tmp[0] == '/')
				tmp = tmp.substr(1);
			if (tmp.size() > 1 && tmp[tmp.size() - 1] == '/')
				tmp.resize(tmp.size() - 1);
			this->root = (tmp.c_str());
		}
		else if (!res[j].compare(0, 21, "\tmax_client_body_size"))
		{
			if (static_cast<std::string>(&res[j][22]).size() == 1)		
				std::cerr << "expecting one argument after max_client_body_size" << std::endl;
			else if (!check_int(&res[j][22]))
				std::cerr << "mauvais int de taille " << std::endl;
			this->max_client_body_size = std::atof((res[j].c_str() + 22));

		}
		(void)nbligne;
		
		return (0);
}