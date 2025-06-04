/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raperez- <raperez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 14:35:02 by raperez-          #+#    #+#             */
/*   Updated: 2025/06/05 01:02:58 by raperez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	degrees_to_radians(double degrees)
{
	return (degrees * M_PI / 180.0);
}

//Convierte el angulo en grados a un vector
t_point	angle_to_vector(double angle_rads)
{
	t_point	p;

	p.x = cos(angle_rads);
	p.y = sin(angle_rads);
	return (p);
}

//A partir del angulo, calcula las delta_dist (distancia que se recorre para
//cruzar una casilla horizontal o verticalmente)
void	set_delta_dist(t_ray *ray)
{
	double	cosAngle;
	double	senAngle;

	cosAngle = cos(ray->angle_radians);
	if (cosAngle == 0)
		ray->delta_dist.x = 1e30;
	else
		ray->delta_dist.x = 1 / cos(ray->angle_radians);
	senAngle = sin(ray->angle_radians);
	if (senAngle == 0)
		ray->delta_dist.y = 1e30;
	else
		ray->delta_dist.y = 1 / sin(ray->angle_radians);
}

void	init_ray(t_game *game, t_ray *ray)
{
	ray->angle_radians = degrees_to_radians(game->player.angle);
	ray->vector = angle_to_vector(ray->angle_radians);	//Calculo el vector direccion
	ray->start_point.x = game->player.x;
	ray->start_point.y = game->player.y;
	ray->pos.x = game->player.x;
	ray->pos.y = game->player.y;
	ray->hit_dir = none;
	set_delta_dist(ray);
}

//Lanza un rayo desde la posición inicial (xO, yO) con el angulo (angle)
//Retorna la distancia que recorrió el rayo
t_ray	launch_ray(t_game *game)
{
	t_ray	ray;
	
	init_ray(game, &ray);

	while (!ray.hit_dir)
	{
		if (ray.vector.x > 0)
			ray.axis_dist.x = 1 - (ray.pos.x - (int)ray.pos.x);
		else
			ray.axis_dist.x = ray.pos.x - (int)ray.pos.x;
		if (ray.vector.y > 0)
			ray.axis_dist.y = 1 - (ray.pos.y - (int)ray.pos.y);
		else
			ray.axis_dist.y = ray.pos.y - (int)ray.pos.y;
		
		//Mover el rayo
		double distX = fabs(ray.delta_dist.x * ray.axis_dist.x);
		double distY = fabs(ray.delta_dist.y * ray.axis_dist.y);
		
		//y - y0 = m(x - x0) | m = tan(angle)
		if (ray.vector.x == 0)
			ray.pos.y = (int)ray.pos.y + 1;
		else if(ray.vector.y == 0)
			ray.pos.x = (int)ray.pos.x + 1;
		else if (distX < distY)
		{
			ray.pos.x = (int)ray.pos.x + 1;
			ray.pos.y = tan(ray.angle_radians) * (ray.pos.x - ray.start_point.x)
				+ ray.start_point.y;
		}
		else
		{
			ray.pos.y = (int)ray.pos.y + 1;
			ray.pos.x = (ray.pos.y - ray.start_point.y)/tan(ray.angle_radians)
				+ ray.start_point.x;
		}
		
		if (game->scene.map2d[(int)ray.pos.y][(int)ray.pos.x] == '1')
		{
			if (distX < distY)
			{
				if (ray.vector.x > 0)
					ray.hit_dir = left;
				else
					ray.hit_dir = right;
			}
			else
			{
				if (ray.vector.y > 0)
					ray.hit_dir = up;
				else
					ray.hit_dir = down;
			}
			ray.hit_point.x = ray.pos.x;
			ray.hit_point.y = ray.pos.y;
		}
	}
	return (ray);
}

/*
int	main(void)
{
	t_game	game;
	t_ray	ray;
	double	distX;
	double	distY;
	double	dist;

	game.player.angle = 45;
	game.player.x = 1;
	game.player.y = 1;
	game.scene.map2d = ft_split("11111 10001 10001 10001 11111", ' ');
 	ray = launch_ray(&game);
	distX = ray.start_point.x - ray.hit_point.x;
	distY = ray.start_point.y - ray.hit_point.y;
	dist = sqrt(distX * distX + distY * distY);
	printf("Distancia: %f\n", dist);
	return (0);
}*/