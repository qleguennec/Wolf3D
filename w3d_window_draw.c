/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_window_draw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 14:01:57 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/27 09:25:25 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "w3d.h"

void
	w3d_window_draw
	(t_window *window
	, t_u32 *rays
	, t_u32 *ray_colors)
{
	size_t	i;
	t_u32	*out;
	t_u32	end;
	t_u32	start;

	i = 0;
	out = window->tex;
	while (i < window->size.x)
	{
		start = (-(t_i32)rays[i] / 2) + WIN_YCENTER;
		end = rays[i] / 2 + WIN_YCENTER;
		while (start < end)
			out[start++ * WIN_WIDTH] = ray_colors[i];
		out++;
		i++;
	}
}
