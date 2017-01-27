/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_window_fps.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 13:19:53 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/27 10:47:49 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "w3d.h"

void
	w3d_window_fps
	(t_window *window
	, t_u64 delta)
{
	char		*buf;
	double		dt;

	dt = (double)delta / 1000000000;
	asprintf(&buf, "render time: %lfs    fps: %lf", dt, 1 / dt);
	mlx_string_put(window->mlx, window->win, 0, 0, 0xFFFFFF, buf);
	free(buf);
}