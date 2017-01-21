/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_window_draw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 14:01:57 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/21 17:08:24 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "w3d.h"
// TODO remove
#include <assert.h>

// TODO lot of optimization possible
static void
	window_draw_ray
	(t_window *window
	, t_i32 ray
	, t_u32 x)
{
	t_i32_v2	line;
	t_u32		*out;

	line.x = -ray / 2 + WIN_YCENTER;
	if (line.x < 0)
		line.x = 0;
	line.y = ray / 2 + WIN_YCENTER;
	if (line.y > (t_i32)WIN_HEIGHT)
		line.y = WIN_HEIGHT;
	out = window->tex + x + (line.x * WIN_WIDTH);
	while (line.x < line.y)
	{
		*out = 0xFF;
		out += WIN_WIDTH;
		line.x++;
	}
}

void
	w3d_window_draw
	(t_window *window
	, t_i32 *rays)
{
	size_t	i;

	i = 0;
	while (i < window->size.x)
	{
		window_draw_ray(window, rays[i], i);
		i++;
	}
}
