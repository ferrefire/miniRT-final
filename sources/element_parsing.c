/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   element_parsing.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/11 23:09:16 by ferre         #+#    #+#                 */
/*   Updated: 2025/05/12 03:45:27 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parsing.h"
#include "vector.h"
#include "scene.h"
#include "shapes.h"
#include "cleaning.h"
#include "utilities.h"
#include "libft.h"

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

void	parse_camera(char **tokens, int token_count, t_data *data)
{
	t_parsed_vec	position;
	t_parsed_vec	foward;
	t_parsed_float	fov;

	if (token_count != 4)
		quit_tokens(tokens, "Invalid camera token count.\n", data);
	if (data->scene_data.c_count > 0)
		quit_tokens(tokens, "Multiple cameras found.\n", data);
	position = parse_vec(tokens[1], 0, 0, 0, data);
	foward = parse_vec(tokens[2], 1, -1, 1, data);
	fov = parse_float(tokens[3], 1, 0, 180, data);
	if (!position.valid || !foward.valid || !fov.valid)
		quit_tokens(tokens, "Invalid camera values.\n", data);
	data->scene_data.camera.position = position.vec;
	data->scene_data.camera.foward = normalize(foward.vec);
	data->scene_data.camera.right = normalize(cross(foward.vec, (t_vec){0, 1, 0}));
	data->scene_data.camera.up = normalize(cross(foward.vec, data->scene_data.camera.right));
	data->scene_data.camera.fov = fov.value;
	data->scene_data.c_count = 1;
}

void	parse_light(char **tokens, int token_count, t_data *data)
{
	t_parsed_vec	source;
	t_parsed_float	intensity;
	t_parsed_vec	color;

	if (token_count != 4)
		quit_tokens(tokens, "Invalid light token count.\n", data);
	if (data->scene_data.l_count > 0)
		quit_tokens(tokens, "Multiple lights found.\n", data);
	source = parse_vec(tokens[1], 0, 0, 0, data);
	color = parse_vec(tokens[3], 1, 0, 255, data);
	intensity = parse_float(tokens[2], 1, 0, 1, data);
	if (!source.valid || !color.valid || !intensity.valid)
		quit_tokens(tokens, "Invalid light values.\n", data);
	data->scene_data.light.source = source.vec;
	data->scene_data.light.intensity = intensity.value;
	data->scene_data.light.color = color.vec;
	data->scene_data.l_count = 1;
}

void	parse_ambient(char **tokens, int token_count, t_data *data)
{
	t_parsed_float	intensity;
	t_parsed_vec	color;

	if (token_count != 3)
		quit_tokens(tokens, "Invalid ambient token count.\n", data);
	if (data->scene_data.a_count > 0)
		quit_tokens(tokens, "Multiple ambients found.\n", data);
	intensity = parse_float(tokens[1], 1, 0, 1, data);
	color = parse_vec(tokens[2], 1, 0, 255, data);
	if (!color.valid || !intensity.valid)
		quit_tokens(tokens, "Invalid ambient values.\n", data);
	data->scene_data.ambient.intensity = intensity.value;
	data->scene_data.ambient.color = color.vec;
	data->scene_data.a_count = 1;
}

t_parsed_vec	parse_vec(char *str, int bounds, float min, float max, t_data *data)
{
	t_parsed_vec	result;
	char			**tokens;
	int				token_count;

	result.valid = 0;
	tokens = ft_split(str, ',');
	token_count = 0;
	while (tokens && tokens[token_count])
		token_count++;
	if (token_count == 3 && is_float(tokens[0]) && is_float(tokens[1]) && is_float(tokens[2]))
	{
		result.valid = 1;
		result.vec.x = ft_atof(tokens[0]);
		if (bounds && (result.vec.x < min || result.vec.x > max))
			result.valid = 0;
		result.vec.y = ft_atof(tokens[1]);
		if (bounds && (result.vec.y < min || result.vec.y > max))
			result.valid = 0;
		result.vec.z = ft_atof(tokens[2]);
		if (bounds && (result.vec.z < min || result.vec.z > max))
			result.valid = 0;
	}
	free_tokens(tokens);
	return (result);
}

t_parsed_float	parse_float(char *str, int bounds, float min, float max, t_data *data)
{
	t_parsed_float	result;

	result.valid = 0;
	if (is_float(str))
	{
		result.value = ft_atof(str);
		if (!bounds || (result.value >= min && result.value <= max))
			result.valid = 1;
	}
	return (result);
}
