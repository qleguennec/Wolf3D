/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_ev_motion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 12:49:42 by qle-guen          #+#    #+#             */
/*   Updated: 2017/02/01 17:46:20 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "w3d.h"

static bool
	ev_motion_camera_fix
	(t_window *window
	, t_player *player
	, t_i32 x)
{
	if (x >= 0 && x < (t_i32)WIN_WIDTH)
		return (false);
	if (x < 0)
		mlx_mouse_set_pos(WIN_WIDTH + 100, WIN_YCENTER);
	if (x >= (t_i32)WIN_WIDTH)
	{
		(void)player;
		mlx_mouse_set_pos(100, WIN_YCENTER);
	}
	return (true);
}

static void
	ev_motion_rotate
	(t_player *player
	, t_f64_v2 mat)
{
	player->camera.x = player->camera_fix.x * mat.x
		+ player->camera_fix.y * mat.y;
	player->camera.y = player->camera_fix.y * mat.x
		- player->camera_fix.x * mat.y;
	player->direction.x = player->direction_fix.x * mat.x
		+ player->direction_fix.y * mat.y;
	player->direction.y = player->direction_fix.y * mat.x
		- player->direction_fix.x * mat.y;
}

t_i32
	w3d_ev_motion
	(t_i32 x
	, t_i32 y
	, t_w3d_data *d)
{
	t_f64		dx;
	t_f64_v2	trig;
	t_player	*player;
	t_window	*window;

	(void)y;
	window = &d->window;
	player = &d->player;
	if (window->fix)
	{
		player->camera_fix.x = player->camera.x;
		player->camera_fix.y = player->camera.y;
		player->direction_fix.x = player->direction.x;
		player->direction_fix.y = player->direction.y;
		window->fix = false;
		return (0);
	}
	else if ((window->fix = ev_motion_camera_fix(window, player, x)))
		return (0);
	window->update = true;
	dx = 2 * (double)x / WIN_WIDTH - 1;
	trig = V2(t_f64, dx, sin(acos(dx)));
	ev_motion_rotate(player, trig);
	return (0);
}
