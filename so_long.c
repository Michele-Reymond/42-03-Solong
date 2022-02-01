/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:50:27 by mreymond          #+#    #+#             */
/*   Updated: 2022/02/01 14:50:01 by mreymond         ###   ########.fr       */
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

typedef struct map_items
{
	int		collectibles;
	int		exit;
	int		player;
}	map_data;

typedef struct	s_param {
	void		*mlx;
	char 		*map;
	int			steps;
	int			collect;
	map_data	map_items;
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

img_data  render_img_anim(void *mlx, void *window, int x, int y)
{
	img_data img;
	char *anim[4];
	int i;
	int frames;

	i = 0;
	frames = 0;
	anim[0] = "./img/herbe1.xpm";
	anim[1] = "./img/herbe2.xpm";
	anim[2] = "./img/herbe3.xpm";
	anim[3] = "./img/herbe4.xpm";
	while (i <= 3)
	{
		frames = 0;
		if (img.img)
			mlx_destroy_image (mlx, img.img);
		img.img = mlx_xpm_file_to_image(mlx, anim[i], &img.width, &img.height);
		mlx_put_image_to_window(mlx, window, img.img, x, y);
		i++;
		while (frames < 1200)
			frames++;
	}
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
	else if (lettre == 'E' )
		img = render_img(mlx, window.w, x, y, "./img/exit.xpm");
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

int go_to_left(t_param *param)
{
	char *player_pos;

	player_pos = ft_strchr(param->map, 'P');
	if (*(player_pos - 1) == 'E' && param->map_items.collectibles == param->collect)
	{
		mlx_destroy_window(param->mlx, param->window.w);
		exit(0);
	}
	if (*(player_pos - 1) != '1' && *(player_pos - 1) != 'E')
	{
		if (*(player_pos - 1) == 'C')
			param->collect = param->collect + 1; 
		*player_pos = '0';
		*(player_pos - 1) = 'P';
		render_img(param->mlx, param->window.w, param->player.x, param->player.y, "./img/herbe.xpm");
		param->player.x = param->player.x - IMG_WIDTH;
		render_img(param->mlx, param->window.w, param->player.x, param->player.y, "./img/pirate-left.xpm");
		return (1);
	}
	return (0);
}

int go_to_right(t_param *param)
{
	char *player_pos;

	player_pos = ft_strchr(param->map, 'P');
	if (*(player_pos + 1) == 'E' && param->map_items.collectibles == param->collect)
	{
		mlx_destroy_window(param->mlx, param->window.w);
		exit(0);
	}
	if (*(player_pos + 1) != '1' && *(player_pos + 1) != 'E')
	{
		if (*(player_pos + 1) == 'C')
			param->collect = param->collect + 1; 
		*player_pos = '0';
		*(player_pos + 1) = 'P';
		render_img(param->mlx, param->window.w, param->player.x, param->player.y, "./img/herbe.xpm");
		param->player.x = param->player.x + IMG_WIDTH;
		render_img(param->mlx, param->window.w, param->player.x, param->player.y, "./img/pirate.xpm");
		return (1);
	}
	return (0);
}

int go_up(t_param *param)
{
	char *player_pos;

	player_pos = ft_strchr(param->map, 'P');
	if (*(player_pos - (param->window.width / IMG_WIDTH + 1)) == 'E' && param->map_items.collectibles == param->collect)
	{
		mlx_destroy_window(param->mlx, param->window.w);
		exit(0);
	}
	if (*(player_pos - (param->window.width / IMG_WIDTH + 1)) != '1' && *(player_pos - (param->window.width / IMG_WIDTH + 1)) != 'E')
	{
		if (*(player_pos - (param->window.width / IMG_WIDTH + 1)) == 'C')
			param->collect = param->collect + 1; 
		*player_pos = '0';
		player_pos = player_pos - (param->window.width / IMG_WIDTH + 1);
		*player_pos = 'P';
		render_img(param->mlx, param->window.w, param->player.x, param->player.y, "./img/herbe.xpm");
		param->player.y = param->player.y - IMG_HEIGHT;
		render_img(param->mlx, param->window.w, param->player.x, param->player.y, "./img/pirate.xpm");
		return (1);
	}
	return (0);
}

int go_down(t_param *param)
{
	char *player_pos;

	player_pos = ft_strchr(param->map, 'P');
	if (*(player_pos + (param->window.width / IMG_WIDTH + 1)) == 'E' && param->map_items.collectibles == param->collect)
	{
		mlx_destroy_window(param->mlx, param->window.w);
		exit(0);
	}
	if (*(player_pos + (param->window.width / IMG_WIDTH + 1)) != '1' && *(player_pos + (param->window.width / IMG_WIDTH + 1)) != 'E')
	{
		if (*(player_pos + (param->window.width / IMG_WIDTH + 1)) == 'C')
			param->collect = param->collect + 1; 
		*player_pos = '0';
		player_pos = player_pos + (param->window.width / IMG_WIDTH + 1);
		*player_pos = 'P';
		render_img(param->mlx, param->window.w, param->player.x, param->player.y, "./img/herbe.xpm");
		param->player.y = param->player.y + IMG_HEIGHT;
		render_img(param->mlx, param->window.w, param->player.x, param->player.y, "./img/pirate.xpm");
		return (1);
	}
	return (0);
}

int	key_hook(int keycode, t_param *param)
{
	char *steps;

	if (keycode == 53)
	{
		mlx_destroy_window(param->mlx, param->window.w);
		exit(0);
	}
	if (keycode == 123 || keycode == 0)
		param->steps = param->steps + go_to_left(param);
	if (keycode == 124 || keycode == 2)
		param->steps = param->steps + go_to_right(param);
	if (keycode == 125 || keycode == 1)
		param->steps = param->steps + go_down(param);
	if (keycode == 126 || keycode == 13)
		param->steps = param->steps + go_up(param);
	ft_printf("Nombre de pas : %d\n", param->steps);
	render_img(param->mlx, param->window.w, 0, 0, "./img/sable.xpm");
	render_img(param->mlx, param->window.w, IMG_WIDTH, 0, "./img/sable.xpm");
	render_img(param->mlx, param->window.w, IMG_WIDTH * 2, 0, "./img/sable.xpm");
	render_img(param->mlx, param->window.w, IMG_WIDTH * 3, 0, "./img/sable.xpm");
	steps = ft_itoa(param->steps);
	mlx_string_put(param->mlx, param->window.w, (IMG_WIDTH / 2), (IMG_HEIGHT / 2), 0000000, "nbr de pas:");
	mlx_string_put(param->mlx, param->window.w, (IMG_WIDTH * 3), (IMG_HEIGHT / 2), 0000000, steps);
	return (0);
}

int str_find(char *str, char lettre)
{
	int i;

	i = 0;
	if (str == NULL)
		return (0);
	while (*str != '\0')
	{
		str = ft_strchr(str, lettre);
		if (str == NULL)
			break;
		i++;
		str++;
	}
	return (i);
}

int closeg(int keycode, t_param param)
{
	(void)keycode;
	(void)param;
	exit(0);
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
	param.map_items.collectibles = str_find(param.map, 'C');
	param.map_items.exit = str_find(param.map, 'E');
	param.map_items.player = str_find(param.map, 'P');
	mlx_key_hook(param.window.w, key_hook, &param);
	render_img_anim(param.mlx, param.window.w, 0, IMG_HEIGHT);
	mlx_hook(param.window.w, 17, 0L << 0, closeg, &param);
	mlx_loop(param.mlx);
	free(param.map);
	return (0);
}