/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 16:30:49 by qle-guen          #+#    #+#             */
/*   Updated: 2017/02/06 10:37:39 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "w3d.h"

static void
	draw
	(t_w3d_data *d)
{
	t_player	*player;
	t_window	*window;

	window = &d->window;
	player = &d->player;
	ft_memcpy(window->tex + WIN_YCENTER * WIN_WIDTH, window->bg, 2 * WIN_AREA);
	w3d_window_draw_skybox(window, player);
	w3d_ray_dda(d);
	w3d_window_draw(window, d->rays, d->ray_colors);
}

t_i32
	w3d_loop
	(t_w3d_data *d)
{
	t_u64		exec_time;
	t_window	*window;

	window = &d->window;
	if (!window->update)
		return (0);
	window->update = false;
	exec_time = w3d_exec_time(&draw, d);
	mlx_put_image_to_window(window->mlx, window->win, window->img, 0, 0);
	w3d_window_fps(window, exec_time);
	return (1);
}
