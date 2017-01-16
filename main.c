/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 12:12:48 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/16 14:41:53 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "w3d.h"

#define DBG_PRINT_MAP 1

static void
	print_map
	(t_map *map)
{
	t_u32	i;

	i = 0;
	PUT("width\t");
	ECHO_U32(map->width);
	PUT("height\t");
	ECHO_U32(map->height);
	while (i < map->height)
	{
		write(1, map->map + i * map->width, map->width);
		write(1, "\n", 1);
		i++;
	}
}

static void
	init
	(t_w3d_data *d)
{
	int		null;

	d->v.mlx = mlx_init();
	d->v.win = mlx_new_window(d->v.mlx, WIN_W, WIN_H, WIN_TITLE);
	d->v.tex = (void *)mlx_get_data_addr(d->v.win, &null, &null, &null);
	mlx_key_hook(d->v.win, &w3d_ev_keyboard, d);
	mlx_loop_hook(d->v.mlx, &w3d_loop, d);
	mlx_loop(d->v.mlx);
}

int
	main
	(int argc
	, char **argv)
{
	t_w3d_data	d;

	(void)argc;
	(void)argv;
	BZERO(d);
	if (!w3d_map_parse(0, &d.map))
		return (ERR(MAP_PARSE_ERR, 1, 0));
	if (DBG_PRINT_MAP)
		print_map(&d.map);
	init(&d);
	return (0);
}
