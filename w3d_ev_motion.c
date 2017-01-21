/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_ev_motion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 12:49:42 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/21 15:54:05 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "w3d.h"

t_i32
	w3d_ev_motion
	(t_i32 x
	, t_i32 y
	, t_w3d_data *d)
{
	t_window	*window;

	(void)x;
	(void)y;
	window = &d->window;
	window->update = true;
	return (0);
}
