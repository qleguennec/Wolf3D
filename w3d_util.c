/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 10:36:01 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/27 10:46:01 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "w3d.h"

/*
** w3d_exec_time
** returns time in nanosecs of the execution
** of the function provided in argument
*/

t_u64
	w3d_exec_time
	(void (*f) (t_w3d_data *)
	, t_w3d_data *d)
{
	t_u64	start;
	t_u64	end;

	start = mach_absolute_time();
	f(d);
	end = mach_absolute_time();
	return (end - start);
}
