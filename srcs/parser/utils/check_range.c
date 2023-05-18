/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_range.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:48:46 by drontome          #+#    #+#             */
/*   Updated: 2023/05/18 17:35:21 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	check_rg(void *data, t_range r)
{
	t_vec3	*v;
	double	*f;

	if (r == HFOV || r == BRIGHT || r == SEGM)
		f = (double *)data;
	else
		v = (t_vec3 *)data;
	if (r == HFOV && (*f > 180 || *f < 0))
		return (false);
	else if (r == BRIGHT && (*f > 1 || *f < 0))
		return (false);
	else if (r == SEGM && (*f > INT_MAX || *f <= 0))//TODO
		return (false);
	else if (r == POINT && (v->x > INT_MAX || v->y > INT_MAX || v->z > INT_MAX)) //TODO
		return (false);
	else if (r == POINT && (v->x < INT_MIN || v->y < INT_MIN || v->z < INT_MIN))//TODO
		return (false);
	else if (r == NVEC && (v->x > 1 || v->y > 1 || v->z > 1))
		return (false);
	else if (r == NVEC && (v->x < -1 || v->y < -1 || v->z < -1))
		return (false);
	else if (r == COLRS && (v->x > 255 || v->x < 0 || v->y > 255 || \
		v->y < 0 || v->z > 255 || v->z < 0))
		return (false);
	return (true);
}
