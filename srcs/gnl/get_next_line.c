/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:19:09 by cmarcu            #+#    #+#             */
/*   Updated: 2021/02/12 09:32:55 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

void	ft_bzero(char *s, size_t n)
{
	unsigned char	*p;
	size_t			a;

	p = (unsigned char *)s;
	a = 0;
	while (a < n)
	{
		p[a] = '\0';
		a++;
	}
}

int		delmem(char **p)
{
	if (p)
	{
		if (*p)
		{
			ft_bzero(*p, ft_strlen(*p));
			free(*p);
			*p = NULL;
			return (1);
		}
	}
	return (0);
}

int		mount_next_line(int re, char **re_acu, char **line)
{
	int		aux;
	char	*temp;

	if (re > 0)
		aux = 1;
	else
		aux = 0;
	temp = ft_substr(*re_acu, ft_strlen(*line) + aux, ft_strlen(*re_acu));
	delmem(re_acu);
	*re_acu = temp;
	if (re == 0)
	{
		delmem(re_acu);
		return (0);
	}
	return (1);
}

int		get_next_line(int fd, char **line)
{
	int			re;
	char		buf[BUFFER_SIZE + 1];
	char		*temp;
	static char	*re_acu;

	re = 1;
	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (!re_acu)
		re_acu = ft_strdup("");
	while (!ft_strchr(re_acu, '\n') && (re = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[re] = '\0';
		temp = ft_strjoin(re_acu, buf);
		delmem(&re_acu);
		re_acu = temp;
	}
	if (re == 0)
		*line = ft_strdup(re_acu);
	else if (re > 0)
		*line = ft_substr(re_acu, 0, (ft_strchr(re_acu, '\n') - re_acu));
	else
		return (-1 * delmem(&re_acu));
	return (mount_next_line(re, &re_acu, line));
}
