/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjouaoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 21:20:19 by yjouaoud          #+#    #+#             */
/*   Updated: 2019/05/08 17:28:35 by yjouaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "get_next_line.h"

static	void		get_line(const int fd, char **tmpfd, char **line)
{
	int		i;
	char	*tmp;

	i = 0;
	while (tmpfd[fd][i] != '\n' && tmpfd[fd][i])
		i++;
	if (tmpfd[fd][i] == '\n')
	{
		*line = ft_strsub(tmpfd[fd], 0, i);
		if (tmpfd[fd] != NULL)
		{
			tmp = tmpfd[fd];
			tmpfd[fd] = ft_strdup(tmp + i + 1);
			free(tmp);
		}
	}
	else if (tmpfd[fd][i] == '\0')
	{
		*line = ft_strdup(tmpfd[fd]);
		tmpfd[fd] = NULL;
	}
}

int					get_next_line(const int fd, char **line)
{
	int			r;
	char		buff[BUFF_SIZE + 1];
	char		*tmp;
	static char *tmpfd[FD_LIMIT];

	while ((r = read(fd, buff, BUFF_SIZE)) > 0)
	{
		if (!(buff[r] = '\0') && tmpfd[fd] != NULL)
		{
			tmp = ft_strdup(tmpfd[fd]);
			free(tmpfd[fd]);
		}
		else
			tmp = ft_strnew(0);
		tmpfd[fd] = ft_strjoin(tmp, buff);
		free(tmp);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	if (r == 0 && (tmpfd[fd] == NULL || tmpfd[fd][0] == '\0'))
		return (0);
	else if (r < 0 || fd < 0 || fd > FD_LIMIT)
		return (-1);
	get_line(fd, tmpfd, line);
	return (1);
}
