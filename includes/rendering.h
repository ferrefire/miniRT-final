/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rendering.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/10 20:20:55 by ferre         #+#    #+#                 */
/*   Updated: 2025/05/13 16:14:27 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

# include "minirt.h"
# include "ray.h"
# include "vector.h"

typedef struct s_hit
{
	int		intersected;
	t_vec	position;
	t_vec	normal;
	t_vec	color;
	float	distance;
}				t_hit;

typedef struct s_ray_data
{
	t_hit	hit;
	t_vec	light_n;
	t_vec	spec_c;
	t_vec	reflect_n;
	float	shadow;
	float	diff;
	float	spec;
	float	closest;
}				t_ray_data;

void	render_pixel(int x, int y, t_vec color, t_data *data);
int		render_image(t_data *data);
t_vec	trace_ray(t_ray ray, t_scene_data scene);
float	in_shadow(t_ray ray, t_scene_data scene);
t_vec	calculate_light(t_ray_data rd, t_scene_data scene);

#endif