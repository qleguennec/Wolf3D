/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 12:13:33 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/17 17:24:42 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef W3D_H
# define W3D_H

# define T_U32_V2
# define T_I32_V2
# define T_F32_V2

# include "X.h"
# include "libfmt/libfmt.h"
# include "libft/libft.h"
# include "libgnl/libgnl.h"
# include "mapgen/mgen_map_conf.h"
# include "w3d_warn.h"
# include <mlx.h>
# include <unistd.h>

# define WIN_TITLE "Wolf3D"
# define WIN_MINH	600
# define WIN_MAXH	1080

# define WIDTH		(video->width)
# define HEIGHT		(video->height)
# define WIDTH_2	(WIDTH / 2)
# define HEIGHT_2	(HEIGHT / 2)

# define MAP(a, b)	(map->map[b * map->width + a])
# define MAP2(v)	MAP((v).x, (v.y))

# define INIT_CV	V2(t_f32, 20, 0)
# define INIT_DV	V2(t_f32, 0, 60)

typedef struct		s_map
{
	t_u8			*map;
	size_t			width;
	size_t			height;
}					t_map;

typedef struct		s_video
{
	t_u32			*tex;
	void			*mlx;
	void			*win;
	void			*img;
	size_t			width;
	size_t			height;
}					t_video;

typedef struct		s_player
{
	t_f32_v2		pos;
	t_f32_v2		dv;
	t_f32_v2		cv;
}					t_player;

typedef struct		s_w3d_data
{
	t_map			map;
	t_player		player;
	t_video			video;
}					t_w3d_data;

t_i32				w3d_loop(t_w3d_data *d);
void				w3d_exit(t_w3d_data *d);
/*
** ray
*/
t_i32_v2			w3d_ray_dda(t_u32_v2 a, t_u32_v2 b, bool (*f)(t_u32_v2, void *), void *ctxt);
/*
** player
*/

/*
** events
*/
t_i32				w3d_ev_keyboard(t_i32 key, t_w3d_data *d);
t_i32				w3d_ev_motion(int x, int y, t_w3d_data *d);

#endif
