/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_ev_motion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 12:49:42 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/17 15:23:20 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "w3d.h"

//TODO remove
static bool pp(t_u32_v2 pos, t_video *video)
{
	mlx_pixel_put(video->mlx, video->win, pos.x, pos.y, 0xFF);
	return ((pos.x > 0 && pos.y > 0 && pos.x < WIDTH && pos.y < HEIGHT));
}

t_i32
	w3d_ev_motion
	(t_i32 x
	, t_i32 y
	, t_w3d_data *d)
{
	t_video		*video;

	video = &d->video;
	w3d_ray_dda(V2(t_u32, WIDTH_2, HEIGHT_2), V2(t_u32, x, y), (bool (*)(t_u32_v2, void *))&pp, video);
	return (0);
}
