/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_init_graphics.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 09:10:59 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/28 09:37:59 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "w3d.h"

void
	w3d_init_graphics
	(t_window *window)
{
	size_t	i;
	size_t	j;

	MALLOC_N(window->clear, WIN_AREA);
	i = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			window->clear[i * WIN_WIDTH + j] =
				(i < WIN_HEIGHT / 2) ? WIN_TOP_COLOR : WIN_BOT_COLOR;
			j++;
		}
		i++;
	}
}
