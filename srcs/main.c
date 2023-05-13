/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 13:24:01 by drontome          #+#    #+#             */
/*   Updated: 2023/05/13 17:25:40 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"



int main(int argc, char **argv)
{
	if (check_scene(argc, argv))
		printf("HECHO\n");
	else
		printf("NO HECHO\n");
}
