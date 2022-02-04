/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:50:27 by mreymond          #+#    #+#             */
/*   Updated: 2022/02/04 15:28:22 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main()
{
	t_param p;
	
	p.mlx = mlx_init();
	check_map_name(MAP_PATH);
	p.w = window_construction(p.mlx, MAP_PATH, &p);
	render_map(p.mlx, p.w, p.map);
	set_player_position(&p);
	p.collected = 0;
	p.collectibles = str_find(p.map, 'C');
	mlx_string_put(p.mlx, p.w.w, IMG_W2, IMG_H2, 0x2f09c0, TEXT_START);
	mlx_key_hook(p.w.w, key_hook, &p);
	mlx_hook(p.w.w, 17, 0L << 0, closeg, &p);
	mlx_loop(p.mlx);
	free(p.map);
	p.map = NULL;
	return (0);
}