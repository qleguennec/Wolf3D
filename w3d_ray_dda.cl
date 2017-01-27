#include <mgen_map_conf.h>

static void
	ray_dda_perform
	(global char *map
	, global uint *rays
	, global uint *ray_colors
	, uint2 map_size
	, uint2 win_size
	, uint2 coords
	, int2 step
	, double2 position
	, double2 side_dist
	, double2 ray_dir
	, double2 delta)
{
	bool	side;

	while (map[coords.y * map_size.x + coords.x] != MAP_WALL)
	{
		if (side_dist.x < side_dist.y)
		{
			side_dist.x += delta.x;
			coords.x += step.x;
			side = false;
		}
		else
		{
			side_dist.y += delta.y;
			coords.y += step.y;
			side = true;
		}
	}
	*rays =  win_size.y / (side ?
		((coords.y - position.y + (1.0 - step.y) / 2.0) / ray_dir.y)
		: ((coords.x - position.x + (1.0 - step.x) / 2.0) / ray_dir.x));
	if (side)
		*ray_colors = step.y < 0 ? 0xFF : 0xFFFF;
	else
		*ray_colors = step.x < 0 ? 0xFF00 : 0xFFFF00;
}

kernel void
	w3d_ray_dda
	(global char *map
	, global int *rays
	, global int *ray_colors
	, uint2 map_size
	, uint2 win_size
	, double2 camera
	, double2 direction
	, double2 position)
{
	double	cameraX;
	double2	delta;
	double2	delta_pos;
	double2	ray_dir;
	double2	ray_dir_2;
	double2	side_dist;
	int2	step;
	size_t	id;
	uint2	coords;

	id = get_global_id(0);
	ray_dir.x = 2 * (double)id / win_size.x - 1;
	ray_dir.y = ray_dir.x;
	ray_dir *= camera;
	ray_dir += direction;
	coords = convert_uint2(position);
	delta_pos = (double2){position.x - coords.x, position.y - coords.y};
	ray_dir_2 = ray_dir * ray_dir;
	delta.x = sqrt(1.0 + ray_dir_2.y / ray_dir_2.x);
	delta.y = sqrt(1.0 + ray_dir_2.x / ray_dir_2.y);
	step = (int2){ray_dir.x >= 0 ? 1 : -1, ray_dir.y >= 0 ? 1 : -1};
	if (ray_dir.x < 0)
		side_dist.x = delta_pos.x * delta.x;
	else
		side_dist.x = (delta_pos.x + 1.0) * delta.x;
	if (ray_dir.y < 0)
		side_dist.y = delta_pos.y * delta.y;
	else
		side_dist.y = (delta_pos.y + 1.0) * delta.y;
	ray_dda_perform(map
		, rays + id
		, ray_colors + id
		, map_size
		, win_size
		, coords
		, step
		, position
		, side_dist
		, ray_dir
		, delta);
}
