/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:50:27 by mreymond          #+#    #+#             */
/*   Updated: 2022/02/01 00:43:06 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>

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
	int			collect;
	p_data		player;
	win_data	window;
}	t_param;

img_data  render_img(void *mlx, void *window, int x, int y, char *path)
{
	img_data img;

	img.img = mlx_xpm_file_to_image(mlx, path, &img.width, &img.height);
	mlx_put_image_to_window(mlx, window, img.img, x, y);
	return (img);
}

win_data window_construction(void *mlx, char *path)
{
	win_data	window;
	int			gnl;
	char		*line;

	window.height = 0;
	gnl = open(path, O_RDONLY);
	line = get_next_line(gnl);
	window.width = (ft_strlen(line) - 1) * IMG_WIDTH;
	while (line != NULL)
	{
		line = get_next_line(gnl);
		window.height += IMG_HEIGHT;
	}
	free(line);
	window.w = mlx_new_window(mlx, window.width, window.height, "Hello world!");
	return (window);
}

img_data define_img(void *mlx, win_data window, int x, int y, char lettre)
{
	img_data img;

	if (lettre == '1' )
		img = render_img(mlx, window.w, x, y, "./img/sable.xpm");
	else if (lettre == '0' )
		img = render_img(mlx, window.w, x, y, "./img/herbe.xpm");
	else if (lettre == 'C' )
		img = render_img(mlx, window.w, x, y, "./img/coffre.xpm");
	else if (lettre == 'P' )
		img = render_img(mlx, window.w, x, y, "./img/pirate.xpm");
	else
	{
		img.img = NULL;
		img.width = 0;
		img.height = 0;
	}
	return (img);
}

char *render_map(void *mlx, win_data	window)
{
	char	*line = NULL;
	int		gnl;
	int		x;
	int		y;
	img_data img;
	char *join;

	x = 0;
	y = 0;
	join = (char *)malloc(1);
	join[0] = '\0';
	gnl = open("map/map.ber", O_RDONLY);
	line = get_next_line(gnl);
	while (line != NULL)
	{
		join = ft_strjoin(join, line);
		while (*line != '\0')
		{
			img = define_img(mlx, window, x, y, *line);
			line++;
			x += img.width;
		} 
		x = 0;
		y += IMG_HEIGHT;
		line = get_next_line(gnl);
	}
	free(line);
	return (join);
}

void go_to_left(t_param *param)
{
	char *player_pos;

	player_pos = ft_strchr(param->map, 'P');
	if (*(player_pos - 1) != '1')
	{
		if (*(player_pos - 1) == 'C')
			param->collect = param->collect + 1; 
		*player_pos = '0';
		*(player_pos - 1) = 'P';
		render_img(param->mlx, param->window.w, param->player.x, param->player.y, "./img/herbe.xpm");
		param->player.x = param->player.x - IMG_WIDTH;
		render_img(param->mlx, param->window.w, param->player.x, param->player.y, "./img/pirate-left.xpm");
	}
}

void go_to_right(t_param *param)
{
	char *player_pos;

	player_pos = ft_strchr(param->map, 'P');
	if (*(player_pos + 1) != '1')
	{
		if (*(player_pos + 1) == 'C')
			param->collect = param->collect + 1; 
		*player_pos = '0';
		*(player_pos + 1) = 'P';
		render_img(param->mlx, param->window.w, param->player.x, param->player.y, "./img/herbe.xpm");
		param->player.x = param->player.x + IMG_WIDTH;
		render_img(param->mlx, param->window.w, param->player.x, param->player.y, "./img/pirate.xpm");
	}
}

void go_up(t_param *param)
{
	char *player_pos;

	player_pos = ft_strchr(param->map, 'P');
	if (*(player_pos - (param->window.width / IMG_WIDTH + 1)) != '1')
	{
		if (*(player_pos - (param->window.width / IMG_WIDTH + 1)) == 'C')
			param->collect = param->collect + 1; 
		*player_pos = '0';
		player_pos = player_pos - (param->window.width / IMG_WIDTH + 1);
		*player_pos = 'P';
		render_img(param->mlx, param->window.w, param->player.x, param->player.y, "./img/herbe.xpm");
		param->player.y = param->player.y - IMG_HEIGHT;
		render_img(param->mlx, param->window.w, param->player.x, param->player.y, "./img/pirate.xpm");
	}
}

void go_down(t_param *param)
{
	char *player_pos;

	player_pos = ft_strchr(param->map, 'P');
	if (*(player_pos + (param->window.width / IMG_WIDTH + 1)) != '1')
	{
		if (*(player_pos + (param->window.width / IMG_WIDTH + 1)) == 'C')
			param->collect = param->collect + 1; 
		*player_pos = '0';
		player_pos = player_pos + (param->window.width / IMG_WIDTH + 1);
		*player_pos = 'P';
		render_img(param->mlx, param->window.w, param->player.x, param->player.y, "./img/herbe.xpm");
		param->player.y = param->player.y + IMG_HEIGHT;
		render_img(param->mlx, param->window.w, param->player.x, param->player.y, "./img/pirate.xpm");
	}
}

int	key_hook(int keycode, t_param *param)
{
	if (keycode == 53)
		mlx_destroy_window(param->mlx, param->window.w);
	if (keycode == 123)
		go_to_left(param);
	if (keycode == 124)
		go_to_right(param);
	if (keycode == 125)
		go_down(param);
	if (keycode == 126)
		go_up(param);
	return (0);
}

int	main(void)
{
	t_param param;

	param.mlx = mlx_init();
	param.window = window_construction(param.mlx, "map/map.ber");
	param.map = render_map(param.mlx, param.window);
	param.player.x = IMG_WIDTH;
	param.player.y = IMG_HEIGHT;
	param.collect = 0;
	mlx_key_hook(param.window.w, key_hook, &param);
	mlx_loop(param.mlx);
	free(param.map);
	return (0);
}