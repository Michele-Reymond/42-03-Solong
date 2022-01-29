/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:50:27 by mreymond          #+#    #+#             */
/*   Updated: 2022/01/29 18:06:19 by mreymond         ###   ########.fr       */
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

int	main(void)
{
	void	*mlx;
	win_data	window;

	mlx = mlx_init();
	window = window_construction(mlx, "map/map.ber");
	render_map(mlx, window);
	mlx_loop(mlx);
}