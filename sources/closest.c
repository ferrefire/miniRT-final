/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   closest.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/12 19:33:17 by ferre         #+#    #+#                 */
/*   Updated: 2025/05/12 22:13:48 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "intersecting.h"
#include "vector.h"
#include "utilities.h"

#include <math.h>

float	closest_sphere(t_vec point, t_shapes *shapes)
{
	t_distance_data	dd;

	dd.i = 0;
	dd.closest = 10000.0;
	while (dd.i < shapes->sphere_count)
	{
		dd.current = dis_sqr(point, shapes->spheres[dd.i].center)
			- (shapes->spheres[dd.i].radius
				* shapes->spheres[dd.i].radius);
		if (dd.current < dd.closest)
		{
			dd.closest = dd.current;
			dd.nearest = shapes->spheres[dd.i].center;
			dd.offset = shapes->spheres[dd.i].radius;
		}
		dd.i++;
	}
	if (dd.closest < 10000.0)
		return (distance(point, dd.nearest) - dd.offset);
	return (dd.closest);
}

float	closest_cylinder(t_vec point, t_shapes *shapes)
{
	t_distance_data	dd;
	t_cylinder_data	cd;

	dd.i = 0;
	dd.closest = 10000.0;
	while (dd.i < shapes->cylinder_count)
	{
		cd.base_vec = sub(point, shapes->cylinders[dd.i].position);
		cd.t = dot(cd.base_vec, shapes->cylinders[dd.i].axis);
		cd.axis_vec = mult(shapes->cylinders[dd.i].axis, cd.t);
		cd.axis_point = add(shapes->cylinders[dd.i].position, cd.axis_vec);
		dd.current = dis_sqr(point, cd.axis_point)
			- (shapes->cylinders[dd.i].radius
				* shapes->cylinders[dd.i].radius);
		if (dd.current < dd.closest)
		{
			dd.closest = dd.current;
			dd.nearest = cd.axis_point;
			dd.offset = shapes->cylinders[dd.i].radius;
		}
		dd.i++;
	}
	if (dd.closest < 10000.0)
		return (distance(point, dd.nearest) - dd.offset);
	return (dd.closest);
}

float	closest_plane(t_vec point, t_shapes *shapes)
{
	t_distance_data	dd;
	float			d;
	float			side;
	int				i;

	i = 0;
	dd.closest = 10000.0;
	while (i < shapes->plane_count)
	{
		d = -(shapes->planes[i].normal.x * shapes->planes[i].position.x
				+ shapes->planes[i].normal.y * shapes->planes[i].position.y
				+ shapes->planes[i].normal.z * shapes->planes[i].position.z);
		side = shapes->planes[i].normal.x * point.x + shapes->planes[i].normal.y
			* point.y + shapes->planes[i].normal.z * point.z + d;
		dd.current = fabs(side);
		if (dd.current < dd.closest)
		{
			dd.closest = dd.current;
		}
		i++;
	}
	return (dd.closest);
}

float	closest_shape(t_vec point, t_shapes *shapes)
{
	float	nearest_plane;
	float	nearest_sphere;
	float	nearest_cylinder;
	float	smallest_distance;

	smallest_distance = 0.01;
	nearest_plane = closest_plane(point, shapes);
	if (nearest_plane <= smallest_distance)
		return (nearest_plane);
	nearest_sphere = closest_sphere(point, shapes);
	if (nearest_sphere <= smallest_distance)
		return (nearest_sphere);
	nearest_cylinder = closest_cylinder(point, shapes);
	if (nearest_plane < nearest_sphere && nearest_plane < nearest_cylinder)
		return (nearest_plane);
	else if (nearest_sphere < nearest_cylinder)
		return (nearest_sphere);
	else
		return (nearest_cylinder);
}
