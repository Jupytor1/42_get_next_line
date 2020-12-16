/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kokobaya <kokobaya@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 20:53:23 by kokobaya          #+#    #+#             */
/*   Updated: 2020/11/18 21:08:55 by kokobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

typedef struct	s_fdlst
{
	int				fd;
	int				next_head;
	struct s_buflst	*buflst;
	struct s_fdlst	*next;
}				t_fdlst;

typedef struct	s_buflst
{
	int				strlen;
	char			*str;
	struct s_buflst	*next;
}				t_buflst;

/*
** get_next_line_utils.c
*/
t_fdlst			*required_fdobj(int fd, t_fdlst **p_fdlst);
int				read_buf(int fd, t_buflst *bufobj);
int				read_and_count_recur(int fd, t_buflst *cur_buf,
										int i, int *len);
void			copy_line(char *pline, int len, t_fdlst *fdobj);
void			delete_used_bufobjs(t_fdlst *fdobj);

/*
** get_next_line.c
*/
int				get_next_line(int fd, char **line);

#endif
