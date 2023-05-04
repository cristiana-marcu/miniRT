/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 19:39:08 by drontome          #+#    #+#             */
/*   Updated: 2022/12/19 13:28:24 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_init_var(t_var *var)
{
	var->line = NULL;
	var->aux = NULL;
	var->eln = NULL;
	var->i = 0;
	var->flag = 0;
	var->size = 0;
	return ;
}

size_t	ft_strlen_gnl(const char *s)
{
	size_t	c;

	c = 0;
	if (!s)
		return (c);
	while (*(s + c) != 0)
		c++;
	return (c);
}

void	ft_cpy(char *dst, char *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dst == src)
		return ;
	while (i < n && *(src + i) != 0)
	{
		*(dst + i) = *(src + i);
		i++;
	}
	*(dst + i) = 0;
	return ;
}

char	*ft_new_line(t_var *var, char *buf)
{
	var->aux = NULL;
	var->size = ft_strlen_gnl(var->eln + 1) + 1;
	var->aux = malloc(var->size);
	if (!var->aux)
		return (NULL);
	ft_cpy(var->aux, (var->eln + 1), var->size);
	free(buf);
	buf = NULL;
	return (var->aux);
}
