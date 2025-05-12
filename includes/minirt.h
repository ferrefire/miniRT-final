/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/19 17:26:12 by ferre         #+#    #+#                 */
/*   Updated: 2025/05/12 22:15:27 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "vector.h"
# include "scene.h"

typedef struct s_image_data
{
	void	*image;
	void	*address;
	int		bpp;
	int		line;
	int		endian;
}				t_image_data;

typedef struct s_mlx_data
{
	void			*mlx;
	void			*win;
	int				width;
	int				height;
	t_image_data	image_data;
}				t_mlx_data;

typedef struct s_data
{
	t_mlx_data		mlx_data;
	t_scene_data	scene_data;
	int				x;
	int				y;
	int				width;
	int				height;
	int				open_fd;
	char			*current_line;
}				t_data;

void	quit(const char *msg, t_data *data);
void	quit_tokens(char **tokens, const char *msg, t_data *data);

#endif
