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


#define MAX_EVENTS 4096

static int error = 0;
//static std::string  newIndex = "";
static std::string	split[250000];
static std::string	newfile[5];
static	int	nbfiles = 0;
static	int	statusfile = 0;
static	int	ext = 0;
static char *bufall;
static int lenall;

char	**Server::ft_regroup_envVector(std::vector<char *> vec)
{
	char **res;
	int i = 0;
	
	if (this->env)
	{
		//freeTab(this->env);
		//this->env = NULL;
	}
	res = (char **)malloc(sizeof(char*) * (vec.size() + 1));
	std::vector<char *>::iterator it = vec.begin();
	for (; it != vec.end(); it++)
	{
		//res[i] = ft_strdup((char *)*it);
		res[i] = (char *)*it;
		//printf("REGROUP: %s\n", res[i]);
		i++;
	}
	res[i] = NULL;
	// res est egal  a this->env[i]
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

std::string	fileToString(std::string loc);
std::string     intToString(int i);
int	ParseBufferupl(std::string buffer);

int	checkBuffBoundary2(char *buff)
{
	int i = 0;
	char **recup = ft_split(buff, '\r');

	while (recup[i])
	{
		std::string cmp = recup[i];
		if (cmp.compare(0, 24, "------WebKitFormBoundary") == 0)
		{
			freeTab2(recup);
			std::cerr << "IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII: " << i << "\n";
			return i + 3;
		}
		i++;
	}
	freeTab2(recup);
	return (1);
}

int	checkBuffBoundary(std::string buff)
{
	int i = 0;
	char **recup = ft_split(buff.c_str(), '\r');

	while (recup[i])
	{
		std::string cmp = recup[i] + 1;
		if (cmp.compare(0, 24, "------WebKitFormBoundary") == 0)
		{
			freeTab2(recup);
			return 0;
		}
		i++;
	}
	freeTab2(recup);
	return (1);
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
		//std::cout << "IN SPLIT: " << str.substr(start, end - start) << std::endl;
		arr[i] = str.substr(start, end - start);
		start = end + deli.size();
		end = str.find(deli, start);
		i++;
	}
	arr[i] = str.substr(start, end - start);
	if (arr[0].compare(0, 24, "------WebKitFormBoundary") == 0 || checkBuffBoundary(buffer) == 0)
	{
	std::cerr << "??????????????????????????????????????????????????????\n";	
		if (ParseBufferupl(buffer) == 413)
		{
			return ;
		}
	}
//	std::cout << "IN SPLIT: " << str.substr(start, end - start) << std::endl;
	if (arr[1].compare("/") != 0 && arr[0].compare("GET") == 0 && arr[1].compare("/html/text.php")
			&& arr[1].compare("/html/galerie.php"))
	{
		//arr[1] = "./html" + arr[1];
		std::ifstream file(arr[1].c_str() + 1, std::ios::in);
		if (!file && open(arr[1].c_str() + 1, O_DIRECTORY) == -1)
		{
			//std::cout << arr[1] << std::endl;
			//std::cerr << "NO FILE" << std::endl;
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
			if (arr[0].compare("POST") && arr[1].compare(0, 21, "/html/upload_img.php") == 0)
				error = 996;
			if (this->loc.getIndex().length() == 0 && this->loc.getAuto() == 1)
				error = -7;

			//error = 404;
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
		unlink(arr[1].c_str() + 1);
	 //if (this->newIndex == "./" || this->newIndex == "/" || this->newIndex == "/favicon.ico")
	if (arr[1].length() <= 1 || this->newIndex == "/favicon.ico")
			this->newIndex = "./html/home.html";
	//iciicicicicici
	//std::cerr << "kgdfvbdfvsdffvsfvrfrfdvrfvifffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff: " << error << "\n";
}

void	CreateFile(std::string filepath)
{

	//char *cpy = ft_strdup(bufall);


	// std::ofstream file;
	// file.open(conca.c_str());
	// filepath = "uploads/" + filepath;
	int i = 0;
	int count = 0;
	while (bufall[i])
	{
		if (bufall[i] == '\n')
			count++;
		std::cerr << "LLLLEEEFESFVSHDVFHSDBVHJFDB HVFB HVF: " << ft_strlen(bufall) << "\n";
		if (count == 4)
			break;
		i++;
	}
	// std::ostringstream oss;
	// oss << cpy + i;
	// std::string data(oss.str());
	// //file << data;
	//int i = checkBuffBoundary(bufall);
	char *wrt = bufall + i + 1;
	wrt[ft_strlen(wrt)] = 0;
	std::string conca = "images/" + filepath;
	int o = open(conca.c_str(), O_CREAT | O_WRONLY | O_TRUNC, 0644);
	write(o, wrt, lenall);
	close(o);
}

int	ParseBufferupl(std::string buffer)
{
	std::cerr << "LENALLLLLLLLLLLLLLLLL" << lenall << "\n";
	if (lenall > 50000)
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
	// if (space != 2 && res.compare(6, 18, "WebKitFormBoundary"))
	// {	
	// 	int fd = open("tesssss", O_CREAT | O_WRONLY | O_WRONLY | O_TRUNC, 0644);
	// 	write(fd, buffer, strlen(buffer));
	// 	std::cout << "BUFFER:" << buffer << std::endl;
	// //	exit (0);
	// }
		//printf("BEFORESPLIT: %s\n", test.c_str());
		splitString(test.c_str(), " ", fd, ret, buffer);
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


	if (filePath.find(".php") != std::string::npos)
	{
		index = execFile(filePath);
		index += "</body>";
		index += "</html>";
		return index;
	}
	else if (filePath.find(".py") != std::string::npos)
	{
		std::cerr <<" SJOJOIHODW"  << std::endl;
		index = execGETpy();
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
		index += data;
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
	findex.close();
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
	for (i = 0; i < 50000; i++)
	{
		if (split[i].compare(0, 13, "Content-Type:") == 0)
		{
			for(int h = i + 2; h < 250000; h++)
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

// void	ParseBuffer(std::string buffer)
// {
// 	splitRet(buffer, "\n");
// 	int i = 0;
// 	int	l = 0;
// 	for (i = 0; i < 250000; i++)
// 	{
// 		if (split[i].length() > 0 && split[i].compare(0, 20, "Content-Disposition:") == 0)
// 		{
// 			std::string filename = splitRetVal(split[i], " ");
// 			for (size_t k = 0; k < filename.length(); k++)
// 			{
// 				if (filename[k] == '=' && filename[k + 1] == '"')
// 				{
// 					l = k + 2;
// 					break ;
// 				}
// 			}
// 			if (nbfiles < 5)
// 			{
// 				newfile[nbfiles] = filename.substr(l, filename.length() - 2);
// 				newfile[nbfiles].erase(newfile[nbfiles].length() - 2, newfile[nbfiles].length());
// 			}
// 			//std::cout << "SIZE =" << newfile.length();
// 			//std::cout << "SPLIT TEST:" << newfile << std::endl;
// 		}
// 	}
// 	if (newfile[nbfiles].length() > 0 && nbfiles < 5)
// 	{
// 		std::cout << "NBFILES=" << newfile[nbfiles] << std::endl;
// 		CreateFile();
// 		nbfiles++;
// 	}
// 	return ;
// }

#include <arpa/inet.h>

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
	//address.sin_addr.s_addr = inet_addr("127.0.0.1");
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
	std::cerr << "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO: " << event.data.fd << "\n";
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
	//if (lenall > 50000)
	//	ret = 413;
	std::cerr << "111111111111111111111111111111: " << ret << std::endl;
	std::cerr << "222222222222222222222222222222: " << lenall << std::endl;
	if (!ret || ret == 200)
		CheckRequest(buff, fd, ret);
	if (!ret)
		ret = error;
	// else if (request->getRetCode() == 404)
	// {
	// 	printf("%d\n", error);
	// 	char str3[] = "HTTP/1.1 404 Not Found\nContent-Type: text/plain\nContent-Length: 19\n\n404 page not found\n";
	// 	write(fd, str3, strlen(str3));
	// }
	//std::cerr << "RETTTTTT: " << ret << "\n";
	if (ret && ret != 200)
	{
		std::cerr << "LOLLLLLLL\n";
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
			std::cerr << "PPPPPPPPPPPPPPPSDDDDDDDDDDDSDSDSDSDSDSDSDSDSDDS\n";
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


std::string	Server::basicsummary(std::string filePath)
{
	//std::string		index;
	//char			buffer[PATH_MAX];
	//std::string		path;
	static	std::string old;

	std::stringstream auto_index;
	auto_index.str(filePath); //.substr(this->root.length() + 1));
	DIR*			dirp;
	struct dirent*	direntp;
	//path = filePath;

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
		array[i].cwd = server.cwd;
		if (array[i].init_serv())
			return ;
		array[i].newIndex = "";
		if (array[i].autoindex) // true
		{
			if (array[i].nom_index.length() == 0)
			{
				std::string tmp;
				//std::cout << "index est empty donc renvoyer vers une page de sommaire" << std::endl;
				array[i].newIndex = array[i].basicsummary(server.cwd); // free buffer 
				nbfiles = 666;
			}
			else
			{
				array[i].newIndex = (array[i].nom_index).substr(1, array[i].nom_index.length()); 
				array[i].newIndex = "";
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
				//freeTab(array[i].env);
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
			//array[i].newIndex = "";
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
	//fcntl(server_fd, F_SETFL, flags | O_NONBLOCK);
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
