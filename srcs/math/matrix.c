/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 10:56:09 by cmarcu            #+#    #+#             */
/*   Updated: 2021/05/06 11:11:36 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/my_math.h"

void	mat44_mult(t_mat44 result, t_mat44 a, t_mat44 b)
{
	int i;
	int j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			result[i][j] = a[i][0] * b[0][j] +
							a[i][1] * b[1][j] +
							a[i][2] * b[2][j] +
							a[i][3] * b[3][j];
			j++;
		}
		i++;
	}
}

void	mat44_transpose(t_mat44 result, t_mat44 a)
{
	int i;
	int j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j  < 4)
		{
			result[i][j] = a[j][i];
			j++;
		}
		i++;
	}
}

double mat44_determinant_mat33(t_mat44 a)
{
	double result;
	int i;
	int j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{

		}
	}
}
