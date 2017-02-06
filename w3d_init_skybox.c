/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_init_skybox.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 09:10:59 by qle-guen          #+#    #+#             */
/*   Updated: 2017/02/06 08:09:46 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "w3d.h"

static bool
	skybox_width_height
	(int fd
	, t_vect *buf
	, t_vect *line)
{
	size_t	width;
	size_t	height;
	char	*inp;

	get_next_line(fd, buf, line, GNL_STR);
	width = 0;
	inp = STRTOB10(line->data, width);
	if (width != SKYBOX_WIDTH)
		return (false);
	if (*inp != ' ')
		return (false);
	inp++;
	height = 0;
	STRTOB10(inp, height);
	if (height != SKYBOX_HEIGHT)
		return (false);
	line->used = 0;
	get_next_line(fd, buf, line, GNL_STR);
	width = 0;
	STRTOB10(line->data, width);
	return (width == 0xFF);
}

static bool
	skybox_read
	(int fd
	, t_u32 **skybox)
{
	char	*s;
	char	buf[3];
	size_t	i;

	MALLOC_N(*skybox, SKYBOX_WIDTH * SKYBOX_HEIGHT);
	s = (void *)*skybox;
	i = 0;
	while (i < SKYBOX_WIDTH * SKYBOX_HEIGHT)
	{
		if (read(fd, buf, 3) != 3)
			return (false);
		i++;
		*s++ = buf[2];
		*s++ = buf[1];
		*s++ = buf[0];
		*s++ = 0;
	}
	return (!read(fd, buf, 1));
}

bool
	w3d_init_skybox
	(t_window *window)
{
	int		fd;
	size_t	i;
	t_vect	buf;
	t_vect	line;

	MALLOC_N(window->bg, WIN_AREA / 2);
	i = 0;
	while (i < WIN_AREA / 2)
		window->bg[i++] = BG_COLOR;
	vect_init(&buf);
	vect_init(&line);
	if ((fd = open(SKYBOX_FILENAME, O_RDONLY)) < 0)
		return (false);
	get_next_line(fd, &buf, &line, 0);
	if (VSTRCMP(&line, (unsigned char *)"P6"))
		return (false);
	line.used = 0;
	if (!skybox_width_height(fd, &buf, &line))
		return (false);
	return (skybox_read(fd, &window->skybox));
}
