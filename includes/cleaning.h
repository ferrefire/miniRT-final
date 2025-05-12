/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleaning.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/19 17:59:15 by ferre         #+#    #+#                 */
/*   Updated: 2025/05/12 22:11:59 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEANING_H
# define CLEANING_H

# include "minirt.h"

void	clean_data(t_data *data);
void	clean_mlx(t_mlx_data *data);
void	clean_shapes(t_shapes *shapes);
void	clear(void *address);
void	free_tokens(char **tokens);

#endif
