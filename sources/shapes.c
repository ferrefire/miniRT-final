/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shapes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/11 14:42:55 by ferre         #+#    #+#                 */
/*   Updated: 2025/05/12 03:53:49 by ferre         ########   odam.nl         */
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
		sizeof(t_sphere) * shapes->sphereCount,
		sizeof(t_sphere) * (shapes->sphereCount + 1));
	if (!shapes->spheres)
		quit_tokens(tokens, "Failed to allocate memory.\n", data);
	return (&shapes->spheres[shapes->sphereCount]);
}

t_plane	*add_plane(char **tokens, t_shapes *shapes, void *data)
{
	if (shapes->planes == NULL)
		shapes->planes = (t_plane *)malloc(sizeof(t_plane));
	else
		shapes->planes = (t_plane *)memory_realloc(shapes->planes,
		sizeof(t_plane) * shapes->planeCount,
		sizeof(t_plane) * (shapes->planeCount + 1));
	if (!shapes->planes)
		quit_tokens(tokens, "Failed to allocate memory.\n", data);
	return (&shapes->planes[shapes->planeCount]);
}

t_cylinder	*add_cylinder(char **tokens, t_shapes *shapes, void *data)
{
	if (shapes->cylinders == NULL)
		shapes->cylinders = (t_cylinder *)malloc(sizeof(t_cylinder));
	else
		shapes->cylinders = (t_cylinder *)memory_realloc(shapes->cylinders,
		sizeof(t_cylinder) * shapes->cylinderCount,
		sizeof(t_cylinder) * (shapes->cylinderCount + 1));
	if (!shapes->cylinders)
		quit_tokens(tokens, "Failed to allocate memory.\n", data);
	return (&shapes->cylinders[shapes->cylinderCount]);
}
