/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 12:12:48 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/17 17:05:37 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "w3d.h"

static bool
	init_map
	(t_i32 fd
	, t_map *map)
{
	t_vect	buf;

	vect_init(&buf);
	if (!(map->width = gnl_read_all(fd, &buf, GNL_CHECK_SIZE, &map->height)))
		return (false);
	map->map = buf.data;
	map->width = buf.used / map->height;
	return (true);
}

static bool
	init_player
	(t_map *map
	, t_player *player)
{
	t_u8	*spawn;

	if (!(spawn = ft_memchr(map->map, MAP_SPAWN, map->width * map->height)))
		return (false);
	*spawn = MAP_POINT;
	player->pos = V2(t_f32
		, (t_u32)((spawn - map->map) / map->width)
		, (t_u32)((spawn - map->map) % map->width));
	ECHO2_U32(player->pos);
	player->dv = INIT_DV;
	player->cv = INIT_CV;
	return (true);
}

static bool
	init_video
	(t_w3d_data *d)
{
	int		null;
	t_video	*video;

	video = &d->video;
	if (!(video->mlx = mlx_init()))
		return (false);
	if (!(video->img = mlx_new_image(video->mlx, WIDTH, HEIGHT)))
		return (false);
	if (!(video->tex = (void *)mlx_get_data_addr(video->img, &null, &null, &null)))
		return (false);
	if (!(video->win = mlx_new_window(video->img, WIDTH, HEIGHT, WIN_TITLE)))
		return (false);
	mlx_loop_hook(video->mlx, &w3d_loop, d);
	mlx_key_hook(video->win, &w3d_ev_keyboard, d);
	mlx_hook(video->win, MotionNotify, PointerMotionMask, &w3d_ev_motion, d);
	mlx_loop(video->mlx);
	return (true);
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
	if (!init_map(0, &d.map))
		return (ERR(MAP_PARSE_ERR, 1, 0));
	if (!init_player(&d.map, &d.player))
		return (ERR(PLAYER_INIT_ERR, 1, 0));
	if (!init_video(&d))
		return (ERR(MLX_INIT_ERR, 1, 0));
	return (0);
}
