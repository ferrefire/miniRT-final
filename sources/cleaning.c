/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleaning.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/19 17:59:01 by ferre         #+#    #+#                 */
/*   Updated: 2025/05/12 19:01:11 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "cleaning.h"
#include "utilities.h"
#include "libft.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void	clean_shapes(t_shapes *shapes)
{
	if (shapes->spheres)
		free_memory(shapes->spheres);
	if (shapes->planes)
		free_memory(shapes->planes);
	if (shapes->cylinders)
		free_memory(shapes->cylinders);
}

void	clean_data(t_data *data)
{
	if (data != NULL)
	{
		if (data->current_line != NULL)
			clear(&data->current_line);
		if (data->open_fd != -1)
		{
			close(data->open_fd);
			get_next_line(data->open_fd);
		}
		clean_mlx(&data->mlx_data);
		clean_shapes(&data->scene_data.shapes);
		clear(&data);
	}
}

void	clean_mlx(t_mlx_data *data)
{
	if (data->mlx)
	{
		if (data->image_data.image)
		{
			mlx_destroy_image(data->mlx, data->image_data.image);
		}
		if (data->win)
		{
			mlx_clear_window(data->mlx, data->win);
			mlx_destroy_window(data->mlx, data->win);
		}
		mlx_destroy_display(data->mlx);
		clear(&data->mlx);
	}
}

void	clear(void *address)
{
	void	**memory;

	memory = (void **)address;
	if (memory != NULL)
	{
		if (*memory != NULL)
			free(*memory);
		*memory = NULL;
	}
}

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	if (!tokens)
		return ;
	while (tokens[i] != NULL)
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}
