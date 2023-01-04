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
#include "server.hpp"
#include "functions.h"
#include <cmath>


#define MAX_EVENTS 5

static int error = 0;
//static std::string  newIndex = "";
static std::string	split[4096];
static std::string	newfile[5];
static	int	nbfiles = 0;
static	int	statusfile = 0;

char	**ft_regroup_envVector(std::vector<char *> vec)
{
	char **res;
	int i = 0;
	
	res = (char **)malloc(sizeof(char*) * (vec.size() + 1));
	std::vector<char *>::iterator it = vec.begin();
	for (; it != vec.end(); it++)
	{
		res[i] = (char *)*it;
		//printf("REGROUP: %s\n", res[i]);
		i++;
	}
	res[i] = 0;
	return res;
}

void	freeTab(char **tab)
{
	int i = 0;
	
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

std::string	fileToString(std::string loc);
std::string     intToString(int i);
std::string	basicsummary(std::string filePath);

void	Server::splitString(const char *buf, std::string deli, int fd)
{
	(void)fd;
	std::string str(buf);
	std::cout << "STARTSPLIT:" << str << std::endl;
	int start = 0;
	int end = str.find(deli);
	std::string	arr[5];
	int	i = 0;
	while (end != -1)
	{
		//std::cout << "IN SPLIT: " << str.substr(start, end - start) << std::endl;
		arr[i] = str.substr(start, end - start);
		start = end + deli.size();
		end = str.find(deli, start);
		i++;
	}
	arr[i] = str.substr(start, end - start);
	std::cout << "SPLIT = " << arr[1] << std::endl;
//	std::cout << "IN SPLIT: " << str.substr(start, end - start) << std::endl;
	if (arr[1].compare("/") != 0 && arr[0].compare("GET") == 0 && arr[1].compare("/html/text.php")
			&& arr[1].compare("/html/galerie.php"))
	{
		//arr[1] = "./html" + arr[1];
		std::ifstream file(arr[1].c_str() + 1, std::ios::in);
		if (!file && open(arr[1].c_str() + 1, O_DIRECTORY) == -1)
		{
			std::cout << arr[1] << std::endl;
			std::cerr << "NO FILE" << std::endl;
			this->newIndex = arr[1];
			std::cout << "HYDRO CONARDDDDDDDDDDDDDDDDDDD: " << this->root + this->loc.getIndex() << std::endl;
			if (this->loc.getLocation().length() > 0 && this->loc.getIndex().length() > 0)
				this->newIndex = this->root + this->loc.getIndex();
			std::cout << "SALOOOOOOOOOOOP: " << this->newIndex << std::endl;
			if (arr[1].compare(0, 12, "/reponse.php") == 0
			|| arr[1].compare(0, 17, "/html/reponse.php") == 0)
				error = 999;
			if (this->loc.getIndex().length() == 0 && this->loc.getAuto() == 1)
				error = -7;

			//error = 404;
		}
		else if (open(arr[1].c_str() + 1, O_DIRECTORY) > 0)
		{
			std::cerr << "KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKk: " << arr[1] << std::endl;
			this->newIndex = basicsummary(arr[1].substr(1, arr[1].length()));
			error = -99;
		}
		else
		{
			this->newIndex = arr[1].substr(1, arr[1].length());
			std::cerr << "HEREEEEEEE this->newIndex: " << this->newIndex << std::endl; 
			error = 200;
		}
	}
	else if (arr[0].compare("POST") == 0 || arr[1].compare("/html/text.php") == 0 || arr[1].compare("/html/galerie.php") == 0)
	{
		std::string recup = "." + arr[1];
		recup = execFile(recup);
		error = 54;
	}
	if (arr[0].compare("POST") == 0 && (arr[1].compare("/html/text.php") == 0
			|| arr[1].compare("/html/galerie.php") == 0))
		error = 998;
	else if (arr[0].compare("DELETE") == 0)
		unlink(arr[1].c_str() + 1);
	std::cerr << "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb: " << this->newIndex << std::endl;
	 //if (this->newIndex == "./" || this->newIndex == "/" || this->newIndex == "/favicon.ico")
	 if (this->newIndex.length() <= 1 || this->newIndex == "/favicon.ico")
	 	this->newIndex = "./html/home.html";
	
	std::cerr << "kgdfvbdfvsdffvsfvrfrfdvrfvifffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff: " << error << "\n";
}


void	Server::CheckRequest(char *buffer, int fd)
{
	std::string cpy(buffer);
	std::string	test;
	int	l = 0;
	while (buffer[l] != '\n' && buffer[l])
		l++;
	test = cpy.substr(0, l);
	l = 0;
	int	space = 0;
	printf("test[l] = %s\n", test.c_str());
	while (test[l])
	{
		if (test[l] == ' ')
			space++;
		l++;
	}
	if (space != 2)
	{
		printf("SPACE = %d\n", space);
		std::cout << "BUFFER:" << buffer << std::endl;
		exit (0);
	}
		//printf("BEFORESPLIT: %s\n", test.c_str());
		splitString(test.c_str(), " ", fd);
}

std::string	intToString(int i)
{
	std::string res;
	std::stringstream recup;
	recup << i;
	recup >> res;
	return res;
}



std::string Server::FirstPage(std::string filePath)
{
	(void)filePath;
	std::string		index;
	std::string		path;

	/*path = getcwd(buffer, PATH_MAX);
	path += "/";
	path += filePath;
	dirp = opendir(path.c_str());*/
	std::cerr << "FILEPATHHHHHHHHHHHHHHH: " << filePath << std::endl;
	if (filePath.find(".php") != std::string::npos
		|| filePath.find(".py") != std::string::npos)
	{
		index = execFile(filePath);
		index += "</body>";
		index += "</html>";
		return index;
	}
	
	std::string recup;
	std::ifstream findex(filePath.c_str());
	if (filePath.find(".png") != std::string::npos
		|| filePath.find(".jpeg") != std::string::npos
		|| filePath.find(".jpg") != std::string::npos)
	{
		std::string pdm = "./" + filePath;
		std::ifstream fin(pdm.c_str(), std::ios::in | std::ios::binary);
		std::ostringstream oss;
		oss << fin.rdbuf();
		std::string data(oss.str());
		int g = open("g.html", O_CREAT | O_WRONLY | O_TRUNC, 0644);
		index += data;
		write(g, index.c_str(), index.length());
	}
	else
	{
		while (getline(findex, recup))
			index += recup;
	}
	/*index += "<!DOCTYPE html>\n<html>\n\n<title>INDEX</title>\n\n<h1>INDEX</h1>";
	index += "<body id=\"all\">";
	index += "<form id=\"form\">";
	index += "<input type=\"file\" name=\"background\" />";
	index += "<button type=\"submit\">SEND</button>\n\n";
	index += "</form>";
	index += "<p id=\"message\"></p>";
	index += "<button id=\"btn\">test</button>\n\n";*/
	// for (int i = 0; i < 3 + nbfiles; i++)
	// {
	// 	index += "<h4>";
	// 	createLink(index, i);
	// 	index += "</h4>\n";
	// }
	//for (int i = 1; i <= nbfiles; i++)
	//	createlinfkFile(index, i);
	/*if( dirp != NULL )
	{
		int	i = 0;
        for(;;)
		{
            direntp = readdir( dirp );
            if ( direntp == NULL )
		break;
			index += "<h4>";
			if ( direntp->d_type == DT_DIR)
				index += "__Directory__| ";
			else if ( direntp->d_type == DT_REG)
				index += "_Regular file_| ";
			else
				index += "                ";
			createLink(index, direntp);
			index += "</h4>\n";
		}
		closedir( dirp );
	}*/
	//index += "<script src=\"upload.js\"></script>\n\n";
	index += "</body>";
	index += "</html>";
	return index;
}

std::string	splitRetVal(std::string str, std::string deli)
{
	int start = 0;
        int end = str.find(deli);
        int     i = 0;
	std::string	ret;
        while (end != -1)
        {
                //std::cout << "IN SPLIT: " << str.substr(start, end - start) << std::endl;
                ret = str.substr(start, end - start);
                start = end + deli.size();
                end = str.find(deli, start);
                i++;
        }
        ret = str.substr(start, end - start);
	return (ret);
}

void	CreateFile(void)
{
	//std::cout << "IN CREATEFILE:" << newfile[nbfiles] << std::endl;
	std::string conca = "Uploads/" + newfile[nbfiles];
	std::ofstream file(conca.c_str());
	newfile[nbfiles] = "Uploads/" + newfile[nbfiles];
	int i = 0;
	for (i = 0; i < 4096; i++)
	{
		if (split[i].compare(0, 13, "Content-Type:") == 0)
		{
			for(int h = i + 2; h < 4096; h++)
			{
				if (split[h + 1].compare(0, 24, "------WebKitFormBoundary") == 0)
					break;
				file << split[h] << std::endl;
			}
		}
	}
	statusfile = 1;
}


void	splitRet(std::string str, std::string deli)
{
	int start = 0;
        int end = str.find(deli);
        int     i = 0;
        while (end != -1)
        {
                //std::cout << "IN SPLIT: " << str.substr(start, end - start) << std::endl;
                split[i] = str.substr(start, end - start);
                start = end + deli.size();
                end = str.find(deli, start);
                i++;
        }
        split[i] = str.substr(start, end - start);
}

void	ParseBuffer(std::string buffer)
{
	splitRet(buffer, "\n");
	int i = 0;
	int	l = 0;
	std::cout << "START PRINT SPLIT" << std::endl;
	for (i = 0; i < 4096; i++)
	{
		if (split[i].length() > 0 && split[i].compare(0, 20, "Content-Disposition:") == 0)
		{
			std::string filename = splitRetVal(split[i], " ");
			for (size_t k = 0; k < filename.length(); k++)
			{
				if (filename[k] == '=' && filename[k + 1] == '"')
				{
					l = k + 2;
					break ;
				}
			}
			if (nbfiles < 5)
			{
				newfile[nbfiles] = filename.substr(l, filename.length() - 2);
				newfile[nbfiles].erase(newfile[nbfiles].length() - 2, newfile[nbfiles].length());
			}
			//std::cout << "SIZE =" << newfile.length();
			//std::cout << "SPLIT TEST:" << newfile << std::endl;
		}
	}
	if (newfile[nbfiles].length() > 0 && nbfiles < 5)
	{
		std::cout << "NBFILES=" << newfile[nbfiles] << std::endl;
		CreateFile();
		nbfiles++;
	}
	return ;
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
	if (setsockopt(this->server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &on, sizeof(int)) == -1)
		return (close(this->server_fd), perror("Setsockopt failed"), -1);
	if (fcntl(server_fd, F_SETFL, O_NONBLOCK) == -1)
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
	event.data.fd = this->server_fd;;
	epoll_ctl(this->epoll_fd, EPOLL_CTL_ADD, this->server_fd, &event);
	return (0);
}

int	Server::newConnection(struct epoll_event event, int fd)
{
	fd = accept(this->server_fd, NULL, NULL);
	if (fd < 0)
		std::cerr << "Error in accept new connec" << std::endl;
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
	else
		return str;
}

int	Server::recvConnection(int fd)
{
	ssize_t	len;
	char	buff[3000];

	std::cerr << "lllllllllllllllllllllllllllllllllllllllllllllllll: " << this->newIndex << std::endl;
	if (nbfiles == 76)
	{
		this->newIndex = FirstPage("./html/403.html"); // page a creer
		if (intToString(this->newIndex.length()) > max_client_body_size)
		{
			error = 413;
		}
		std::string header = "HTTP/1.1 404 NOT FOUND\nContent-type: text/html; charset=UTF-8\nContent-Length: " + intToString(this->newIndex.length()) + "\n\n" + this->newIndex + "\n";
		send(fd, header.c_str(), header.length(), 0);
		nbfiles = 0;
	}
	if (nbfiles == 666)
	{
		if (intToString(this->newIndex.length()) > max_client_body_size)
		{
			error = 413;
		}
		std::string header = "HTTP/1.1 200 OK\nContent-type: text/html; charset=UTF-8\nContent-Length: " + intToString(this->newIndex.length()) + "\n\n" + this->newIndex + "\n";
		send(fd, header.c_str(), header.length(), 0);
		nbfiles = 0;
	}
	len = recv(fd, buff, 3000, 0);
	if (len > 0)
		printf("BUFF in recv:\n%s\n", buff);
	int	ret = 0;
	request = new Request;
	std::cerr << "999999999999999999999999999999999999999999999999999: " << this->loc.getIndex() << std::endl;
	//ret = request->parsRequest(buff, this->location, this->loc);
//	this->newIndex = request->getPath();
//	if (this->newIndex == "./")
//		this->newIndex = "./html/home.html";
///	std::string firstline;
//	for (int index = 0; buff[index] != '\n'; index++){
//		firstline += buff[index];
//	}
	//this->splitString(firstline.c_str(), " ", fd);
//	if (request->getRetCode() == 400){
//		char str3[] = "bad version http";
//		write(fd, str3, ft_strlen(str3));
//	}
	std::cerr << "111111111111111111111111111111: " << error << std::endl;
	CheckRequest(buff, fd);
	std::cerr << "222222222222222222222222222222: " << error << std::endl;
	// else if (request->getRetCode() == 404)
	// {
	// 	printf("%d\n", error);
	// 	char str3[] = "HTTP/1.1 404 Not Found\nContent-Type: text/plain\nContent-Length: 19\n\n404 page not found\n";
	// 	write(fd, str3, strlen(str3));
	// }
	std::cerr << "RETTTTTT: " << ret << "\n";
	if (ret && ret != 200)
		this->newIndex = checkRet(ret);
	if (this->newIndex.length() > 1 && ret && ret != 200)
	{
		std::string header = "HTTP/1.1 200 OK\nContent-type: text/html; charset=UTF-8\nContent-Length: " + intToString(this->newIndex.length()) + "\n\n" + this->newIndex + "\n";
		send(fd, header.c_str(), header.length(), 0);
		return 0;
	}
	if (error == 999)
	{
		
		int fd1;
		this->vectorenv.push_back((char *)("REQUEST_METHOD=GET"));
		this->vectorenv.push_back((char *)"PATH_INFO=./reponse.php");
		this->vectorenv.push_back((char *)"PATH_TRANSLATED=./reponse.php");
		this->vectorenv.push_back((char *)"PATH_NAME=./reponse.php");
		this->vectorenv.push_back((char *)"SCRIPT_NAME=./reponse.php");
		this->vectorenv.push_back((char *)"SCRIPT_FILENAME=./reponse.php");
		std::string str1;// = fileToString(this->newIndex);
		std::string header;// = "HTTP/1.1 200 OK\nContent-type: text/html; charset=UTF-8\nContent-Length: " + intToString(str1.length()) + "\n\n" + str1 + "\n";
		char	**cmd = (char **)malloc(3);;
		cmd[0] = strdup("/usr/bin/php-cgi");
		cmd[1] = strdup("./reponse.php");
		cmd[2] = 0;
		int i = 0 ;
		char **recup = ft_split(this->newIndex.c_str(), '?');
		i = 0;
		while (recup[i])
		{
			if (strncmp(recup[i], "fname", 5) == 0)
				break ;
			i++;
		}
		int tmp = open(".tmp", O_CREAT | O_WRONLY | O_TRUNC, 0666);
		write(tmp, recup[i], ft_strlen(recup[i]));
		lseek(tmp, 0, SEEK_SET);
		fd1 = open("lucieCGI", O_CREAT | O_RDONLY | O_WRONLY | O_TRUNC, 0666);
		if (ft_strlen(recup[i]) > ft_atoi(max_client_body_size.c_str()))
			{
				error = 413;
			}
		std::string len = "CONTENT_LENGTH=" + intToString(ft_strlen(recup[i]));
		std::string res = recup[i];
		std::string query = "QUERY_STRING=" + res;
		this->vectorenv.push_back((char *)query.c_str());
		this->vectorenv.push_back((char *)len.c_str());
		this->env =  ft_regroup_envVector(this->vectorenv);
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
		str1 = fileToString("lucieCGI");
		std::string skip = "Content-type: text/html; charset=UTF-8 ";
		str1 = str1.substr(skip.length(), str1.length());
		if (intToString(str1.length())  > max_client_body_size)
		{
			error = 413;
		}
		header = "HTTP/1.1 200 OK\nContent-type: text/html; charset=UTF-8\nContent-Length: " + intToString(str1.length()) + "\n\n" + str1 + "\n";
		//unlink(".tmp");
		//unlink("lucieCGI");
		//freeTab(this->env);
		this->vectorenv.clear();
		this->vectorenv = this->vectorenvcpy;
		send(fd, header.c_str(), header.length(), 0);
	}
	else if (error == 998)
	{
		int fd1;

		std::cerr << "LAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAa\n";

		this->vectorenv.push_back((char *)("REQUEST_METHOD=POST"));
		this->vectorenv.push_back((char *)("REMOTE_HOST=localhost"));
		this->vectorenv.push_back((char *)"PATH_INFO=html/text.php");
		this->vectorenv.push_back((char *)"PATH_TRANSLATED=html/text.php");
		//this->vectorenv.push_back((char *)"PATH_NAME=html/text.php");
		this->vectorenv.push_back((char *)"SCRIPT_NAME=html/text.php");
		this->vectorenv.push_back((char *)"SCRIPT_FILENAME=html/text.php");
		char	**cmd = (char **)malloc(3);;
		cmd[0] = strdup("/usr/bin/php-cgi8.1");
		cmd[1] = strdup("html/text.php");
		cmd[2] = 0;
		int i = 0 ;
		int agent = 0;
		char **recup = ft_split(buff, '\r');
		i = 0;
		while (recup[i])
		{
			recup[i] = recup[i] + 1;
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
		i = 0;
		while (this->env[i])
		{
			printf("ENV: %s\n", this->env[i]);
			i++;
		}
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
		std::string str1 = FirstPage("lucieCGI");
		std::string skip = "Content-type: text/html; charset=UTF-8 ";
		str1 = str1.substr(skip.length(), str1.length());
		if (((int)str1.length())  > ft_atoi(max_client_body_size.c_str()))
		{
			error = 413;
		}
		std::string header = "HTTP/1.1 200 OK\nContent-type: text/html; charset=UTF-8\nContent-Length: " + intToString(str1.length()) + "\n\n" + str1 + "\n";
		//unlink("lucieCGI");
		unlink(".tmp");
		this->vectorenv.clear();
		this->vectorenv = this->vectorenvcpy;
		send(fd, header.c_str(), header.length(), 0);
	}
	else if (error == -99)
	{
		std::string header = "HTTP/1.1 200 OK\nContent-type: text/html; charset=UTF-8\nContent-Length: " + intToString(this->newIndex.length()) + "\n\n" + this->newIndex + "\n";
		send(fd, header.c_str(), header.length(), 0);
		error = 0;
	}
	else if (error == -7)
	{
		std::string str1 = basicsummary(".");
		std::string header = "HTTP/1.1 200 OK\nContent-type: text/html; charset=UTF-8\nContent-Length: " + intToString(str1.length()) + "\n\n" + str1 + "\n";
		send(fd, header.c_str(), header.length(), 0);
	}
	else
	{
		std::string str1;
		if (error == 54)
		{
			str1 = fileToString("lucieCGI");
			std::string skip = "Content-type: text/html; charset=UTF-8 ";
			str1 = str1.substr(skip.length(), str1.length());
			error = 0;
		}
		else
		str1 = FirstPage(this->newIndex);
		if (((int)str1.length())  > ft_atoi(max_client_body_size.c_str()))
		{
			error = 413;
		}
		std::string header = "HTTP/1.1 200 OK\nContent-type: text/html; charset=UTF-8\nContent-Length: " + intToString(str1.length()) + "\n\n" + str1 + "\n";
		send(fd, header.c_str(), header.length(), 0);
	}
	return (0);
}

int	Server::sendConnection(int fd)
{
	static int a;
	if (a == 0)
	{
		std::string str1 = FirstPage(this->newIndex);
		std::cout << "TESTTTT 1111 SENDCONNECTION" << this->newIndex << std::cout;

		if ((int)str1.length() > ft_atoi(max_client_body_size.c_str()))
		{
			error = 413;
		}
		std::string header = "HTTP/1.1 200 OK\nContent-type: text/html; charset=UTF-8\nContent-Length: " + intToString(str1.length()) + "\n\n" + str1 + "\n";
		send(fd, header.c_str(), header.length(), 0);
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

void	createlinfkFile(std::string &index, int i)
{
	//std::cout << "TTETTSTST:" << newfile[i] << std::endl;
	index += "<h4>";
	//index += "File " + std::to_string(i) + ":";
	index += "File " + intToString(i) + ":";
	index += "<a href=\"";
	index += newfile[i - 1];
	index += "\">";
	index += newfile[i - 1];
	index += "</a>";
	index += "</h4>\n";
}

bool is_directory(const std::string &filename)
{
	struct stat st_buf;
	int status = stat(filename.c_str(), &st_buf);
	if (status != 0) {
		return false;
	}
	return (S_ISDIR(st_buf.st_mode) == 1);
}

std::string	basicsummary(std::string filePath)
{
	DIR*			dirp;
	struct dirent*	direntp;
	std::string		index;
	//char			buffer[PATH_MAX];
	std::string		path;
	static	std::string old;

	//path = getcwd(buffer, PATH_MAX);
	//if (open(filePath.c_str(), O_DIRECTORY) >= 0)
	//	filePath += "/";
	//old = "";
	path = filePath;
	/*while (filePath.find("//") != std::string::npos)
	{
		filePath.erase(filePath.find("//"), 1);
	}
	std::cerr << "pooooooooooooooooooooooooooooooooooooooooooooooooooooooo: " << old << std::endl;
		//filePath = "/";
	if (filePath == "/")
		path = old;
	else
		path += filePath; // ici
	if (open(old.c_str(), O_DIRECTORY) >= 0)
		path = old + path;
	old = path;
	//path += "/";*/

	index += "<!DOCTYPE html>\n<html>\n\n<title>INDEX</title>\n\n<h1>INDEX</h1>";
	index += "<hr>";
	/*if (path.compare("/") == 0)
	{
		path = ".";
*/
	std::cerr << "LAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA: " << path << std::endl;
	// if (path.compare(".") != 0)
	// {
	// 	path = "." + path;
	// 	path += old;
	// }
	dirp = opendir(path.c_str());
	if( dirp != NULL )
	{
		std::string test;
		while((direntp = readdir(dirp)) != NULL)
		{
			test = direntp->d_name;	
			if (is_directory(path + '/' + test))
			{	
				index += "<ul>";
				index += "<li><p><a <style=\"font-weight:bold'\" href=\"";
				index += test;
				index += "\" class=\"active\">";
				index += test;
				index += "</li></a></p>\n";
				index += "</ul>";
		 	}
			else
			{
		 		index += "<ul>";
		 		index += "<li><p><a <style=\"font-weight:bold'\" href=\"";
		 		index += test;
		 		index += "\" class=\"active\">";
		 		index += test;
		 		index += "</li></a></p>\n";
		 		index += "</ul>";
			}
		}
		//index += "<title>ici aussi</title>";
		//int	i = 0;
        // for(;;)
		// {
        //     direntp = readdir( dirp );
        //     if ( direntp == NULL )
		// break;
		// 	index += "<h4>";
		// std::string test = direntp->d_name;
		// std::cout << "dirp  ---> " <<  test << std::endl;
		//index += "<a href=\"" + test +"\">" + test + "</a>\n";

		// if ( direntp->d_type == DT_DIR)
		// 		index += "__Directory__| ";
		// else if ( direntp->d_type == DT_REG)
		// 		index += "_Regular file_| ";
		// else
		// 		index += "                ";
		// 	index += "</h4>\n"
		index += "</body>";
		index += "</html>";;
		closedir( dirp );
	}
	return index;
}

void	StartServer(Server server)
{
	int	event_count;
	struct	epoll_event events[5];

	//std::vector<std::string>::iterator op = server.vectorroot.begin();
	//std::cerr << "ROOOOOOOOOOOOOOOOT: " << *op << std::endl;
	/*std::vector<char *>::iterator it = server.vectorenvcpy.begin();
	for (; it != server.vectorenvcpy.end(); it++)
		std::cerr << "vec first: " << *it << std::endl;*/
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
		if (array[i].init_serv())
			return ;
		array[i].newIndex = "";
		if (array[i].autoindex) // true
		{
			if (array[i].nom_index.length() == 0)
			{
				std::string tmp;
				//std::cout << "index est empty donc renvoyer vers une page de sommaire" << std::endl;
				array[i].newIndex = basicsummary("."); 
				nbfiles = 666;
			}
			else
			{
				array[i].newIndex = (array[i].nom_index).substr(1, array[i].nom_index.length()); 
				array[i].newIndex = array[i].root +  "/" + array[i].newIndex;
				//std::cout << " pas empty mais autoindex on " << std::endl;
			}
		}
		else
		{
			if (array[i].nom_index.length() == 0)
			{
				//std::cout << "foutre une page 404" << std::endl;
				nbfiles = 76;
			}
			else
			{
				array[i].newIndex = (array[i].nom_index).substr(1, array[i].nom_index.length()); 
				//std::cerr << "avant concatene: " << array[i].newIndex << std::endl;
				array[i].newIndex = array[i].root +  "/" + array[i].newIndex;
				//std::cerr << "apres concatene: " << array[i].newIndex << std::endl;
				//std::cout << " pas empty mais autoindex off" << std::endl;
			}
		}
		array[i].parsLoc(i);
		i++;
	}
	while (1)
	{
			for (i = 0; i < len; i++)
			{
			event_count = epoll_wait(array[i].epoll_fd, events, 5, 1000);
			if (event_count < 0)
				fprintf(stderr, "error in epoll_wait\n");
			if (event_count > 0)
				array[i].event_receptor(events, event_count);
			//this->newIndex = "";
			array[i].vectorenv.clear();
			array[i].vectorenv = array[i].vectorenvcpy;
			error = 0;
		}
	}
}

/*void	StartServer(Server server)
{
	(void)server;
	struct	epoll_event event, events[MAX_EVENTS];
	int	event_count;
	int	epoll_fd = epoll_create1(0);
	int	server_fd, new_socket = 0;
	long	retread;
	struct	sockaddr_in address;
	int	addrlen = sizeof(address);
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		std::cerr << "Error in socket" << std::endl;
		return ;
	}
	//int flags = fcntl(server_fd, F_GETFL, 0);
	//`fcntl(server_fd, F_SETFL, flags | O_NONBLOCK);
	address.sin_family= AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(server.port);
	memset(address.sin_zero, '\0', sizeof address.sin_zero);
	
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
	{
		std::cerr << "Error in bind" << std::endl;
		return ;
	}
	if (listen(server_fd, 10) < 0)
	{
		std::cerr << "Error in listen" << std::endl;
		return ;
	}
	event.events = EPOLLIN;
	event.data.fd = server_fd;;
	epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &event);
	while (1)
	{
		if ((tab[k] = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0)
		{
			std::cerr << "Error in accept" << std::endl;
			return ;
		}
		char	buffer[30000] = {0};
		event_count = epoll_wait(events, events, MAX_EVENTS, 1000);
		printf("%d, ready events\n", event_count);
		//for (i = 0; i <= event_count; i++)
		//{
			//retread = read(events[k].data.fd, buffer, 30000);
			retread = read(tab[k], buffer, 30000);
			buffer[retread] = '\0';
			CheckRequest(buffer);
			//std::string str1 = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 33\n\n<p style=\"color:red\">Coucou</p>\n";
			CheckRequest(buffer);
			std::string str1 = FirstPage(this->newIndex);
			std::string header = "HTTP/1.1 200 OK\nContent-type: text/html; charset=UTF-8\nContent-Length: " + intToString(str1.length()) + "\n\n" + str1 + "\n";
			//std::string header = "HTTP/1.1 200 OK\nContent-type: text/html; charset=UTF-8\nContent-Length: " + std::to_string(str1.length()) + "\n\n" + str1 + "\n";
			//char str[] = "GET /hello.html HTTP/1.1\r\n";
			if (error == 404)
			{
				char str3[] = "HTTP/1.1 404 Not Found\nContent-Type: text/plain\nContent-Length: 19\n\n404 page not found\n";
				write(tab[k], str3, strlen(str3));
			}
			if (this->newIndex.length() > 0)
			{
				//std::string header1 = "HTTP/1.1 200 OK\nContent-type: text/html; charset=UTF-8\nContent-Length: " + std::to_string(str2.length()) + "\n\n" + str2 + "\n";
				std::string str2 = fileToString(this->newIndex);
				std::string header1 = "HTTP/1.1 200 OK\nContent-type: text/html; charset=UTF-8\nContent-Length: " + intToString(str2.length()) + "\n\n" + str2 + "\n";
				write(tab[k], header1.c_str(), strlen(header1.c_str()));
				this->newIndex="";
			}
			else
				send(tab[k], header.c_str(), header.length(), 0);
			//send(tab[k], str1.c_str(), str1.length(), 0);
			//write(tab[k], str1.c_str(), strlen(str1.c_str()));
			printf("read on %d fd\n", events[k].data.fd);
			retread = read(tab[k], buffer, 30000);
			//retread = read(events[k].data.fd, buffer, 30000);
			printf("%ld, bytes read\n", retread);
			buffer[retread] = '\0';
			printf("READ = %s\n", buffer);
			ParseBuffer(buffer);
			if (strcmp(buffer, "stop") == 0)
				break;
		//}
		//retread = read(tab[k], buffer, 30000);
		//printf("test = %s\n", buffer);
		//printf("RETREAD = %ld\n", retread);
		close(new_socket);
		k++;
		error = 0;
	}
}*/

std::string	fileToString(std::string loc)
{
	std::string buffer;

	std::ifstream fin(loc.c_str());
	getline(fin, buffer, char(-1));
	fin.close();
	return buffer;
}
