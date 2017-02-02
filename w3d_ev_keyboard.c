/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_ev_keyboard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:35:36 by qle-guen          #+#    #+#             */
/*   Updated: 2017/02/02 10:54:21 by qle-guen         ###   ########.fr       */
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
	dir.x = player->direction.x;
	dir.y = player->direction.y;
	if (KEY(ANSI_W))
		window->update = ev_keyboard_player_move(d, dir.x, dir.y);
	else if (KEY(ANSI_S))
		window->update = ev_keyboard_player_move(d, -dir.x, -dir.y);
	else if (KEY(ANSI_A))
		window->update = ev_keyboard_player_move(d, dir.y, -dir.x);
	else if (KEY(ANSI_D))
		window->update = ev_keyboard_player_move(d, -dir.y, dir.x);
	return (0);
}
