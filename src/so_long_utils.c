/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 22:06:58 by mreymond          #+#    #+#             */
/*   Updated: 2022/02/04 16:18:12 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

win_data window_construction(void *mlx, char *path, t_param *p)
{
	win_data	window;
	int			fd;
	char		*line;

	p->map = ft_strdup("");
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		free(p->map);
		exit(0);
	}
	line = get_next_line(fd);
	window.width = (ft_strlen(line) - 1) * IMG_W;
	while (line != NULL)
	{
		p->map = ft_strjoin(p->map, line);
		line = get_next_line(fd);
		window.height += IMG_H;
	}
	free(line);
	line = NULL;
	close(fd);
	map_errors(p->map, window.width, window.height);
	window.w = mlx_new_window(mlx, window.width, window.height, TEXT_TITRE);
	return (window);
}

int closeg(int keycode, t_param p)
{
	(void)keycode;
	(void)p;
	exit(0);
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

void free_mlx(t_param *p)
{
	free(p->map);
	p->map = NULL;
	free(p->w.w);
	p->w.w = NULL;
	free(p->mlx);
	p->mlx = NULL;
}
