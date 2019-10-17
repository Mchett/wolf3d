/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:18:30 by mchett            #+#    #+#             */
/*   Updated: 2019/10/14 13:18:38 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		step(t_wolf *w)
{
	if (w->map.ray_dir.x < 0)
	{
		w->map.step.x = -1;
		w->map.side_dist.x = (w->dev.pos.x -
			w->map.map.x) * w->map.delta_dist.x;
	}
	else
	{
		w->map.step.x = 1;
		w->map.side_dist.x = (w->map.map.x + 1 -
			w->dev.pos.x) * w->map.delta_dist.x;
	}
	if (w->map.ray_dir.y < 0)
	{
		w->map.step.y = -1;
		w->map.side_dist.y = (w->dev.pos.y -
			w->map.map.y) * w->map.delta_dist.y;
	}
	else
	{
		w->map.step.y = 1;
		w->map.side_dist.y = (w->map.map.y + 1 -
			w->dev.pos.y) * w->map.delta_dist.y;
	}
}

void		draw_floor(t_wolf *w, int y)
{
	double	curr;
	double	weight;
	int		fx;
	int		fy;

	while (y <= w->img.h)
	{
		curr = w->img.h / (2.0f * y - w->img.h);
		weight = curr / w->map.perp_wall_dist;
		fx = (int)((weight * w->map.floor.x + (1.0f - weight) * w->dev.pos.x)
			* w->textures[6].w) % w->textures[6].w;
		fy = (int)((weight * w->map.floor.y + (1.0f - weight) * w->dev.pos.y)
			* w->textures[6].h) % w->textures[6].h;
		image_set_pixel(&w->img, w->map.x, y,
			get_pixel(&w->textures[6], fx, fy));
		fx = (int)((weight * w->map.floor.x + (1.0f - weight) * w->dev.pos.x)
			* w->textures[1].w) % w->textures[1].w;
		fy = (int)((weight * w->map.floor.y + (1.0f - weight) * w->dev.pos.y)
			* w->textures[1].h) % w->textures[1].h;
		image_set_pixel(&w->img, w->map.x, w->img.h - y,
			get_pixel(&w->textures[1], fx, fy));
		y++;
	}
}

void		ver_line(t_wolf *w)
{
	int		y;

	y = w->map.draw_start - 1;
	draw_floor(w, w->map.draw_end);
	while (++y < w->map.draw_end + 1)
	{
		w->projection.y = ((y - w->img.h / 2 + w->map.line_h / 2)
			* w->projection.img.h) / w->map.line_h;
		image_set_pixel(&(w->img), w->map.x, y,
			get_pixel(&w->projection.img, w->projection.x, w->projection.y));
	}
}

static void	floor_init(t_wolf *w)
{
	w->map.floor.x = (double)w->map.map.x + (w->map.side ?
		w->projection.factor : 0) +
		(!w->map.side && w->map.ray_dir.x < 0 ? 1.0f : 0);
	w->map.floor.y = (double)w->map.map.y + (w->map.side ?
		0 : w->projection.factor) +
		(w->map.side && w->map.ray_dir.y < 0 ? 1.0f : 0);
}

void		calculate(t_wolf *w)
{
	if (w->map.side == 0)
		w->map.perp_wall_dist = (w->map.map.x - w->dev.pos.x +
			(1 - w->map.step.x)
				/ 2) / w->map.ray_dir.x;
	else
		w->map.perp_wall_dist = (w->map.map.y - w->dev.pos.y +
			(1 - w->map.step.y)
				/ 2) / w->map.ray_dir.y;
	w->map.line_h = (int)(w->img.h / w->map.perp_wall_dist);
	w->map.draw_start = -w->map.line_h / 2 + w->img.h / 2;
	if (w->map.draw_start < 0)
		w->map.draw_start = 0;
	w->map.draw_end = w->map.line_h / 2 + w->img.h / 2;
	if (w->map.draw_end >= w->img.h)
		w->map.draw_end = w->img.h - 1;
	w->projection.factor = (w->map.side ? w->dev.pos.x + w->map.perp_wall_dist *
		w->map.ray_dir.x : w->dev.pos.y + w->map.perp_wall_dist *
			w->map.ray_dir.y);
	w->projection.factor -= floor(w->projection.factor);
	w->projection.x = (int)(w->projection.factor * w->projection.img.w);
	floor_init(w);
	ver_line(w);
}
