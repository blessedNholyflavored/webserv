/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 12:34:00 by jtaravel          #+#    #+#             */
/*   Updated: 2022/03/30 15:38:03 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (c == s[i])
		return ((char *)&s[i]);
	return (NULL);
}

/*int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}*/

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*cpy;

	i = 0;
	cpy = s;
	while (i < n)
	{
		cpy[i] = '\0';
		i++;
	}
	s = cpy;
}

char	*ft_strjoin2(char *s1, char *s2, char *res)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (s1[++i])
	{
		res[j] = s1[i];
		j++;
	}
	i = -1;
	while (s2[++i])
	{
		res[j] = s2[i];
		j++;
	}
	res[j] = '\0';
	return (res);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*res;

	if (!s1)
	{
		s1 = malloc(1);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	res = malloc(sizeof(char) * ((ft_strlen((char *)s1)
					+ ft_strlen((char *)s2)) + 1));
	if (!res)
		return (0);
	res = ft_strjoin2(s1, s2, res);
	free(s1);
	return (res);
}
