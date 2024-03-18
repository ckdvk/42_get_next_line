Como otros compañeros, la solución que he elegido implica directamente hacer el bonus. Dado que nos piden en este ser capaces de gestionar varios `file descriptor's`, lo que haremos será tener una variable estática que contenga los restos de info leída y no devuelta en cada aplicación de `get_next_line` en esos file descriptors. Para ello, usamos la variable `remainder_reg[MAX_FD]`, donde `MAX_FD` será un valor que definimos en el header y que será suficientemente alto para que no haya problemas con los límites del sistema. Yo por ejemplo lo he puesto a 10000000, de modo que no tendré problemas. Es posible saber el máximo número de file `file descriptor's` posible usando `ulimit -n -H`. 

Los  pasos son los mencionados arriba:
1. Comprobamos que no hay errores.
2. Leemos hasta encontrar un salto de línea y metemos todo el contenido leído en `remainder_reg[fd]`. Esto se hace con `current_read`.
3. Cortamos el contenido de la lectura para meter la línea en `current_line`. Esto se hace con `get_line`.
4. Actualizamos el valor de `remainder_reg[fd]` para que solo se quede con lo que hay después del salto de línea en la lectura anterior. Esto se hace con `get_remainder`.
5. Devolvemos la línea.

## Explicaciones de cada una de las funciones principales:

#### `current_read` 

PROTOTIPO
---------------------
`char    *current_read(int fd, char *remainder);`
VARIABLES
--------------------
- `int fd`: el `file descriptor` del archivo a leer.
- `char *remainder`: que es la entrada del array `remainder_ref[fd]` correspondiente a `fd`.

SALIDA
--------------
`remainder`: con el valor actualizado tras encadenar todos los trozos de buffer hasta encontrar `\n` en uno de ellos.

FUNCIONAMIENTO
----------------------------------
Reservamos `BUFFER_SIZE` bytes de memoria para buffer y empezamos a leer hasta encontrar el caracter `\n` o terminar la lectura (si hay error de lectura devolveremos `NULL` para que este valor se almacene en `current_line` más tarde y que `get_next_line` acabe devolviendo `NULL`). Mientras la lectura vaya bien terminamos el buffer actual con el caracter `\0` y hacemos un `ft_strjoin` de la variable `remainder` de entrada y el buffer actual `buffer`. Nótese que esto reserva memoria suficiente para el nuevo valor de remainder.

Cuando salimos de la lectura liberamos la memoria reservada para `buffer` y devolvemos la nueva cadena `remainder`, ahora con todo el contenido leído hasta encontrar el salto de línea.


#### `get_line` 

PROTOTIPO
---------------------
`char    *get_line(char *remainder);`
VARIABLES
--------------------
- `char *remainder`: que es la entrada del array `remainder_ref[fd]` correspondiente a `fd`. En este punto, actualizada con la línea leída por `current_line`.

SALIDA
--------------
`line`: con el contenido de `remainder` antes del salto de línea, terminado además en `\n` y `\0`.

FUNCIONAMIENTO
----------------------------------
Si `remainder` no tiene contenido simplemente devolvemos `NULL`. En otro caso, leemos `remainder` caracter a caracter hasta encontrar el salto de línea (o el fin de la cadena). Así, calculamos el tamaño necesario para reservar para nuestra variable de salida `line`. Le guardamos (tanto como haga falta + 2) bytes, para meter el salto de línea y el carácter nulo al final. Acto seguido, volvemos a leer `remainder` desde el principio, ahora guardando el contenido en `line`. Terminamos añadiendo los caracteres antes mencionados y devolvemos `line`. Nótese que el caso en que el archivo acaba sin salto de línea en el último trozo de buffer está gestionado, de modo que line contendrá un salto de línea si el archivo acaba en salto de línea, y no lo contendrá en caso contrario.

#### `get_remainder` 

PROTOTIPO
---------------------
`char    *get_remainder(char *remainder);`
VARIABLES
--------------------
- `char *remainder`: que es la entrada del array `remainder_ref[fd]` correspondiente a `fd`. En este punto, actualizada con la línea leída por `current_line`, y aún sin recortar.

SALIDA
--------------
`new_remainder`: con el contenido de `remainder` después del salto de línea, terminado en `\0`.

FUNCIONAMIENTO
----------------------------------
Contamos cuántos caracteres hay hasta el salto de línea. El tamaño de `new_remainder` es la longitud de `remainder` menos esa cantidad. Si no hay nada tras el salto de línea, simplemente devolvemos `NULL`, liberando antes la memoria reservada para `remainder`. Si hay algo, reservamos el tamaño de `new_remainder` calculado antes más 1 (para el `\0`) y rellenamos `new_remainder` con el contenido de `remainder` tras el salto de línea. Antes de devolver `new_remainder`, liberamos el espacio reservado a `remainder` anteriormente. 

