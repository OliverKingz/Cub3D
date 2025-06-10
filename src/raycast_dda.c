/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:00:54 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/10 16:02:25 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//A partir del angulo, calcula las delta_dist (distancia que se recorre para
//cruzar una casilla horizontal o verticalmente)
// cos alfa = cat contig / hipotenusa
// delta x = hipotenusa = cat contiguo / cos alfa = 1 / cos(alfa)
// sen alfa = cat opuesto / hipotensa
// delta y = hipotenusa = cat opuesto / sen alfa = 1 / sen(alfa)
void	get_delta(t_ray *ray)
{
	double	cosAngle;
	double	senAngle;

	cosAngle = cos(ray->angle_radians);
	if (cosAngle == 0)
		ray->delta_dist.x = 1e30;
	else
		ray->delta_dist.x = fabs(1 / cos(ray->angle_radians));
	senAngle = sin(ray->angle_radians);
	if (senAngle == 0)
		ray->delta_dist.y = 1e30;
	else
		ray->delta_dist.y = fabs(1 / sin(ray->angle_radians));
}

void	get_ray_to_axis_distance(t_ray *ray)
{
		// Chequear distancia del punto hasta eje x e y
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
		//Mover el rayo
		// Regla de tres:
		// 1 casilla x --> delta x
		// 0,8 casilla x --> ?
		// ? = (delta x * 0,8)/1
		ray->real_axis_dist.x = fabs(ray->delta_dist.x * ray->axis_dist.x);
		ray->real_axis_dist.y = fabs(ray->delta_dist.y * ray->axis_dist.y);
}

void	move_ray_to_next_axis(t_ray *ray)
{
	// Nos quedamos con el pequeño, que es el que intersecciona primero con el eje cualquiera
		
		/*
		Ecuacion de la recta | Punto pendiente
		y - y0 = m(x - x0) 
		y = variable a calcular
		y0 = posicion inicial y
		m = pendiente
		x = variable a calcular
		x0 = posicion inicial x

		Ecuacion de la pendiente
		m = tan(alpha) = sen(alpha)/cos(alpha)
		*/
	

		/* Ejemplo: dist x < dis y (interseccion con eje y)
			P (0.7 , 2.3)
			pos x = (int) pos.x + 1 = 0 + 1 = 1.0 (de 0.7 avanzamos a 1.0 en x)
			Ahora calculamos el avance de y usando punto pendiente
			y = m(x -x0) + y0 = tan(alpha) * (x - x0) + y0
		*/
	
		/* Ejemplo: dist y < dis x (interseccion con eje x)
			P (0.7 , 2.3)
			pos y = (int) pos.y + 1 = 0 + 1 = 1.0 (de 2.3 avanzamos a 3.0 en y)
			Ahora calculamos el avance de x usando punto pendiente
			x = (y -y0)/m +x0
		*/

		// Hacemos ajustes porque cos pueden valer 0, descarto esos casos
		if (ray->vector.x == 0) // nos movemos verticalmente, solo avanzo 1
			ray->end_pos.y = ray->end_pos.y + ray->axis_dist.y;
		else if(ray->vector.y == 0) // nos movemos horizontalmente, solo avanzo 1
			ray->end_pos.x = ray->end_pos.x + ray->axis_dist.x;
		else if (ray->real_axis_dist.x < ray->real_axis_dist.y) // intersecciona primero con el eje vertical y
		{
			ray->end_pos.x = ray->end_pos.x + ray->axis_dist.x;
			ray->end_pos.y = tan(ray->angle_radians) * (ray->end_pos.x - ray->start_pos.x)
				+ ray->start_pos.y;
		}
		else //intersecciona primero con el eje horizontal x
		{
			ray->end_pos.y = ray->end_pos.y + ray->axis_dist.y;
			ray->end_pos.x = (ray->end_pos.y - ray->start_pos.y)/tan(ray->angle_radians)
				+ ray->start_pos.x;
		}
		//printf("Interseccion P(%f, %f)\n", ray->pos.x, ray->pos.y);
}

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
	if (scene->map2d[y][x] == WALL)
	{
		if (ray->real_axis_dist.x < ray->real_axis_dist.y && ray->vector.x >= 0)
			ray->collision_dir = WEST;
		else if (ray->real_axis_dist.x < ray->real_axis_dist.y && ray->vector.x < 0)
			ray->collision_dir = EAST;
		else if (ray->real_axis_dist.x >= ray->real_axis_dist.y && ray->vector.y > 0)
			ray->collision_dir = NORTH;
		else
			ray->collision_dir = SOUTH;
	}
}
