/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmanfred <cmanfred@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:19:31 by mchett            #+#    #+#             */
/*   Updated: 2019/10/14 15:48:14 by cmanfred         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		init_mlx(t_wolf *w)
{
	if ((w->img.mlx_ptr = mlx_init()) == NULL)
		ft_return("error: mlx");
	if ((w->img.win_ptr = mlx_new_window(w->img.mlx_ptr, w->img.w,
		w->img.h, w->titel)) == NULL)
		ft_return("error: mlx");
	if ((w->img.img_ptr = mlx_new_image(w->img.mlx_ptr, w->img.w,
		w->img.h)) == NULL)
		ft_return("error:img_ptr");
	w->img.adr = mlx_get_data_addr(w->img.img_ptr, &(w->img.bitspp),
		&(w->img.size_line), &(w->img.endian));
	w->img.bitspp /= 8;
	w->textures = (t_img *)malloc(sizeof(t_img) * 20);
	read_textures(w);
}

void		init_lodev(t_wolf *w)
{
	w->dev.plane.x = 0;
	w->dev.plane.y = 2.0f / 3.0f;
	w->img.size_line = 0;
	w->key.step_flag = 0;
}

void		ft_init(t_wolf *w)
{
	ft_bzero(w, sizeof(t_wolf));
	w->titel = "WOLF 3D";
	w->img.h = 720;
	w->img.w = 1280;
	w->map.color = 0xFF;
	w->talos = 0;
	w->move = ft_memalloc(sizeof(int) * 4);
	init_lodev(w);
}
