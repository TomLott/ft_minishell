/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 17:08:51 by itollett          #+#    #+#             */
/*   Updated: 2021/02/02 10:09:32 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define BUFFER_SIZE 100

int				ft_finish(char **line, char **leftover)
{
	if (ft_strchr(*leftover, '\0'))
	{
		*line = ft_strdup(*leftover);
		free(*leftover);
		*leftover = NULL;
	}
	return (0);
}

int				ft_error(int available, char **leftover)
{
	if (available < 0)
	{
		if (*leftover)
		{
			free(*leftover);
			*leftover = NULL;
		}
		return (-1);
	}
	return (0);
}

int				ft_check_available(char **leftover, char **line, int available)
{
	char *pointer;
	char *temp;

	if (!available && !*leftover)
	{
		*line = ft_strdup("");
		return (0);
	}
	if (ft_error(available, &*leftover))
		return (-1);
	if ((pointer = ft_strchr(*leftover, '\n')))
	{
		*pointer++ = '\0';
		*line = ft_strdup(*leftover);
		temp = ft_strdup(pointer);
		if (!temp || !*line)
			return (-1);
		free(*leftover);
		*leftover = temp;
		return (1);
	}
	return (ft_finish(&*line, &*leftover));
}

int				get_next_line(int fd, char **line)
{
	static char	*leftover[1025];
	char		*buff;
	int			available;
	char		*temp;

	if (!line || fd < 0 || fd > 1025 || BUFFER_SIZE <= 0 ||
		!(buff = (char *)malloc(BUFFER_SIZE + 1)) || (read(fd, buff, 0) < 0))
		return (-1);
	while ((available = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[available] = '\0';
		if (!leftover[fd])
			leftover[fd] = ft_strdup(buff);
		else
		{
			temp = ft_strjoin(leftover[fd], buff);
			free(leftover[fd]);
			leftover[fd] = temp;
		}
		if (ft_strchr(leftover[fd], '\n'))
			break ;
	}
	free(buff);
	buff = NULL;
	return (ft_check_available(&leftover[fd], &*line, available));
}
