/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungsle <kyungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 12:25:01 by kyungsle          #+#    #+#             */
/*   Updated: 2022/02/03 18:14:04 by kyungsle         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int rtn_split(t_list *curr_ptr, char *nlptr, char **res, size_t dup_size)
{
	char *temp;

	*res = ft_strndup(curr_ptr->content, dup_size);
	if (!*res)
		return (-1);
	if (nlptr)
		temp = ft_strndup(nlptr + 1, ft_strlen(nlptr + 1));
	else
		temp = ft_strndup("", 0);
	if (!temp)
	{
		free(*res);
		return (-1);
	}
	free(curr_ptr->content);
	curr_ptr->content = temp;
	if (nlptr)
		return (ft_strlen(curr_ptr->content) > 0);
	return (0);
}

int set_result(t_list *curr_ptr, char *nlptr, char **res)
{
	int rtn;

	rtn = 0;
	if (nlptr)
	{
		rtn = rtn_split(curr_ptr, nlptr, res, nlptr - (curr_ptr->content) + 1);
	}
	else
	{
		if (*(curr_ptr->content) == '\0')
			*res = NULL;
		else
			rtn = rtn_split(curr_ptr, nlptr, res, ft_strlen(curr_ptr->content));
	}
	return (rtn);
}

int read_file(t_list *curr_ptr, char *buff, char **res)
{
	char *nlptr;
	char *temp;
	ssize_t len;
	int eof;

	eof = 0;
	while (1)
	{
		nlptr = ft_strchr(curr_ptr->content, '\n');
		if (nlptr || eof)
			break;
		len = read(curr_ptr->fd, buff, BUFFER_SIZE);
		if (len == -1)
			return (-1);
		buff[len] = '\0';
		temp = ft_strjoin(curr_ptr->content, buff);
		if (!temp)
			return (-1);
		free(curr_ptr->content);
		curr_ptr->content = temp;
		if (len < BUFFER_SIZE)
			eof = 1;
	}
	return (set_result(curr_ptr, nlptr, res));
}

t_list *set_curr_ptr(t_list **head_ptr, int fd)
{
	t_list *curr_ptr;

	curr_ptr = *head_ptr;
	while (curr_ptr && (curr_ptr->fd != fd))
		curr_ptr = curr_ptr->next;
	if (curr_ptr)
		return (curr_ptr);
	curr_ptr = (t_list *)malloc(sizeof(t_list));
	if (!curr_ptr)
		return (NULL);
	curr_ptr->fd = fd;
	curr_ptr->content = ft_strndup("", 0);
	if (!(curr_ptr->content))
	{
		free(curr_ptr);
		curr_ptr = NULL;
		return (NULL);
	}
	curr_ptr->next = *head_ptr;
	*head_ptr = curr_ptr;
	return (curr_ptr);
}

char *get_next_line(int fd)
{
	static t_list *head_ptr;
	t_list *curr_ptr;
	char *buff;
	char *res;
	int status;

	res = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	curr_ptr = set_curr_ptr(&head_ptr, fd);
	if (!curr_ptr)
		return (NULL);
	buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (ft_lstdel(&head_ptr, curr_ptr));
	status = read_file(curr_ptr, buff, &res);
	free(buff);
	buff = NULL;
	if (status == 0 || status == -1)
		ft_lstdel(&head_ptr, curr_ptr);
	if (status == -1)
		return (NULL);
	return (res);
}

int get_start_idx(const char *haystack, const char *needle)
{
	int i = 0;
	int j = 0;

	while (haystack[i] != '\n' && haystack[i] != '\0')
	{
		while (haystack[i + j] == needle[j] && haystack[i + j] != '\n' && haystack[i + j] != '\0' && needle[j] != '\0')
			j++;
		if (needle[j] == '\0')
			return (i);
		j = 0;
		i++;
	}
	return (-1);
}

int main()
{
	char **all_string = (char **)malloc(1024);
	char **result = (char **)malloc(1024);
	char *line;
	int fd;
	int i = 0;

	if (!(fd = open("test.txt", O_RDONLY))) // 1
	{
		printf("\nError in open");
		return (0);
	}
	while (line = get_next_line(fd)) // 2
	{
		line[ft_strlen(line) - 1] = '\0';
		all_string[i] = line;
		// printf("Gnl %d line : %s", i, all_string[i]);
		i++;
		// free(line);				// 6
	}
	all_string[i] = NULL;
	printf("\n");

	// all string에 있는 것들에서 shift started by 로 시작하면 체크하기 시작
	// 4eye check라는 단어를 찾음
	// 해당 문자열의 위로 올라가면서 숫자로 시작하는 문장 찾기
	// 해당 문자열 반환

	i = 0;

	int j = 0;
	int k = 0;

	while (all_string[i])
	{
		// printf(all_string[i]);
		if (get_start_idx(all_string[i], "shift started by") != -1)
		{
			result[k++] = all_string[i];
			// printf(all_string[i]);
			// printf("\n");
			while (all_string[i] && get_start_idx(all_string[i], "shift ended by") == -1)
			{
				if (get_start_idx(all_string[i], "4eye check") != -1)
				{
					j = i;
					while (j >= 0)
					{
						if (all_string[j][0] >= 48 && all_string[j][0] <= 57)
						{
							result[k++] = all_string[j];
							// printf(all_string[j]);
							// printf("\n");
							break;
						}
						j--;
					}
					result[k++] = all_string[i];
					// printf(all_string[i]);
					// printf("\n");
					j = 0;
				}
				i++;
			}
		}
		i++;
	}
	result[k] = NULL;
	k = 0;

	int fd2;

	if (0 < (fd2 = open("./test2.txt", O_WRONLY | O_CREAT | O_EXCL, 0644)))
	{
		while (result[k])
		{
			write(fd2, result[k], strlen(result[k]));
			write(fd2, "\n", 1);
			k++;
		}
		close(fd2);
	}
	else
	{
		printf("파일이 이미 존재합니다.\n");
	}

	// TODO all_string free 해줘야 함

	free(line); // 4
	close(fd);	// 5

	return (0);
}