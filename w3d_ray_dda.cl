#include <mgen_map_conf.h>

static void
	ray_dda_perform
	(global char *map
	, global uint *outp
	, uint2 map_size
	, uint2 win_size
	, uint2 coords
	, int2 step
	, float2 position
	, float2 side_dist
	, float2 ray_dir
	, float2 delta)
{
	bool	side;
	uint2	wall_dist;

	while (map[coords.y * map_size.y + coords.x] != MAP_WALL)
	{
		if (side_dist.x < side_dist.y)
		{
			side_dist.x += delta.x;
			coords += step.x;
			side = false;
		}
		else
		{
			side_dist.y += delta.y;
			coords.y += step.y;
			side = true;
		}
	}
	wall_dist = (coords - position + (1 - step) / 2) / ray_dir;
	*outp = win_size.y / (side ? wall_dist.y : wall_dist.x);
}

kernel void
	w3d_ray_dda
	(global char *map
	, global uint *outp
	, uint2 map_size
	, uint2 win_size
	, float2 camera
	, float2 direction
	, float2 position)
{
	float2	camera_coord;
	float2	delta;
	float2	ray_dir;
	float2	ray_dir_2;
	float2	ray_dir_prod;
	float2	side_dist;
	int2	step;
	uint	id;
	uint2	coords;

	id = get_global_id(0);
	camera_coord = 2 * camera / id - 1;
	ray_dir = direction + camera * camera_coord;
	coords = convert_uint2(position);
	ray_dir_prod = ray_dir.x * ray_dir.y;
	ray_dir_2 = ray_dir * ray_dir;
	delta = sqrt(1 + ray_dir_prod / ray_dir_2);
	if (ray_dir.x < 0 && (step.x = -1))
		side_dist.x = (position.x - coords.x) * delta.x;
	else if ((step.x = 1))
		side_dist.x = (coords.x + 1 - position.x) * delta.x;
	if (ray_dir.y < 0 && (step.y = -1))
		side_dist.y = (position.y - coords.y) * delta.y;
	else if ((step.y = 1))
		side_dist.y = (coords.y + 1 - position.y) * delta.y;
	ray_dda_perform(map, outp, map_size, win_size, coords, step, position, side_dist, ray_dir, delta);
}
