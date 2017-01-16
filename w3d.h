/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 12:13:33 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/16 17:44:44 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef W3D_H
# define W3D_H

# include "mapgen/mapgen.h"
# include "libfmt/libfmt.h"
# include "libft/libft.h"
# include "libmlx/mlx.h"
# include "w3d_warn.h"
# include <unistd.h>

# define WIN_TITLE "Wolf3D"
# define WIN_W		600
# define WIN_H		400

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
}					t_video;

typedef struct		s_w3d_data
{
	t_video			v;
	t_map			map;
}					t_w3d_data;

bool				w3d_map_parse(t_i32 fd, t_map *map);
int					w3d_ev_keyboard(t_i32 key, t_w3d_data *d);
int					w3d_loop(t_w3d_data *d);
void				w3d_exit(t_w3d_data *d);

#endif
