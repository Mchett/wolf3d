/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 15:26:58 by mchett            #+#    #+#             */
/*   Updated: 2019/10/14 15:27:08 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include "./libs/libft/libft.h"
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include "./libs/minilibx_macos/mlx.h"
# include "pthread.h"
# include <sys/uio.h>
# define BUFF_SIZE 1000
# define MULT 15000
# define ENDL '\n'
# define END '\0'

typedef struct	s_vector
{
	double		x;
	double		y;
}				t_vector;

typedef struct	s_img
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*adr;
	int			w;
	int			h;
	int			bitspp;
	int			size_line;
	int			endian;
}				t_img;

typedef struct	s_player
{
	double		x;
	double		y;
	int			pov;
}				t_player;

typedef struct	s_block
{
	int			x;
	int			y;
	int			id;
}				t_block;

typedef struct	s_lodev
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
}				t_lodev;

typedef struct	s_map
{
	t_vector	floor;
	t_vector	camera;
	t_vector	ray_dir;
	t_vector	map;
	t_vector	side_dist;
	t_vector	delta_dist;
	double		perp_wall_dist;
	t_vector	step;
	int			hit;
	int			side;
	int			line_h;
	int			draw_start;
	int			draw_end;
	int			x;
	int			color;

}				t_map;

typedef struct	s_key
{
	double		speed;
	double		angle;
	int			speed_flag;
	int			step_flag;
}				t_key;

typedef struct	s_menu
{
	int			x;
	int			y;
	int			xl;
	int			xr;
	int			yu;
	int			yd;
	int			p;
	int			dx;
	int			dy;
	int			flag_menu;
	int			str_col;
	int			speed_flag;
}				t_menu;

typedef struct	s_texture
{
	int			x;
	int			y;
	double		factor;
	t_img		img;
}				t_texture;

typedef struct	s_wolf
{
	char		**maps;
	char		*titel;
	int			xwin;
	int			ywin;
	int			xpr;
	int			ypr;
	int			w;
	int			h;
	t_img		img;
	t_block		*block;
	t_player	player_start;
	t_player	player_cond;
	t_lodev		dev;
	t_map		map;
	t_menu		menu;
	t_texture	projection;
	int			*move;
	int			t;
	int			l_color;
	int			talos;
	t_key		key;
	t_img		*textures;
	int			lvl_count;
	int			curlvl;
}				t_wolf;

void			ft_return(char *str);
int				map_valid(t_wolf *wolf);
int				mapread(int *fd, t_wolf *wolf);
int				main(int argc, char **argv);
double			dig_to_rad(int angle);
t_img			*delimage(t_img *img);
void			image_set_pixel(t_img *img, int x, int y, int color);
void			new_image(t_img *img);
t_block			pos(t_wolf *wolf, int x, int y);
void			cast_ray(t_wolf *w);
void			key(t_img *img, t_wolf *f);
void			move_player(t_wolf *w, double step);
void			rotate_player(t_wolf *w, int key);
int				reset_key(int key, t_wolf *w);
void			speed(t_wolf *w);
void			menu(t_wolf *w, int i);
void			start(t_wolf *w);
void			draw(t_wolf *w);
void			read_textures(t_wolf *wolf);
int				get_pixel(t_img *img, int x, int y);
void			choose_lvl(t_wolf *w, int *fd);
void			ft_init(t_wolf *w);
void			init_mlx(t_wolf *w);
void			draw_floor(t_wolf *w, int y);
void			init_lodev(t_wolf *w);
void			calculate(t_wolf *w);
void			step(t_wolf *w);
int				get_next_line(const int fd, char **line);
int				clean(t_list **head, t_wolf **wolf);
int				ft_nbofwords(char const *s, char c);
void			ft_lstrev(t_list **alst);
#endif
