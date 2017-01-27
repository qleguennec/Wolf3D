/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_ev_motion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 12:49:42 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/27 08:19:26 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "w3d.h"

t_i32
	w3d_ev_motion
	(t_i32 x
	, t_i32 y
	, t_w3d_data *d)
{
	double		xdeg;
	double		ydeg;
	double		xtmp;
	t_player	*player;
	t_window	*window;

	window = &d->window;
	(void)y;
	(void)ydeg;
	window->update = true;
	player = &d->player;
	if (x < 0 || y < 0)
		return (0);
	x -= WIN_XCENTER;
	xdeg = (double)x / WIN_WIDTH * M_PI * 2 * player->rspeed;
	xtmp = player->direction.x * cos(xdeg);
	player->direction.x = xtmp;
	player->camera.x = player->camera.x * cos(xdeg);
	return (0);
}
