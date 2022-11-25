#include "location.hpp"
#include "inc.hpp"

Location::Location() 
{
	
}

Location::~Location()
{

}


std::vector<std::string> ft_split2(std::string str, std::string deli)
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

void Location::parser_la_location(std::string loc, size_t nbligne, int j)
{
    //Location new_instance;
    //std::cout << "cc" << loc << std::endl;
    std::vector<std::string> ligne = ft_split2(loc, " ");
    //  typedef std::vector<std::string>::iterator iterator;
    //         for (iterator it = ligne.begin(); it != ligne.end(); it++ )
    //             std::cout << *it << std::endl;
    //         std::cout << "ligne" << ligne[1] << std::endl; 
    (void) nbligne;
    (void) j;
    //return new_instance;
}