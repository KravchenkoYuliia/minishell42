/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:26:08 by yukravch          #+#    #+#             */
/*   Updated: 2025/04/09 19:06:51 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef  BUFFER_SIZE
#  define BUFFER_SIZE 10

# endif

# include <stdlib.h>
# include <unistd.h>

char	*ft_cut_line(char *reserve);
char	*ft_copy_from_buffer(char *reserve, char *buffer);
char	*ft_get_line(char *full_reserve);
char	*ft_read_buffer(int fd, char *reserve);
char	*get_next_line(int fd);
void	ft_bzero_gnl(void *s, size_t n);
void	*ft_calloc_gnl(size_t nmemb, size_t size);
int		ft_strlen_gnl(char *str);
char	*ft_strcpy_gnl(char *dest, char *src);
int		ft_strchr_gnl(const char *s, int c);

#endif
