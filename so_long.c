/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:50:27 by mreymond          #+#    #+#             */
/*   Updated: 2022/01/31 17:37:47 by mreymond         ###   ########.fr       */
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

typedef struct window
{
	void 	*w;
	int		width;
	int		height;
}	win_data;

typedef struct	s_vars {
	void		*mlx;
	win_data	window;
}	t_vars;

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

void render_map(void *mlx, win_data	window)
{
	char	*line = NULL;
	int		gnl;
	int		x;
	int		y;
	img_data img;

	x = 0;
	y = 0;
	gnl = open("map/map.ber", O_RDONLY);
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
		y += IMG_HEIGHT;
		line = get_next_line(gnl);
	}
	free(line);
}

void go_to_left(t_vars *vars)
{
	printf("left\n");
	render_img(vars->mlx, vars->window.w, 0, 0, "./img/pirate.xpm");
}

void go_to_right()
{
	printf("right\n");
}

void go_up()
{
	printf("up\n");
}

void go_down()
{
	printf("down\n");
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == 53)
		mlx_destroy_window(vars->mlx, vars->window.w);
	if (keycode == 123)
		go_to_left(vars);
	if (keycode == 124)
		go_to_right();
	if (keycode == 125)
		go_down();
	if (keycode == 126)
		go_up();
	return (0);
}

int	main(void)
{
	t_vars vars;

	vars.mlx = mlx_init();
	vars.window = window_construction(vars.mlx, "map/map.ber");
	render_map(vars.mlx, vars.window);
	mlx_key_hook(vars.window.w, key_hook, &vars);
	mlx_loop(vars.mlx);
}