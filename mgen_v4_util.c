/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mgen_v4_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 23:05:51 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/15 19:19:59 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mapgen.h"

/*
** mgen_v4_is_free
** checks if square v4 is free for writing
** returns false if v4 intersects with somme vector in l
** returns true otherwise
*/

/*
** mgen_v4_max
** determines the maximum value of the vector
*/

bool
	mgen_v4_is_free
	(t_vll *l
	, t_u32_v4 a)
{
	t_u32_v4	b;
	t_vll_node	*n;

	n = l->head;
	while (n)
	{
		MEMCPY(b, VLL_DATA(n));
		if (V4X1(a) < V4X2(b)
			&& V4X2(a) > V4X1(b)
			&& V4Y1(a) < V4Y2(b)
			&& V4Y2(a) > V4Y1(b))
			return (false);
		n = n->next;
	}
	return (true);
}

t_u32
	mgen_v4_max
	(t_u32_v4 v4)
{
	if (v4.a > v4.b && v4.a > v4.c && v4.a > v4.d)
		return (1);
	if (v4.b > v4.a && v4.b > v4.c && v4.b > v4.d)
		return (2);
	if (v4.c > v4.a && v4.c > v4.b && v4.c > v4.d)
		return (4);
	if (v4.d > v4.a && v4.d > v4.b && v4.d > v4.c)
		return (8);
	return (0);
}
