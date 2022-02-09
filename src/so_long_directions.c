/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_directions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 22:07:33 by mreymond          #+#    #+#             */
/*   Updated: 2022/02/09 18:46:52 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_move(t_param *p, char *cat, int direction, int steps)
{
	t_pos	pos;

	pos.x = p->player.x;
	pos.y = p->player.y;
	render_img(p->mlx, p->w.w, &pos, IMG_GROUND);
	if (steps == 1 || steps == -1)
		p->player.x = p->player.x + direction;
	else
		p->player.y = p->player.y + direction;
	pos.x = p->player.x;
	pos.y = p->player.y;
	render_img(p->mlx, p->w.w, &pos, cat);
}

int	move(t_param *p, int steps, char *cat, int direction)
{
	char	*p_pos;
	char	lettre_left;

	p_pos = ft_strchr(p->map, 'P');
	lettre_left = *(p_pos + steps);
	if (lettre_left == 'E' && p->collectibles == p->collected)
	{
		free(p->map);
		p->map = NULL;
		mlx_destroy_window(p->mlx, p->w.w);
		exit(0);
	}
	if (lettre_left != '1' && lettre_left != 'E')
	{
		if (lettre_left == 'C')
			p->collected = p->collected + 1;
		*p_pos = '0';
		*(p_pos + steps) = 'P';
		print_move(p, cat, direction, steps);
		return (1);
	}
	return (0);
}

void	display_steps(int p_steps, void *mlx, t_win_data window)
{
	char	*steps;

	printf("Nombre de pas : %d\n", p_steps);
	render_text_box(mlx, window);
	steps = ft_itoa(p_steps);
	mlx_string_put(mlx, window.w, IMG_W2, IMG_H2, 0x2f09c0, "Nbr de pas:");
	mlx_string_put(mlx, window.w, (IMG_W2 * 4), IMG_H2, 0x2f09c0, steps);
	free(steps);
	steps = NULL;
}

int	key_hook(int keycode, t_param *p)
{
	int	horizontal_move;
	int	vertical_move;

	horizontal_move = 1;
	vertical_move = p->w.width / IMG_W + 1;
	if (keycode == KEY_ESC)
	{
		free(p->map);
		p->map = NULL;
		mlx_destroy_window(p->mlx, p->w.w);
		exit(0);
	}
	else if (keycode == KEY_LEFT || keycode == KEY_A)
		p->steps = p->steps + move(p, -horizontal_move, IMG_CAT_L, -IMG_H);
	else if (keycode == KEY_RIGHT || keycode == KEY_D)
		p->steps = p->steps + move(p, horizontal_move, IMG_CAT_R, IMG_H);
	else if (keycode == KEY_DOWN || keycode == KEY_S)
		p->steps = p->steps + move(p, vertical_move, IMG_CAT_F, IMG_H);
	else if (keycode == KEY_UP || keycode == KEY_W)
		p->steps = p->steps + move(p, -vertical_move, IMG_CAT_B, -IMG_H);
	display_steps(p->steps, p->mlx, p->w);
	return (0);
}
