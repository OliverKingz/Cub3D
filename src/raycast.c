/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 14:35:02 by raperez-          #+#    #+#             */
/*   Updated: 2025/06/06 18:35:26 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	degrees_to_radians(double degrees)
{
	return (degrees * PI / 180.0);
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
// cos alfa = cat contig / hipotenusa
// delta x = hipotenusa = cat contiguo / cos alfa = 1 / cos(alfa)
// sen alfa = cat opuesto / hipotensa
// delta y = hipotenusa = cat opuesto / sen alfa = 1 / sen(alfa)
void	set_delta_dist(t_ray *ray)
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

void	init_ray(t_game *game, t_ray *ray, double angle)
{
	ray->angle_radians = degrees_to_radians(angle);
	ray->vector = angle_to_vector(ray->angle_radians);	//Calculo el vector direccion
	ray->start_point.x = game->player.pos.x;
	ray->start_point.y = game->player.pos.y;
	ray->pos.x = game->player.pos.x;
	ray->pos.y = game->player.pos.y;
	ray->hit_dir = NONE;
	set_delta_dist(ray);
	if (ray->vector.x >= 0)
		ray->step.x = 1;
	else
		ray->step.x = -1;
	if (ray->vector.y >= 0)
		ray->step.y = 1;
	else
		ray->step.y = -1;
}

void	calculate_axis_dist(t_ray *ray)
{
		// Chequear distancia del punto hasta eje x e y
		if (ray->vector.x > 0)
			ray->axis_dist.x = 1 - (ray->pos.x - (int)ray->pos.x);
		else if (ray->pos.x - (int)ray->pos.x == 0)
			ray->axis_dist.x = -1;
		else
			ray->axis_dist.x = -(ray->pos.x - (int)ray->pos.x);
		if (ray->vector.y > 0)
			ray->axis_dist.y = 1 - (ray->pos.y - (int)ray->pos.y);
		else if (ray->pos.y - (int)ray->pos.y == 0)
			ray->axis_dist.y = -1;
		else
			ray->axis_dist.y = -(ray->pos.y - (int)ray->pos.y);
		//Mover el rayo
		// Regla de tres:
		// 1 casilla x --> delta x
		// 0,8 casilla x --> ?
		// ? = (delta x * 0,8)/1
		ray->real_axis_dist.x = fabs(ray->delta_dist.x * ray->axis_dist.x);
		ray->real_axis_dist.y = fabs(ray->delta_dist.y * ray->axis_dist.y);
}

void	move_ray(t_ray *ray)
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
			ray->pos.y = ray->pos.y + ray->axis_dist.y;
		else if(ray->vector.y == 0) // nos movemos horizontalmente, solo avanzo 1
			ray->pos.x = ray->pos.x + ray->axis_dist.x;
		else if (ray->real_axis_dist.x < ray->real_axis_dist.y) // intersecciona primero con el eje vertical y
		{
			ray->pos.x = ray->pos.x + ray->axis_dist.x;
			ray->pos.y = tan(ray->angle_radians) * (ray->pos.x - ray->start_point.x)
				+ ray->start_point.y;
		}
		else //intersecciona primero con el eje horizontal x
		{
			ray->pos.y = ray->pos.y + ray->axis_dist.y;
			ray->pos.x = (ray->pos.y - ray->start_point.y)/tan(ray->angle_radians)
				+ ray->start_point.x;
		}
		//printf("Interseccion P(%f, %f)\n", ray->pos.x, ray->pos.y);
}

void	check_hit(t_ray *ray, t_scene *scene)
{
	int	x;
	int	y;
	
	x = (int)ray->pos.x;
	y = (int)ray->pos.y;
	
	if (ray->vector.x < 0 && ray->pos.x - (int)ray->pos.x == 0.0)
		x -= 1;
	if (ray->vector.y < 0 && ray->pos.y - (int)ray->pos.y == 0.0)
		y -= 1;
	if (scene->map2d[y][x] == '1')
	{
		if (ray->real_axis_dist.x < ray->real_axis_dist.y && ray->vector.x >= 0)
			ray->hit_dir = WE;
		else if (ray->real_axis_dist.x < ray->real_axis_dist.y && ray->vector.x < 0)
			ray->hit_dir = EA;
		else if (ray->real_axis_dist.x >= ray->real_axis_dist.y && ray->vector.y > 0)
			ray->hit_dir = NO;
		else
			ray->hit_dir = SO;
	}
}

double	calculate_ray_size(t_ray ray)
{
	double	size_x;
	double	size_y;

	size_x = ray.start_point.x - ray.pos.x;
	size_y = ray.start_point.y - ray.pos.y;
	return (sqrt(size_x * size_x + size_y * size_y));
}

//Lanza un rayo desde la posición inicial (xO, yO) con el angulo (angle)
//Retorna la distancia que recorrió el rayo
t_ray	launch_ray(t_game *game, double angle)
{
	t_ray	ray;

	init_ray(game, &ray, angle);
	while (!ray.hit_dir)
	{
		calculate_axis_dist(&ray);
		move_ray(&ray);
		check_hit(&ray, &(game->scene));
	}
	ray.size = calculate_ray_size(ray);
	return (ray);
}

/*
int	main(void)
{
	t_game	game;
	t_ray	ray;

	game.player.pos.x = 4;
	game.player.pos.y = 4;
	game.scene.map2d = ft_split("11111 10001 10001 10001 11111", ' ');
 	ray = launch_ray(&game, 180 + 45);
	printf("Distancia: %f\n", ray.size);
	return (0);
}*/

/*
11111
10001
10001
10001
11111
*/