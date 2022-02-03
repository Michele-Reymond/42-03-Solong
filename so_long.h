/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:32:48 by mreymond          #+#    #+#             */
/*   Updated: 2022/02/03 19:45:05 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _SOLONG_H
# define _SOLONG_H

# include "mlx/mlx.h"
# include "src/gnl/get_next_line.c"
# include "src/printf/ft_printf.c"
# include "src/printf/ft_printf_utils.c"
# include "src/printf/ft_printf_unsigned.c"
# include "src/printf/ft_printf_hexa.c"
# include "src/libft/ft_itoa.c"

#define MAP_PATH "map/map.ber"

#define TEXT_TITRE "So long!"
#define TEXT_START "Manges vite les souris"
#define TEXT_ERROR "Error\n"
#define TEXT_ERROR_MAP "Attention, la carte n'est pas conforme!\n"
#define TEXT_ERROR_EXIT "Attention, il n'y a pas de panier sur la carte!\n"
#define TEXT_ERROR_M_PLAYER "Attention, il n'y a plusieurs player sur la carte!\n"
#define TEXT_ERROR_PLAYER "Attention, il n'y a pas de chat sur la carte!\n"
#define TEXT_ERROR_COLLECTIBLE "Attention, il n'y a pas de souris sur la carte!\n"

#define IMG_GROUND "./img/sol.xpm"
#define IMG_CAT_F "./img/Cat-front.xpm"
#define IMG_CAT_B "./img/Cat-back.xpm"
#define IMG_CAT_L "./img/Cat-left.xpm"
#define IMG_CAT_R "./img/Cat-right.xpm"
#define IMG_BOX "./img/box.xpm"
#define IMG_EXIT "./img/panier.xpm"
#define IMG_COLLECT "./img/mouse.xpm"
#define IMG_WALL "./img/mur.xpm"


#define IMG_W 64
#define IMG_H 64
#define IMG_W2 32
#define IMG_H2 32

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

typedef struct map_items
{
	int		c;
	int		exit;
	int		player;
}	map_data;

typedef struct	s_param {
	void		*mlx;
	char 		*map;
	int			steps;
	int			collect;
	map_data	items;
	p_data		player;
	win_data	w;
}	t_param;

#endif