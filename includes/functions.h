/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:28:47 by jtaravel          #+#    #+#             */
/*   Updated: 2023/01/09 18:17:13 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_HPP

#define FUNCTIONS_HPP

#include "server.hpp"
class Server;

typedef struct s_list
{
	char *name;
	char *content;
	char *line;
	struct s_list *next;
} t_list;

void    StartServer(Server server);
t_list    *init_lst(char **env, t_list *list);
void	ft_lstadd_back(t_list **alst, t_list *newm);
t_list	*ft_lstnew(char	*name, char *content, char *line);
char    **ft_regroup_env(t_list *lst);
char    **ft_split(char const *s, char c);
void    ft_lstclear(t_list **lst, void (*del)(void *));
void    del(void *data);
int		ft_strlen(char *str);
int	ft_atoi(const char *str);
std::string     fileToString(std::string loc);
char    **ft_regroup_envVector(std::vector<char *> vec);
std::string     intToString(int i);
char    *ft_strdup(char *s);
void	freeTab(char **tab);
void	freeTab2(char **tab);
void	splitRet(std::string str, std::string deli);
std::string	splitRetVal(std::string str, std::string deli);
int	checkBuffBoundary(std::string buff);
int	ParseBufferupl(std::string buffer);
void	CreateFile(std::string filepath);
int	checkBuffBoundary2(char *buff);
bool is_directory(const std::string &filename);

#endif
