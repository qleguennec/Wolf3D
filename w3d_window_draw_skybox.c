/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_window_draw_skybox.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 09:00:35 by qle-guen          #+#    #+#             */
/*   Updated: 2017/02/06 08:38:22 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "w3d.h"

void
	w3d_window_draw_skybox
	(t_window *window
	, t_player *player)
{
	size_t	bytes;
	size_t	i;
	size_t	start;
	t_u32	*bg;
	t_u32	*tex;

	start = ((atan2(player->direction.x, player->direction.y) / M_PI)) * SKYBOX_WIDTH;
	i = 0;
	tex = window->tex;
	bg = window->skybox + start;
	bytes = MIN(WIN_WIDTH, SKYBOX_WIDTH - start);
	while (i < WIN_YCENTER)
	{
		ft_memcpy(tex, bg, bytes * 4);
		i++;
		bg += SKYBOX_WIDTH;
		tex += WIN_WIDTH;
	}
	if (bytes == WIN_WIDTH)
		return ;
	tex = window->tex + bytes;
	bytes = WIN_WIDTH - (SKYBOX_WIDTH - start);
	i = 0;
	bg = window->skybox;
	while (i < WIN_YCENTER)
	{
		ft_memcpy(tex, bg + i++ * SKYBOX_WIDTH, bytes * 4);
		tex += WIN_WIDTH;
	}
}
