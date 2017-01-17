/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_ray_send.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 16:36:08 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/17 17:19:07 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "w3d.h"

static bool
	ray_wall_hit
	(t_u32_v2 ray
	, t_map *map)
{
	return (MAP2(ray) != MAP_WALL);
}

void
	w3d_ray_send
	(t_w3d_data *d)
{
	t_player	*player;
	t_u32_v2	i;
	t_i32_v2	ray;
	t_u32_v2	vsum;

	player = &d->player;
	i = V2(t_u32, 0, 0);
	vsum = SUM2(t_u32, player->dv, player->pos);
	while (i.x != player->cv.x)
	{
		ray = w3d_ray_dda(V2(t_u32, player->pos.x, player->pos.y)
			, SUM2(t_u32, i, vsum)
			, (bool (*)(t_u32_v2, void *))&ray_wall_hit
			, &d->map);
		i.x++;
	}
}
