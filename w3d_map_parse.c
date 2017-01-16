/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_map_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 16:38:47 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/16 17:39:58 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "w3d.h"
#include "libgnl/libgnl.h"

bool
	w3d_map_parse
	(t_i32 fd
	, t_map *map)
{
	t_vect	buf;

	vect_init(&buf);
	if (!(map->width = gnl_read_all(fd, &buf, GNL_CHECK_SIZE, &map->height)))
		return (false);
	map->map = buf.data;
	map->width = buf.used / map->height;
	return (true);
}
