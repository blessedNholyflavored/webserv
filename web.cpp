#include <iostream>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <sys/wait.h>
#include <fstream>
#include <fcntl.h>
#include <dirent.h>
#include <vector>
#include <cmath>
#include <arpa/inet.h>
#include "includes/server.hpp"
#include "includes/functions.h"


#define MAX_EVENTS 4096

static int error = 0;
static std::string	split[250000];
static std::string	newfile[5];
static	int	nbfiles = 0;
static	int	ext = 0;
static char *bufall;
static int lenall;

char	**Server::ft_regroup_envVector(std::vector<char *> vec)
{
	char **res;
	int i = 0;

	res = (char **)malloc(sizeof(char*) * (vec.size() + 1));
	std::vector<char *>::iterator it = vec.begin();
	for (; it != vec.end(); it++)
	{
		res[i] = (char *)*it;
		i++;
	}
	res[i] = NULL;
	return res;
}

void	freeTab2(char **tab)
{
	int i = 0;

	while (tab[i])
	{
		if (tab[i])
		{
			free(tab[i]);
		}
		i++;
	}
	free(tab);
	tab = NULL;
}

void	freeTab(char **tab)
{
	int i = 0;

	while (tab[i])
	{
		if (tab[i])
		{
			//printf("TAB[i] = %s\n", tab[i]);
			//free(tab[i]);
		}
		i++;
	}
	free(tab);
	tab = NULL;
}

std::string	Server::basicsummary(std::string filePath)
{
	static	std::string old;

	std::stringstream auto_index;
	auto_index.str(filePath);
	DIR*			dirp;
	struct dirent*	direntp;

	auto_index <<  "	<body style=\"background-color: grey; color: lightgrey;\">\n\
		<div style=\"display: flex; flex-direction: column; align-items: center; justify-content: center; \">\n\
		<h1>Auto Index</h1>\n";
	if ((dirp = opendir(filePath.c_str())) != NULL)
	{
		while((direntp = readdir(dirp)) != NULL)
		{
			std::string test = direntp->d_name;
			if (test != "." && test != "..")
			{
				if (is_directory(filePath + '/' + test))
				{
					test += '/';
				}
				if (is_directory(this->newIndex) && newIndex[newIndex.size() - 1] != '/')
					newIndex += '/';
				auto_index << "<p><a href=\"" << test << "\" class=\"active\">" << test << "</a></p>\n";
			}

		}
		closedir (dirp);
	}
	auto_index << "	</div>\n\
		</body>\n\
		</html>";
	error = 200;
	return auto_index.str();
}


void	createlinfkFile(std::string &index, int i)
{
	index += "<h4>";
	index += "File " + intToString(i) + ":";
	index += "<a href=\"";
	index += newfile[i - 1];
	index += "\">";
	index += newfile[i - 1];
	index += "</a>";
	index += "</h4>\n";
}

void	CreateFile(std::string filepath)
{
	int i = checkBuffBoundary2(bufall);
	int count = 0;
	while (bufall[i])
	{
		if (bufall[i] == '\n')
			count++;
		if (count == 4)
			break;
		i++;
	}
	char *wrt = bufall + i + 1;
	wrt[ft_strlen(wrt)] = 0;
	std::string conca = "images/" + filepath;
	int check = open(conca.c_str(), O_RDONLY, 0644);
	if (check >= 0)
	{
		close(check);
		return;
	}
	int o = open(conca.c_str(), O_CREAT | O_WRONLY, 0644);
	write(o, wrt, lenall);
	close(o);
}

void	Server::splitString(const char *buf, std::string deli, int fd, int ret, std::string buffer)
{
	(void)fd;
	(void)buffer;
	std::string str(buf);
	int start = 0;
	int end = str.find(deli);
	std::string	arr[5];
	int	i = 0;
	while (end != -1)
	{
		arr[i] = str.substr(start, end - start);
		start = end + deli.size();
		end = str.find(deli, start);
		i++;
	}
	arr[i] = str.substr(start, end - start);
	if ((arr[0].compare(0, 24, "------WebKitFormBoundary") == 0 || checkBuffBoundary(buffer) == 0) && error != 888 && lenall)
	{
		if (ParseBufferupl(buffer) == 413)
		{
			return ;
		}
	}
	if (arr[1].compare("/") != 0 && arr[0].compare("GET") == 0 && arr[1].compare("/html/text.php")
			&& arr[1].compare("/html/galerie.php"))
	{
		std::ifstream file(arr[1].c_str() + 1, std::ios::in);
		if (!file && open(arr[1].c_str() + 1, O_DIRECTORY) == -1)
		{
			this->newIndex = arr[1];
			std::vector<Location>::iterator it = location.begin();
			for (; it != location.end(); it++)
			{
				if (this->newIndex.length() <= 1 && (*it).getLocation().length() > 0 && (*it).getIndex().length() > 0)
					this->newIndex = this->root + (*it).getIndex();
				if (arr[1] == (*it).getLocation() && (*it).getIndex().length() > 1)
					this->newIndex = this->root + (*it).getIndex();
			}
			if (arr[1].compare(0, 12, "/reponse.php") == 0
					|| arr[1].compare(0, 17, "/html/reponse.php") == 0)
				error = 999;
			else if (arr[0].compare("POST") && arr[1].compare(0, 21, "/html/upload_img.php") == 0)
				error = 996;
			else if (this->loc.getIndex().length() == 0 && this->loc.getAuto() == 1)
				error = -7;
		}
		else if (open(arr[1].c_str() + 1, O_DIRECTORY) > 0)
		{
			this->newIndex = basicsummary(arr[1].substr(1, arr[1].length()));
			error = -99;
		}
		else
		{
			this->newIndex = arr[1].substr(1, arr[1].length());
			error = 200;
		}
	}
	else if (arr[0].compare("POST") == 0 || arr[1].compare("/html/text.php") == 0 || arr[1].compare("/html/galerie.php") == 0)
	{
		std::string recup = "." + arr[1];
		recup = execFile(recup);
		error = 54;
	}
	if (arr[0].compare("GET") == 0 && arr[1].compare(0, 16, "/html/py/post.py") == 0)
	{
		error = 63;
	}
	if ((arr[0].compare("GET") == 0 || arr[0].compare("POST") == 0) && (arr[1].compare(0, 16, "/html/upload.php") == 0) && error != 413)
	{
		std::string recup = "." + arr[1];
		recup = execFile(recup);
		error = 53;
	}
	if (arr[0].compare("POST") == 0 && (arr[1].compare("/html/text.php") == 0
				|| arr[1].compare("/html/galerie.php") == 0))
	{
		error = 998;
	}

	else if (arr[0].compare("DELETE") == 0 && ret != 405)
	{
		unlink(arr[1].c_str() + 1);
		error = 888;
	}
	if (arr[1].length() <= 1 || this->newIndex == "/favicon.ico")
		this->newIndex = "./html/home.html";
}


int	ParseBufferupl(std::string buffer)
{
	if (lenall > 50000 || error == 888)
	{
		error = 413;
		return (413);
	}
	splitRet(buffer, "\n");
	std::string filename;
	int i = 0;
	int	l = 0;
	for (i = 0; i < 50000; i++)
	{
		if (split[i].length() > 0 && split[i].compare(0, 20, "Content-Disposition:") == 0)
		{
			filename = splitRetVal(split[i], " ");

			for (int k = 0; k < (int)filename.length(); k++)
			{     
				if (filename[k] == '=' && filename[k + 1] == '"')
				{
					l = k + 2;
					break ;
				}
			}
		}
	}
	std::string recup = filename.substr(l, filename.length() - 2);
	char *test = ft_strdup((char *)recup.c_str());
	test[ft_strlen(test) - 2] = 0;
	recup = test;
	free(test);
	if (recup.length() > 0)
	{
		CreateFile(recup);
	}
	return 0;
}

void	Server::CheckRequest(char *buffer, int fd, int ret)
{
	std::string cpy(buffer);
	std::string	test;
	int	l = 0;
	while (buffer[l] != '\n' && buffer[l])
		l++;
	test = cpy.substr(0, l);
	l = 0;
	int	space = 0;
	std::string res(test);
	while (test[l])
	{
		if (test[l] == ' ')
			space++;
		l++;
	}
	splitString(test.c_str(), " ", fd, ret, buffer);
}


std::string	splitRetVal(std::string str, std::string deli)
{
	int start = 0;
	int end = str.find(deli);
	int     i = 0;
	std::string	ret;
	while (end != -1)
	{
		ret = str.substr(start, end - start);
		start = end + deli.size();
		end = str.find(deli, start);
		i++;
	}
	ret = str.substr(start, end - start);
	return (ret);
}




void	splitRet(std::string str, std::string deli)
{
	int start = 0;
	int end = str.find(deli);
	int     i = 0;
	while (end != -1)
	{
		split[i] = str.substr(start, end - start);
		start = end + deli.size();
		end = str.find(deli, start);
		i++;

	}
	split[i] = str.substr(start, end - start);
}

int	Server::init_serv(void)
{
	struct	sockaddr_in address;
	struct	epoll_event event;
	int	on = 0;

	if ((this->server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		std::cerr << "Error in socket" << std::endl;
		return (1);
	}
	if (setsockopt(this->server_fd, SOL_SOCKET, SO_REUSEPORT, &on, sizeof(int)) == -1)
		return (close(this->server_fd), perror("Setsockopt failed"), -1);
	if (fcntl(this->server_fd, F_SETFL, O_NONBLOCK) == -1)
		return (close(this->server_fd), perror("Fcntl failed"), -1);
	address.sin_family= AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(this->port);
	memset(address.sin_zero, '\0', sizeof address.sin_zero);
	if (bind(this->server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
	{
		std::cerr << "Error in bind" << std::endl;
		return (1);
	}
	if (listen(this->server_fd, 10) < 0)
	{
		std::cerr << "Error in listen" << std::endl;
		return (1);
	}
	event.events = EPOLLIN;
	event.data.fd = this->server_fd;
	this->addrstruct = address;
	epoll_ctl(this->epoll_fd, EPOLL_CTL_ADD, this->server_fd, &event);
	return (0);
}

int	Server::newConnection(struct epoll_event event, int fd)
{
	fd = accept(fd, NULL, NULL);
	if (fd < 0)
		return (close(this->server_fd), perror("error in acept new connec"), -1);
	if (fcntl(fd, F_SETFL, O_NONBLOCK) == -1)
		return (close(fd), perror("Fcntl failed"), -1);
	event.events = EPOLLIN;
	event.data.fd = fd;
	epoll_ctl(this->epoll_fd, EPOLL_CTL_ADD, fd, &event);
	return (0);
}

std::string	checkRet(int ret)
{
	std::string str;
	if (ret == 775)
		return (fileToString("./html/405.html"));
	if (ret == 404)
		return (fileToString("./html/404.html"));
	if (ret == 413)
		return (fileToString("./html/413.html"));
	else
		return str;
}

int	checkConnection(char buff[50001])
{
	splitRet(buff, "\n");
	int i = 0;
	for (i = 0; i < 50001; i++)
	{
		if (split[i].length() > 0 && split[i].compare(0, 17, "Connection: close") == 0)
			return (1);
	}
	return 0;
}


int	Server::recvConnection(int fd)
{
	ssize_t	len;
	char	buff[50001];

	if (nbfiles == 76)
	{
		this->newIndex = FirstPage("./html/403.html"); // page a creer
		if (intToString(this->newIndex.length()) > max_client_body_size)
		{
			error = 413;
		}
		std::string header = "HTTP/1.1 404 NOT FOUND\nContent-type: text/html; charset=UTF-8\nContent-Length: " + intToString(this->newIndex.length()) + "\n\n" + this->newIndex + "\n";
		if(send(fd, header.c_str(), header.length(), 0) <= 0)
		{
			close(fd);
			return (0);
		}
		nbfiles = 0;
	}
	if (nbfiles == 666)
	{
		if (intToString(this->newIndex.length()) > max_client_body_size)
		{
			error = 413;
		}
		std::string header = "HTTP/1.1 200 OK\nContent-type: text/html; charset=UTF-8\nContent-Length: " + intToString(this->newIndex.length()) + "\n\n" + this->newIndex + "\n";
		if(send(fd, header.c_str(), header.length(), 0) <= 0)
		{
			close(fd);
			return (0);
		}
		nbfiles = 0;
	}
	len = recv(fd, buff, 50001, 0);
	if (len > 0)
		printf("BUFF in recv:\n%s\n", buff);
	int	ret = 0;
	bufall = buff;
	lenall = len;
	
	request = new Request;
	ret = request->parsRequest(buff, this->location, *this);
	delete request;
	if (lenall > (int)std::atof(this->max_client_body_size.c_str()))
		ret = 413;
	if (!ret || ret == 200)
		CheckRequest(buff, fd, ret);
	if (!ret)
		ret = error;
	if (ret && ret != 200)
	{
		std::string header = recupHeader(ret, this->newIndex);
		if(send(fd, header.c_str(), header.length(), 0) <= 0)
		{
			close(fd);
			//return (0);
		}
		error = 0;
		ret = 0;
	}
	else if (error == 999)
	{
		std::string str1 = execPOST();
		std::string header;
		header = "HTTP/1.1 200 OK\nContent-type: text/html; charset=UTF-8\nContent-Length: " + intToString(str1.length()) + "\n\n" + str1 + "\n";
		if(send(fd, header.c_str(), header.length(), 0) <= 0)
		{
			close(fd);
			return (0);
		}	
	}
	else if (error == 63)
	{
		std::string str1 = execGETpy();
		std::string header;
		header = "HTTP/1.1 200 OK\nContent-type: text/html; charset=UTF-8\nContent-Length: " + intToString(str1.length()) + "\n\n" + str1 + "\n";
		if(send(fd, header.c_str(), header.length(), 0) <= 0)
		{
			close(fd);
			return (0);
		}
	}
	else if (error == 998)
	{
		int fd1;

		this->vectorenv.push_back((char *)("REQUEST_METHOD=POST"));
		this->vectorenv.push_back((char *)("REMOTE_HOST=localhost"));
		this->vectorenv.push_back((char *)"PATH_INFO=html/text.php");
		this->vectorenv.push_back((char *)"PATH_TRANSLATED=html/text.php");
		this->vectorenv.push_back((char *)"SCRIPT_NAME=html/text.php");
		this->vectorenv.push_back((char *)"SCRIPT_FILENAME=html/text.php");
		char	**cmd = new char*[3];
		cmd[0] = strdup("/usr/bin/php-cgi");
		cmd[1] = strdup("html/text.php");
		cmd[2] = 0;
		int i = 0 ;
		int agent = 0;
		char **recup = ft_split(buff, '\r');
		i = 0;
		while (recup[i])
		{
			char *str = ft_strdup(recup[i] + 1);
			free(recup[i]);
			recup[i] = ft_strdup(str);
			free(str);
			if (strncmp(recup[i], "User-Agent", 10) == 0)
				agent = i;
			if (strncmp(recup[i], "textToUpload", 12) == 0)
				break ;
			i++;
		}
		std::string res = recup[agent];
		std::string strAgent = "USER_AGENT=" + res;
		this->vectorenv.push_back((char *)strAgent.c_str());
		int tmp = open(".tmp", O_CREAT | O_WRONLY | O_TRUNC, 0666);
		write(tmp, recup[i], strlen(recup[i]));
		lseek(tmp, 0, SEEK_SET);
		fd1 = open("lucieCGI", O_CREAT | O_RDONLY | O_WRONLY | O_TRUNC, 0666);
		if (ft_strlen(recup[i]) > ft_atoi(max_client_body_size.c_str()))
		{
			error = 413;
		}
		std::string len = "CONTENT_LENGTH=" + intToString(ft_strlen(recup[i]));
		res = recup[i];
		std::string query = "QUERY_STRING=" + res;
		query = "QUERY_STRING=";
		this->vectorenv.push_back((char *)query.c_str());
		this->vectorenv.push_back((char *)len.c_str());
		this->env = ft_regroup_envVector(this->vectorenv);
		int frk = fork();
		if (frk == 0)
		{
			dup2(tmp, 0);
			close(tmp);
			dup2(fd1, 1);
			close(fd1);
			execve("/usr/bin/php-cgi", cmd, this->env);
		}
		else
			wait(NULL);
		freeTab2(recup);
		if (this->env)
			freeTab(this->env);
		free(cmd[0]);
		free(cmd[1]);
		delete [] cmd;
		std::string str1 = FirstPage("lucieCGI");
		std::string skip = "Content-type: text/html; charset=UTF-8 ";
		str1 = str1.substr(skip.length(), str1.length());
		if (((int)str1.length())  > ft_atoi(max_client_body_size.c_str()))
		{
			error = 413;
		}
		std::string header = "HTTP/1.1 200 OK\nContent-type: text/html; charset=UTF-8\nContent-Length: " + intToString(str1.length()) + "\n\n" + str1 + "\n";
		//close(lucieCGI);
		close(tmp);
		unlink("lucieCGI");
		unlink(".tmp");
		this->vectorenv.clear();
		this->vectorenv = this->vectorenvcpy;
		if(send(fd, header.c_str(), header.length(), 0) <= 0)
		{
			close(fd);
			return (0);
		}
	}
	else if (error == -99)
	{
		std::string header = "HTTP/1.1 200 OK\nContent-type: text/html; charset=UTF-8\nContent-Length: " + intToString(this->newIndex.length()) + "\n\n" + this->newIndex + "\n";
		if(send(fd, header.c_str(), header.length(), 0) <= 0)
		{
			close(fd);
			return (0);
		}
		error = 0;
	}
	else if (error == -7)
	{
		std::string str1 = basicsummary(this->cwd);
		std::string header = "HTTP/1.1 200 OK\nContent-type: text/html; charset=UTF-8\nContent-Length: " + intToString(str1.length()) + "\n\n" + str1 + "\n";
		if(send(fd, header.c_str(), header.length(), 0) <= 0)
		{
			close(fd);
			return (0);
		}
	}
	else
	{
		std::string str1;
		if (error == 54)
		{
			str1 = fileToString("lucieCGI");
			std::string skip = "Content-type: text/html; charset=UTF-8 ";
			str1 = str1.substr(skip.length(), str1.length());
			//close(lucieCGI);
			unlink("lucieCGI");
			error = 0;
		}
		else if (error == 53)
		{
			str1 = fileToString("lucieCGI");
			std::string skip = "Status: 500 Internal Server Error\n";
			skip += "Content-type: text/html; charset=UTF-8 ";
			str1 = str1.substr(skip.length(), str1.length());
			//close(lucieCGI);
			unlink("lucieCGI");
			error = 0;
		}
		else
			str1 = FirstPage(this->newIndex);
		if (((int)str1.length())  > ft_atoi(max_client_body_size.c_str()))
		{
			error = 413;
		}
		std::string header = "HTTP/1.1 200 OK\nContent-type: text/html; charset=UTF-8\nContent-Length: " + intToString(str1.length()) + "\n\n" + str1 + "\n";
		if(send(fd, header.c_str(), header.length(), 0) <= 0)
		{
			//close(fd);
			//		return (0);
		}
	}
	if (checkConnection(buff))
		close(fd);
	return (0);
}

int	Server::sendConnection(int fd)
{
	static int a;
	if (a == 0)
	{
		std::string str1 = FirstPage(this->newIndex);
		if ((int)str1.length() > ft_atoi(max_client_body_size.c_str()))
		{
			error = 413;
		}
		std::string header = "HTTP/1.1 200 OK\nContent-type: text/html; charset=UTF-8\nContent-Length: " + intToString(str1.length()) + "\n\n" + str1 + "\n";
		if(send(fd, header.c_str(), header.length(), 0) <= 0)
		{
			close(fd);
			return (0);
		}
	}
	a = 1;
	return (0);
}	

int	Server::event_receptor(struct epoll_event events[5], int event_count)
{
	for (int i = 0; i < event_count; i++)
	{
		if (events[i].data.fd == this->server_fd)
			newConnection(events[i], events[i].data.fd);
		else if (events[i].events == EPOLLIN)
			recvConnection(events[i].data.fd);
		else if (events[i].events == EPOLLOUT)
			sendConnection(events[i].data.fd);
	}
	return (0);
}





void	handler(int sig)
{
	if (sig == 2)
	{
		ext = 1;
	}
}

void	StartServer(Server server)
{
	int	event_count;
	struct	epoll_event events[5];

	Server array[server.nbport.size()];
	int i = 0;
	int len = server.nbport.size();
	std::vector<int>::iterator portIT = server.nbport.begin();
	std::vector<std::string>::iterator indexIT = server.index.begin();
	std::vector<int>::iterator autoindexIT = server.vectorauto.begin();
	std::vector<std::string>::iterator rootIT = server.vectorroot.begin();
	std::vector<std::string>::iterator nameIT = server.vectorname_server.begin();
	for(; portIT != server.nbport.end(); portIT++)
	{
		array[i].port = *portIT;
		if (nameIT <= server.vectorname_server.end() && server.vectorname_server.size() > 0)
		{
			array[i].name_server = *nameIT;
			nameIT++;
		}
		if (autoindexIT <= server.vectorauto.end() && server.vectorauto.size() > 0)
		{
			array[i].autoindex = *autoindexIT;
			autoindexIT++;
		}
		if (rootIT <= server.vectorroot.end() && server.vectorroot.size() > 0)
		{
			array[i].root = *rootIT;
			rootIT++;
		}
		if (indexIT <= server.index.end() && server.index.size() > 0)
		{
			array[i].nom_index = *indexIT;
			indexIT++;
		}
		array[i].epoll_fd = epoll_create1(0);
		array[i].vectorenv = server.vectorenv;
		array[i].vectorenvcpy = server.vectorenvcpy;
		array[i].cwd = server.cwd;
		if (server.max_client_body_size.length() > 0)
			array[i].max_client_body_size = server.max_client_body_size;
		else
			array[i].max_client_body_size = "999999999";
		if (array[i].init_serv())
			return ;
		array[i].newIndex = "";
		if (array[i].autoindex)
		{
			if (array[i].nom_index.length() == 0)
			{
				std::string tmp;
				array[i].newIndex = array[i].basicsummary(server.cwd);
				nbfiles = 666;
			}
			else
			{
				array[i].newIndex = (array[i].nom_index).substr(1, array[i].nom_index.length()); 
				array[i].newIndex = "";
				array[i].newIndex = array[i].root +  "/" + array[i].newIndex;
			}
		}
		else
		{
			if (array[i].nom_index.length() == 0)
			{
				nbfiles = 76;
			}
			else
			{
				array[i].newIndex = (array[i].nom_index).substr(1, array[i].nom_index.length()); 
				array[i].newIndex = array[i].root +  "/" + array[i].newIndex;

			}
		}
		array[i].parsLoc(i);
		array[i].env = NULL;
		i++;
	}
	while (1)
	{
		signal(SIGINT, handler);
		for (i = 0; i < len; i++)
		{
			if (ext == 1)
			{
				return ;
			}
			event_count = epoll_wait(array[i].epoll_fd, events, 5, 1000);
			if (event_count < 0)
			{
				fprintf(stderr, "error in epoll_wait\n");
				return ;

			}
			if (event_count > 0)
				array[i].event_receptor(events, event_count);
			array[i].vectorenv.clear();
			array[i].vectorenv = array[i].vectorenvcpy;
			error = 0;
		}
	}
}

