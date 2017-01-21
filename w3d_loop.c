/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 16:30:49 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/21 16:59:46 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "w3d.h"

t_i32
	w3d_loop
	(t_w3d_data *d)
{
	t_window	*window;

	window = &d->window;
	//d->player.camera.x -= 1;
	//d->player.camera.y -= 1;
	if (!window->update)
		return (0);
	window->update = false;
	w3d_ray_dda(d);
	mlx_clear_window(window->mlx, window->win);
	ft_bzero(window->tex, WIN_AREA * sizeof(int));
	cl_read(&d->cl_info, &d->cl_krl, 1, d->rays);
	w3d_window_draw(window, d->rays);
	mlx_put_image_to_window(window->mlx, window->win, window->img, 0, 0);
	return (1);
}
