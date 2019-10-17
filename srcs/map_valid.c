/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:21:15 by mchett            #+#    #+#             */
/*   Updated: 2019/10/14 13:21:21 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	init_player(t_wolf *w)
{
	t_block	*b;
	int		i;

	b = w->block;
	i = 0;
	while (b[i].id != 0)
		i++;
	w->dev.pos.x = i % w->w + 0.5f;
	w->dev.pos.y = i / w->w + 0.5f;
	w->dev.dir.x = 1.0f;
	w->dev.dir.y = 0.0f;
}

static int	reason(int reason)
{
	if (reason == 1)
		ft_putendl("There are holes in map perimiter");
	else if (reason == 2)
		ft_putendl("There is no place for spawn in the map");
	return (reason);
}

int			map_valid(t_wolf *wolf)
{
	t_block	*b;
	int		i;
	int		flag;

	b = wolf->block;
	i = -1;
	while (++i < wolf->w)
		if ((b[i].id != 1 || b[i + wolf->w * (wolf->h - 1)].id != 1)
		&& (b[i].id != 4 || b[i + wolf->w * (wolf->h - 1)].id != 4))
			return (reason(1));
	i = -1;
	while (++i < wolf->h)
		if ((b[i * wolf->w].id != 1 || b[i * wolf->w + wolf->w - 1].id != 1)
		&& (b[i * wolf->w].id != 4 || b[i * wolf->w + wolf->w - 1].id != 4))
			return (reason(1));
	i = -1;
	flag = 0;
	while (++i < wolf->w * wolf->h)
		if (b[i].id == 0)
			flag++;
	if (!flag)
		return (reason(2));
	init_player(wolf);
	return (0);
}
