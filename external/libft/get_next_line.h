/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 15:12:58 by hflohil-      #+#    #+#                 */
/*   Updated: 2025/03/11 15:07:18 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

//char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_empty_string(void);
//char	*ft_strchr(const char *s, int c);
//size_t	ft_strlen(const char *s);
//char	*ft_strjoin(char const *s1, char const *s2);
char	*get_full_chunk(int fd, char *previous_read, char *chunk_buffer);
char	*trim_line_buffer(char *line_buffer);
char	*get_next_line(int fd);
ssize_t	find_new_line(char *source);

#endif