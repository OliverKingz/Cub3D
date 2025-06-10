# Guía rápida: PNG, RGBA y Acceso a Píxeles en C

## ¿Cómo se almacena un PNG en memoria?

Cuando cargas una imagen PNG usando una librería como LodePNG (o MLX42), los datos de la imagen se decodifican a un array lineal de bytes, donde cada píxel ocupa 4 bytes en formato **RGBA**:

- **R**: Rojo (Red) – 1 byte (8 bits)
- **G**: Verde (Green) – 1 byte (8 bits)
- **B**: Azul (Blue) – 1 byte (8 bits)
- **A**: Alpha (Transparencia) – 1 byte (8 bits)

El array de píxeles se almacena en memoria así:

```
[R][G][B][A][R][G][B][A] ...
```

Cada fila de la imagen está seguida por la siguiente, sin relleno.

---

## Acceso a un píxel concreto

Supón que tienes:
- `unsigned char *pixels` (array de datos RGBA)
- `unsigned width, height` (dimensiones de la imagen)

Para acceder al píxel en la posición `(x, y)`:

```c
unsigned idx = (y * width + x) * 4;
unsigned char r = pixels[idx + 0];
unsigned char g = pixels[idx + 1];
unsigned char b = pixels[idx + 2];
unsigned char a = pixels[idx + 3];
```

---

## Empaquetar el color en un uint32_t

Para usar el color en funciones como `mlx_put_pixel`, puedes empaquetar los canales RGBA en un entero de 32 bits:

```c
uint32_t color = (r << 24) | (g << 16) | (b << 8) | a;
```

Algunas librerías pueden requerir otro orden (por ejemplo, ABGR).

---

## Ejemplo de uso con LodePNG

```c
#include "lodepng.h"

unsigned char *image = NULL;
unsigned width, height;
unsigned error = lodepng_decode32_file(&image, &width, &height, "ruta.png");
if (!error) {
    unsigned x = 10, y = 5;
    unsigned idx = (y * width + x) * 4;
    unsigned char r = image[idx + 0];
    unsigned char g = image[idx + 1];
    unsigned char b = image[idx + 2];
    unsigned char a = image[idx + 3];
    printf("Pixel (%u,%u): R=%u G=%u B=%u A=%u\n", x, y, r, g, b, a);
    free(image);
}
```

---

## ¿Por qué se usan desplazamientos de 8 bits?

Cada canal de color ocupa 1 byte (8 bits). Para empaquetar 4 canales en un entero de 32 bits, se desplaza el resultado 8 bits a la izquierda antes de añadir el siguiente canal:

```c
result = 0;
int i = 0;
while (i < 4)
{
    result <<= 8;
    result |= pixels[idx + i];
    i++;
}
```

---

## Resumen
- Un PNG decodificado a RGBA es un array de bytes: 4 bytes por píxel.
- El acceso a un píxel es directo usando el índice `(y * width + x) * 4`.
- Puedes empaquetar el color en un uint32_t para usarlo en gráficos.
- LodePNG y MLX42 trabajan con este formato por defecto.

---

## Ejemplo de código en C para acceder a un píxel de una textura PNG
Aquí tienes un ejemplo de main en C que carga una textura PNG usando LodePNG (`lodepng_decode32_file`), accede a un píxel concreto y muestra sus valores RGBA por consola. Puedes compilarlo y probarlo en tu entorno.

```c
#include <stdio.h>
#include <stdlib.h>
#include "lodepng/lodepng.h"

int main(int argc, char *argv[])
{
    if (argc != 4) {
        printf("Uso: %s <ruta_png> <x> <y>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    unsigned x = atoi(argv[2]);
    unsigned y = atoi(argv[3]);
    unsigned char *image = NULL;
    unsigned width, height;

    // Cargar la imagen PNG en RGBA 8 bits por canal
    unsigned error = lodepng_decode32_file(&image, &width, &height, filename);
    if (error) {
        printf("Error %u: %s\n", error, lodepng_error_text(error));
        return 1;
    }

    if (x >= width || y >= height) {
        printf("Coordenadas fuera de rango: la imagen es de %ux%u\n", width, height);
        free(image);
        return 1;
    }

    // Calcular el índice del píxel
    unsigned idx = (y * width + x) * 4;
    unsigned char r = image[idx + 0];
    unsigned char g = image[idx + 1];
    unsigned char b = image[idx + 2];
    unsigned char a = image[idx + 3];

    printf("Pixel en (%u, %u): R=%u G=%u B=%u A=%u\n", x, y, r, g, b, a);

    // Empaquetar en uint32_t (RGBA)
    unsigned int color = (r << 24) | (g << 16) | (b << 8) | a;
    printf("Color RGBA empaquetado: 0x%08X\n", color);

    free(image);
    return 0;
}
```

**Cómo usarlo:**
```sh
cc -o test_png_pixel test_png_pixel.c lodepng.c
./test_png_pixel assets/textures/basic_EA.png 10 5
```
(Reemplaza el path y las coordenadas por los que quieras probar.)

Esto te mostrará el valor RGBA del píxel (10,5) de la textura PNG.