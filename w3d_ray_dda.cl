#include <mgen_map_conf.h>
#define MAP(a, b) (map[b * map_size.x + a])
#define MAP2(a) (MAP((a).x, (a).y))

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

	while (MAP2(coords) != MAP_WALL)
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
		((coords.y - position.y + (1 - step.y) / 2) / ray_dir.y)
		: ((coords.x - position.x + (1 - step.x) / 2) / ray_dir.x));
	if (side)
		*ray_colors = step.y < 0 ? 0xFF : 0xFFFF;
	else
		*ray_colors = step.x < 0 ? 0x96227b : 0xbc1616;
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
	double	ray_dir_2;
	double2	delta;
	double2	delta_pos;
	double2	ray_dir;
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
	ray_dir_2 = (ray_dir.x * ray_dir.x) / (ray_dir.y * ray_dir.y);
	delta.x = sqrt(1.0 + 1.0 / ray_dir_2);
	delta.y = sqrt(1.0 + ray_dir_2);
	step = (int2){ray_dir.x >= 0 ? 1 : -1, ray_dir.y >= 0 ? 1 : -1};
	side_dist.x = delta.x * (ray_dir.x < 0
		? (position.x - coords.x) : (coords.x + 1.0 - position.x));
	side_dist.y = delta.y * (ray_dir.y < 0
		? (position.y - coords.y) : (coords.y + 1.0 - position.y));
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
