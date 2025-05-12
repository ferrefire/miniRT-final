/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/10 22:35:50 by ferre         #+#    #+#                 */
/*   Updated: 2025/05/12 22:19:19 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ray.h"

#include <math.h>

t_ray	initiate_ray(int x, int y, t_camera camera)
{
	t_ray	result;
	float	u;
	float	v;

	u = 1.0 - 2.0 * (x + 0.5) / (float)camera.width;
	v = 2.0 * ((y + 0.5) / (float)camera.height) - 1.0;
	u = u * tan(camera.fov * 0.5 * PI / 180.0) * camera.aspect_ratio;
	v = v * tan(camera.fov * 0.5 * PI / 180.0);
	result.direction = normalize(add(add(mult(camera.right, u),
					mult(camera.up, v)), camera.foward));
	result.position = camera.position;
	result.origin = camera.position;
	result.target = add(result.origin, mult(result.direction, camera.far));
	result.max = camera.far;
	return (result);
}
