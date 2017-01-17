/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 12:12:48 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/17 12:37:01 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "w3d.h"

#define DBG_PRINT_MAP 0

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
	init_video
	(t_w3d_data *d)
{
	int		null;

	d->video.mlx = mlx_init();
	d->video.win = mlx_new_window(d->video.mlx, d->video.width, d->video.height, WIN_TITLE);
	d->video.tex = (void *)mlx_get_data_addr(d->video.win, &null, &null, &null);
	mlx_key_hook(d->video.win, &w3d_ev_keyboard, d);
	mlx_loop_hook(d->video.mlx, &w3d_loop, d);
	mlx_loop(d->video.mlx);
}

int
	main
	(int argc
	, char **argv)
{
	t_w3d_data	d;

	BZERO(d);
	if (argc != 2)
		return (ERR(USAGE, 1, 0));
	STRTOB10(argv[1], d.video.height);
	if (d.video.height < WIN_MINH || d.video.height > WIN_MAXH)
		return (ERR(WRONG_HEIGHT, 1, WIN_MINH, WIN_MAXH));
	d.video.width = d.video.height * 16 / 9;
	if (!w3d_map_parse(0, &d.map))
		return (ERR(MAP_PARSE_ERR, 1, 0));
	if (DBG_PRINT_MAP)
		print_map(&d.map);
	init_video(&d);
	return (0);
}
