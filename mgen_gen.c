/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mgen_gen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 15:47:33 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/15 23:21:09 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mapgen.h"

#define WIDTH	(gen->width)
#define HEIGHT	(gen->height)

#define XRAND (RAND(0, WIDTH - (WIDTH / ROOM_MINW)))
#define YRAND (RAND(0, HEIGHT - (HEIGHT / ROOM_MINH)))
#define WRAND (RAND(WIDTH / ROOM_MAXW, WIDTH / ROOM_MINW))
#define HRAND (RAND(HEIGHT / ROOM_MAXH, HEIGHT / ROOM_MINH))

#define X V4X(*room)
#define Y V4Y(*room)
#define W V4W(*room)
#define H V4H(*room)

#define ARBRAND RAND(2, 256)

static bool
	gen_next_room
	(t_gen *gen
	, t_u32_v4 *room)
{
	t_u32		dx;
	t_u32		dy;
	t_u32		max;
	t_u32_v4	direction;

	dx = WRAND;
	dy = HRAND;
	direction.a = (X >= dx && Y + dy < HEIGHT) ? ARBRAND : 0;
	direction.b = (Y >= dy && X + dx < WIDTH) ? ARBRAND : 0;
	direction.c = (Y + dy < HEIGHT && X + W + dx < WIDTH) ? ARBRAND : 0;
	direction.d = (Y + H + dy < HEIGHT && X + dx < WIDTH) ? ARBRAND : 0;
	max = mgen_v4_max(direction);
	if (!max)
		return (false);
	if (max == 1)
		*room = V4(t_u32, X - dx, Y, dx, dy);
	else if (max == 2)
		*room = V4(t_u32, X, Y - dy, dx, dy);
	else if (max == 4)
		*room = V4(t_u32, X + W, Y, dx, dy);
	else if (max == 8)
		*room = V4(t_u32, X, Y + H, dx, dy);
	return (mgen_v4_is_free(gen->rooms, *room));
}

void
	mgen_gen
	(t_gen *gen)
{
	t_u32		attempts;
	t_u32_v4	room;
	t_vll_node	*n;

	room = V4(t_u32, XRAND, YRAND, WRAND, HRAND);
	n = VLL_ADD(gen->rooms, room);
	attempts = 0;
	while (attempts < MAP_AVG_DENSITY)
	{
		if (!gen_next_room(gen, &room) && ++attempts)
			MEMCPY(room, VLL_DATA(n));
		else
			n = VLL_ADD_BACK(gen->rooms, n, room);
	}
}
