/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <mchett@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:20:44 by mchett            #+#    #+#             */
/*   Updated: 2019/10/14 15:42:11 by cmanfred         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		ft_return(char *str)
{
	ft_putendl(str);
	system("sh scripts/killscript");
	exit(-1);
}

void		maps_init(t_wolf *w, char **argv)
{
	w->maps = (char**)ft_memalloc(sizeof(char*) * 3);
	w->maps[0] = (char*)ft_memalloc(sizeof(char) * ft_strlen(argv[0]));
	w->maps[1] = (char*)ft_memalloc(sizeof(char) * 5);
	w->maps[2] = (char*)ft_memalloc(sizeof(char) * 5);
	ft_strcpy(w->maps[0], (const char*)argv[0]);
	ft_strcpy(w->maps[1], "map1");
	ft_strcpy(w->maps[2], "map2");
	w->lvl_count = 3;
}

void		play(t_wolf *w, char **argv, int *fd, int argc)
{
	if (argc == 2)
		(*fd) = open(argv[1], O_RDONLY);
	ft_init(w);
	if (argc == 1)
		maps_init(w, argv);
	else
	{
		w->lvl_count = argc - 1;
		w->maps = argv;
	}
	w->curlvl = 1;
	w->menu.flag_menu = 0;
	init_mlx(w);
	menu(w, 1);
}

int			main(int argc, char **argv)
{
	t_wolf	wolf;
	int		fd;

	fd = 0;
	system("./scripts/wolf_play_guitar &");
	play(&wolf, argv, &fd, argc);
	mlx_loop(wolf.img.mlx_ptr);
	exit(0);
	return (0);
}
