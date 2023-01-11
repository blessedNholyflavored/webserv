#include "includes/server.hpp"
#include "includes/inc.hpp"
#include "includes/functions.h"

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
	index += "</body>";
	index += "</html>";
	findex.close();
	return index;
}


std::string	fileToString(std::string loc)
{
	std::string buffer;

	std::ifstream fin(loc.c_str());
	getline(fin, buffer, char(-1));
	fin.close();
	return buffer;
}


bool Server::autoindexed() const
{
	return this->autoindex;
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

