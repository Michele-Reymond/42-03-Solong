/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 22:10:35 by mreymond          #+#    #+#             */
/*   Updated: 2022/02/04 16:26:36 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void  render_img(void *mlx, void *window, int x, int y, char *path)
{
	img_data img;

	img.img = mlx_xpm_file_to_image(mlx, path, &img.width, &img.height);
	mlx_put_image_to_window(mlx, window, img.img, x, y);
}

void define_img(void *mlx, win_data window, int x, int y, char lettre)
{
	if (lettre == '1' )
		render_img(mlx, window.w, x, y, IMG_WALL);
	else if (lettre == '0' )
		render_img(mlx, window.w, x, y, IMG_GROUND);
	else if (lettre == 'C' )
		render_img(mlx, window.w, x, y, IMG_COLLECT);
	else if (lettre == 'P' )
		render_img(mlx, window.w, x, y, IMG_CAT_F);
	else if (lettre == 'E' )
		render_img(mlx, window.w, x, y, IMG_EXIT);
}

void render_text_box(void *mlx, win_data window)
{
	int x;
	int y;

	x = IMG_W / 4;
	y = IMG_H / 4;
	render_img(mlx, window.w, x, y, IMG_BOX);
	x += IMG_W;
	render_img(mlx, window.w, x, y, IMG_BOX);
	x += IMG_W;
	render_img(mlx, window.w, x, y, IMG_BOX);
}

void render_map(void *mlx, win_data	window, char *map)
{
	int		x;
	int		y;
	int		i;

	x = 0;
	y = 0;
	i = 0;
	while (map[i] !='\0')
	{
		while (map[i] != '\n')
		{
			define_img(mlx, window, x, y, map[i]);
			x += IMG_W;
			i++;
		}
		i++; 
		x = 0;
		y += IMG_H;
	}
	render_text_box(mlx, window);
}

void set_player_position(t_param *p)
{
	char *player_pos;
	char *map;
	int i;

	i = 0;
	map = p->map;
	player_pos = ft_strchr(map, 'P');
	while (player_pos[i] != '\n')
		i++;
	p->player.x = (p->w.width - (i * IMG_W));
	i = 0;
	while (map[i] != 'P')
		i++;
	i++;
	p->player.y = IMG_H * ((i * (p->w.height / IMG_H)) / ft_strlen(map));
}
