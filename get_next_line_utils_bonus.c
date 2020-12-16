/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kokobaya <kokobaya@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 20:54:06 by kokobaya          #+#    #+#             */
/*   Updated: 2020/11/18 21:16:52 by kokobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_fdlst		*required_fdobj(int fd, t_fdlst **p_fdlst)
{
	int	endcode;

	while (*p_fdlst && (*p_fdlst)->fd != fd)
		p_fdlst = &((*p_fdlst)->next);
	if (*p_fdlst == NULL)
	{
		if (!(*p_fdlst = malloc(sizeof(t_fdlst))))
			return (NULL);
		(*p_fdlst)->fd = fd;
		(*p_fdlst)->next_head = 0;
		(*p_fdlst)->buflst = NULL;
		(*p_fdlst)->next = NULL;
	}
	if ((*p_fdlst)->next_head == 0)
	{
		if (!((*p_fdlst)->buflst = malloc(sizeof(t_buflst))))
			return (NULL);
		(*p_fdlst)->buflst->next = NULL;
		endcode = read_buf(fd, (*p_fdlst)->buflst);
		if (endcode == -1)
			return (NULL);
	}
	return (*p_fdlst);
}

int			read_buf(int fd, t_buflst *bufobj)
{
	int	readlen;

	if (!(bufobj->str = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	readlen = (int)read(fd, bufobj->str, BUFFER_SIZE);
	if (readlen >= 0)
	{
		bufobj->strlen = readlen;
		bufobj->str[readlen] = '\0';
	}
	return (readlen);
}

int			read_and_count_recur(int fd, t_buflst *cur_buf, int i, int *len)
{
	int	endcode;

	if (cur_buf->str[i] == '\n')
		return (1);
	if (cur_buf->str[i] == '\0')
	{
		if (!(cur_buf->next = malloc(sizeof(t_buflst))))
			return (-1);
		cur_buf->next->next = NULL;
		endcode = read_buf(fd, cur_buf->next);
		if (endcode == -1 || endcode == 0)
			return (endcode);
		return (read_and_count_recur(fd, cur_buf->next, 0, len));
	}
	(*len)++;
	i++;
	return (read_and_count_recur(fd, cur_buf, i, len));
}

void		copy_line(char *pline, int len, t_fdlst *fdobj)
{
	t_buflst	*bufobj;
	int			i;
	int			j;

	bufobj = fdobj->buflst;
	j = 0;
	i = fdobj->next_head;
	while (j < len)
	{
		if (bufobj->str[i] == '\0')
		{
			bufobj = bufobj->next;
			i = -1;
			j--;
		}
		else
			pline[j] = bufobj->str[i];
		i++;
		j++;
	}
	pline[j] = '\0';
}

void		delete_used_bufobjs(t_fdlst *fdobj)
{
	t_buflst	*bufobj;
	t_buflst	*next;

	bufobj = fdobj->buflst;
	while (bufobj && fdobj->next_head >= bufobj->strlen)
	{
		fdobj->next_head -= bufobj->strlen;
		next = bufobj->next;
		free(bufobj->str);
		free(bufobj);
		bufobj = next;
	}
	fdobj->buflst = bufobj;
}
