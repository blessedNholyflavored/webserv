#include "server.hpp"
#include "inc.hpp"

Server::Server() //: max_client_body_size(4096), listen_fd(0)
{
	max_client_body_size = 0;
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

int Server::parser_le_server(std::string res[], size_t *nbligne, int j)
{
	res[j] = c_trop_complik(res[j]);
		// if (res[j][0] != '}')
		// 	std::cout <<"\t" << res[j][0] << ":" << std::endl;
		// if (res[j][0] == '}')
		// {
		// 	// (*nbligne)++;
		// 	break;
		// }
		// else if (ligne[0] == "location")
		// {

		// }
		if (!res[j].compare(0, 12, "\tserver_name"))
		{
			if (static_cast<std::string>(&res[j][13]).size() < 2)
				{
					std::cerr << "expecting at least 1 argument after 'server_name' "<< std::endl;
					exit(1);
				}
			this->name_server = (res[j].c_str() + 13);
			std::cout << this->name_server <<std::endl;
		}
		// else if (line[0] == "listen")
		// {

		// }
		// else if (line[0] == "index")
		// {
			
		// }
		else if (!res[j].compare(0, 5, "\troot"))
		{
			if (static_cast<std::string>(&res[j][6]).size() == 1) // empty
				std::cerr << "excepeting one argument after root"<< std::endl;
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