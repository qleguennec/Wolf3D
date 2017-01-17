/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_ray_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 10:48:57 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/17 17:06:34 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "w3d.h"
#include <stdio.h>

t_i32_v2
	w3d_ray_dda
	(t_u32_v2 a
	, t_u32_v2 b
	, bool (*f)(t_u32_v2, void *)
	, void *ctxt)
{
	t_i32_v2	e;
	t_i32_v2	i;
	t_i32_v2	s;
	t_u32_v2	d;

	d = DD2(a, b);
	s = V2(t_i32, (a.x < b.x ? 1 : -1), (a.y < b.y ? 1 : - 1));
	e.x = d.x > d.y ? d.x : -((t_i32)d.x);
	i = V2(t_i32, 0, 0);
	while (f(a, ctxt))
	{
		e.y = e.x;
		if (e.y > -((t_i32)d.x))
		{
			e.x -= d.y;
			a.x += s.x;
			i.x += s.x;
		}
		if (e.y < (t_i32)d.y)
		{
			e.x += d.x;
			a.y += s.y;
			i.y += s.y;
		}
	}
	return (i);
}
