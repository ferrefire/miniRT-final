/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/10 20:28:06 by ferre         #+#    #+#                 */
/*   Updated: 2025/05/12 22:12:47 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "minirt.h"

# define KEY_ESC       65307
# define KEY_FORWARD   119
# define KEY_BACKWARD  115
# define KEY_LEFT      97
# define KEY_RIGHT     100

int		key_pressed(int keycode, t_data *data);
void	set_hooks(t_data *data);

#endif