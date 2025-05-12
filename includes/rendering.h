/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rendering.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/10 20:20:55 by ferre         #+#    #+#                 */
/*   Updated: 2025/05/12 04:04:27 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
#define RENDERING_H

#include "minirt.h"
#include "ray.h"
#include "vector.h"

#define WHITE (t_vec){255, 255, 255}
#define BLACK (t_vec){0, 0, 0}
#define RED (t_vec){255, 0, 0}
#define GREEN (t_vec){0, 255, 0}
#define BLUE (t_vec){0, 0, 255}

typedef struct	s_hit
{
	int		intersected;
	t_vec	position;
	t_vec	normal;
	t_vec	color;
	float	distance;
}				t_hit;

int		colorToInt(t_vec color);
void	renderPixel(int x, int y, t_vec color, t_data *data);
int		renderImage(t_data *data);
t_vec	traceRay(t_ray ray, t_scene_data scene);
float	inShadow(t_ray ray, t_scene_data scene);
t_hit	checkIntersections(t_ray ray, t_scene_data scene);

#endif