/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 16:20:44 by jtaravel          #+#    #+#             */
/*   Updated: 2022/09/21 16:39:37 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

char	*ft_read(char *buff, int fd)
{
	int		ret;
	char	*tmp;

	ret = 1;
	tmp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (ret != 0 && !ft_strchr(buff, '\n'))
	{
		ret = read(fd, tmp, BUFFER_SIZE);
		if (ret == -1)
		{
			free(tmp);
			return (NULL);
		}
		tmp[ret] = '\0';
		buff = ft_strjoin_gnl(buff, tmp);
	}
	free(tmp);
	return (buff);
}

char	*ft_next_line(char *str)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	tmp = malloc(sizeof(char) * (ft_strlen(str) - i) + 1);
	i++;
	j = 0;
	while (str[i + j])
	{
		tmp[j] = str[i + j];
		j++;
	}
	tmp[j] = '\0';
	free(str);
	return (tmp);
}

char	*ft_get_line(char *str)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		line = malloc(sizeof(char) * (i + 2));
	else
		line = malloc(sizeof(char) * (i + 1));
	while (str[j] && str[j] != '\n')
	{
		line[j] = str[j];
		j++;
	}
	if (str[j] == '\n')
	{
		line[j] = '\n';
		j++;
	}
	line[j] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buff;

	if (fd == 42)
	{
		free(buff);
		return (NULL);
	}
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = ft_read(buff, fd);
	if (!buff)
		return (NULL);
	if (!buff[0])
	{
		free(buff);
		buff = NULL;
		return (NULL);
	}
	line = ft_get_line(buff);
	buff = ft_next_line(buff);
	return (line);
}
