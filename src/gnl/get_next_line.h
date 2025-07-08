/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vradis <vradis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:39:06 by vflorez           #+#    #+#             */
/*   Updated: 2024/08/17 13:51:13 by vradis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <limits.h>

//Get_next_line_required
char	*get_next_line(int fd);
char	*get_line_storage(char *storage);
char	*read_join_file(int fd, char *storage);
char	*rest_storage(char *storage);

//utils_required
int		ft_strchr_gnl(const char *str, int c);
void	*ft_calloc_gnl(size_t num_elements, size_t size);
char	*ft_strjoin_gnl(char *s1, char *s2);
size_t	ft_strlen_gnl(const char *str);

#endif