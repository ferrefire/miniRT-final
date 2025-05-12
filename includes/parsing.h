/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/11 14:01:36 by ferre         #+#    #+#                 */
/*   Updated: 2025/05/12 22:16:51 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minirt.h"
# include "vector.h"

typedef struct s_parse_config
{
	char	*str;
	int		bounds;
	float	min;
	float	max;
}				t_parse_config;

typedef struct s_parsed_vec
{
	t_vec	vec;
	int		valid;
}				t_parsed_vec;

typedef struct s_parsed_float
{
	float	value;
	int		valid;
}				t_parsed_float;

typedef struct s_parse_results
{
	t_parsed_vec	center;
	t_parsed_vec	normal;
	t_parsed_float	diameter;
	t_parsed_float	height;
	t_parsed_vec	color;
}				t_parse_results;

t_parsed_vec	parse_vec(t_parse_config config, t_data *data);
t_parsed_float	parse_float(t_parse_config config, t_data *data);
void			parse_camera(char **tokens, int token_count, t_data *data);
void			parse_light(char **tokens, int token_count, t_data *data);
void			parse_ambient(char **tokens, int token_count, t_data *data);
void			parse_sphere(char **tokens, int token_count,
					t_shapes *shapes, t_data *data);
void			parse_plane(char **tokens, int token_count,
					t_shapes *shapes, t_data *data);
void			parse_cylinder(char **tokens, int token_count,
					t_shapes *shapes, t_data *data);
void			parse_shape(char **tokens, int token_count,
					t_shapes *shapes, t_data *data);
void			handle_file(char *filename, t_data *data);
void			parse_file(int fd, t_data *data);
void			parse_line(char *line, t_data *data);

#endif
