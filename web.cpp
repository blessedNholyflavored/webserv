/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   web.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:25:46 by jtaravel          #+#    #+#             */
/*   Updated: 2022/11/29 16:48:34 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <fstream>
#include <fcntl.h>
#include <dirent.h>
#include "server.hpp"
#include "functions.h"


#define MAX_EVENTS 5

static int error = 0;
static std::string  newIndex = "";
static std::string	split[4096];
static std::string	newfile[5];
static	int	nbfiles = 0;
static	int	statusfile = 0;

void	splitString(const char *buf, std::string deli)
{
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
	//std::cout << "SPLIT = " << arr[1] << std::endl;
//	std::cout << "IN SPLIT: " << str.substr(start, end - start) << std::endl;
	if (arr[1].compare("/") != 0 && arr[0].compare("GET") == 0)
	{
		std::ifstream file(arr[1].c_str() + 1, std::ios::in);
		if (!file)
		{
			std::cout << arr[1] << std::endl;
			std::cerr << "NO FILE" << std::endl;
			error = 404;
		}
		else
		{
			newIndex = arr[1].substr(1, arr[1].length());
			error = 200;
		}
	}
	else if (arr[0].compare("POST") == 0)
		printf("TEST REQUEST=%s\n", arr[1].c_str());
}

std::string	fileToString(std::string loc);

void	CheckRequest(char *buffer)
{
	static	int a = 0;
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
	if (space != 2 && a > 0)
	{
		printf("SPACE = %d\n", space);
		std::cout << "BUFFER:" << buffer << std::endl;
		exit (0);
	}
	if (a > 0)
	{
		//printf("BEFORESPLIT: %s\n", test.c_str());
		splitString(test.c_str(), " ");
	}
	a++;
}

static void	createLink(std::string & index, int i)
{
	if (i == 0)
	{
		std::string test;
		std::ifstream f("coke.html");
		getline(f, test);
		index += test;
		index += "jtaravel: ";
		index += "<a href=\"";
		index += "https://profile.intra.42.fr/users/jtaravel";
		index += "\">";
		index += "jtaravel";
		index += "</a>";
	}
	if (i == 1)
	{
		index += "lkhamlac: ";
		index += "<a href=\"";
		index += "https://profile.intra.42.fr/users/lkhamlac";
		index += "\">";
		index += "lkhamlac";
		index += "</a>";
	}
	if (i == 2)
	{
		index += "mmhaya: ";
		index += "<a href=\"";
		index += "https://profile.intra.42.fr/users/mmhaya";
		index += "\">";
		index += "mmhaya";
		index += "</a>";
	}
}

std::string	intToString(int i)
{
	std::string res;
	int	neg = 0;
	if (i < 0)
		neg = 1;
	i *= -1;
	while (i > 0)
	{
		res += i % 10;
		i = i / 10;
	}
	return res;
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

std::string FirstPage(std::string filePath)
{
	(void)filePath;
	std::string		index;
	std::string		path;

	/*path = getcwd(buffer, PATH_MAX);
	path += "/";
	path += filePath;
	dirp = opendir(path.c_str());*/
	std::string recup;
	std::ifstream findex("lucie_est_la_plus_belle.html");
	while (getline(findex, recup))
		index += recup;
	/*index += "<!DOCTYPE html>\n<html>\n\n<title>INDEX</title>\n\n<h1>INDEX</h1>";
	index += "<body id=\"all\">";
	index += "<form id=\"form\">";
	index += "<input type=\"file\" name=\"background\" />";
	index += "<button type=\"submit\">SEND</button>\n\n";
	index += "</form>";
	index += "<p id=\"message\"></p>";
	index += "<button id=\"btn\">test</button>\n\n";*/
	for (int i = 0; i < 3 + nbfiles; i++)
	{
		index += "<h4>";
		createLink(index, i);
		index += "</h4>\n";
	}
	for (int i = 1; i <= nbfiles; i++)
		createlinfkFile(index, i);
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
	index += "<script src=\"upload.js\"></script>\n\n";
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


void	StartServer(Server server)
{
	(void)server;
	struct	epoll_event event, events[MAX_EVENTS];
	int	event_count;
	//int	epoll_fd = epoll_create1(1);
	int	server_fd, new_socket = 0;
	long	retread;
	struct	sockaddr_in address;
	int	addrlen = sizeof(address);

	event.events = EPOLLIN;
	event.data.fd = 0;
	/*if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, 0, &event))
	{
		std::cerr << "Error in epoll" << std::endl;
		return ;
	}*/
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
	int	tab[10];
	int	k = 1;
	while (1)
	{
		if ((tab[k] = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0)
		{
			std::cerr << "Error in accept" << std::endl;
			return ;
		}
		char	buffer[30000] = {0};
		event_count = epoll_wait(events[k].data.fd, events, MAX_EVENTS, 10);
		printf("%d, ready events\n", event_count);
		//for (i = 0; i <= event_count; i++)
		//{
			//retread = read(events[k].data.fd, buffer, 30000);
			retread = read(tab[k], buffer, 30000);
			buffer[retread] = '\0';
			CheckRequest(buffer);
			//std::string str1 = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 33\n\n<p style=\"color:red\">Coucou</p>\n";
			std::string str1 = FirstPage(newIndex);
			//std::string header = "HTTP/1.1 200 OK\nContent-type: text/html; charset=UTF-8\nContent-Length: " + std::to_string(str1.length()) + "\n\n" + str1 + "\n";
			std::string header = "HTTP/1.1 200 OK\nContent-type: text/html; charset=UTF-8\nContent-Length: " + intToString(str1.length()) + "\n\n" + str1 + "\n";
			//char str[] = "GET /hello.html HTTP/1.1\r\n";
			if (error == 404)
			{
				char str3[] = "HTTP/1.1 404 Not Found\nContent-Type: text/plain\nContent-Length: 19\n\n404 page not found\n";
				write(tab[k], str3, strlen(str3));
			}
			if (newIndex.length() > 0)
			{
				std::string str2 = fileToString(newIndex);
				//std::string header1 = "HTTP/1.1 200 OK\nContent-type: text/html; charset=UTF-8\nContent-Length: " + std::to_string(str2.length()) + "\n\n" + str2 + "\n";
				std::string header1 = "HTTP/1.1 200 OK\nContent-type: text/html; charset=UTF-8\nContent-Length: " + intToString(str2.length()) + "\n\n" + str2 + "\n";
				write(tab[k], header1.c_str(), strlen(header1.c_str()));
				newIndex="";
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
}

std::string	fileToString(std::string loc)
{
	std::string buffer;

	std::ifstream fin(loc.c_str());
	getline(fin, buffer, char(-1));
	fin.close();
	return buffer;
}