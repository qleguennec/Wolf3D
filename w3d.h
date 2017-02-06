/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 12:13:33 by qle-guen          #+#    #+#             */
/*   Updated: 2017/02/06 10:23:13 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef W3D_H
# define W3D_H

# define T_F32_V2
# define T_F64_V2
# define T_I32_V2
# define T_U32_V2
# define T_U32_V4

# include "libcl/libcl.h"
# include "libfmt/libfmt.h"
# include "libft/libft.h"
# include "libgnl/libgnl.h"
# include "libqlex/mlx.h"
# include "libvll/libvll.h"
# include "mapgen.h"
# include "mgen_map_conf.h"
# include "w3d_warn.h"
# include <X.h>
# include <mach/mach_time.h>
# include <math.h>
# include <time.h>

# define WIN_TITLE "Wolf3D"
# define WIN_MINH	600
# define WIN_MAXH	1300
# define WIN_RATIO	(16.0 / 9.0)

# define WIN_WIDTH		(window->size.x)
# define WIN_HEIGHT		(window->size.y)
# define WIN_XCENTER	(WIN_WIDTH / 2)
# define WIN_YCENTER	(WIN_HEIGHT / 2)
# define WIN_AREA		(WIN_WIDTH * WIN_HEIGHT)

# define BG_COLOR		0x444044

# define MAP_WIDTH		80
# define MAP_HEIGHT		80
# define MAP_XCENTER	(MAP_WIDTH / 2)
# define MAP_YCENTER	(MAP_HEIGHT / 2)

# define COLLIDER_RADIUS	2
# define COLLIDER_FRACT		4.5

# define MAP(a, b)	(map[b * MAP_WIDTH + a])
# define MAP2(v)	MAP((v).x, (v).y)

# define INIT_DIRECTION_X	-1
# define INIT_DIRECTION_Y	0
# define INIT_CAMERA_X		0
# define INIT_CAMERA_Y		0.66
# define INIT_PLAYER_MS		0.25

# define CL_SRC_FILE	"w3d_ray_dda.cl"
# define CL_KRL			"w3d_ray_dda"
# define CL_BUILD_OPTS	""
# define CL_BUILD_LINE	CL_KRL ":" CL_BUILD_OPTS

# define SKYBOX_FILENAME	"res/skybox.ppm"
# define SKYBOX_WIDTH		4096
# define SKYBOX_HEIGHT		650

typedef struct		s_window
{
	void			*mlx;
	void			*win;
	void			*img;
	t_u32			*tex;
	t_u32			*bg;
	t_u32			*skybox;
	cl_uint2		size;
	bool			update : 1;
}					t_window;

typedef struct		s_player
{
	cl_double2		camera;
	cl_double2		direction;
	cl_double2		camera_fix;
	cl_double2		direction_fix;
	cl_double2		position;
	cl_double		mspeed;
}					t_player;

typedef struct		s_w3d_data
{
	t_u8			*map;
	t_player		player;
	t_window		window;
	t_cl_info		cl_info;
	t_cl_krl		cl_krl;
	cl_uint			*rays;
	cl_uint			*ray_colors;
}					t_w3d_data;

bool				w3d_init_skybox(t_window *window);
t_i32				w3d_loop(t_w3d_data *d);
void				w3d_exit(t_w3d_data *d);

/*
** ray
*/
void				w3d_ray_dda(t_w3d_data *d);

/*
** window
*/
void				w3d_window_draw
	(t_window *window, cl_uint *rays, cl_uint *ray_colors);
void				w3d_window_draw_skybox(t_window *window, t_player *player);
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

/*
** Cocoa
*/
void				w3d_move_mouse(int x, int y);

#endif
