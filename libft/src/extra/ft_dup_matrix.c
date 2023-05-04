/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:46:28 by drontome          #+#    #+#             */
/*   Updated: 2022/11/03 12:37:43 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_dup_matrix(char **mtx)
{
	int		i;
	char	**dup;

	if (!mtx)
		return (NULL);
	i = 0;
	while (mtx[i])
		i++;
	dup = malloc(sizeof(char *) * (i + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (mtx[i])
	{
		dup[i] = ft_strdup(mtx[i]);
		if (!dup[i])
			return (ft_free_matrix(dup));
		i++;
	}
	dup[i] = NULL;
	return (dup);
}
