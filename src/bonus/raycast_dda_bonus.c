/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_dda_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:00:54 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/16 16:04:09 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Calculates the delta distances for the DDA algorithm based on the rays
 *       angle. The delta distances represent the distance the rays must travel
 *       along the x or y axis to cross a grid cell boundary, which is essential
 *       for efficient raycasting in grid-based maps.
 *
 * @param ray Pointer to the ray structure containing the rays angle in radians
 *            and where the computed delta distances will be stored.
 *
 * The function computes the absolute values of 1/cos(angle) for the x direction
 * and 1/sin(angle) for the y direction. If the cosine or sine of the angle is
 * zero (to avoid division by zero), a large value (1e30) is assigned instead.
 */
void	get_delta(t_ray *ray)
{
	double	cos_angle;
	double	sen_angle;

	cos_angle = cos(ray->angle_rads);
	if (cos_angle == 0)
		ray->delta_dist.x = 1e30;
	else
		ray->delta_dist.x = fabs(1 / cos(ray->angle_rads));
	sen_angle = sin(ray->angle_rads);
	if (sen_angle == 0)
		ray->delta_dist.y = 1e30;
	else
		ray->delta_dist.y = fabs(1 / sin(ray->angle_rads));
}

/**
 * @brief Calculates the distance from the ray's position to the next x/y axis.
 *
 * For each axis, computes the distance to the next grid line based on the ray's
 * direction. Updates ray->axis_dist and ray->real_axis_dist accordingly.
 *
 * @param ray The current ray structure.
 */
void	get_ray_to_axis_distance(t_ray *ray)
{
	if (ray->vector.x > 0)
		ray->axis_dist.x = 1 - (ray->end_pos.x - (int)ray->end_pos.x);
	else if (ray->end_pos.x - (int)ray->end_pos.x == 0)
		ray->axis_dist.x = -1;
	else
		ray->axis_dist.x = -(ray->end_pos.x - (int)ray->end_pos.x);
	if (ray->vector.y > 0)
		ray->axis_dist.y = 1 - (ray->end_pos.y - (int)ray->end_pos.y);
	else if (ray->end_pos.y - (int)ray->end_pos.y == 0)
		ray->axis_dist.y = -1;
	else
		ray->axis_dist.y = -(ray->end_pos.y - (int)ray->end_pos.y);
	ray->real_axis_dist.x = fabs(ray->delta_dist.x * ray->axis_dist.x);
	ray->real_axis_dist.y = fabs(ray->delta_dist.y * ray->axis_dist.y);
}

/**
 * @brief Advances the ray to the next axis intersection in the DDA algorithm.
 *
 * This function updates the ray's end position to the next intersection point
 * with either a vertical or horizontal grid line, depending on which is closer.
 * It handles special cases where the ray is perfectly vertical or horizontal.
 * The calculation uses the point-slope form of a line and the ray's angle.
 *
 * @param ray Pointer to the t_ray structure containing the ray's state.
 *
 * @note
 * The function determines which axis (x or y) the ray will intersect next by
 * comparing the distances to the next vertical and horizontal grid lines.
 * - If the ray is vertical (vector.x == 0), only the y position is advanced.
 * - If the ray is horizontal (vector.y == 0), only the x position is advanced.
 * - Otherwise, if the next x-axis intersection is closer, the function advances
 *   the ray to the next vertical grid line, updating x and calculating y using
 *   the ray's angle and the point-slope equation.
 * - If the next y-axis intersection is closer, the function advances the ray to
 *   the next horizontal grid line, updating y and calculating x accordingly.
 */
void	move_ray_to_next_axis(t_ray *ray)
{
	if (ray->vector.x == 0)
		ray->end_pos.y = ray->end_pos.y + ray->axis_dist.y;
	else if (ray->vector.y == 0)
		ray->end_pos.x = ray->end_pos.x + ray->axis_dist.x;
	else if (ray->real_axis_dist.x < ray->real_axis_dist.y)
	{
		ray->end_pos.x = ray->end_pos.x + ray->axis_dist.x;
		ray->end_pos.y = tan(ray->angle_rads) * (ray->end_pos.x
				- ray->start_pos.x) + ray->start_pos.y;
	}
	else
	{
		ray->end_pos.y = ray->end_pos.y + ray->axis_dist.y;
		ray->end_pos.x = (ray->end_pos.y - ray->start_pos.y)
			/ tan(ray->angle_rads) + ray->start_pos.x;
	}
}

static void	classify_collision(t_ray *ray, t_scene *scene, int x, int y)
{
	if (ray->real_axis_dist.x < ray->real_axis_dist.y
		&& ray->vector.x >= 0)
		ray->collision_dir = WEST;
	else if (ray->real_axis_dist.x < ray->real_axis_dist.y
		&& ray->vector.x < 0)
		ray->collision_dir = EAST;
	else if (ray->real_axis_dist.x >= ray->real_axis_dist.y
		&& ray->vector.y > 0)
		ray->collision_dir = NORTH;
	else
		ray->collision_dir = SOUTH;
	if (scene->map2d[y][x] == WALL)
		ray->collition = WALL_COLL;
	else
		ray->collition = DOOR_COLL;
}

/**
 * @brief Checks if the ray has collided with a wall in the scene.
 *
 * This function checks the end position of the ray against the 2D map of the
 * scene to determine if it has hit a wall. It also sets the collision direction
 * based on the ray's vector and the relative distances to the next axis.
 *
 * @param ray Pointer to the t_ray structure containing the ray's state.
 * @param scene Pointer to the t_scene structure containing the map data.
 */
void	check_axis_is_wall_collision(t_ray *ray, t_scene *scene)
{
	int	x;
	int	y;

	x = (int)ray->end_pos.x;
	y = (int)ray->end_pos.y;
	if (ray->vector.x < 0 && ray->end_pos.x - (int)ray->end_pos.x == 0.0)
		x -= 1;
	if (ray->vector.y < 0 && ray->end_pos.y - (int)ray->end_pos.y == 0.0)
		y -= 1;
	if (y >= 0 && y < scene->height_map && x >= 0
		&& x < scene->width_map && ft_strchr("1D", scene->map2d[y][x]))
	{
		classify_collision(ray, scene, x, y);
	}
}
