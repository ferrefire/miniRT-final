/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initiation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/19 17:55:00 by ferre         #+#    #+#                 */
/*   Updated: 2025/05/12 22:19:19 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "minirt.h"
#include "initiation.h"
#include "parsing.h"

#include <stdio.h>
#include <stdlib.h>

t_data	*initiate_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->x = 0;
	data->y = 0;
	data->width = 400;
	data->height = 400;
	data->open_fd = -1;
	data->current_line = NULL;
	initiate_scene(&data->scene_data, data);
	initiate_mlx(&data->mlx_data, data);
	return (data);
}

void	initiate_mlx(t_mlx_data *mlx_data, t_data *data)
{
	mlx_data->mlx = NULL;
	mlx_data->win = NULL;
	mlx_data->image_data.image = NULL;
	mlx_data->image_data.address = NULL;
	mlx_data->width = data->width;
	mlx_data->height = data->height;
	mlx_data->mlx = mlx_init();
	mlx_data->win = mlx_new_window(mlx_data->mlx, mlx_data->width,
			mlx_data->height, "test");
	mlx_data->image_data.image = mlx_new_image(mlx_data->mlx,
			mlx_data->width, mlx_data->height);
	mlx_data->image_data.address = mlx_get_data_addr(mlx_data->image_data.image,
			&mlx_data->image_data.bpp, &mlx_data->image_data.line,
			&mlx_data->image_data.endian);
}

void	initiate_scene(t_scene_data *sd, t_data *data)
{
	sd->camera.position = (t_vec){0, 0, 0};
	sd->camera.foward = (t_vec){0, 0, 1};
	sd->camera.right = normalize(cross(sd->camera.foward, (t_vec){0, 1, 0}));
	sd->camera.up = normalize(cross(sd->camera.right, sd->camera.foward));
	sd->camera.fov = 45;
	sd->camera.aspect_ratio = (float)data->width / (float)data->height;
	sd->camera.width = data->width;
	sd->camera.height = data->height;
	sd->c_count = 0;
	sd->ambient.color = (t_vec){255, 255, 255};
	sd->ambient.intensity = 0.1;
	sd->a_count = 0;
	sd->light.color = (t_vec){255, 255, 255};
	sd->light.intensity = 1.0;
	sd->light.source = normalize((t_vec){1, 1, -1});
	sd->l_count = 0;
	sd->shapes.spheres = NULL;
	sd->shapes.sphere_count = 0;
	sd->shapes.planes = NULL;
	sd->shapes.plane_count = 0;
	sd->shapes.cylinders = NULL;
	sd->shapes.cylinder_count = 0;
	sd->step = 0.005;
	sd->camera.far = 50.0;
}
