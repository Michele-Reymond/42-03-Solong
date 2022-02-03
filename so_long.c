/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:50:27 by mreymond          #+#    #+#             */
/*   Updated: 2022/02/03 19:57:39 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>

int closeg(int keycode, t_param p)
{
	(void)keycode;
	(void)p;
	exit(0);
}

img_data  render_img(void *mlx, void *window, int x, int y, char *path)
{
	img_data img;

	img.img = mlx_xpm_file_to_image(mlx, path, &img.width, &img.height);
	mlx_put_image_to_window(mlx, window, img.img, x, y);
	return (img);
}

int inside_lines(unsigned long i, char *line, unsigned long w)
{
	while (i < (ft_strlen(line) - 1))
	{
		if (line[i] != '1')
			return(0);
		i += (w - 1);
		if (line[i] != '1')
			return(0);
		i++;
		if (line[i] != '\n' && i < (ft_strlen(line) - 1))
			return(0);
		i++;
	}
	i -= 2;
	return (i);
}

int map_wall_error(char *line, int width)
{
	unsigned long i;
	unsigned long w;

	i = 0;
	w = (unsigned long)width;
	while (i < w)
	{
		if (line[i] != '1')
			return (0);
		i++;
	}
	if (line[i] != '\n')
		return (0);
	i++;
	i = inside_lines(i, line, w);
	if (i == 0)
		return (0);
	while (i > (ft_strlen(line) - w))
	{
		if (line[i] != '1')
			return (0);
		i--;
	}
	return (1);
}

int item_error(char *line)
{
	char *player;

	player = ft_strchr(line, 'P');
	if (ft_strchr(line, 'C') == NULL)
	{
		printf(TEXT_ERROR_COLLECTIBLE);
		return (0);
	}
	else if (player == NULL)
	{
		printf(TEXT_ERROR_PLAYER);
		return (0);
	}
	else if (ft_strchr(++player, 'P') != NULL)
	{
		printf(TEXT_ERROR_M_PLAYER);
		return (0);
	}
	else if (ft_strchr(line, 'E') == NULL)
	{
		printf(TEXT_ERROR_EXIT);
		return (0);
	}
	else
		return (1);
}

void map_errors(char *line, int w_width, int w_height)
{
	int width;
	int height;

	(void)line;
	width = w_width / IMG_W;
	height = w_height / IMG_H;
	if (map_wall_error(line, width) == 0)
	{
		free(line);
		printf(TEXT_ERROR_MAP);
		printf(TEXT_ERROR);
		exit(0);
	}
	if (item_error(line) == 0)
	{
		free(line);
		printf(TEXT_ERROR);
		exit(0);
	}
}

win_data window_construction(void *mlx, char *path, t_param *p)
{
	win_data	window;
	int			fd;
	char		*line;
	char		*join;

	window.height = 0;
	join = (char *)malloc(1);
	join[0] = '\0';
	fd = open(path, O_RDONLY);
	line = get_next_line(fd);
	window.width = (ft_strlen(line) - 1) * IMG_W;
	while (line != NULL)
	{
		join = ft_strjoin(join, line);
		line = get_next_line(fd);
		window.height += IMG_H;
	}
	free(line);
	p->map = join;
	map_errors(join, window.width, window.height);
	window.w = mlx_new_window(mlx, window.width, window.height, TEXT_TITRE);
	return (window);
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

int go_to_left(t_param *p)
{
	char *p_pos;
	char lettre_left;

	p_pos = ft_strchr(p->map, 'P');
	lettre_left = *(p_pos - 1);
	if (lettre_left == 'E' && p->items.c == p->collect)
	{
		mlx_destroy_window(p->mlx, p->w.w);
		exit(0);
	}
	if (lettre_left != '1' && lettre_left != 'E')
	{
		if (lettre_left == 'C')
			p->collect = p->collect + 1; 
		*p_pos = '0';
		*(p_pos - 1) = 'P';
		render_img(p->mlx, p->w.w, p->player.x, p->player.y, IMG_GROUND);
		p->player.x = p->player.x - IMG_W;
		render_img(p->mlx, p->w.w, p->player.x, p->player.y, IMG_CAT_L);
		return (1);
	}
	return (0);
}

int go_to_right(t_param *p)
{
	char *p_pos;
	char lettre_right;

	p_pos = ft_strchr(p->map, 'P');
	lettre_right = *(p_pos + 1);
	if (lettre_right == 'E' && p->items.c == p->collect)
	{
		mlx_destroy_window(p->mlx, p->w.w);
		exit(0);
	}
	if (lettre_right != '1' && lettre_right != 'E')
	{
		if (lettre_right == 'C')
			p->collect = p->collect + 1; 
		*p_pos = '0';
		*(p_pos + 1) = 'P';
		render_img(p->mlx, p->w.w, p->player.x, p->player.y, IMG_GROUND);
		p->player.x = p->player.x + IMG_W;
		render_img(p->mlx, p->w.w, p->player.x, p->player.y, IMG_CAT_R);
		return (1);
	}
	return (0);
}

int go_up(t_param *p)
{
	char *p_pos;
	char lettre_up;

	p_pos = ft_strchr(p->map, 'P');
	lettre_up = *(p_pos - (p->w.width / IMG_W + 1));
	if (lettre_up == 'E' && p->items.c == p->collect)
	{
		mlx_destroy_window(p->mlx, p->w.w);
		exit(0);
	}
	if (lettre_up != '1' && lettre_up != 'E')
	{
		if (lettre_up == 'C')
			p->collect = p->collect + 1; 
		*p_pos = '0';
		p_pos = p_pos - (p->w.width / IMG_W + 1);
		*p_pos = 'P';
		render_img(p->mlx, p->w.w, p->player.x, p->player.y, IMG_GROUND);
		p->player.y = p->player.y - IMG_H;
		render_img(p->mlx, p->w.w, p->player.x, p->player.y, IMG_CAT_B);
		return (1);
	}
	return (0);
}

int go_down(t_param *p)
{
	char *p_pos;
	char lettre_down;

	p_pos = ft_strchr(p->map, 'P');
	lettre_down = *(p_pos + (p->w.width / IMG_W + 1));
	if (lettre_down == 'E' && p->items.c == p->collect)
	{
		mlx_destroy_window(p->mlx, p->w.w);
		exit(0);
	}
	if (lettre_down != '1' && lettre_down != 'E')
	{
		if (lettre_down == 'C')
			p->collect = p->collect + 1; 
		*p_pos = '0';
		p_pos = p_pos + (p->w.width / IMG_W + 1);
		*p_pos = 'P';
		render_img(p->mlx, p->w.w, p->player.x, p->player.y, IMG_GROUND);
		p->player.y = p->player.y + IMG_H;
		render_img(p->mlx, p->w.w, p->player.x, p->player.y, IMG_CAT_F);
		return (1);
	}
	return (0);
}

void display_steps(int p_steps, void *mlx, win_data window)
{
	char *steps;

	printf("Nombre de pas : %d\n", p_steps);
	render_text_box(mlx, window);
	steps = ft_itoa(p_steps);
	mlx_string_put(mlx, window.w, IMG_W2, IMG_H2, 0x2f09c0, "Nbr de pas:");
	mlx_string_put(mlx, window.w, (IMG_W2 * 4), IMG_H2, 0x2f09c0, steps);
}

int	key_hook(int keycode, t_param *p)
{
	if (keycode == 53)
	{
		mlx_destroy_window(p->mlx, p->w.w);
		exit(0);
	}
	if (keycode == 123 || keycode == 0)
		p->steps = p->steps + go_to_left(p);
	if (keycode == 124 || keycode == 2)
		p->steps = p->steps + go_to_right(p);
	if (keycode == 125 || keycode == 1)
		p->steps = p->steps + go_down(p);
	if (keycode == 126 || keycode == 13)
		p->steps = p->steps + go_up(p);
	display_steps(p->steps, p->mlx, p->w);
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

int	main(void)
{
	t_param p;
	
	p.mlx = mlx_init();
	p.w = window_construction(p.mlx, MAP_PATH, &p);
	render_map(p.mlx, p.w);
	set_player_position(&p);
	p.collect = 0;
	p.items.c = str_find(p.map, 'C');
	p.items.exit = str_find(p.map, 'E');
	p.items.player = str_find(p.map, 'P');
	mlx_string_put(p.mlx, p.w.w, IMG_W2, IMG_H2, 0x2f09c0, TEXT_START);
	mlx_key_hook(p.w.w, key_hook, &p);
	mlx_hook(p.w.w, 17, 0L << 0, closeg, &p);
	mlx_loop(p.mlx);
	free(p.map);
	return (0);
}