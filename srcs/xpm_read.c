/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:21:38 by mchett            #+#    #+#             */
/*   Updated: 2019/10/14 13:21:42 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static t_img	get_xpm(char *file, t_wolf *w)
{
	t_img	img;

	if ((img.img_ptr = mlx_xpm_file_to_image(w->img.mlx_ptr,
		file, &img.w, &img.h)) == NULL)
		ft_return("can't read textures");
	img.adr = mlx_get_data_addr(img.img_ptr, &img.bitspp,
		&img.size_line, &img.endian);
	img.bitspp /= 8;
	img.w = img.size_line / img.bitspp;
	img.h = img.w;
	return (img);
}

void			read_textures(t_wolf *wolf)
{
	wolf->textures[0] = get_xpm("textures/brick.xpm", wolf);
	wolf->textures[1] = get_xpm("textures/metal.xpm", wolf);
	wolf->textures[2] = get_xpm("textures/stone.xpm", wolf);
	wolf->textures[3] = get_xpm("textures/wood.xpm", wolf);
	wolf->textures[4] = get_xpm("textures/maze.xpm", wolf);
	wolf->textures[5] = get_xpm("textures/g.xpm", wolf);
	wolf->textures[6] = get_xpm("textures/gravel.xpm", wolf);
	wolf->textures[7] = get_xpm("textures/finish.xpm", wolf);
}

double			dig_to_rad(int angle)
{
	double		new_angl;
	double		pi;

	pi = 3.1415926535;
	new_angl = (((double)angle) * pi) / 180.0f;
	return (new_angl);
}

t_block			pos(t_wolf *wolf, int x, int y)
{
	return (wolf->block[x + y * wolf->w]);
}

void			start(t_wolf *w)
{
	system("./scripts/killscript");
	if (w->talos == 0)
		system("./scripts/wolf_play_intro &");
	else
		system("./scripts/wolf_play_sigils &");
	cast_ray(w);
	key(&(w->img), w);
}
