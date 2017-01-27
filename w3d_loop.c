/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 16:30:49 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/27 09:24:37 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "w3d.h"

t_i32
	w3d_loop
	(t_w3d_data *d)
{
	t_u64		end;
	t_u64		start;
	t_window	*window;

	window = &d->window;
	if (!window->update)
		return (0);
	window->update = false;
	start = mach_absolute_time();
	w3d_ray_dda(d);
	ft_bzero(window->tex, WIN_AREA * sizeof(*window->tex));
	cl_read(&d->cl_info, &d->cl_krl, 1, d->rays);
	cl_read(&d->cl_info, &d->cl_krl, 2, d->ray_colors);
	w3d_window_draw(window, d->rays, d->ray_colors);
	end = mach_absolute_time();
	mlx_put_image_to_window(window->mlx, window->win, window->img, 0, 0);
	d->ftime = w3d_window_fps(window, start, end);
	return (1);
}
