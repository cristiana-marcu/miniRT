/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 19:39:03 by drontome          #+#    #+#             */
/*   Updated: 2022/12/07 18:41:12 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_end_line(t_var	*var, char *buf)
{
	var->size = ft_strlen_gnl(var->line) + ft_strlen_gnl(buf) \
	- ft_strlen_gnl(var->eln + 1) + 1;
	var->i = 0;
	var->aux = malloc(var->size);
	if (!var->aux)
		return (NULL);
	if (var->line)
	{
		ft_cpy(var->aux, var->line, var->size);
		var->i = ft_strlen_gnl(var->aux);
		free(var->line);
		var->line = NULL;
	}
	while (*buf != *var->eln)
	{
		*(var->aux + var->i) = *buf;
		buf++;
		var->i++;
	}
	*(var->aux + var->i) = *buf;
	*(var->aux + var->i + 1) = 0;
	return (var->aux);
}

static char	*ft_store_line(t_var *var, char *buf)
{
	var->aux = NULL;
	var->eln = ft_strchr(buf, '\n');
	if (var->eln == NULL)
	{
		var->aux = malloc((ft_strlen_gnl(buf) + ft_strlen_gnl(var->line)) + 1);
		if (!var->aux)
			return (NULL);
		if (var->line)
		{
			ft_cpy(var->aux, var->line, (ft_strlen_gnl(var->line) + 1));
		}
		ft_cpy((var->aux + ft_strlen_gnl(var->line)), buf, \
		(ft_strlen_gnl(buf) + 1));
	}
	else if (*(var->eln) == '\n')
	{
		var->aux = ft_end_line(var, buf);
		var->flag = 1;
	}
	if (var->line && (var->line != var->aux))
	{
		free(var->line);
		var->line = NULL;
	}
	return (var->aux);
}

static char	*ft_free_buffer(t_var *var, char *buf)
{
	if (var->flag <= 0)
	{
		free (buf);
		buf = NULL;
	}
	else if (var->flag == 1)
	{
		buf = ft_new_line(var, buf);
		if (*buf == 0)
		{
			free(buf);
			buf = NULL;
		}
	}
	return (buf);
}

static char	*ft_fill_buffer(t_var *var, char *buf)
{
	if (var->size > 0)
	{
		*(buf + var->size) = 0;
		var->line = ft_store_line(var, buf);
	}
	else
	{
		buf = ft_free_buffer(var, buf);
		var->flag = -1;
	}
	return (buf);
}

char	*get_next_line(int fd)
{
	t_var		var;
	static char	*buf;

	ft_init_var(&var);
	while (var.flag == 0 && fd >= 0 && BUFFER_SIZE >= 0)
	{
		if (buf == NULL)
		{
			buf = malloc(BUFFER_SIZE + 1);
			if (!buf)
				return (NULL);
			var.size = read(fd, buf, BUFFER_SIZE);
			buf = ft_fill_buffer(&var, buf);
			if (var.flag == -1)
				break ;
		}
		else
			var.line = ft_store_line(&var, buf);
		buf = ft_free_buffer(&var, buf);
	}
	return (var.line);
}

/*
int	main(void)
{
	char	*line;
	int		i;
	int		fd1;
	int		fd2;
	int		fd3;
	fd1 = open("tests/test.txt", O_RDONLY);
	fd2 = open("tests/test2.txt", O_RDONLY);
	fd3 = open("tests/test3.txt", O_RDONLY);
	i = 1;
	while (i < 7)
	{
		line = get_next_line(fd1);
		printf("line [%02d]: %s", i, line);
		free(line);
		line = get_next_line(fd2);
		printf("line [%02d]: %s", i, line);
		free(line);
		line = get_next_line(fd3);
		printf("line [%02d]: %s", i, line);
		free(line);
		i++;
	}
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}
*/
