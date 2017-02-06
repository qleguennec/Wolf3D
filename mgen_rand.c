/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mgen_rand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 15:45:57 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/15 13:24:33 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mapgen.h"

#define MODULUS		2147483647
#define MULTIPLIER	48271

t_u32
	mgen_rand
	(t_u32 *seed
	, t_u32 min
	, t_u32 max)
{
	const static t_u32		q = MODULUS / MULTIPLIER;
	const static t_u32		r = MODULUS % MULTIPLIER;
	float					res;
	t_i32					t;

	t = MULTIPLIER * (*seed % q) - r * (*seed / q);
	*seed = t + ((t < 0) * MODULUS);
	res = ((float)*seed / MODULUS) * (max - min + 1);
	return ((t_u32)res + min);
}
