/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 22:06:58 by mreymond          #+#    #+#             */
/*   Updated: 2022/02/10 14:12:24 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	store_map(int fd, t_param *p, t_win_data *window)
{
	char	*line;
	char	*tmp;

	line = get_next_line(fd);
	window->width = (ft_strlen(line) - 1) * IMG_W;
	window->height = 0;
	while (line != NULL)
	{
		tmp = line;
		p->map = ft_strjoin_gnl(p->map, tmp);
		line = get_next_line(fd);
		free(tmp);
		tmp = NULL;
		window->height += IMG_H;
	}
	free(line);
	line = NULL;
}

t_win_data	window_construction(char *path, t_param *p)
{
	t_win_data	window;
	int			fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		free_mlx(p);
		exit(0);
	}
	store_map(fd, p, &window);
	close(fd);
	map_errors(p, window);
	window.w = mlx_new_window(p->mlx, window.width, window.height, TEXT_TITRE);
	return (window);
}

int	closeg(int keycode, t_param p)
{
	(void)keycode;
	(void)p;
	exit(0);
}

int	str_find(char *str, char lettre)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (*str != '\0')
	{
		str = ft_strchr(str, lettre);
		if (str == NULL)
			break ;
		i++;
		str++;
	}
	return (i);
}

void	free_mlx(t_param *p)
{
	if (p->map)
	{
		free(p->map);
		p->map = NULL;
	}
	if (p->w.w)
	{
		free(p->w.w);
		p->w.w = NULL;
	}
	if (p->mlx)
	{
		free(p->mlx);
		p->mlx = NULL;
	}
}
