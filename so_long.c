/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:50:27 by mreymond          #+#    #+#             */
/*   Updated: 2022/01/28 16:00:13 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	main(void)
{
	void	*mlx;
	void	*window;
	t_data	img;
	int x;
	int y;
	int i;
	int line;

	char *la = "11111x11111";
	char *lb = "111xxxxx111";
	char *lc = "1xxxxxxxxx1";
	char *ld = "111xxxxx111";
	char *le = "11111x11111";
	
	x = 0;
	y = 0;
	i = 0;
	line = 0;

	mlx = mlx_init();
	window = mlx_new_window(mlx, 500, 500, "Hello world!");
	img.img = mlx_new_image(mlx, 500, 500);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);


	while (la[i] != '\0')
	{
		if (la[i] == '1')
		{
			while (line < 30)
			{
				my_mlx_pixel_put(&img, x, y, 0x00FFFF00);
				line++;
				x++;
			}
		}
		if (la[i] == 'x')
		{
			while (line < 30)
			{
				my_mlx_pixel_put(&img, x, y, 0x00FF00FF);
				x++;
				line++;
			}
		}
		line = 0;
		i++;
	}

	x = 0;
	i = 0;
	y++;
	while (lb[i] != '\0')
	{
		if (lb[i] == '1')
		{
			while (line < 30)
			{
				my_mlx_pixel_put(&img, x, y, 0x00FFFF00);
				line++;
				x++;
			}
		}
		if (lb[i] == 'x')
		{
			while (line < 30)
			{
				my_mlx_pixel_put(&img, x, y, 0x00FF00FF);
				x++;
				line++;
			}
		}
		line = 0;
		i++;
	}

	x = 0;
	i = 0;
	y++;
	while (lc[i] != '\0')
	{
		if (lc[i] == '1')
		{
			while (line < 30)
			{
				my_mlx_pixel_put(&img, x, y, 0x00FFFF00);
				line++;
				x++;
			}
		}
		if (lc[i] == 'x')
		{
			while (line < 30)
			{
				my_mlx_pixel_put(&img, x, y, 0x00FF00FF);
				x++;
				line++;
			}
		}
		line = 0;
		i++;
	}

	x = 0;
	i = 0;
	y++;
	while (ld[i] != '\0')
	{
		if (ld[i] == '1')
		{
			while (line < 30)
			{
				my_mlx_pixel_put(&img, x, y, 0x00FFFF00);
				line++;
				x++;
			}
		}
		if (ld[i] == 'x')
		{
			while (line < 30)
			{
				my_mlx_pixel_put(&img, x, y, 0x00FF00FF);
				x++;
				line++;
			}
		}
		line = 0;
		i++;
	}

	x = 0;
	i = 0;
	y++;
	while (le[i] != '\0')
	{
		if (le[i] == '1')
		{
			while (line < 30)
			{
				my_mlx_pixel_put(&img, x, y, 0x00FFFF00);
				line++;
				x++;
			}
		}
		if (le[i] == 'x')
		{
			while (line < 30)
			{
				my_mlx_pixel_put(&img, x, y, 0x00FF00FF);
				x++;
				line++;
			}
		}
		line = 0;
		i++;
	}

	mlx_put_image_to_window(mlx, window, img.img, 50, 50);
	mlx_loop(mlx);
}
