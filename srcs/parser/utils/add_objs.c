/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_objs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:56:05 by drontome          #+#    #+#             */
/*   Updated: 2023/06/01 11:51:25 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_object_list	*obj_lstnew(void *obj, int type);
static void				obj_addbk(t_object_list **lst, t_object_list *new_obj);

void	*add_obj_to_scene(t_world *world, void *obj, int type)
{
	t_object_list	*elem;

	elem = obj_lstnew(obj, type);
	if (!elem)
		return (NULL);
	obj_addbk(&(world->objs), elem);
	return (obj);
}

static t_object_list	*obj_lstnew(void *obj, int type)
{
	t_object_list	*result;

	result = ft_calloc(1, sizeof(t_object_list));
	if (!result)
		return (NULL);
	result->type = type;
	result->obj = obj;
	result->next = NULL;
	return (result);
}

static void	obj_addbk(t_object_list **lst, t_object_list *new_obj)
{
	t_object_list	*last;

	if (!(*lst))
	{
		*lst = new_obj;
		new_obj->next = NULL;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new_obj;
	new_obj->next = NULL;
	return ;
}
