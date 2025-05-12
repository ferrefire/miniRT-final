/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shapes_parsing.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/12 00:09:02 by ferre         #+#    #+#                 */
/*   Updated: 2025/05/12 03:46:18 by ferre         ########   odam.nl         */
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

void	parse_shape(char **tokens, int token_count, t_shapes *shapes, t_data *data)
{
	if (ft_strncmp(tokens[0], "sp", 2) == 0)
		parse_sphere(tokens, token_count, shapes, data);
	else if (ft_strncmp(tokens[0], "pl", 2) == 0)
		parse_plane(tokens, token_count, shapes, data);
	else if (ft_strncmp(tokens[0], "cy", 2) == 0)
		parse_cylinder(tokens, token_count, shapes, data);
}

void	parse_sphere(char **tokens, int token_count, t_shapes *shapes, t_data *data)
{
	t_sphere		*sphere;
	t_parsed_vec	center;
	t_parsed_vec	color;
	t_parsed_float	diameter;

	if (token_count != 4)
		quit_tokens(tokens, "Invalid sphere token count.\n", data);
	center = parse_vec(tokens[1], 0, 0, 0, data);
	color = parse_vec(tokens[3], 1, 0, 255, data);
	diameter = parse_float(tokens[2], 0, 0, 0, data);
	if (!center.valid || !color.valid || !diameter.valid)
		quit_tokens(tokens, "Invalid sphere values.\n", data);
	sphere = add_sphere(tokens, shapes, data);
	sphere->center = center.vec;
	sphere->radius = fabs(diameter.value) * 0.5;
	sphere->color = color.vec;
	shapes->sphereCount++;
}

void	parse_plane(char **tokens, int token_count, t_shapes *shapes, t_data *data)
{
	t_plane			*plane;
	t_parsed_vec	position;
	t_parsed_vec	normal;
	t_parsed_vec	color;

	if (token_count != 4)
		quit_tokens(tokens, "Invalid plane token count.\n", data);
	position = parse_vec(tokens[1], 0, 0, 0, data);
	normal = parse_vec(tokens[2], 1, -1, 1, data);
	color = parse_vec(tokens[3], 1, 0, 255, data);
	if (!position.valid || !normal.valid || !color.valid)
		quit_tokens(tokens, "Invalid plane values.\n", data);
	plane = add_plane(tokens, shapes, data);
	plane->position = position.vec;
	plane->normal = normalize(normal.vec);
	plane->color = color.vec;
	shapes->planeCount++;
}

void	parse_cylinder(char **tokens, int token_count, t_shapes *shapes, t_data *data)
{
	t_cylinder		*cylinder;
	t_parsed_vec	center;
	t_parsed_vec	normal;
	t_parsed_float	diameter;
	t_parsed_float	height;
	t_parsed_vec	color;

	if (token_count != 6)
		quit_tokens(tokens, "Invalid cylinder token count.\n", data);
	center = parse_vec(tokens[1], 0, 0, 0, data);
	normal = parse_vec(tokens[2], 1, -1, 1, data);
	diameter = parse_float(tokens[3], 0, 0, 0, data);
	height = parse_float(tokens[4], 0, 0, 0, data);
	color = parse_vec(tokens[5], 1, 0, 255, data);
	if (!center.valid || !normal.valid || !diameter.valid || !height.valid || !color.valid)
		quit_tokens(tokens, "Invalid cylinder values.\n", data);
	cylinder = add_cylinder(tokens, shapes, data);
	cylinder->position = center.vec;
	cylinder->axis = normalize(normal.vec);
	cylinder->radius = fabs(diameter.value) * 0.5;
	cylinder->height = fabs(height.value);
	cylinder->color = color.vec;
	shapes->cylinderCount++;
}
