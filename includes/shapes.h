/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shapes.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/11 14:02:36 by ferre         #+#    #+#                 */
/*   Updated: 2025/05/12 22:19:38 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

# include "minirt.h"
# include "vector.h"

# define PI 3.141592654

typedef struct s_sphere
{
	int		type;
	t_vec	color;
	t_vec	center;
	float	radius;
	float	radius_squared;
}				t_sphere;

typedef struct s_plane
{
	int		type;
	t_vec	color;
	t_vec	position;
	t_vec	normal;
}				t_plane;

typedef struct s_cylinder
{
	int		type;
	t_vec	color;
	t_vec	position;
	t_vec	axis;
	float	radius;
	float	height;
}				t_cylinder;

typedef struct s_shapes
{
	t_sphere	*spheres;
	int			sphere_count;
	t_plane		*planes;
	int			plane_count;
	t_cylinder	*cylinders;
	int			cylinder_count;
}				t_shapes;

t_sphere	*add_sphere(char **tokens, t_shapes *shapes, void *data);
t_plane		*add_plane(char **tokens, t_shapes *shapes, void *data);
t_cylinder	*add_cylinder(char **tokens, t_shapes *shapes, void *data);

#endif