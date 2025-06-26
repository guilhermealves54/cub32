/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:15:20 by ruida-si          #+#    #+#             */
/*   Updated: 2025/06/26 17:47:11 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	apply_dda(t_ray *ray, t_cub *cub, int map_x, int map_y);
static void	compute_wall_hit(t_cub *cub, t_ray *ray);
static void	init_ray(t_ray *ray, t_player *player, int map_x, int map_y);
double		deg_to_rad(double degree);

void	raycast(t_cub *cub)
{
	t_ray	ray;
	double	deg_step;
	int		map_x;
	int		map_y;

	ray.x = 0;
	map_x = (int)cub->player.pos_x;
	map_y = (int)cub->player.pos_y;
	deg_step = FOV / (WIDTH - 1);
	while (ray.x < WIDTH)
	{
		ray.angle = (cub->player.angle + (FOV / 2)) - (ray.x * deg_step);
		ray.raydir_x = cos(deg_to_rad(ray.angle));
		ray.raydir_y = sin(deg_to_rad(ray.angle));
		ray.dist_x = fabs(1 / ray.raydir_x);
		ray.dist_y = fabs(1 / ray.raydir_y);
		apply_dda(&ray, cub, map_x, map_y);
		ray.x++;
	}
}

static void	apply_dda(t_ray *ray, t_cub *cub, int map_x, int map_y)
{
	init_ray(ray, &cub->player, map_x, map_y);
	while (1)
	{
		if (ray->f_dist_x < ray->f_dist_y)
		{
			ray->f_dist_x += ray->dist_x;
			map_x += ray->step_x;
			ray->side = X;
		}
		else
		{
			ray->f_dist_y += ray->dist_y;
			map_y += ray->step_y;
			ray->side = Y;
		}
		if (cub->map.map[map_y][map_x] == '1')
			break ;
	}
	if (ray->side == X)
		ray->wall_dist = ray->f_dist_x - ray->dist_x;
	else
		ray->wall_dist = ray->f_dist_y - ray->dist_y;
	compute_wall_hit(cub, ray);
	ft_draw_image(ray, cub, &cub->player);
}

static void	compute_wall_hit(t_cub *cub, t_ray *ray)
{
	double	wall_hit;

	if (ray->side == Y)
	{
		wall_hit = cub->player.pos_x + ray->wall_dist * ray->raydir_x;
		ray->wall_x = wall_hit - floor(wall_hit);
	}
	else
	{
		wall_hit = cub->player.pos_y + ray->wall_dist * ray->raydir_y;
		ray->wall_x = wall_hit - floor(wall_hit);
	}
	if ((ray->side == X && ray->raydir_x > 0) || (ray->side == Y && ray->raydir_y < 0))
		ray->wall_x = 1.0 - ray->wall_x;
}

static void	init_ray(t_ray *ray, t_player *player, int map_x, int map_y)
{
	if (ray->raydir_x < 0)
	{
		ray->step_x = -1;
		ray->f_dist_x = (player->pos_x - map_x) * ray->dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->f_dist_x = (map_x + 1.0 - player->pos_x) * ray->dist_x;
	}
	if (ray->raydir_y < 0)
	{
		ray->step_y = 1;
		ray->f_dist_y = (map_y + 1.0 - player->pos_y) * ray->dist_y;
	}
	else
	{
		ray->step_y = -1;
		ray->f_dist_y = (player->pos_y - map_y) * ray->dist_y;
	}
}

double	deg_to_rad(double degree)
{
	double	rad;

	rad = degree * (M_PI / 180);
	return (rad);
}
