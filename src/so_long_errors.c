/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 22:07:25 by mreymond          #+#    #+#             */
/*   Updated: 2022/02/09 18:43:33 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_map_name(char *name, t_param *p)
{
	char	*ext;
	int		point;

	point = ft_strlen(name) - 4;
	ext = ft_strnstr(name, ".ber", ft_strlen(name));
	if (ext == NULL || name + point != ext)
	{
		printf(TEXT_ERROR);
		printf(TEXT_ERROR_MAP_NAME);
		free_mlx(p);
		exit(0);
	}
}

int	inside_lines(unsigned long i, char *line, unsigned long w)
{
	while (i < (ft_strlen(line) - 1))
	{
		if (line[i] != '1')
			return (0);
		i += (w - 1);
		if (line[i] != '1')
			return (0);
		i++;
		if (line[i] != '\n' && i < (ft_strlen(line) - 1))
			return (0);
		i++;
	}
	i -= 2;
	return (i);
}

int	map_wall_error(char *line, int width)
{
	unsigned long	i;
	unsigned long	w;

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

int	item_error(char *line)
{
	char	*player;

	player = ft_strchr(line, 'P');
	if (ft_strchr(line, 'C') == NULL)
	{
		printf("%s%s", TEXT_ERROR, TEXT_ERROR_COLLECTIBLE);
		return (0);
	}
	else if (player == NULL)
	{
		printf("%s%s", TEXT_ERROR, TEXT_ERROR_PLAYER);
		return (0);
	}
	else if (ft_strchr(++player, 'P') != NULL)
	{
		printf("%s%s", TEXT_ERROR, TEXT_ERROR_M_PLAYER);
		return (0);
	}
	else if (ft_strchr(line, 'E') == NULL)
	{
		printf("%s%s", TEXT_ERROR, TEXT_ERROR_EXIT);
		return (0);
	}
	else
		return (1);
}

void	map_errors(t_param	*p, t_win_data window)
{
	int	width;
	int	height;

	width = window.width / IMG_W;
	height = window.height / IMG_H;
	if (map_wall_error(p->map, width) == 0)
	{
		printf(TEXT_ERROR);
		printf(TEXT_ERROR_MAP);
		free_mlx(p);
		exit(0);
	}
	if (item_error(p->map) == 0)
	{
		free_mlx(p);
		exit(0);
	}
}
