# To do list

## Consejos supremos

- El player ponerlo siempre inicialmente en el centro, nunca en un borde o fuera del mapa. Ocurren bugs.
- Legend: ✅❌

## Fixed

- ✅ Mirar por qué el mapa no funciona -> Player tiene que estar dentro del mapa, no fuera
- ✅ Si te acercas mucho a pared, se distorsiona.
- ✅ FOV constante, da igual WIDTH y HEIGHT
- ✅ Mover diagonal va mas rapido, tiene que ir constante.

## Urgente

- El file acepta 6 elementos aunque este duplicados

- Check map logic
	- Si esta rodeado de 1
		- Leer de izq a derecha cada fila. Ignorar si es ' ', el primer char encontrado tiene que ser '1'. 
		- Leer de dcha a izq, arriba a abajo, abajo a arriba. Seguir misma idea. 

## Con calma

- Linea vertical. Arreglar rayo que da justo en una esquina.
- Linea horizontal. Se han intercambiado pixeles por alguna razon

## Opcional

- Arreglar el grid cuando hay espacios. No las pinta del todo bien

## Raul

- Cerrar el fd
