/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/11 14:11:00 by ferre         #+#    #+#                 */
/*   Updated: 2025/05/12 03:44:41 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parsing.h"
#include "vector.h"
#include "scene.h"
#include "shapes.h"
#include "cleaning.h"
#include "libft.h"

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

void	handle_file(char *filename, t_data *data)
{
	int	len;
	int	fd;

	len = ft_strlen(filename);
	if (len <= 3 || ft_strncmp(filename + (len - 3), ".rt", 3) != 0)
		quit("Invalid file extension.\n", data);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		quit("Cannot open file.\n", data);
	data->open_fd = fd;
	parse_file(fd, data);
	close(fd);
	data->open_fd = -1;
	if (data->scene_data.c_count == 0)
		quit("No camera found.\n", data);
	else if (data->scene_data.l_count == 0)
		quit("No light found.\n", data);
	else if (data->scene_data.a_count == 0)
		quit("No ambient found.\n", data);
}

void	parse_file(int fd, t_data *data)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line[0] == '\0' || line[0] == '\n' || line[0] == '#')
		{
			free(line);
			line = get_next_line(fd);
			continue;
		}
		parse_line(line, data);
		free(line);
		line = get_next_line(fd);
	}
}

void	parse_line(char *line, t_data *data)
{
	char	**tokens;
	int		token_count;
	int		len;

	tokens = ft_split(line, ' ');
	if (tokens == NULL || tokens[0] == NULL)
		return;
	token_count = 0;
	while (tokens && tokens[token_count])
		token_count++;
	len = ft_strlen(tokens[0]);
	data->current_line = line;
	if (len == 1 && ft_strncmp(tokens[0], "C", 1) == 0)
		parse_camera(tokens, token_count, data);
	else if (len == 1 && ft_strncmp(tokens[0], "L", 1) == 0)
		parse_light(tokens, token_count, data);
	else if (len == 1 && ft_strncmp(tokens[0], "A", 1) == 0)
		parse_ambient(tokens, token_count, data);
	else if (len == 2 && (ft_strncmp(tokens[0], "sp", 2) == 0 || ft_strncmp(tokens[0], "pl", 2) == 0 || ft_strncmp(tokens[0], "cy", 2) == 0))
		parse_shape(tokens, token_count, &data->scene_data.shapes, data);
	else
		quit_tokens(tokens, "Invalid element type.\n", data);
	free_tokens(tokens);
	data->current_line = NULL;
}
