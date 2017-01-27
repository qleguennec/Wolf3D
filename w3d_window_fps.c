/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_window_fps.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 13:19:53 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/26 15:33:11 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "w3d.h"

double
	w3d_window_fps
	(t_window *window
	, t_u64 start
	, t_u64 end)
{
	char		*buf;
	double		dt;

	dt = (double)(end - start) / 1000000000;
	asprintf(&buf, "render time: %lfs    fps: %lf", dt, 1 / dt);
	mlx_string_put(window->mlx, window->win, 0, 0, 0xFFFFFF, buf);
	free(buf);
	return (dt);
}
