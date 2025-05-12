/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/10 21:25:15 by ferre         #+#    #+#                 */
/*   Updated: 2025/05/12 22:17:05 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "minirt.h"
# include "vector.h"

typedef struct s_ray
{
	t_vec	position;
	t_vec	direction;
	t_vec	origin;
	t_vec	target;
	float	max;
}				t_ray;

t_ray	initiate_ray(int x, int y, t_camera camera);

#endif