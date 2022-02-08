/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 22:10:35 by mreymond          #+#    #+#             */
/*   Updated: 2022/02/08 17:31:34 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	render_img(void *mlx, void *window, t_pos *pos, char *path)
{
	t_img_data	img;

	img.img = mlx_xpm_file_to_image(mlx, path, &img.width, &img.height);
	mlx_put_image_to_window(mlx, window, img.img, pos->x, pos->y);
}

void	define_img(void *mlx, t_win_data window, t_pos *pos, char lettre)
{
	if (lettre == '1' )
		render_img(mlx, window.w, pos, IMG_WALL);
	else if (lettre == '0' )
		render_img(mlx, window.w, pos, IMG_GROUND);
	else if (lettre == 'C' )
		render_img(mlx, window.w, pos, IMG_COLLECT);
	else if (lettre == 'P' )
		render_img(mlx, window.w, pos, IMG_CAT_F);
	else if (lettre == 'E' )
		render_img(mlx, window.w, pos, IMG_EXIT);
}

void	render_text_box(void *mlx, t_win_data window)
{
	t_pos	pos;

	pos.x = IMG_W / 4;
	pos.y = IMG_H / 4;
	render_img(mlx, window.w, &pos, IMG_BOX);
	pos.x += IMG_W;
	render_img(mlx, window.w, &pos, IMG_BOX);
	pos.x += IMG_W;
	render_img(mlx, window.w, &pos, IMG_BOX);
}

void	render_map(void *mlx, t_win_data window, char *map)
{
	int			i;
	t_pos		pos;

	pos.x = 0;
	pos.y = 0;
	i = 0;
	while (map[i] != '\0')
	{
		while (map[i] != '\n')
		{
			define_img(mlx, window, &pos, map[i]);
			pos.x += IMG_W;
			i++;
		}
		i++;
		pos.x = 0;
		pos.y += IMG_H;
	}
	render_text_box(mlx, window);
}

void	set_player_position(t_param *p)
{
	char	*player_pos;
	char	*map;
	int		i;

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
