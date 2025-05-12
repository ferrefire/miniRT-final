/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/10 20:27:41 by ferre         #+#    #+#                 */
/*   Updated: 2025/05/12 19:11:16 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "minirt.h"
#include "input.h"
#include "cleaning.h"

#include <stdio.h>

int	key_pressed(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		mlx_loop_end(data->mlx_data.mlx);
	return (keycode);
}

void	set_hooks(t_data *data)
{
	mlx_hook(data->mlx_data.win, 2, 1L << 0, key_pressed, data);
	mlx_hook(data->mlx_data.win, 17, 1L << 0, mlx_loop_end, data->mlx_data.mlx);
}
