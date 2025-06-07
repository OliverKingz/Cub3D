# Teoría y Comentarios de raycast.c y move.c

## Definiciones importantes y glosario

- **FOV (Field of View):** Ángulo de visión del jugador, determina el rango de ángulos para los que se lanzan rayos (por ejemplo, 60º).
- **DDA (Digital Differential Analyzer):** Algoritmo para recorrer una cuadrícula de forma eficiente, saltando de celda en celda siguiendo una dirección determinada.
- **Fish-eye:** Distorsión visual que ocurre si no se corrige la distancia del rayo según el ángulo respecto al centro de la cámara; se corrige multiplicando la distancia por el coseno de la diferencia angular.
- **Raycasting:** Técnica para simular una cámara 3D lanzando rayos desde la posición del jugador, calculando intersecciones con el mapa.
- **delta_dist:** Distancia que el rayo debe recorrer para cruzar el siguiente eje de la cuadrícula, incrementando exactamente 1 unidad en x (para delta_x) o en y (para delta_y), según la dirección del rayo. Es decir, es la distancia real que el rayo avanza en su trayectoria para que su coordenada x o y aumente en 1 celda entera.

## 1. Sistema de coordenadas y ángulos

- El mapa es un array 2D donde:
  - El eje X crece de izquierda a derecha (columnas de menor a mayor).
  - El eje Y crece de arriba hacia abajo (filas de menor a mayor).
- Los ángulos se miden en sentido horario, siguiendo la convención de los videojuegos clásicos:
  - Este (E): 0º (X crece)
  - Sur (S): 90º (Y crece)
  - Oeste (O): 180º (X decrece)
  - Norte (N): 270º (Y decrece)
- Esta convención facilita el cálculo de movimiento y raycasting en el array, aunque difiere de la matemática tradicional (antihoraria).

## 2. Movimiento del jugador y trigonometría (move.c)

- El jugador puede moverse hacia adelante/atrás (W/S) y lateralmente (A/D), siempre respecto a su ángulo actual.
- **Movimiento adelante/atrás (W/S):**
  - Se calcula el desplazamiento usando el ángulo:
    - `new_pos.x += cos(angle_rad) * -dy * SPEED;`
    - `new_pos.y += sin(angle_rad) * -dy * SPEED;`
  - El signo negativo en `-dy` hace que W (dy = -1) avance y S (dy = 1) retroceda.
- **Movimiento lateral (A/D):**
  - Se usa el vector perpendicular al ángulo:
    - `new_pos.x += -sin(angle_rad) * dx * SPEED;`
    - `new_pos.y += cos(angle_rad) * dx * SPEED;`
  - Así, A (dx = -1) mueve a la izquierda y D (dx = 1) a la derecha.
- **Colisiones:**
  - Antes de actualizar la posición, se comprueba que la nueva celda no sea un muro (`WALL`).
  - El movimiento es suave y permite combinaciones (diagonales) gracias a la suma de ambos componentes.

## 3. Teoría de Raycasting y DDA

- El raycasting permite simular una "cámara 3D" lanzando rayos desde la posición del jugador en diferentes ángulos (uno por cada columna de la pantalla o minimapa).
- **Algoritmo DDA (Digital Differential Analyzer):**
  - Se utiliza para recorrer la cuadrícula del mapa de forma eficiente, saltando de celda en celda.
  - Para cada rayo:
    1. Se calcula cuánto debe avanzar en X o Y para cruzar la siguiente celda (ver `delta_dist`).
    2. Se determina cuál de las dos distancias (x o y) es menor para saber si el rayo cruza primero una línea vertical u horizontal.
    3. Se avanza el rayo a la siguiente celda usando ecuaciones de la recta (punto-pendiente):
       - Si cruza eje vertical (x):
         - Avanza en x, calcula y: `y = tan(α) * (x - x0) + y0`
       - Si cruza eje horizontal (y):
         - Avanza en y, calcula x: `x = (y - y0)/tan(α) + x0`
    4. Se repite el proceso hasta encontrar un muro.
- **Aplicaciones del raycasting:**
  - El resultado de cada rayo se usa para:
    - Pintar la línea del rayo en el minimapa (debug o visualización).
    - Calcular la distancia a la pared y, con ello, la altura de la pared a dibujar en la vista 3D (efecto de perspectiva).
  - En la función de dibujo principal (`draw_walls_and_rays`):
    - Se lanza un rayo por cada columna de la pantalla (o por cada ángulo del FOV).
    - Se pinta la pared correspondiente con una altura proporcional a la distancia del rayo (corrigiendo el efecto "fish-eye" si es necesario).

## 4. Detalles de implementación

### Conversión de ángulos y vectores

- `degrees_to_radians`: Convierte grados a radianes.
- `angle_to_vector`: Convierte un ángulo en radianes a un vector unitario (cos, sin).

### Cálculo de delta_dist

- A partir del ángulo, calcula las distancias (`delta_dist`) que el rayo debe recorrer para cruzar una casilla horizontal o verticalmente.
- Específicamente, `delta_x` es la distancia que el rayo debe recorrer para que su coordenada x aumente exactamente en 1 unidad (de x0 a x0+1), y `delta_y` es la distancia para que y aumente en 1 unidad (de y0 a y0+1).
- Fórmulas:
  - cos(α) = cateto contiguo / hipotenusa
  - delta_x = hipotenusa = cateto contiguo / cos(α) = 1 / cos(α)
  - sen(α) = cateto opuesto / hipotenusa
  - delta_y = hipotenusa = cateto opuesto / sen(α) = 1 / sen(α)
- Si el coseno o seno es 0 (rayo paralelo a un eje), se usa un valor muy grande (1e30) para evitar divisiones por cero y asegurar que el rayo nunca cruce esa dirección.
- Se usa `fabs` para asegurar que las distancias sean siempre positivas.

### Cálculo de axis_dist

- Calcula la distancia desde la posición actual del rayo hasta la siguiente línea de la cuadrícula en x o y.
- Si el rayo apunta en dirección positiva, se calcula la distancia hasta el siguiente entero mayor; si es negativa, hasta el anterior.
- Se usa para saber cuánto avanzar hasta la próxima intersección con una celda del mapa.

### Movimiento del rayo (move_ray)

- Se determina cuál de las dos distancias (x o y) es menor para saber si el rayo cruza primero una línea vertical u horizontal.
- Se usan ecuaciones de la recta (punto-pendiente) para calcular la nueva posición:
  - Si se cruza primero eje vertical (x):
    - Avanza en x, calcula y usando: y = tan(α) \* (x - x0) + y0
  - Si se cruza primero eje horizontal (y):
    - Avanza en y, calcula x usando: x = (y - y0)/tan(α) + x0
- Se hacen ajustes para evitar divisiones por cero (por ejemplo, si el rayo es perfectamente vertical u horizontal).
- El avance se realiza en pasos de celda a celda, no en incrementos pequeños.

### Detección de colisión (check_hit)

- Se determina si el rayo ha chocado con una pared ('1' en el mapa).
- Se ajustan los índices x/y si el rayo viene de dirección negativa y está justo en el borde de una celda (para evitar errores de redondeo).
- Se determina la dirección del impacto (NO, SO, EA, WE) según el vector y la distancia recorrida.
- Es importante controlar que los índices x/y estén dentro de los límites del mapa para evitar segmentation faults.

### Cálculo de la distancia del rayo

- `calculate_ray_size`: Calcula la distancia euclídea entre el punto de inicio y el punto de colisión.
- Se usa sqrt((x0-x1)^2 + (y0-y1)^2).

### Lógica general de lanzamiento de rayos

- `launch_ray`: Inicializa el rayo y lo avanza paso a paso hasta que choca con una pared, devolviendo la distancia recorrida.
- En cada paso:
  - Se calcula la distancia a los siguientes ejes.
  - Se mueve el rayo al siguiente cruce.
  - Se comprueba si ha chocado con una pared.
- El bucle termina cuando se detecta una colisión.

## 5. Consideraciones numéricas y robustez

- El uso de valores grandes como 1e30 y fabs ayuda a evitar problemas numéricos y divisiones por cero.
- Es importante comprobar los límites del mapa antes de acceder a `map2d[y][x]`.
- El raycasting es sensible a errores de redondeo, por lo que se recomienda usar double para las posiciones y distancias.
- Para evitar el efecto "fish-eye" en la proyección 3D, se puede corregir la distancia del rayo usando la diferencia angular respecto al ángulo central del jugador.

## 6. Fórmulas utilizadas y su aplicación

### Conversión de ángulos
- **De grados a radianes:**
  - Fórmula: `radianes = grados * π / 180`
  - Uso: Todas las funciones trigonométricas en C usan radianes, por lo que es necesario convertir los ángulos del jugador y los rayos.

### Vector unitario a partir de un ángulo
- **Coordenadas del vector dirección:**
  - Fórmulas:
    - `x = cos(α)`
    - `y = sin(α)`
  - Uso: Para obtener el vector de avance del jugador o del rayo según su ángulo.

### Cálculo de delta_dist (DDA step size)
- **Distancia para cruzar una celda en X o Y:**
  - Fórmulas oficiales:
    - `delta_x = |1 / cos(α)|`  (distancia para incrementar x en 1)
    - `delta_y = |1 / sin(α)|`  (distancia para incrementar y en 1)
  - Variante: Si cos(α) o sin(α) es 0, se usa un valor muy grande (1e30) para evitar divisiones por cero.
  - Uso: Determina cuánto debe avanzar el rayo para cruzar la siguiente línea de la cuadrícula en X o Y.

### Cálculo de axis_dist (DDA initial side distance)
- **Distancia desde la posición actual hasta el primer eje de la cuadrícula:**
  - Fórmulas:
    - Si el rayo va en dirección positiva:
      - `axis_dist.x = 1 - (pos.x - floor(pos.x))`
      - `axis_dist.y = 1 - (pos.y - floor(pos.y))`
    - Si el rayo va en dirección negativa:
      - `axis_dist.x = -(pos.x - floor(pos.x))`
      - `axis_dist.y = -(pos.y - floor(pos.y))`
  - Uso: Determina el primer salto parcial del rayo antes de entrar en el bucle DDA.

### Ecuación de la recta (punto-pendiente)
- **Para calcular la nueva coordenada tras cruzar un eje:**
  - Si se avanza en X:
    - `y = tan(α) * (x - x0) + y0`
  - Si se avanza en Y:
    - `x = (y - y0) / tan(α) + x0`
  - Uso: Permite calcular la posición exacta del rayo tras cruzar un eje de la cuadrícula.

### Distancia euclídea
- **Distancia entre dos puntos (Pitagoras):**
  - Fórmula: `dist = sqrt((x0 - x1)^2 + (y0 - y1)^2)`
  - Uso: Para calcular la distancia real recorrida por el rayo desde el jugador hasta la pared.

### Corrección del efecto fish-eye
- **Proyección sin distorsión:**
  - Fórmula: `distancia_corregida = distancia * cos(ángulo_rayo - ángulo_jugador)`
  - Uso: Corrige la distorsión de perspectiva al renderizar las paredes en la vista 3D.

### Altura de la pared en la proyección 3D
- **Cálculo de la altura de la pared:**
  - Fórmula: `wall_height = HEIGHT / distancia_corregida`
  - Uso: Determina cuántos píxeles de alto se debe dibujar la pared en la columna correspondiente.

### Movimiento del jugador
- **Avance en la dirección del ángulo:**
  - Fórmulas:
    - Adelante/atrás: `x += cos(α) * velocidad`, `y += sin(α) * velocidad`
    - Lateral: `x += -sin(α) * velocidad`, `y += cos(α) * velocidad`
  - Uso: Permite mover al jugador en la dirección que mira o de forma lateral (strafe).
