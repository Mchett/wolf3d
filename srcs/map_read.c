/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmanfred <cmanfred@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:21:00 by mchett            #+#    #+#             */
/*   Updated: 2019/10/14 15:50:26 by cmanfred         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "wolf3d.h"

void		ft_free2darr(char **res)
{
	int		i;

	i = 0;
	while (res[i])
	{
		ft_strdel(&(res[i]));
		i++;
	}
	free(res);
}

static int	check_map(char *tmp)
{
	int		i;

	i = -1;
	while (tmp[++i] != '\0')
		if ((tmp[i] > '9' || tmp[i] < '0') && tmp[i] != ' ')
		{
			ft_putendl("incorrect symbols");
			return (1);
		}
	return (0);
}

/*
** Function, that fills list with lines of the map, checks there are
** the same amount of points in every line and launches mapcheck
*/

static int	lstfill(int fd, t_list **head, t_wolf **wolf)
{
	t_list	*curr;
	char	*tmp;
	int		est;
	int		flag;

	curr = *head;
	flag = 0;
	est = -1;
	while (get_next_line(fd, &tmp))
	{
		if (est == -1)
			est = ft_nbofwords(tmp, ' ');
		else if (ft_nbofwords(tmp, ' ') != est || check_map(tmp))
			flag++;
		((*wolf)->h)++;
		if (!(curr = ft_lstnew(tmp, ft_strlen(tmp) + 1)))
			ft_return("can't allocate list");
		ft_lstadd(head, curr);
		ft_strdel(&tmp);
	}
	if (flag)
		return (1);
	(*wolf)->w = est;
	ft_lstrev(head);
	return (0);
}

/*
** Function, that converts checked valid lines into coordinates of points
** and place them into t_vector structure
*/

static int	mapconv(t_list **head, t_wolf **wolf)
{
	int		x;
	int		y;
	t_list	*tmp;
	char	**split;
	int		pos;

	tmp = *head;
	y = -1;
	while (++y < (*wolf)->h)
	{
		x = -1;
		split = ft_strsplit(tmp->content, ' ');
		while (++x < (*wolf)->w)
		{
			pos = y * (*wolf)->w + x;
			(((*wolf)->block)[pos]).id = ft_atoi(split[x]);
			(((*wolf)->block)[pos]).y = y;
			(((*wolf)->block)[pos]).x = x;
		}
		tmp = tmp->next;
		ft_free2darr(split);
	}
	return (0);
}

/*
** Reads the map, checks if something went wrong
*/

int			mapread(int *fd, t_wolf *wolf)
{
	t_list	*head;

	wolf->h = 0;
	head = NULL;
	if (*fd < 0)
		return (1);
	if (lstfill(*fd, &head, &wolf) == 1)
	{
		ft_putendl("error in map strings");
		return (clean(&head, &wolf));
	}
	if (wolf->w < 3 || wolf->h < 3)
		ft_return("the minimum size of map is 3x3");
	if (!(wolf->block = (t_block *)ft_memalloc(sizeof(t_block)
			* wolf->w * wolf->h)))
		ft_return("can't allocate map");
	if (mapconv(&head, &wolf))
		return (clean(&head, &wolf));
	clean(&head, NULL);
	if (map_valid(wolf))
		return (clean(NULL, &wolf));
	if (close(*fd))
		ft_return("close error");
	return (0);
}
