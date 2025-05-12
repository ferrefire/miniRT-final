/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersecting.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/10 22:48:45 by ferre         #+#    #+#                 */
/*   Updated: 2025/05/12 22:14:15 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTING_H
# define INTERSECTING_H

# include "minirt.h"
# include "vector.h"
# include "rendering.h"
# include "shapes.h"

typedef struct s_distance_data
{
	t_vec	nearest;
	float	closest;
	float	current;
	float	offset;
	int		i;
}				t_distance_data;

typedef struct s_cylinder_data
{
	t_vec	base_vec;
	t_vec	axis_vec;
	t_vec	axis_point;
	float	t;
}				t_cylinder_data;

typedef struct s_intersect_data
{
	t_hit	hit;
	float	closest;
}				t_intersect_data;

t_hit				intersecting_sphere(t_vec point, t_sphere sphere);
t_hit				intersecting_plane(t_vec point, t_plane plane);
t_hit				intersecting_cylinder(t_vec point, t_cylinder cylinder);
t_hit				check_intersections(t_ray ray, t_scene_data scene);
t_intersect_data	get_intersection(int type, int count, t_ray ray,
						t_scene_data scene);
float				closest_sphere(t_vec point, t_shapes *shapes);
float				closest_cylinder(t_vec point, t_shapes *shapes);
float				closest_plane(t_vec point, t_shapes *shapes);
float				closest_shape(t_vec point, t_shapes *shapes);

#endif