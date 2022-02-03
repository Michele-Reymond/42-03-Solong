/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 22:10:35 by mreymond          #+#    #+#             */
/*   Updated: 2022/02/03 22:40:41 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

img_data  render_img(void *mlx, void *window, int x, int y, char *path)
{
	img_data img;

	img.img = mlx_xpm_file_to_image(mlx, path, &img.width, &img.height);
	mlx_put_image_to_window(mlx, window, img.img, x, y);
	return (img);
}

img_data define_img(void *mlx, win_data window, int x, int y, char lettre)
{
	img_data img;

	if (lettre == '1' )
		img = render_img(mlx, window.w, x, y, IMG_WALL);
	else if (lettre == '0' )
		img = render_img(mlx, window.w, x, y, IMG_GROUND);
	else if (lettre == 'C' )
		img = render_img(mlx, window.w, x, y, IMG_COLLECT);
	else if (lettre == 'P' )
		img = render_img(mlx, window.w, x, y, IMG_CAT_F);
	else if (lettre == 'E' )
		img = render_img(mlx, window.w, x, y, IMG_EXIT);
	else
	{
		img.img = NULL;
		img.width = 0;
		img.height = 0;
	}
	return (img);
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

void render_map(void *mlx, win_data	window)
{
	char	*line = NULL;
	int		gnl;
	int		x;
	int		y;
	img_data img;

	x = 0;
	y = 0;
	gnl = open(MAP_PATH, O_RDONLY);
	line = get_next_line(gnl);
	while (line != NULL)
	{
		while (*line != '\0')
		{
			img = define_img(mlx, window, x, y, *line);
			line++;
			x += img.width;
		} 
		x = 0;
		y += IMG_H;
		line = get_next_line(gnl);
	}
	render_text_box(mlx, window);
	free(line);
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
	while (map [i] != 'P')
		i++;
	p->player.y = (i / (p->w.width / IMG_H)) * IMG_H;
}
