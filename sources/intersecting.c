/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersecting.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/10 22:49:31 by ferre         #+#    #+#                 */
/*   Updated: 2025/05/12 22:13:48 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "intersecting.h"
#include "vector.h"
#include "utilities.h"

#include <math.h>

t_hit	intersecting_sphere(t_vec point, t_sphere sphere)
{
	t_hit	hit;
	float	sphere_distance;

	hit.intersected = 0;
	sphere_distance = distance(point, sphere.center) - sphere.radius;
	if (sphere_distance <= 0.0)
	{
		hit.intersected = 1;
		hit.position = sphere.center;
		hit.normal = normalize(sub(point, sphere.center));
		hit.color = sphere.color;
	}
	hit.distance = fabs(sphere_distance);
	return (hit);
}

t_hit	intersecting_plane(t_vec point, t_plane plane)
{
	t_hit	hit;
	float	d;
	float	side;

	hit.intersected = 0;
	d = -(plane.normal.x * plane.position.x + plane.normal.y
			* plane.position.y + plane.normal.z * plane.position.z);
	side = plane.normal.x * point.x + plane.normal.y * point.y
		+ plane.normal.z * point.z + d;
	if (side <= 0.0)
	{
		hit.intersected = 1;
		hit.position = plane.position;
		hit.normal = plane.normal;
		hit.color = plane.color;
	}
	hit.distance = fabs(side);
	return (hit);
}

t_hit	intersecting_cylinder(t_vec point, t_cylinder cylinder)
{
	t_hit			hit;
	t_cylinder_data	cd;
	float			cy_dis;

	hit.intersected = 0;
	cd.base_vec = sub(point, cylinder.position);
	cd.t = dot(cd.base_vec, cylinder.axis);
	cd.axis_vec = mult(cylinder.axis, clamp(cd.t, cylinder.height
				* -0.5, cylinder.height * 0.5));
	cd.axis_point = add(cylinder.position, cd.axis_vec);
	cy_dis = distance(point, cd.axis_point) - cylinder.radius;
	if (cy_dis <= 0.0 && cd.t >= cylinder.height
		* -0.5 && cd.t <= cylinder.height * 0.5)
	{
		hit.intersected = 1;
		hit.position = cylinder.position;
		hit.normal = normalize(sub(point, cd.axis_point));
		hit.color = cylinder.color;
	}
	hit.distance = fabs(cy_dis);
	return (hit);
}

t_hit	check_intersections(t_ray ray, t_scene_data scene)
{
	t_intersect_data	id;

	id = get_intersection(1, scene.shapes.plane_count, ray, scene);
	if (id.hit.intersected)
		return (id.hit);
	id = get_intersection(2, scene.shapes.sphere_count, ray, scene);
	if (id.hit.intersected)
		return (id.hit);
	id = get_intersection(3, scene.shapes.cylinder_count, ray, scene);
	if (id.hit.intersected)
		return (id.hit);
	id.hit.intersected = 0;
	id.hit.distance = id.closest;
	return (id.hit);
}

t_intersect_data	get_intersection(int type, int count,
	t_ray ray, t_scene_data scene)
{
	t_intersect_data	id;
	int					i;

	i = 0;
	while (i < count)
	{
		if (type == 1)
			id.hit = intersecting_plane(ray.position, scene.shapes.planes[i]);
		else if (type == 2)
			id.hit = intersecting_sphere(ray.position, scene.shapes.spheres[i]);
		else if (type == 3)
			id.hit = intersecting_cylinder(ray.position,
					scene.shapes.cylinders[i]);
		if (id.hit.intersected)
			return (id);
		if (id.hit.distance < id.closest)
			id.closest = id.hit.distance;
		i++;
	}
	return (id);
}
