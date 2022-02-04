/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:32:48 by mreymond          #+#    #+#             */
/*   Updated: 2022/02/04 12:12:37 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../mlx/mlx.h"
# include "./libft/libft.h"
# include "./get_next_line.h"
# include <stdio.h>
# include <stdlib.h>

# define MAP_PATH "map/map.ber"

# define TEXT_TITRE "So long!"
# define TEXT_START "Manges vite les souris"
# define TEXT_ERROR "Error\n"
# define TEXT_ERROR_MAP "Attention, la carte n'est pas conforme!\n"
# define TEXT_ERROR_EXIT "Attention, il n'y a pas de panier sur la carte!\n"
# define TEXT_ERROR_M_PLAYER "Attention, il n'y a plusieurs player sur la carte!\n"
# define TEXT_ERROR_PLAYER "Attention, il n'y a pas de chat sur la carte!\n"
# define TEXT_ERROR_COLLECTIBLE "Attention, il n'y a pas de souris sur la carte!\n"

# define IMG_GROUND "./img/sol.xpm"
# define IMG_CAT_F "./img/Cat-front.xpm"
# define IMG_CAT_B "./img/Cat-back.xpm"
# define IMG_CAT_L "./img/Cat-left.xpm"
# define IMG_CAT_R "./img/Cat-right.xpm"
# define IMG_BOX "./img/box.xpm"
# define IMG_EXIT "./img/panier.xpm"
# define IMG_COLLECT "./img/mouse.xpm"
# define IMG_WALL "./img/mur.xpm"

# define IMG_W 64
# define IMG_H 64
# define IMG_W2 32
# define IMG_H2 32

# define KEY_ESC 53
# define KEY_UP 126
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2

typedef struct image
{
	void	*img;
	int		width;
	int		height;
}	img_data;

typedef struct player
{
	int		x;
	int		y;
}	p_data;

typedef struct window
{
	void 	*w;
	int		width;
	int		height;
}	win_data;

typedef struct	s_param {
	void		*mlx;
	char 		*map;
	int			steps;
	int			collected;
	int			collectibles;
	p_data		player;
	win_data	w;
}	t_param;

int closeg(int keycode, t_param p);
int move(t_param *p, int steps, char *cat, int direction);
void print_move(t_param *p, char *cat, int direction, int steps);
void  render_img(void *mlx, void *window, int x, int y, char *path);
int inside_lines(unsigned long i, char *line, unsigned long w);
int map_wall_error(char *line, int width);
int item_error(char *line);
void map_errors(char *line, int w_width, int w_height);
win_data window_construction(void *mlx, char *path, t_param *p);
void define_img(void *mlx, win_data window, int x, int y, char lettre);
void render_text_box(void *mlx, win_data window);
void render_map(void *mlx, win_data	window, char *map);
int go_to_left(t_param *p);
int go_to_right(t_param *p);
int go_up(t_param *p);
int go_down(t_param *p);
void display_steps(int p_steps, void *mlx, win_data window);
int	key_hook(int keycode, t_param *p);
int str_find(char *str, char lettre);
void set_player_position(t_param *p);

#endif