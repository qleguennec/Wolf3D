 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 12:12:48 by qle-guen          #+#    #+#             */
/*   Updated: 2017/02/06 09:58:24 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "w3d.h"

static void
	init_map
	(t_u32 seed
	, t_u8 **map)
{
	size_t	area;
	t_gen	gen;

	MALLOC_N(*map, MAP_WIDTH * MAP_HEIGHT);
	gen.seed = seed;
	gen.width = MAP_WIDTH;
	gen.height = MAP_HEIGHT;
	gen.rooms = vll_new();
	area = MAP_WIDTH * MAP_HEIGHT;
	ft_memset(*map, MAP_NONE, area);
	mgen_gen(&gen);
	mgen_map_draw(&gen, *map);
	vll_free(gen.rooms);
}

static bool
	init_player
	(t_u8 *map
	, t_player *player)
{
	t_u8	*spawn;

	if (!(spawn = ft_memchr(map, MAP_SPAWN, MAP_WIDTH * MAP_HEIGHT)))
		return (false);
	*spawn = MAP_POINT;
	player->position.x = (spawn - map) % MAP_WIDTH;
	player->position.y = (spawn - map) / MAP_WIDTH;
	player->camera.x = INIT_CAMERA_X;
	player->camera.y = INIT_CAMERA_Y;
	player->direction.x = INIT_DIRECTION_X;
	player->direction.y = INIT_DIRECTION_Y;
	player->camera_fix.x = INIT_CAMERA_X;
	player->camera_fix.y = INIT_CAMERA_Y;
	player->direction_fix.x = INIT_DIRECTION_X;
	player->direction_fix.y = INIT_DIRECTION_Y;
	player->mspeed = INIT_PLAYER_MS;
	return (true);
}

static bool
	init_cl
	(t_window *window
	, t_u8 *map
	, t_cl_info *cl_info
	, t_cl_krl *cl_krl)
{
	int		fd;

	if ((fd = open(CL_SRC_FILE, O_RDONLY)) < 0)
		return (false);
	cl_init(cl_info);
	cl_krl_init(cl_krl, 3);
	cl_krl->sizes[0] = MAP_WIDTH * MAP_HEIGHT * sizeof(char);
	cl_krl->sizes[1] = WIN_WIDTH * sizeof(cl_uint);
	cl_krl->sizes[2] = cl_krl->sizes[1];
	if (cl_krl_build(cl_info, cl_krl, fd, CL_BUILD_LINE) != CL_SUCCESS)
		return (false);
	close(fd);
	if (cl_write(cl_info, cl_krl, 0, map) != CL_SUCCESS)
		return (false);
	if (CL_KRL_ARG(cl_krl->krl, 3, window->size) != CL_SUCCESS)
		return (false);
	return (true);
}

static bool
	init_window
	(t_w3d_data *d)
{
	t_i32		ox;
	t_window	*window;

	window = &d->window;
	if (!(window->mlx = mlx_init()))
		return (false);
	if (!(window->img = mlx_new_image(window->mlx, WIN_WIDTH, WIN_HEIGHT)))
		return (false);
	if (!(window->tex = (t_u32 *)mlx_get_data_addr(window->img, &ox, &ox, &ox)))
		return (false);
	if (!(window->win = mlx_new_window(window->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE)))
		return (false);
	mlx_do_key_autorepeaton(window->mlx);
	mlx_loop_hook(window->mlx, &w3d_loop, d);
	mlx_hook(window->win, MotionNotify, PointerMotionMask, &w3d_ev_motion, d);
	mlx_hook(window->win, KeyPress, 0, &w3d_ev_keyboard, d);
	mlx_window_get_origin(window->win, &ox, NULL);
	mlx_mouse_hidden(1);
	mlx_mouse_set_pos(WIN_XCENTER + ox, WIN_YCENTER);
	window->update = true;
	return (true);
}

int
	main
	(int argc
	, char **argv)
{
	t_u32		seed;
	t_w3d_data	d;

	if (argc != 3 || ft_strlen(argv[1]) > 9 || ft_strlen(argv[2]) > 9
		|| !(STRONLY(argv[1], DIGIT) && STRONLY(argv[2], DIGIT)))
		return (ERR(USAGE, 1, 0));
	BZERO(d);
	seed = 0;
	STRTOB10(argv[1], d.window.size.y);
	STRTOB10(argv[2], seed);
	if (d.window.size.y < WIN_MINH || d.window.size.y > WIN_MAXH)
		return (ERR(WRONG_HEIGHT, 1, WIN_MINH, WIN_MAXH));
	d.window.size.x = d.window.size.y * WIN_RATIO;
	init_map(seed, &d.map);
	if (!init_player(d.map, &d.player))
		return (ERR(PLAYER_INIT_ERR, 1, 0));
	if (!init_cl(&d.window, d.map, &d.cl_info, &d.cl_krl))
		return (ERR(CL_INIT_ERR, 1, 0));
	if (!init_window(&d))
		return (ERR(MLX_INIT_ERR, 1, 0));
	MALLOC_N(d.rays, d.window.size.x);
	MALLOC_N(d.ray_colors, d.window.size.x);
	if (!(w3d_init_skybox(&d.window)))
		return (ERR(SKYBOX_INIT_ERR, 1, 0));
	mlx_loop(d.window.mlx);
}
