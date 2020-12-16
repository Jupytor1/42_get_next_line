/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kokobaya <kokobaya@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 20:53:38 by kokobaya          #+#    #+#             */
/*   Updated: 2020/11/18 22:05:38 by kokobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		get_next_line(int fd, char **line)
{
	static t_fdlst	*st_fdlst = NULL;
	t_fdlst			*fdobj;
	int				len;
	int				endcode;

	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	if (!(fdobj = required_fdobj(fd, &st_fdlst)))
		return (-1);
	len = 0;
	endcode = read_and_count_recur(fd, fdobj->buflst, fdobj->next_head, &len);
	if (endcode == -1)
		return (-1);
	if (!(*line = malloc(sizeof(char) * (len + 1))))
		return (-1);
	copy_line(*line, len, fdobj);
	fdobj->next_head += len + 1;
	delete_used_bufobjs(fdobj);
	if (endcode == 0)
	{
		fdobj->next_head = 0;
		return (0);
	}
	return (1);
}
