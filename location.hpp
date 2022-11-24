# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <cstdlib>
# include <unistd.h>
#include <vector>
# define WHITESPACES "; \t"
# ifndef LOCATION_HPP
# define LOCATION_HPP


class Location
{
	private:
    //lister tous les elements qui composent location 
	public:
	Location();
	~Location();
    std::string location;


    void parser_la_location(std::string loc, size_t nbligne, int j);	
};

#endif
