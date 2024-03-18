Un *file descriptor* es un número entero que identifica de manera única un archivo. 
En Linux, todo es un archivo, desde archivos de verdad a dispositivos de hardware. De esta manera, todos estos recursos se pueden manejar con el mismo conjunto de operaciones.
El sistema operativo asigna una tabla de file descriptors para cada proceso (pueden verse en `/proc/[pid]/fd/`, --donde `pid` significa process ID-- que contiene enlaces simbólicos a los archivos originales). Cuando un proceso quiere leer un archivo o escribir en él, lo abre y a dicho archivo se le asigna un file descriptor. **No son `inode's` (de index node), que son, en cambio, estructuras de datos describiendo un archivo o directorio de manera permanente.**
1. Al abrir un archivo, el sistema operativo busca el `inode` del archivo para obtener sus metradatos. Luego, proporciona un `file descriptor` para operaciones futuras.
2. Al leer o escribir usando el `file descriptor`, el sistema operativo consulta el `inode` para encontrar dónde leer o escribir en el disco.
3. Cuando hay diferentes procesos con el mismo archivo abierto (o el archivo tiene múltiples hard links), puede haber varios `file descriptor` apuntando al mismo `inode` (al mismo archivo). 
Los file descriptor estándar son 0, 1 y 2, donde:
- 0 . Es la *standard input* (`stdin`);
- 1 . Es la *standard output* (`stdout`);
- 2 . Es el *standard error* (`stderr`).
Al comenzar cualquier proceso, estos tres file descriptors se incluyen automáticamente a la tabla correspondiente a dicho proceso. Estos apuntan a /dev/tty/. Cuando escribimos cualquier cosa en el teclado, esta se lee de `stdin` y se guarda en /dev/tty, de donde se puede leer por medio de `stdout`. Cualquier error que aparece sale del mismo archivo por medio de `stderr`.  

El número máximo de `file descriptor's` en un sistema Linux puede obtenerse a través del comando `ulimit -n -H`.