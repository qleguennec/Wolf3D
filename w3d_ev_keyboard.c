/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_ev_keyboard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:35:36 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/27 08:29:20 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "w3d.h"
#include <Events.h>

#define KEY(a) (key == kVK_ ## a)

static bool
	ev_keyboard_player_move
	(t_w3d_data *d
	, double xdir
	, double ydir)
{
	cl_double2	new_pos;
	t_i32_v2	map_coords;
	t_map		*map;
	t_player	*player;

	player = &d->player;
	map = &d->map;
	new_pos.x = player->position.x + xdir * player->mspeed;
	new_pos.y = player->position.y + ydir * player->mspeed;
	map_coords.x = (t_i32)new_pos.x;
	map_coords.y = (t_i32)new_pos.y;
	if (MAP2(map_coords) != MAP_WALL)
	{
		player->position.x = new_pos.x;
		player->position.y = new_pos.y;
		return (true);
	}
	return (false);
}

static bool
	ev_keyboard_player_rotate
	(t_player *player
	, double rotspeed)
{
	double		xtmp;
	double		rcos;
	double		rsin;

	rcos = cos(rotspeed);
	rsin = sin(rotspeed);
	xtmp = player->direction.x * rcos - player->direction.y * rsin;
	player->direction.y = player->direction.x * rsin
		+ player->direction.y * rcos;
	player->direction.x = xtmp;
	xtmp = player->camera.x * rcos - player->camera.y * rsin;
	player->camera.y = player->camera.x * rsin + player->camera.y * rcos;
	player->camera.x = xtmp;
	return (true);
}

t_i32
	w3d_ev_keyboard
	(t_i32 key
	, t_w3d_data *d)
{
	cl_double2	dir;
	t_map		*map;
	t_player	*player;
	t_window	*window;

	if (KEY(Escape))
		w3d_exit(d);
	player = &d->player;
	window = &d->window;
	map = &d->map;
	dir = player->direction;
	if (KEY(ANSI_W))
		window->update = ev_keyboard_player_move(d, dir.x, dir.y);
	else if (KEY(ANSI_S))
		window->update = ev_keyboard_player_move(d, -dir.x, -dir.y);
	else if (KEY(ANSI_A))
		window->update = ev_keyboard_player_rotate(player, player->rspeed);
	else if (KEY(ANSI_D))
		window->update = ev_keyboard_player_rotate(player, -player->rspeed);
	return (0);
}
