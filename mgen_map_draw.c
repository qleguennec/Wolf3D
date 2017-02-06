/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mgen_map_draw.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 23:05:07 by qle-guen          #+#    #+#             */
/*   Updated: 2017/02/06 09:05:38 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mapgen.h"

#define X V4X(*room)
#define Y V4Y(*room)
#define W V4W(*room)
#define H V4H(*room)

static void
	map_room_push
	(t_gen *gen
	, t_u8 *map
	, t_u32_v4 *room)
{
	t_u32_v2	rb;
	t_u32_v2	lu;

	rb = V4_V2(t_u32, *room, SUM2);
	lu = V2(t_u32, X, Y);
	while (NEQ2(lu, rb))
	{
		if (GENMAP2(lu) == MAP_NONE)
			GENMAP2(lu) = lu.x == X
				|| lu.y == Y
				|| lu.x == rb.x
				|| lu.y == rb.y
				? MAP_WALL : MAP_POINT;
		lu = SUM2(t_u32
			, lu
			, (lu.x == rb.x ? V2(t_i32, -W, 1) : V2(t_i32, 1, 0)));
	}
	if (GENMAP2(rb) == MAP_NONE)
		GENMAP2(rb) = MAP_WALL;
}

static void
	gen_exit
	(t_gen *gen
	, t_u8 *map
	, t_u32_v4 *prev
	, t_u32_v4 *room)
{
	if (Y == V4Y(*prev) && X < V4X(*prev))
		GENMAP(V4X(*prev)
			, RAND(Y + 1
			, MIN(Y + H, V4Y2(*prev)) - 1)) = MAP_DOOR;
	else if (X == V4X(*prev) && Y < V4Y2(*prev))
		GENMAP(RAND(X + 1
			, MIN(X + W, V4X2(*prev)) - 1)
			, V4Y(*prev)) = MAP_DOOR;
	else if (Y == V4Y(*prev) && X > V4X(*prev))
		GENMAP(X, RAND(Y + 1, MIN(Y + H, V4Y2(*prev)) - 1)) = MAP_DOOR;
	else if (X == V4X(*prev) && Y > V4Y(*prev))
		GENMAP(RAND(X + 1, MIN(X + W, V4X2(*prev)) - 1), Y) = MAP_DOOR;
}

void
	mgen_map_draw
	(t_gen *gen
	, t_u8 *map)
{
	t_u32_v4	*room;
	t_vll_node	*n;

	n = gen->rooms->head;
	room = VLL_DATA(n);
	GENMAP((X + 3), (Y + 3)) = MAP_SPAWN;
	while (n)
	{
		room = VLL_DATA(n);
		map_room_push(gen, map, room);
		n = n->next;
		if (n)
			gen_exit(gen, map, VLL_DATA(n), room);
	}
}
