/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_directions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 22:07:33 by mreymond          #+#    #+#             */
/*   Updated: 2022/02/03 22:40:38 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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