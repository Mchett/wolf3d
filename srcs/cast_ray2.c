/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <mchett@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:18:48 by mchett            #+#    #+#             */
/*   Updated: 2019/10/14 15:16:34 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	which_texture(t_wolf *w)
{
	if ((pos(w, w->map.map.x, w->map.map.y)).id == 4)
		w->projection.img = w->textures[5];
	else if (w->map.side == 0)
	{
		if (w->map.step.x > 0)
			w->projection.img = w->textures[0];
		else
			w->projection.img = w->textures[1];
	}
	else
	{
		if (w->map.step.y > 0)
			w->projection.img = w->textures[2];
		else
			w->projection.img = w->textures[3];
	}
}

void		dda(t_wolf *w)
{
	while (w->map.hit == 0)
	{
		if (w->map.side_dist.x < w->map.side_dist.y)
		{
			w->map.side_dist.x += w->map.delta_dist.x;
			w->map.map.x += w->map.step.x;
			w->map.side = 0;
		}
		else
		{
			w->map.side_dist.y += w->map.delta_dist.y;
			w->map.map.y += w->map.step.y;
			w->map.side = 1;
		}
		if ((pos(w, w->map.map.x, w->map.map.y)).id > 0)
			w->map.hit = 1;
	}
	which_texture(w);
	calculate(w);
}

void		cast_ray(t_wolf *w)
{
	bzero(w->img.adr, w->img.w * w->img.h * w->img.bitspp);
	mlx_clear_window(w->img.mlx_ptr, w->img.win_ptr);
	w->map.x = 0;
	w->projection.img = w->textures[0];
	while (w->map.x < w->img.w)
	{
		w->map.camera.x = 2 * w->map.x / (double)(w->img.w) - 1;
		w->map.ray_dir.x = w->dev.dir.x + w->dev.plane.x * w->map.camera.x;
		w->map.ray_dir.y = w->dev.dir.y + w->dev.plane.y * w->map.camera.x;
		w->map.map.x = (int)(w->dev.pos.x);
		w->map.map.y = (int)(w->dev.pos.y);
		w->map.delta_dist.x = fabs(1 / w->map.ray_dir.x);
		w->map.delta_dist.y = fabs(1 / w->map.ray_dir.y);
		w->map.hit = 0;
		step(w);
		dda(w);
		w->map.x++;
	}
	mlx_put_image_to_window(w->img.mlx_ptr, w->img.win_ptr,
		w->img.img_ptr, 0, 0);
}
