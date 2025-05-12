/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initiation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/19 17:55:00 by ferre         #+#    #+#                 */
/*   Updated: 2025/05/12 03:43:49 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "minirt.h"
#include "initiation.h"
#include "parsing.h"

#include <stdio.h>
#include <stdlib.h>

t_data	*initiateData(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	//data->start = time(NULL);
	data->x = 0;
	data->y = 0;
	data->width = 400;
	data->height = 400;
	data->open_fd = -1;
	data->current_line = NULL;
	initiateScene(&data->scene_data, data);
	initiateMLX(&data->mlx_data, data);
	return (data);
}

void	initiateMLX(t_mlx_data *mlx_data, t_data *data)
{
	mlx_data->mlx = NULL;
	mlx_data->win = NULL;
	mlx_data->image_data.image = NULL;
	mlx_data->image_data.address = NULL;
	mlx_data->width = data->width;
	mlx_data->height = data->height;
	mlx_data->mlx = mlx_init();
	mlx_data->win = mlx_new_window(mlx_data->mlx, mlx_data->width, mlx_data->height, "test");
	mlx_data->image_data.image = mlx_new_image(mlx_data->mlx, mlx_data->width, mlx_data->height);
	mlx_data->image_data.address = mlx_get_data_addr(mlx_data->image_data.image, &mlx_data->image_data.bpp, &mlx_data->image_data.line, &mlx_data->image_data.endian);
}

void	initiateScene(t_scene_data *scene_data, t_data *data)
{
	scene_data->camera.position = (t_vec){0, 0, 0};
	scene_data->camera.foward = (t_vec){0, 0, 1};
	scene_data->camera.right = normalize(cross(scene_data->camera.foward, (t_vec){0, 1, 0}));
	scene_data->camera.up = normalize(cross(scene_data->camera.right, scene_data->camera.foward));
	scene_data->camera.fov = 45;
	scene_data->camera.aspectRatio = (float)data->width / (float)data->height;
	scene_data->c_count = 0;
	scene_data->ambient.color = (t_vec){255, 255, 255};
	scene_data->ambient.intensity = 0.1;
	scene_data->a_count = 0;
	scene_data->light.color = (t_vec){255, 255, 255};
	scene_data->light.intensity = 1.0;
	scene_data->light.source = normalize((t_vec){1, 1, -1});
	scene_data->l_count = 0;
	scene_data->shapes.spheres = NULL;
	scene_data->shapes.sphereCount = 0;
	scene_data->shapes.planes = NULL;
	scene_data->shapes.planeCount = 0;
	scene_data->shapes.cylinders = NULL;
	scene_data->shapes.cylinderCount = 0;
	scene_data->step = 0.005;
	scene_data->camera.far = 50.0;
}
