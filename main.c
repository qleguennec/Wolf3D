/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 12:12:48 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/27 09:26:10 by qle-guen         ###   ########.fr       */
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
	if (!(map->size.x = gnl_read_all(fd
		, &buf
		, GNL_CHECK_SIZE
		, (size_t *)&map->size.y)))
		return (false);
	map->map = buf.data;
	return (true);
}

static bool
	init_player
	(t_map *map
	, t_player *player)
{
	t_u8	*spawn;

	if (!(spawn = ft_memchr(map->map, MAP_SPAWN, MAP_WIDTH * MAP_HEIGHT)))
		return (false);
	*spawn = MAP_POINT;
	player->position.x = (spawn - map->map) / MAP_WIDTH;
	player->position.y = (spawn - map->map) % MAP_WIDTH;
	player->camera.x = INIT_CAMERA_X;
	player->camera.y = INIT_CAMERA_Y;
	player->direction.x = INIT_DIRECTION_X;
	player->direction.y = INIT_DIRECTION_Y;
	player->mspeed = INIT_PLAYER_MS;
	player->rspeed = INIT_PLAYER_RS;
	return (true);
}

static bool
	init_cl
	(t_window *window
	, t_map *map
	, t_cl_info *cl_info
	, t_cl_krl *cl_krl)
{
	int		fd;

	if ((fd = open(CL_SRC_FILE, O_RDONLY)) < 0)
		return (false);
	cl_init(cl_info);
	cl_krl_init(cl_krl, 3);
	cl_krl->sizes[0] = MAP_WIDTH * MAP_HEIGHT * sizeof(char);
	cl_krl->sizes[1] = WIN_WIDTH * sizeof(t_u32);
	cl_krl->sizes[2] = WIN_WIDTH * sizeof(t_u32);
	if (cl_krl_build(cl_info, cl_krl, fd, CL_BUILD_LINE) != CL_SUCCESS)
		return (false);
	close(fd);
	if (!(cl_write(cl_info, cl_krl, 0, map->map) == CL_SUCCESS))
		return (false);
	if (CL_KRL_ARG(cl_krl->krl, 3, map->size) != CL_SUCCESS)
		return (false);
	if (CL_KRL_ARG(cl_krl->krl, 4, window->size) != CL_SUCCESS)
		return (false);
	return (true);
}

static bool
	init_window
	(t_w3d_data *d)
{
	t_i32		null;
	t_window	*window;

	window = &d->window;
	if (!(window->mlx = mlx_init()))
		return (false);
	if (!(window->img = mlx_new_image(window->mlx, WIN_WIDTH, WIN_HEIGHT)))
		return (false);
	if (!(window->tex = (t_u32 *)mlx_get_data_addr(window->img, &null, &null, &null)))
		return (false);
	ft_bzero(window->tex, WIN_AREA * sizeof(*window->tex));
	if (!(window->win = mlx_new_window(window->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE)))
		return (false);
	mlx_loop_hook(window->mlx, &w3d_loop, d);
	mlx_key_hook(window->win, &w3d_ev_keyboard, d);
	//mlx_hook(window->win, MotionNotify, PointerMotionMask, &w3d_ev_motion, d);
	window->update = true;
	return (true);
}

int
	main
	(int argc
	, char **argv)
{
	t_w3d_data	d;

	if (argc != 2)
		return (ERR(USAGE, 1, 0));
	BZERO(d);
	STRTOB10(argv[1], d.window.size.y);
	if (d.window.size.y < WIN_MINH || d.window.size.y > WIN_MAXH)
		return (ERR(WRONG_HEIGHT, 1, WIN_MINH, WIN_MAXH));
	d.window.size.x = d.window.size.y * WIN_RATIO;
	if (!init_map(0, &d.map))
		return (ERR(MAP_PARSE_ERR, 1, 0));
	if (!init_player(&d.map, &d.player))
		return (ERR(PLAYER_INIT_ERR, 1, 0));
	if (!init_cl(&d.window, &d.map, &d.cl_info, &d.cl_krl))
		return (ERR(CL_INIT_ERR, 1, 0));
	if (!init_window(&d))
		return (ERR(MLX_INIT_ERR, 1, 0));
	MALLOC_N(d.rays, d.window.size.x);
	MALLOC_N(d.ray_colors, d.window.size.x);
	mlx_loop(d.window.mlx);
}
