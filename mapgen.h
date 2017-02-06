/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapgen.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/30 18:54:23 by qle-guen          #+#    #+#             */
/*   Updated: 2017/02/06 09:47:02 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPGEN_H
# define MAPGEN_H

# define T_I32_V2
# define T_U32_V2
# define T_U32_V4

# include "libfmt/libfmt.h"
# include "libft/libft.h"
# include "libvll/libvll.h"
# include "mgen_map_conf.h"
# include <limits.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>

# define ROOM_MINH 5
# define ROOM_MAXH 6
# define ROOM_MINW 6
# define ROOM_MAXW 7

# define MAXSEED INT_MAX
# define MINSEED 1

# define MAP_MAXW INT_MAX
# define MAP_MINW (ROOM_MINW * ROOM_MAXW)

# define MAP_MAXH INT_MAX
# define MAP_MINH (ROOM_MINH * ROOM_MAXH)

# define MAP_AVG_DENSITY 10000

# define BRAND(b) mgen_rand(&gen->seed, (b).x, ((b).y - 1))
# define GENMAP(a, b) (map[b * gen->width + a])
# define GENMAP2(a) (GENMAP((a).x, (a).y))
# define RAND(min, max) mgen_rand(&gen->seed, (min), (max) - 1)

typedef struct	s_gen
{
	t_u32		seed;
	t_vll		*rooms;
	t_u32		width;
	t_u32		height;
}				t_gen;

bool			mgen_v4_is_free(t_vll *l, t_u32_v4 v4);
t_u32			mgen_rand(t_u32 *seed, t_u32 min, t_u32 max);
t_u32			mgen_v4_max(t_u32_v4 v4);
void			mgen_gen(t_gen *gen);
void			mgen_map_draw(t_gen *gen, t_u8 *map);
void			mgen_room_rand(t_gen *gen);

#endif
