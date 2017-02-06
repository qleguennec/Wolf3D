/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_ev_keyboard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:35:36 by qle-guen          #+#    #+#             */
/*   Updated: 2017/02/06 09:37:22 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "w3d.h"
#include <Events.h>

#define KEY(a) (key == kVK_ ## a)

static void
	dda_increment
	(t_f64_v2 *side_dist
	, t_f64_v2 delta
	, t_u32_v2 step
	, t_u32_v2 *coords)
{
	if (side_dist->x < side_dist->y)
	{
		side_dist->x += delta.x;
		coords->x += step.x;
	}
	else
	{
		side_dist->y += delta.y;
		coords->y += step.y;
	}
}

static bool
	check_bounds_dda
	(t_u8 *map
	, cl_double2 *pos
	, t_f64_v2 col
	, t_u32 *wall_dist)
{
	t_f64		col2;
	t_f64_v2	delta;
	t_f64_v2	side_dist;
	t_u32_v2	coords;
	t_u32_v2	step;

	col2 = (col.x * col.x) / (col.y * col.y);
	delta = V2(t_f64, sqrt(1.0 + 1.0 / col2), sqrt(1.0 + col2));
	step = V2(t_u32, col.x >= 0 ? 1 : -1, col.y >= 0 ? 1 : -1);
	coords = V2(t_u32, (t_u32)pos->x, (t_u32)pos->y);
	side_dist.x = delta.x * (col.x < 0
		? (pos->x - coords.x) : (pos->x + 1.0 - coords.x));
	side_dist.y = delta.y * (col.y < 0
		? (pos->y - coords.y) : (pos->y + 1.0 - coords.y));
	while (*wall_dist < COLLIDER_RADIUS)
	{
		if (MAP2(coords) == MAP_WALL)
			return (false);
		dda_increment(&side_dist, delta, step, &coords);
		(*wall_dist)++;
	}
	return (true);
}

static bool
	player_move_check_walls
	(t_u8 *map
	, t_player *player
	, cl_double2 *new_pos)
{
	t_f64_v2	mid;
	t_f64_v2	left;
	t_f64_v2	right;
	t_u32		wall_dist;

	mid = V2(t_f64
		, player->direction.x
		, player->direction.y);
	left = V2(t_f64
		, player->direction.x - player->camera.x / COLLIDER_FRACT
		, player->direction.y - player->camera.y / COLLIDER_FRACT);
	right = V2(t_f64
		, player->direction.x + player->camera.x / COLLIDER_FRACT
		, player->direction.y + player->camera.y / COLLIDER_FRACT);
	wall_dist = 0;
	if (!check_bounds_dda(map, new_pos, mid, &wall_dist))
		return (false);
	wall_dist = 0;
	if (!check_bounds_dda(map, new_pos, left, &wall_dist))
		return (false);
	wall_dist = 0;
	if (!check_bounds_dda(map, new_pos, right, &wall_dist))
		return (false);
	return (true);
}

static bool
	ev_keyboard_player_move
	(t_w3d_data *d
	, double xdir
	, double ydir)
{
	cl_double2	new_pos;
	t_player	*player;
	t_u8		*map;

	player = &d->player;
	map = d->map;
	new_pos.x = player->position.x + xdir * player->mspeed;
	new_pos.y = player->position.y + ydir * player->mspeed;
	if (!player_move_check_walls(map, player, &new_pos))
		return (false);
	player->position = new_pos;
	return (true);
}

t_i32
	w3d_ev_keyboard
	(t_i32 key
	, t_w3d_data *d)
{
	cl_double2	dir;
	t_player	*player;
	t_window	*window;

	if (KEY(Escape))
		w3d_exit(d);
	player = &d->player;
	window = &d->window;
	dir.x = player->direction.x;
	dir.y = player->direction.y;
	if (KEY(ANSI_W))
		window->update = ev_keyboard_player_move(d, dir.x, dir.y);
	else if (KEY(ANSI_S))
		window->update = ev_keyboard_player_move(d, -dir.x, -dir.y);
	else if (KEY(ANSI_A))
		window->update = ev_keyboard_player_move(d, -dir.y, dir.x);
	else if (KEY(ANSI_D))
		window->update = ev_keyboard_player_move(d, dir.y, -dir.x);
	return (0);
}
