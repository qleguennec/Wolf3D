/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_ev_keyboard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:35:36 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/21 16:53:58 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "w3d.h"
#include <Events.h>

#define KEY(a) 			if (key == kVK_ ## a)
#define KEY_UPDATE(a)	if (key == kVK_ ## a && (window->update = true))

static void
	ev_keyboard_pos_check_bounds
	(t_map *map
	, t_player *player
	, t_i32_v2 delta)
{
	t_i32_v2	sum;

	sum = V2(t_i32
		, ((t_i32)player->position.x + delta.x)
		, ((t_i32)player->position.y + delta.y));
	if (sum.x >= 0 && sum.x < (t_i32)MAP_WIDTH
		&& sum.y >= 0 && sum.y < (t_i32)MAP_HEIGHT
		&& MAP2(sum) != MAP_WALL)
	{
		player->position.x = sum.x;
		player->position.y = sum.y;
	}
}

t_i32
	w3d_ev_keyboard
	(t_i32 key
	, t_w3d_data *d)
{
	t_i32_v2	delta;
	t_map		*map;
	t_player	*player;
	t_window	*window;

	KEY(Escape)
		w3d_exit(d);
	player = &d->player;
	window = &d->window;
	map = &d->map;
	delta = V2(t_i32, 0, 0);
	KEY_UPDATE(ANSI_A)
		delta.x = -DX;
	KEY_UPDATE(ANSI_D)
		delta.x = DX;
	KEY_UPDATE(ANSI_S)
		delta.y = -DY;
	KEY_UPDATE(ANSI_W)
		delta.y = +DY;
	ev_keyboard_pos_check_bounds(map, player, delta);
	return (0);
}
