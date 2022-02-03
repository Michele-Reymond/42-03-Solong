/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 22:06:58 by mreymond          #+#    #+#             */
/*   Updated: 2022/02/03 22:40:43 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

int closeg(int keycode, t_param p)
{
	(void)keycode;
	(void)p;
	exit(0);
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
