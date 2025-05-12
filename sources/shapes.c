/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shapes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/11 14:42:55 by ferre         #+#    #+#                 */
/*   Updated: 2025/05/12 21:54:59 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "shapes.h"
#include "parsing.h"
#include "libft.h"
#include "utilities.h"
#include "vector.h"

#include <math.h>
#include <stdio.h>

t_sphere	*add_sphere(char **tokens, t_shapes *shapes, void *data)
{
	if (shapes->spheres == NULL)
		shapes->spheres = (t_sphere *)malloc(sizeof(t_sphere));
	else
		shapes->spheres = (t_sphere *)memory_realloc(shapes->spheres,
				sizeof(t_sphere) * shapes->sphere_count,
				sizeof(t_sphere) * (shapes->sphere_count + 1));
	if (!shapes->spheres)
		quit_tokens(tokens, "Failed to allocate memory.\n", data);
	return (&shapes->spheres[shapes->sphere_count]);
}

t_plane	*add_plane(char **tokens, t_shapes *shapes, void *data)
{
	if (shapes->planes == NULL)
		shapes->planes = (t_plane *)malloc(sizeof(t_plane));
	else
		shapes->planes = (t_plane *)memory_realloc(shapes->planes,
				sizeof(t_plane) * shapes->plane_count,
				sizeof(t_plane) * (shapes->plane_count + 1));
	if (!shapes->planes)
		quit_tokens(tokens, "Failed to allocate memory.\n", data);
	return (&shapes->planes[shapes->plane_count]);
}

t_cylinder	*add_cylinder(char **tokens, t_shapes *shapes, void *data)
{
	if (shapes->cylinders == NULL)
		shapes->cylinders = (t_cylinder *)malloc(sizeof(t_cylinder));
	else
		shapes->cylinders = (t_cylinder *)memory_realloc(shapes->cylinders,
				sizeof(t_cylinder) * shapes->cylinder_count,
				sizeof(t_cylinder) * (shapes->cylinder_count + 1));
	if (!shapes->cylinders)
		quit_tokens(tokens, "Failed to allocate memory.\n", data);
	return (&shapes->cylinders[shapes->cylinder_count]);
}
