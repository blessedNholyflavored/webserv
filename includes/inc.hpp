/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhamlac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:33:04 by lkhamlac          #+#    #+#             */
/*   Updated: 2023/01/11 15:33:07 by lkhamlac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <cstdlib>
# include <cmath>
# include <unistd.h>
# include <vector>
# define WHITESPACES "; \t"

#ifndef INC_HPP
# define INC_HPP

extern std::string res[4096];


class Server;
class Location;

void		ft_split1(std::string str, std::string charset);
std::string get_file( std::string file);
int 		check_int(std::string str);
int         check_int1(std::string str);
std::string ltrim(std::string &s);
size_t      countEndl(std::string content);
std::string remove_charset(std::string res);
std::string	fileToString(std::string loc);
std::string     intToString(int i);

#endif
