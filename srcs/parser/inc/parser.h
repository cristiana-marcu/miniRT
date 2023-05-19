/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 13:21:03 by drontome          #+#    #+#             */
/*   Updated: 2023/05/08 18:31:46 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/* ************************************************************************** */
/*                                 INCLUDES                                   */
/* ************************************************************************** */

# include "errors.h"
# include "libft.h"
# include "objects.h"
# include <errno.h>
# include <fcntl.h>
# include <mlx.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

/* ************************************************************************** */
/*                                  DEFINES                                   */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                  STRUCTS                                   */
/* ************************************************************************** */

typedef struct s_pars
{
	u_int16_t	errors;
	int			fd;
	bool		dup[3];
	char		*line;
	t_world		world;

}				t_pars;

/* ************************************************************************** */
/*                                   ENUMS                                    */
/* ************************************************************************** */
typedef enum e_may
{
	AMB,
	CAM,
	LIT,
}				t_may;

typedef enum e_range
{
	POINT,
	NVEC,
	HFOV,
	BRIGHT,
	COLRS,
	SEGM,
}				t_range;

/* ************************************************************************** */
/*                                 PROTOTYPES                                 */
/* ************************************************************************** */
bool			check_scene(int argc, char **argv);
t_world			*load_scene(char *scene);
void			load_amb(t_pars *pars, char **tokens);
void			load_cam(t_pars *pars, char **tokens);
void			load_light(t_pars *pars, char **tokens);
void			load_sp(t_pars *pars, char **tokens);
double			get_dob(char *str, bool *is_right, t_range r);
t_vec3			get_vector(char *str, bool *is_right, t_range r);
bool			check_right(bool *is_right, int size);
bool			check_rg(void *data, t_range r);
void			free_objs(t_object_list **lst, void (*del)(void*));
void 			init_mlx(t_data	*data);
void			start_rt(t_data *data);

//double			get_bright(char *str);
//t_vec3			get_colours(char *str);

#endif