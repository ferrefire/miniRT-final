/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleaning.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/19 17:59:15 by ferre         #+#    #+#                 */
/*   Updated: 2025/03/11 14:56:42 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEANING_H
#define CLEANING_H

#include "minirt.h"

void	cleanData(t_data *data);
void	cleanMLX(t_mlx_data *data);
void	clear(void *address);
void	free_tokens(char **tokens);


#endif
