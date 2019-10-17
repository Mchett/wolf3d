/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmanfred <cmanfred@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:19:12 by mchett            #+#    #+#             */
/*   Updated: 2019/10/14 15:52:18 by cmanfred         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			draw(t_wolf *w)
{
	int	fd;

	fd = 0;
	system("pkill afplay");
	if (w->curlvl == 1)
	{
		w->menu.flag_menu = 0;
		fd = open(w->maps[1], O_RDONLY);
		if (mapread(&fd, w))
			ft_return("error");
		start(w);
	}
	else if (w->curlvl <= w->lvl_count)
	{
		if (w->block)
			ft_memdel((void **)&w->block);
		fd = open(w->maps[w->curlvl], O_RDONLY);
		choose_lvl(w, &fd);
		w->menu.flag_menu = 0;
		cast_ray(w);
	}
}

int				reset_key(int key, t_wolf *w)
{
	if (key == 126 || key == 13)
		w->move[0] = 0;
	if (key == 125 || key == 1)
		w->move[1] = 0;
	if (key == 124 || key == 2)
		w->move[2] = 0;
	if (key == 123 || key == 0)
		w->move[3] = 0;
	return (0);
}
