/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rendering.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/10 20:18:41 by ferre         #+#    #+#                 */
/*   Updated: 2025/05/13 16:25:37 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "minirt.h"
#include "rendering.h"
#include "intersecting.h"
#include "ray.h"
#include "utilities.h"
#include <math.h>

#include <stdio.h>

void	render_pixel(int x, int y, t_vec color, t_data *data)
{
	char	*dst;

	dst = data->mlx_data.image_data.address
		+ (y * data->mlx_data.image_data.line + x
			* (data->mlx_data.image_data.bpp / 8));
	*(unsigned int *)dst = (255 << 24 | (int)color.x << 16 | (int)color.y << 8
			| (int)color.z);
}

int	render_image(t_data *data)
{
	t_ray	current_ray;
	t_vec	pixel_color;

	if (data->y >= data->height)
		return (1);
	current_ray = initiate_ray(data->x, data->y, data->scene_data.camera);
	pixel_color = trace_ray(current_ray, data->scene_data);
	render_pixel(data->x, data->y, pixel_color, data);
	data->x += 1;
	if (data->x >= data->width)
	{
		data->x = 0;
		data->y += 1;
		mlx_put_image_to_window(data->mlx_data.mlx, data->mlx_data.win,
			data->mlx_data.image_data.image, 0, 0);
	}
	return (0);
}

t_vec	trace_ray(t_ray ray, t_scene_data sd)
{
	t_ray_data	rd;

	while (dis_sqr(ray.position, ray.origin) < sd.camera.far * sd.camera.far)
	{
		rd.hit = check_intersections(ray, sd);
		if (rd.hit.intersected)
		{
			rd.light_n = normalize(sub(sd.light.source, ray.position));
			rd.shadow = in_shadow((t_ray){ray.position, rd.light_n,
					ray.position, sd.light.source, distance(ray.position,
						sd.light.source)}, sd);
			rd.diff = dot(rd.hit.normal, rd.light_n) * rd.shadow;
			rd.reflect_n = sub(mult(rd.hit.normal, 2.0 * dot(rd.light_n,
							rd.hit.normal)), rd.light_n);
			rd.spec = pow(clamp(dot(mult(ray.direction, -1.0),
							rd.reflect_n), 0.0, 1.0), 4.0);
			return (calculate_light(rd, sd));
		}
		rd.closest = clamp(rd.hit.distance, sd.step, sd.camera.far);
		ray.position = add(ray.position, mult(ray.direction, rd.closest));
	}
	return ((t_vec){0, 0, 0});
}

float	in_shadow(t_ray ray, t_scene_data scene)
{
	t_hit	hit;
	float	closest;

	ray.position = add(ray.position, mult(ray.direction, 0.1));
	while (dis_sqr(ray.position, ray.origin) < ray.max * ray.max)
	{
		hit = check_intersections(ray, scene);
		if (hit.intersected)
			return (0.0);
		closest = clamp(hit.distance, scene.step, ray.max);
		ray.position = add(ray.position, mult(ray.direction, closest));
	}
	return (1.0);
}

t_vec	calculate_light(t_ray_data rd, t_scene_data scene)
{
	t_vec	result;
	t_vec	ambient;
	t_vec	direct;
	t_vec	specular;

	ambient = mult(scene.ambient.color, scene.ambient.intensity);
	direct = mult(mult(scene.light.color, scene.light.intensity), rd.diff);
	specular = mult(direct, rd.spec);
	result = clamp_vec(add(ambient, direct), 0, 255);
	return (clamp_vec(add(mult_col(result, rd.hit.color), specular), 0, 255));
}
