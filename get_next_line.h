/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungsle <kyungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 12:24:24 by kyungsle          #+#    #+#             */
/*   Updated: 2022/02/03 15:20:24 by kyungsle         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#define BUFFER_SIZE 1

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <fcntl.h>
#include <string.h> // strlen()

typedef struct s_list
{
	int fd;
	char *content;
	struct s_list *next;
} t_list;

char *get_next_line(int fd);
size_t ft_strlen(const char *s);
char *ft_strchr(const char *s, int c);
char *ft_strndup(const char *s1, size_t n);
char *ft_strjoin(const char *s1, const char *s2);
char *ft_lstdel(t_list **head_ptr, t_list *curr_ptr);

#endif
