/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_operators.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/12 22:10:09 by ferre         #+#    #+#                 */
/*   Updated: 2025/05/13 16:27:27 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector.h"
#include "math.h"
#include "utilities.h"

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

t_vec	div_vec(t_vec a, float b)
{
	t_vec	result;

	result.x = a.x / b;
	result.y = a.y / b;
	result.z = a.z / b;
	return (result);
}

t_vec	mult_col(t_vec a, t_vec b)
{
	t_vec	result;
	t_vec	norm_r;
	t_vec	norm_a;
	t_vec	norm_b;

	norm_a = div_vec(a, 255);
	norm_b = div_vec(b, 255);
	norm_r.x = norm_a.x * norm_b.x;
	norm_r.y = norm_a.y * norm_b.y;
	norm_r.z = norm_a.z * norm_b.z;
	result = mult(norm_r, 255);
	return (result);
}
