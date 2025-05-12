/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   scene.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/11 14:32:44 by ferre         #+#    #+#                 */
/*   Updated: 2025/05/12 22:19:19 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "shapes.h"
# include "vector.h"

typedef struct s_ambient
{
	float	intensity;
	t_vec	color;
}				t_ambient;

typedef struct s_camera
{
	t_vec	position;
	t_vec	foward;
	t_vec	up;
	t_vec	right;
	float	fov;
	float	aspect_ratio;
	float	far;
	int		width;
	int		height;
}				t_camera;

typedef struct s_light
{
	float	intensity;
	t_vec	color;
	t_vec	source;
}				t_light;

typedef struct s_scene_data
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_shapes	shapes;
	float		step;
	int			c_count;
	int			l_count;
	int			a_count;
}				t_scene_data;

#endif