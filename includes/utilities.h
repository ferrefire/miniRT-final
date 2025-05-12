/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilities.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/10 21:37:01 by ferre         #+#    #+#                 */
/*   Updated: 2025/05/12 22:20:34 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_H
# define UTILITIES_H

# include "vector.h"
# include <stdio.h>

typedef struct s_atof_setup
{
	float	result;
	float	sign;
	float	divisor;
}				t_atof_setup;

float			clamp(float value, float min, float max);
void			*memory_realloc(void *ptr, size_t old_size, size_t new_size);
void			free_memory(void *buffer);
void			*allocate_memory(size_t buffer_size);
t_atof_setup	atof_setup(const char *str);
float			ft_atof(const char *str);
int				is_float(const char *str);
t_vec			clamp_vec(t_vec a, float min, float max);

#endif
