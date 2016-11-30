/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_sdl_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 14:25:03 by qle-guen          #+#    #+#             */
/*   Updated: 2016/11/17 14:53:46 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "w3d.h"

void		w3d_sdl_init(t_video *v)
{
	SDL_Init(SDL_INIT_VIDEO);
	v->win = SDL_CreateWindow(WIN_TITLE
		, SDL_WINDOWPOS_UNDEFINED
		, SDL_WINDOWPOS_UNDEFINED
		, WIN_W
		, WIN_H
		, 0);
}
