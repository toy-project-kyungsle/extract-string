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
