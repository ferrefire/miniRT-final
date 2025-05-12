/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersecting.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/10 22:49:31 by ferre         #+#    #+#                 */
/*   Updated: 2025/05/12 04:07:13 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "intersecting.h"
#include "vector.h"
#include "utilities.h"

#include <math.h>

t_hit	intersectingSphere(t_vec point, t_sphere sphere)
{
	t_hit	hitInfo;
	float	sphereDistance;

	hitInfo.intersected = 0;
	sphereDistance = distance(point, sphere.center) - sphere.radius;
	if (sphereDistance <= 0.0) 
	{
		hitInfo.intersected = 1;
		hitInfo.position = sphere.center;
		hitInfo.normal = normalize(sub(point, sphere.center));
		hitInfo.color = sphere.color;
	}
	hitInfo.distance = fabs(sphereDistance);
	return (hitInfo);
}

t_hit	intersectingPlane(t_vec point, t_plane plane)
{
	t_hit	hitInfo;
	float	d;
	float	side;

	hitInfo.intersected = 0;
	d = -(plane.normal.x * plane.position.x + plane.normal.y * plane.position.y + plane.normal.z * plane.position.z);
	side = plane.normal.x * point.x + plane.normal.y * point.y + plane.normal.z * point.z + d;
	if (side <= 0.0)
	{
		hitInfo.intersected = 1;
		hitInfo.position = plane.position;
		hitInfo.normal = plane.normal;
		hitInfo.color = plane.color;
	}
	hitInfo.distance = fabs(side);
	return (hitInfo);
}

t_hit	intersectingCylinder(t_vec point, t_cylinder cylinder)
{
	t_hit	hitInfo;
	t_vec	baseVec;
	t_vec	axisVec;
	t_vec	axisPoint;
	float	t;
	float	cylinderDistance;

	hitInfo.intersected = 0;
	baseVec = sub(point, cylinder.position);
	t = dot(baseVec, cylinder.axis);
	axisVec = mult(cylinder.axis, clamp(t, cylinder.height * -0.5, cylinder.height * 0.5));
	axisPoint = add(cylinder.position, axisVec);
	cylinderDistance = distance(point, axisPoint) - cylinder.radius;
	if (cylinderDistance <= 0.0 && t >= cylinder.height * -0.5 && t <= cylinder.height * 0.5)
	{
		hitInfo.intersected = 1;
		hitInfo.position = cylinder.position;
		hitInfo.normal = normalize(sub(point, axisPoint));
		hitInfo.color = cylinder.color;
	}
	hitInfo.distance = fabs(cylinderDistance);
	return (hitInfo);
}

float	closestSphere(t_vec point, t_scene_data scene)
{
	t_vec	closestSphere;
	float	closestDistance;
	float	currentDistance;
	float	closestRadius;
	int		i;

	i = 0;
	closestDistance = 10000.0;
	while (i < scene.shapes.sphereCount)
	{
		currentDistance = distanceSquared(point, scene.shapes.spheres[i].center) - 
			(scene.shapes.spheres[i].radius * scene.shapes.spheres[i].radius);
		if (currentDistance < closestDistance)
		{
			closestDistance = currentDistance;
			closestSphere = scene.shapes.spheres[i].center;
			closestRadius = scene.shapes.spheres[i].radius;
		}
		i++;
	}
	if (closestDistance < 10000.0)
		return (distance(point, closestSphere) - closestRadius);
	return (closestDistance);
}

float	closestCylinder(t_vec point, t_scene_data scene)
{
	t_vec	closestCylinder;
	float	closestDistance;
	float	currentDistance;
	float	closestRadius;
	t_vec	baseVec;
	t_vec	axisVec;
	t_vec	axisPoint;
	float	t;
	int		i;

	i = 0;
	closestDistance = 10000.0;
	while (i < scene.shapes.cylinderCount)
	{
		baseVec = sub(point, scene.shapes.cylinders[i].position);
		t = dot(baseVec, scene.shapes.cylinders[i].axis);
		axisVec = mult(scene.shapes.cylinders[i].axis, t);
		axisPoint = add(scene.shapes.cylinders[i].position, axisVec);
		currentDistance = distanceSquared(point, axisPoint) -
			(scene.shapes.cylinders[i].radius * scene.shapes.cylinders[i].radius);
		if (currentDistance < closestDistance)
		{
			closestDistance = currentDistance;
			closestCylinder = axisPoint;
			closestRadius = scene.shapes.cylinders[i].radius;
		}
		i++;
	}
	if (closestDistance < 10000.0)
		return (distance(point, closestCylinder) - closestRadius);
	return (closestDistance);
}

float	closestPlane(t_vec point, t_scene_data scene)
{
	float	closestDistance;
	float	currentDistance;
	float	d;
	float	side;
	int		i;

	i = 0;
	closestDistance = 10000.0;
	while (i < scene.shapes.planeCount)
	{
		d = -(scene.shapes.planes[i].normal.x * scene.shapes.planes[i].position.x + 
			scene.shapes.planes[i].normal.y * scene.shapes.planes[i].position.y + 
			scene.shapes.planes[i].normal.z * scene.shapes.planes[i].position.z);
		side = scene.shapes.planes[i].normal.x * point.x + scene.shapes.planes[i].normal.y * 
			point.y + scene.shapes.planes[i].normal.z * point.z + d;
		currentDistance = fabs(side);
		if (currentDistance < closestDistance)
		{
			closestDistance = currentDistance;
		}
		i++;
	}
	return (closestDistance);
}

float	closestShape(t_vec point, t_scene_data scene)
{
	float	nearestPlane;
	float	nearestSphere;
	float	nearestCylinder;
	float	smallestDistance;

	smallestDistance = 0.01;
	nearestPlane = closestPlane(point, scene);
	if (nearestPlane <= smallestDistance) return (nearestPlane);
	nearestSphere = closestSphere(point, scene);
	if (nearestSphere <= smallestDistance) return (nearestSphere);
	nearestCylinder = closestCylinder(point, scene);
	if (nearestPlane < nearestSphere && nearestPlane < nearestCylinder)
		return (nearestPlane);
	else if (nearestSphere < nearestCylinder)
		return (nearestSphere);
	else
		return (nearestCylinder);
}