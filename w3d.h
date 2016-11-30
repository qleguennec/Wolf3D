/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 12:13:33 by qle-guen          #+#    #+#             */
/*   Updated: 2016/11/30 14:58:26 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef W3D_H
# define W3D_H

# define WIN_TITLE "Wolf3D"
# define WIN_W		600
# define WIN_H		400

# include <SDL.h>

typedef struct		s_video
{
	SDL_Window		*win;
}					t_video;

void				w3d_sdl_init(t_video *v);

#endif
