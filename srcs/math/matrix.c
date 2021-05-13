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

t_mat44	mat44_mult(t_mat44 a, t_mat44 b)
{
	int i;
	int j;
	t_mat44 result;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			result.d[i][j] = a.d[i][0] * b.d[0][j] +
							a.d[i][1] * b.d[1][j] +
							a.d[i][2] * b.d[2][j] +
							a.d[i][3] * b.d[3][j];
			j++;
		}
		i++;
	}
	return (result);
}

t_mat44	mat44_transpose(t_mat44 a)
{
	int i;
	int j;
	t_mat44 result;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j  < 4)
		{
			result.d[i][j] = a.d[j][i];
			j++;
		}
		i++;
	}
	return (result);
}

double mat44_det_mat33(t_mat33 a)
{
	double result;

	result = a.d[0][0] * (a.d[1][1] * a.d[2][2] - a.d[1][2] * a.d[2][1])
			- a.d[0][1] * (a.d[1][0] * a.d[2][2] - a.d[1][2] * a.d[2][0])
			+ a.d[0][2] * (a.d[1][0] * a.d[2][1] - a.d[1][1] * a.d[2][0]);
}

double mat44_det_mat44(t_mat44 a)
{
	double result;

	result = a[0][0] * (a[1][1] * a[2][2] - a[1][2] * a[2][1])
			- a[0][1] * (a[1][0] * a[2][2] - a[1][2] * a[2][0])
			+ a[0][2] * (a[1][0] * a[2][1] - a[1][1] * a[2][0]);
}

t_mat33	mat44_submatrix(t_mat44 a, unsigned int row, unsigned int column)
{
	unsigned int i;
	unsigned int j;
	t_mat33 result;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j  < 4)
		{
			if (i != row && j != column)
				result.d[i][j] = a.d[i][j];
			j++;
		}
		i++;
	}
	return (result);
}
