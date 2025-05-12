/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilities.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/10 21:37:01 by ferre         #+#    #+#                 */
/*   Updated: 2025/05/12 04:06:21 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_H
#define UTILITIES_H

#include "vector.h"
#include <stdio.h>

float	clamp(float value, float min, float max);
void 	*memory_realloc(void *ptr, size_t old_size, size_t new_size);
void 	free_memory(void *buffer);
void 	*allocate_memory(size_t buffer_size);  
float 	ft_atof(const char *str);
int		is_float(const char *str);

#endif
