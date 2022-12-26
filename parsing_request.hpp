
#include "server.hpp"
#include <string>

class Request {
	public:
		void							parsRequest(std::string str, std::vector<Location> location);
		int								checkLocation(std::string str, int method, std::vector<Location> location);
		std::vector<Location>::iterator	&findGoodLocation(std::string str, std::vector<Location> location, std::vector<Location>::iterator &it);
		int								getRetCode() const;
		std::string						getMethod() const;
		std::string						getPath() const;

	private:
		std::string _method;
		std::string	_path;
		int			_retCode;
};