/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <mchett@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:21:29 by mchett            #+#    #+#             */
/*   Updated: 2019/10/14 15:28:18 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		init_menu(t_wolf *w)
{
	mlx_clear_window(w->img.mlx_ptr, w->img.win_ptr);
	bzero(w->img.adr, w->img.w * w->img.h * w->img.bitspp);
	w->menu.x = 0;
	w->menu.y = -1;
	w->menu.p = 25;
	w->menu.flag_menu++;
	w->menu.dx = (w->img.w / 2) * w->menu.p / 100;
	if (w->menu.dx % 2 != 0)
		w->menu.dx++;
	w->menu.xl = (w->img.w / 2) - w->menu.dx / 2;
	w->menu.xr = (w->img.w / 2) + w->menu.dx / 2;
	w->menu.dy = (w->img.h / 2) * w->menu.p / 100;
	if (w->menu.dy % 2 != 0)
		w->menu.dy++;
	w->menu.yd = (w->img.h / 2) + w->menu.dy / 2;
	w->menu.yu = (w->img.h / 2) - w->menu.dy / 2;
	w->menu.str_col = 0x003153;
}

void			colorize(t_wolf *w)
{
	w->menu.y = w->menu.yu;
	if (w->menu.flag_menu % 2 != 0)
	{
		while (w->menu.y <= (w->menu.yu + 20))
		{
			w->menu.x = w->menu.xl;
			while (w->menu.x <= w->menu.xr)
				image_set_pixel(&(w->img), w->menu.x++, w->menu.y, 0xffffff);
			w->menu.y++;
		}
	}
	else if (w->menu.flag_menu % 2 == 0)
	{
		w->menu.y = w->menu.yu + 30;
		while (w->menu.y <= (w->menu.yu + 20 + 30))
		{
			w->menu.x = w->menu.xl;
			while (w->menu.x <= w->menu.xr)
				image_set_pixel(&(w->img), w->menu.x++, w->menu.y, 0xffffff);
			w->menu.y++;
		}
	}
}

void			putsrr(t_wolf *w, int i)
{
	if (i == 1)
		mlx_string_put(w->img.mlx_ptr, w->img.win_ptr, w->menu.xl + 55,
		w->menu.yu, w->menu.str_col, "Start");
	else
		mlx_string_put(w->img.mlx_ptr, w->img.win_ptr, w->menu.xl + 40,
		w->menu.yu, w->menu.str_col, "You win!");
}

void			menu(t_wolf *w, int i)
{
	init_menu(w);
	while (++w->menu.y < w->img.h)
	{
		w->menu.x = -1;
		while (++w->menu.x < w->img.w)
		{
			if (w->menu.x >= w->menu.xl && w->menu.x <= w->menu.xr)
				image_set_pixel(&(w->img), w->menu.x, w->menu.y, 0xffdead);
			else if ((w->menu.x >= 0 && w->menu.x < w->menu.xl) ||
				(w->menu.x > w->menu.xr && w->menu.x <= w->img.w))
				image_set_pixel(&(w->img), w->menu.x, w->menu.y,
				get_pixel(&w->textures[4], w->menu.x * 1.9, w->menu.y * 2));
			if ((w->menu.x == (w->menu.xl - 1) || w->menu.x == (w->menu.xr + 1))
			&& (w->menu.y % 3 == 0))
				image_set_pixel(&(w->img), w->menu.x, w->menu.y, 990066);
		}
	}
	colorize(w);
	mlx_put_image_to_window(w->img.mlx_ptr, w->img.win_ptr,
		w->img.img_ptr, 0, 0);
	putsrr(w, i);
	key(&(w->img), w);
}
