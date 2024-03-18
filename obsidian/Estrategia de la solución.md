Dado el archivo (su `fd`), leeremos en lotes de tamaño `BUFFER_SIZE`,  que es una cantidad  configurable a la hora de compilar. Vamos a tener en cuenta que la función `read` que podemos utilizar se acuerda de por dónde se ha quedado en su lectura.

¿Cómo leeremos?
- Para empezar, si no hay nada más que leer o si ha ocurrido un error, devolvemos `NULL`.
- La función `get_next_line` leerá en el archivo con file descriptor `fd` en trozos de tamaño `BUFFER_SIZE` hasta encontrar `\n` o hasta que acabe el archivo (si solo tiene una línea).
- Guardaremos, en una variable `remainder`, lo que hay en el buffer después de encontrar un salto de línea, para agregarlo al comienzo de la siguiente si se usara de nuevo la función.
- En la variable `current_line`, que almacenará la línea a devolver, se concatenan *primero* el contenido de la variable `remainder` (al principio, esta variable tendrá una cadena vacía) y *luego* cada uno de los fragmentos de texto leídos hasta alcanzar el primer `\n` o `\0`. 
- Toda línea devuelta debe acabar con `\n`, A NO SER, que se haya llegado al final del archivo, no terminando este en `\n`.