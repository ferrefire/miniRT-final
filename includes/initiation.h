/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initiation.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/19 17:55:21 by ferre         #+#    #+#                 */
/*   Updated: 2025/05/12 03:38:53 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INITIATION_H
#define INITIATION_H

#include "minirt.h"

t_data	*initiateData(void);
void 	initiateMLX(t_mlx_data *mlx_data, t_data *data);
void 	initiateScene(t_scene_data *scene_data, t_data *data);

#endif