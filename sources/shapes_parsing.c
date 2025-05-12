/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shapes_parsing.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/12 00:09:02 by ferre         #+#    #+#                 */
/*   Updated: 2025/05/12 21:54:17 by ferre         ########   odam.nl         */
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

void	parse_shape(char **tokens, int token_count,
	t_shapes *shapes, t_data *data)
{
	if (ft_strncmp(tokens[0], "sp", 2) == 0)
		parse_sphere(tokens, token_count, shapes, data);
	else if (ft_strncmp(tokens[0], "pl", 2) == 0)
		parse_plane(tokens, token_count, shapes, data);
	else if (ft_strncmp(tokens[0], "cy", 2) == 0)
		parse_cylinder(tokens, token_count, shapes, data);
}

void	parse_sphere(char **tokens, int token_count,
	t_shapes *shapes, t_data *data)
{
	t_sphere		*sphere;
	t_parse_results	pr;

	if (token_count != 4)
		quit_tokens(tokens, "Invalid sphere token count.\n", data);
	pr.center = parse_vec((t_parse_config){tokens[1], 0, 0, 0}, data);
	pr.color = parse_vec((t_parse_config){tokens[3], 1, 0, 255}, data);
	pr.diameter = parse_float((t_parse_config){tokens[2], 0, 0, 0}, data);
	if (!pr.center.valid || !pr.color.valid || !pr.diameter.valid)
		quit_tokens(tokens, "Invalid sphere values.\n", data);
	sphere = add_sphere(tokens, shapes, data);
	sphere->center = pr.center.vec;
	sphere->radius = fabs(pr.diameter.value) * 0.5;
	sphere->color = pr.color.vec;
	shapes->sphere_count++;
}

void	parse_plane(char **tokens, int token_count,
	t_shapes *shapes, t_data *data)
{
	t_plane			*plane;
	t_parse_results	pr;

	if (token_count != 4)
		quit_tokens(tokens, "Invalid plane token count.\n", data);
	pr.center = parse_vec((t_parse_config){tokens[1], 0, 0, 0}, data);
	pr.normal = parse_vec((t_parse_config){tokens[2], 1, -1, 1}, data);
	pr.color = parse_vec((t_parse_config){tokens[3], 1, 0, 255}, data);
	if (!pr.center.valid || !pr.normal.valid || !pr.color.valid)
		quit_tokens(tokens, "Invalid plane values.\n", data);
	plane = add_plane(tokens, shapes, data);
	plane->position = pr.center.vec;
	plane->normal = normalize(pr.normal.vec);
	plane->color = pr.color.vec;
	shapes->plane_count++;
}

void	parse_cylinder(char **tokens, int token_count,
	t_shapes *shapes, t_data *data)
{
	t_cylinder		*cylinder;
	t_parse_results	pr;

	if (token_count != 6)
		quit_tokens(tokens, "Invalid cylinder token count.\n", data);
	pr.center = parse_vec((t_parse_config){tokens[1], 0, 0, 0}, data);
	pr.normal = parse_vec((t_parse_config){tokens[2], 1, -1, 1}, data);
	pr.diameter = parse_float((t_parse_config){tokens[3], 0, 0, 0}, data);
	pr.height = parse_float((t_parse_config){tokens[4], 0, 0, 0}, data);
	pr.color = parse_vec((t_parse_config){tokens[5], 1, 0, 255}, data);
	if (!pr.center.valid || !pr.normal.valid || !pr.diameter.valid
		|| !pr.height.valid || !pr.color.valid)
		quit_tokens(tokens, "Invalid cylinder values.\n", data);
	cylinder = add_cylinder(tokens, shapes, data);
	cylinder->position = pr.center.vec;
	cylinder->axis = normalize(pr.normal.vec);
	cylinder->radius = fabs(pr.diameter.value) * 0.5;
	cylinder->height = fabs(pr.height.value);
	cylinder->color = pr.color.vec;
	shapes->cylinder_count++;
}
