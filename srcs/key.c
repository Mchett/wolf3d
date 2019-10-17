/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <mchett@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:20:29 by mchett            #+#    #+#             */
/*   Updated: 2019/10/14 15:13:48 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int		exit_x(t_img *img)
{
	mlx_destroy_window(img->mlx_ptr, img->win_ptr);
	system("./scripts/killscript");
	system("pkill afplay");
	exit(1);
	return (0);
}

static int		ch_key(int key, t_wolf *f)
{
	if (key == 45)
		f->talos = (f->talos + 1) % 2;
	if (key == 53)
		exit_x(&(f->img));
	if (((key == 126 || key == 13 || f->move[0]) && f->menu.flag_menu == 0))
		move_player(f, 0.1f);
	if (((key == 125 || key == 1 || f->move[1]) && f->menu.flag_menu == 0))
		move_player(f, -0.1f);
	if (((key == 124 || key == 2 || f->move[2])) && f->menu.flag_menu == 0)
		rotate_player(f, key);
	if (((key == 123 || key == 0 || f->move[3]) && f->menu.flag_menu == 0))
		rotate_player(f, key);
	else if ((key == 257 || key == 258) && f->menu.flag_menu == 0)
		speed(f);
	else if (key == 36 && f->menu.flag_menu != 0)
		draw(f);
	if (f->menu.flag_menu == 0)
		cast_ray(f);
	return (0);
}

static int		launch_loop_hook(t_wolf *w)
{
	ch_key(-1, w);
	return (0);
}

void			key(t_img *img, t_wolf *f)
{
	mlx_hook(img->win_ptr, 3, 0, reset_key, f);
	mlx_hook(img->win_ptr, 2, 0, ch_key, f);
	mlx_hook(img->win_ptr, 17, 0, exit_x, img);
	mlx_loop_hook(img->mlx_ptr, launch_loop_hook, f);
}

void			choose_lvl(t_wolf *w, int *fd)
{
	system("./scripts/killscript");
	if (mapread(fd, w))
		ft_return("error2");
	if (w->talos == 0)
		system("./scripts/wolf_play_electro &");
	else
		system("./scripts/wolf_play_sigils &");
}
