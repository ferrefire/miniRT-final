/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_operators.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/12 22:10:09 by ferre         #+#    #+#                 */
/*   Updated: 2025/05/12 22:10:45 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector.h"
#include "math.h"
#include "utilities.h"

t_vec	normalize(t_vec vec)
{
	t_vec	normalized;
	float	magnitude;

	magnitude = length(vec);
	normalized.x = vec.x / magnitude;
	normalized.y = vec.y / magnitude;
	normalized.z = vec.z / magnitude;
	return (normalized);
}

t_vec	cross(t_vec a, t_vec b)
{
	t_vec	result;

	result.x = (a.y * b.y) - (a.z * b.y);
	result.y = (a.z * b.x) - (a.x * b.z);
	result.z = (a.x * b.y) - (a.y * b.x);
	return (result);
}

t_vec	add(t_vec a, t_vec b)
{
	t_vec	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

t_vec	sub(t_vec a, t_vec b)
{
	t_vec	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}

t_vec	mult(t_vec a, float b)
{
	t_vec	result;

	result.x = a.x * b;
	result.y = a.y * b;
	result.z = a.z * b;
	return (result);
}
