/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/19 17:24:26 by ferre         #+#    #+#                 */
/*   Updated: 2025/05/12 19:46:40 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "initiation.h"
#include "cleaning.h"
#include "rendering.h"
#include "input.h"
#include "vector.h"
#include "utilities.h"
#include "parsing.h"
#include "mlx.h"

#include <stdio.h>
#include <stdlib.h>

void	quit(const char *msg, t_data *data)
{
	printf("Error\n");
	if (msg != NULL)
		printf("%s", msg);
	clean_data(data);
	exit(EXIT_FAILURE);
}

void	quit_tokens(char **tokens, const char *msg, t_data *data)
{
	free_tokens(tokens);
	quit(msg, data);
}

int	main(int argc, char *argv[])
{
	t_data	*data;

	if (argc != 2)
		quit("Invalid argument count.\n", NULL);
	data = initiate_data();
	handle_file(argv[1], data);
	set_hooks(data);
	mlx_loop_hook(data->mlx_data.mlx, render_image, data);
	mlx_loop(data->mlx_data.mlx);
	clean_data(data);
	exit(EXIT_SUCCESS);
}
