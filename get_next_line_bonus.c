/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habenydi <habenydi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 14:23:32 by habenydi          #+#    #+#             */
/*   Updated: 2024/12/14 14:24:58 by habenydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*readline(int fd, char *string, char *buff)
{
	ssize_t	cont;
	char	*fnl;
	char	*fre;

	cont = 0;
	fnl = NULL;
	while (!fnl)
	{
		cont = read(fd, buff, BUFFER_SIZE);
		if (!cont)
			break ;
		if (cont < 0)
			return (NULL);
		buff[cont] = '\0';
		fnl = ft_strchr(buff, '\n');
		fre = string;
		string = ft_strjoin(string, buff);
		free(fre);
	}
	return (string);
}

static void	ft_getline(char **string, char **line)
{
	size_t	i;
	char	*fre;

	if (!**string)
	{
		free(*string);
		*string = NULL;
		*line = NULL;
		return ;
	}
	i = 0;
	while ((*string)[i] && (*string)[i] != '\n')
		i++;
	if (!(*string)[i])
	{
		*line = ft_strdup(*string);
		free(*string);
		*string = NULL;
		return ;
	}
	*line = ft_substr(*string, i + 1);
	fre = *string;
	*string = ft_strdup(&(*string)[i + 1]);
	free(fre);
}

char	*get_next_line(int fd)
{
	char		*buff;
	static char	*string[INDEX];
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || INDEX < fd)
		return (NULL);
	if (!ft_strchr(string[fd], '\n'))
	{
		buff = malloc(BUFFER_SIZE + 1);
		string[fd] = readline(fd, string[fd], buff);
		if (!string[fd])
			return (free(buff), NULL);
	}
	ft_getline(&string[fd], &line);
	free(buff);
	return (line);
}
