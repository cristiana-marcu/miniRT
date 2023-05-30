/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smart_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 19:14:31 by drontome          #+#    #+#             */
/*   Updated: 2023/05/29 20:22:36 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static size_t	count_tokens(char *s);
static char		*cross_string(char *s, size_t *i);
static char		*get_end_str(char *s, size_t *len);
static size_t	count_string(char *s);

char	**smart_split(char *s)
{
	char	**pp;
	size_t	len;
	size_t	i;

	if (!s)
		return (NULL);
	len = count_tokens(s);
	if (len == 0)
		return (NULL);
	pp = ft_calloc(len + 1, sizeof(s));
	if (!pp)
		return (NULL);
	i = 0;
	while (*s && i < len)
	{
		while (*s && (*s == ' ' || *s == '\t'))
			s++;
		pp[i] = ft_substr(s, 0, count_string(s));
		if (!pp[i])
			return (ft_free_matrix(pp));
		if (*s)
			s = cross_string(s, NULL);
		i++;
	}
	return (pp);
}

static size_t	count_tokens(char *s)
{
	size_t	i;

	i = 0;
	while (s && *s)
	{
		while (s && *s && (*s == ' ' || *s == '\t'))
			s++;
		if (*s)
			i++;
		s = cross_string(s, NULL);
	}
	return (i);
}

static char	*cross_string(char *s, size_t *i)
{
	size_t	len;

	len = 0;
	if (*s && (*s == ' ' || *s == '\t'))
		s++;
	s = get_end_str(s, &len);
	if (i)
		*i = len;
	return (s);
}

static char	*get_end_str(char *s, size_t *len)
{
	int	i;

	i = 0;
	while ((s[i] && !ft_isspace(s[i])) || (i > 0 && s[i] == ' ' \
		&& (s[i - 1]) == ','))
	{
		i++;
		*len = *len + 1;
	}
	return (s + i);
}

static size_t	count_string(char *s)
{
	size_t	i;

	i = 0;
	cross_string(s, &i);
	return (i);
}
