/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_ray_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 11:27:05 by qle-guen          #+#    #+#             */
/*   Updated: 2017/02/06 09:05:42 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "w3d.h"

static cl_int
	ray_dda_run
	(t_player *player
	, t_i32 win_width
	, t_cl_info *cl_info
	, cl_kernel krl)
{
	size_t	work_size;

	work_size = win_width;
	CL_KRL_ARG(krl, 4, player->camera);
	CL_KRL_ARG(krl, 5, player->direction);
	CL_KRL_ARG(krl, 6, player->position);
	return (cl_krl_exec(cl_info, krl, 1, &work_size));
}

void
	w3d_ray_dda
	(t_w3d_data *d)
{
	t_cl_info	*cl_info;
	t_cl_krl	*cl_krl;
	t_player	*player;
	t_window	*window;

	cl_info = &d->cl_info;
	cl_krl = &d->cl_krl;
	player = &d->player;
	window = &d->window;
	ray_dda_run(player, window->size.x, cl_info, cl_krl->krl);
	cl_read(cl_info, cl_krl, 1, d->rays);
	cl_read(cl_info, cl_krl, 2, d->ray_colors);
}
