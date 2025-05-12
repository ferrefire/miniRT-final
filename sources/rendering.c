/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rendering.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/10 20:18:41 by ferre         #+#    #+#                 */
/*   Updated: 2025/05/12 03:52:45 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "minirt.h"
#include "rendering.h"
#include "intersecting.h"
#include "ray.h"
#include "utilities.h"
#include <math.h>

#include <stdio.h>

int	colorToInt(t_vec color)
{
	return (255 << 24 | (int)color.x << 16 | (int)color.y << 8 | (int)color.z);
}

void	renderPixel(int x, int y, t_vec color, t_data *data)
{
	char	*dst;

	dst = data->mlx_data.image_data.address + (y * data->mlx_data.image_data.line + x * (data->mlx_data.image_data.bpp / 8));
	*(unsigned int *)dst = colorToInt(color);
}

int	renderImage(t_data *data)
{
	t_ray	currentRay;
	t_vec	pixelColor;

	if (data->y >= data->height)
		return (1);
	currentRay = initiateRay(data->x, data->y, data->width, data->height, data->scene_data.camera);
	pixelColor = traceRay(currentRay, data->scene_data);
	renderPixel(data->x, data->y, pixelColor, data);
	data->x += 1;
	if (data->x >= data->width)
	{
		data->x = 0;
		data->y += 1;
		//if (data->y >= data->height)
		//	printf("image rendered in %ld seconds\n", (time(NULL) - data->start));
		mlx_put_image_to_window(data->mlx_data.mlx, data->mlx_data.win, data->mlx_data.image_data.image, 0, 0);
	}
	return (0);
}

t_vec	traceRay(t_ray ray, t_scene_data scene)
{
	t_hit	hitInfo;
	t_vec	lightNormal;
	t_vec	specularColor;
	t_vec	reflectionNormal;
	float	shadow;
	float	diffuse;
	float	specular;
	float	closest;

	while (distanceSquared(ray.position, ray.origin) < scene.camera.far * scene.camera.far)
	{
		hitInfo = checkIntersections(ray, scene);
		if (hitInfo.intersected)
		{
			lightNormal = normalize(sub(scene.light.source, ray.position));
			shadow = inShadow((t_ray){ray.position, lightNormal, ray.position, scene.light.source, 
				distance(ray.position, scene.light.source)}, scene);
			diffuse = clamp(dot(hitInfo.normal, lightNormal) * shadow, scene.ambient.intensity, 1.0);
			reflectionNormal = sub(mult(hitInfo.normal, 2.0 * dot(lightNormal, hitInfo.normal)), lightNormal);
			specular = pow(clamp(dot(mult(ray.direction, -1.0), reflectionNormal), 0.0, 1.0), 4.0);
			specularColor = mult(WHITE, specular);
			return (clampVec(mult(add(hitInfo.color, specularColor), diffuse), 0.0, 255.0));
		}
		closest = clamp(hitInfo.distance, scene.step, scene.camera.far);
		ray.position = add(ray.position, mult(ray.direction, closest));
	}

	return (BLACK);
}

float	inShadow(t_ray ray, t_scene_data scene)
{
	t_hit	hitInfo;
	float	closest;

	ray.position = add(ray.position, mult(ray.direction, 0.1));
	while (distanceSquared(ray.position, ray.origin) < ray.max * ray.max)
	{
		hitInfo = checkIntersections(ray, scene);
		if (hitInfo.intersected)
			return (0.0);
		closest = clamp(hitInfo.distance, scene.step, ray.max);
		ray.position = add(ray.position, mult(ray.direction, closest));
	}
	return (1.0);
}

t_hit	checkIntersections(t_ray ray, t_scene_data scene)
{
	t_hit	hitInfo;
	float	closest;
	int		i;

	closest = 10000.0;
	i = 0;
	while (i < scene.shapes.planeCount)
	{
		hitInfo = intersectingPlane(ray.position, scene.shapes.planes[i]);
		if (hitInfo.intersected)
			return (hitInfo);
		if (hitInfo.distance < closest)
			closest = hitInfo.distance;
		i++;
	}
	i = 0;
	while (i < scene.shapes.sphereCount)
	{
		hitInfo = intersectingSphere(ray.position, scene.shapes.spheres[i]);
		if (hitInfo.intersected)
			return (hitInfo);
		if (hitInfo.distance < closest)
			closest = hitInfo.distance;
		i++;
	}
	i = 0;
	while (i < scene.shapes.cylinderCount)
	{
		hitInfo = intersectingCylinder(ray.position, scene.shapes.cylinders[i]);
		if (hitInfo.intersected)
			return (hitInfo);
		if (hitInfo.distance < closest)
			closest = hitInfo.distance;
		i++;
	}
	hitInfo.intersected = 0;
	hitInfo.distance = closest;
	return (hitInfo);
}
