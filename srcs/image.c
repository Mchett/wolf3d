/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:19:54 by mchett            #+#    #+#             */
/*   Updated: 2019/10/14 13:20:16 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

/*
 ** Function, that will free the image if something went wrong
*/

t_img		*delimage(t_img *img)
{
	if (img != NULL)
	{
		if (img->img_ptr != NULL)
			mlx_destroy_image(img->mlx_ptr, img->img_ptr);
		ft_memdel((void **)&img);
	}
	return (NULL);
}

/*
 ** User-friendly function, that sets pixel in the image, using it's formatted
 ** X and Y coordinates
*/

void		image_set_pixel(t_img *image, int x, int y, int color)
{
	if (x < 0 || x >= image->w || y < 0 || y >= image->h)
		return ;
	*(int *)(image->adr + (x * image->bitspp + y * image->size_line)) = color;
}

int			get_pixel(t_img *image, int x, int y)
{
	if (x < 0 || y < 0 || x >= image->w || y >= image->h)
		return (0);
	return (*(int *)(image->adr + ((x + y * image->w)
					* image->bitspp)));
}

/*
 ** Function, that allocates new image
*/

void		new_image(t_img *img)
{
	if ((img->img_ptr = mlx_new_image(img->mlx_ptr, img->w,
		img->h)) == NULL)
	{
		(delimage(img));
		return ;
	}
	img->adr = mlx_get_data_addr(img->img_ptr, &img->bitspp, &img->size_line,
			&img->endian);
	img->bitspp /= 8;
}
