/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 16:05:39 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/20 13:37:11 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "w3d.h"

void
	w3d_exit
	(t_w3d_data *d)
{
	mlx_destroy_window(d->window.mlx, d->window.win);
	exit(0);
}
