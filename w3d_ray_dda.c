/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_ray_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 10:48:57 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/17 12:37:02 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "w3d.h"

void
	w3d_ray_dda
	(t_u32_v2 a
	, t_u32_v2 b
	, bool (*f)(t_u32_v2, void *)
	, void *ctxt)
{
	t_i32_v2	e;
	t_i32_v2	s;
	t_u32_v2	d;

	if (a.y > b.x)
		return (w3d_ray_dda(b, a, f, ctxt));
	d = DD2(a, b);
	s = V2(t_i32, (a.x < b.x ? 1 : -1), (a.y < b.y ? 1 : - 1));
	e.x = (d.x > d.y ? d.x : -((t_i32)d.x)) / 2;
	while (NEQ2(a, b) && f(a, ctxt))
	{
		e.y = e.x;
		if (e.y > -((t_i32)d.x))
		{
			e.x -= d.y;
			a.x += s.x;
		}
		if (e.y < (t_i32)d.y)
		{
			e.x += d.x;
			a.y += s.y;
		}
	}
}
