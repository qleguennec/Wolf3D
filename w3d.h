/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 12:13:33 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/27 10:46:34 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef W3D_H
# define W3D_H

# define T_U32_V2
# define T_I32_V2
# define T_F32_V2

# include "libcl/libcl.h"
# include "libfmt/libfmt.h"
# include "libft/libft.h"
# include "libgnl/libgnl.h"
# include "mapgen/mgen_map_conf.h"
# include "w3d_warn.h"
# include <math.h>
# include <X.h>
# include <mach/mach_time.h>
# include <mlx.h>
# include <time.h>
// TODO remove
# include <unistd.h>
# include <stdio.h>

# define WIN_TITLE "Wolf3D"
# define WIN_MINH	600
# define WIN_MAXH	1300
# define WIN_RATIO	(16.0 / 9.0)

# define WIN_WIDTH		(window->size.x)
# define WIN_HEIGHT		(window->size.y)
# define WIN_XCENTER	(WIN_WIDTH / 2)
# define WIN_YCENTER	(WIN_HEIGHT / 2)
# define WIN_AREA		(WIN_WIDTH * WIN_HEIGHT)

# define MAP_WIDTH		(map->size.x)
# define MAP_HEIGHT		(map->size.y)
# define MAP_XCENTER	(MAP_WIDTH / 2)
# define MAP_YCENTER	(MAP_HEIGHT / 2)

# define MAP(a, b)	(map->map[b * map->size.x + a])
# define MAP2(v)	MAP((v).x, (v.y))

# define INIT_DIRECTION_X	-1
# define INIT_DIRECTION_Y	0
# define INIT_CAMERA_X		0
# define INIT_CAMERA_Y		0.66
# define INIT_PLAYER_MS		1.0
# define INIT_PLAYER_RS		0.5

# define CL_SRC_FILE	"w3d_ray_dda.cl"
# define CL_KRL			"w3d_ray_dda"
# define CL_BUILD_OPTS	"-I /Users/qle-guen/wp/w3d/mapgen"
# define CL_BUILD_LINE	CL_KRL ":" CL_BUILD_OPTS

typedef struct		s_map
{
	t_u8			*map;
	cl_uint2		size;
}					t_map;

typedef struct		s_window
{
	t_u32			*tex;
	void			*mlx;
	void			*win;
	int				*img;
	cl_uint2		size;
	bool			update : 1;
}					t_window;

typedef struct		s_player
{
	cl_double2		camera;
	cl_double2		direction;
	cl_double2		position;
	cl_double		mspeed;
	cl_double		rspeed;
}					t_player;

typedef struct		s_w3d_data
{
	t_map			map;
	t_player		player;
	t_window		window;
	t_cl_info		cl_info;
	t_cl_krl		cl_krl;
	cl_uint			*rays;
	cl_uint			*ray_colors;
}					t_w3d_data;

t_i32				w3d_loop(t_w3d_data *d);
void				w3d_exit(t_w3d_data *d);

/*
** ray
*/
void				w3d_ray_dda(t_w3d_data *d);

/*
** window
*/
void				w3d_window_draw(t_window *window, cl_uint *rays, cl_uint *ray_colors);
void				w3d_window_fps(t_window *window, t_u64 delta);

/*
** events
*/
t_i32				w3d_ev_keyboard(t_i32 key, t_w3d_data *d);
t_i32				w3d_ev_motion(int x, int y, t_w3d_data *d);

/*
** util
*/
t_u64				w3d_exec_time(void (*f) (t_w3d_data *), t_w3d_data *d);

#endif
