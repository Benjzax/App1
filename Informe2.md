# Informe de Diseño – Tarea 1: Pizzería en C

## Objetivo General

Esta tarea tiene como propósito desarrollar un programa en lenguaje C que permita procesar un archivo CSV con pedidos de pizzas y calcular distintas métricas a partir de dichos datos.  
El enfoque adoptado fue modular y organizado, siguiendo principios de buenas prácticas en C, como el uso de estructuras (`struct`), punteros a funciones, separación en archivos fuente y un manejo adecuado de la memoria dinámica.

## Estructura del Proyecto

```
App1/
├── main.c
├── parse.c
├── parse.h
├── metrics.c
├── metrics.h
├── Makefile
└── README.md
```

- **main.c**: Programa principal. Lee los argumentos, carga el archivo CSV y ejecuta las métricas.
- **parse.c / parse.h**: Módulos responsables de la lectura del CSV y definición de la estructura de datos (`struct order`).
- **metrics.c / metrics.h**: Implementación y declaración de las funciones de métricas.
- **Makefile**: Facilita la compilación y limpieza del proyecto.
- **README.md**: Documento de explicación y justificación de la solución.

## Diagrama de Flujo del Programa

```
Inicio
  |
  v
¿Se pasaron argumentos por consola? (CSV + métricas)
  |
  |-- No --> Mostrar mensaje de error y salir
  |
  |-- Sí
  v
Leer archivo CSV → parse.c → leer_csv()
  |
  v
Cargar datos en arreglo de estructuras (order[])
  |
  v
Iterar sobre métricas solicitadas
  |
  v
Encontrar métrica → Invocar con puntero a función
  |
  v
Mostrar resultado en consola
  |
  v
Liberar memoria → Finalizar
```

## Estructuras de Datos Utilizadas

La estructura central utilizada en el proyecto es:

```c
struct order {
    float pizza_id;
    float order_id;
    char pizza_name_id[50];
    float quantity;
    char order_date[30];
    char order_time[30];
    float unit_price;
    float total_price;
    char pizza_size[5];
    char pizza_category[50];
    char pizza_ingredients[200];
    char pizza_name[100];
};
```

Los datos se almacenan en un arreglo dinámico de estructuras `order`, lo cual permite realizar búsquedas, recorridos y agrupamientos de manera eficiente.

## Lectura del CSV

La función `leer_csv()` contenida en `parse.c` realiza los siguientes pasos:

1. Abre el archivo mediante `fopen()`.
2. Omite la primera línea (cabecera).
3. Lee cada línea con `fgets()`.
4. Utiliza `strtok()` para dividir cada campo por comas.
5. Guarda cada línea en una estructura `order`.
6. Devuelve un arreglo dinámico de estructuras `order`.


## Métricas Implementadas

Cada métrica se implementa como una función en `metrics.c` con la misma firma:

```c
char* metrica_nombre(int size, struct order *orders);
```

Esto permite su uso mediante punteros a funciones, facilitando su ejecución desde `main.c`.

Métricas disponibles:

| Código  Descripción                                   
| pms     Pizza más vendida (por cantidad)               
| pls     Pizza menos vendida                            
| dms     Fecha con más ventas (en dinero)               
| dls     Fecha con menos ventas (en dinero)             
| dmsp    Día con más pizzas vendidas                    
| dlsp    Día con menos pizzas vendidas                  
| apo     Promedio de pizzas por orden                   
| apd     Promedio de pizzas por día                     
| ims     Ingrediente más vendido                        
| hp      Total de pizzas por categoría                  

Cada función retorna una cadena con el resultado, que es muestra posteriormente.

## Modularidad y Uso de Punteros a Funciones

El proyecto emplea un `typedef` para definir el tipo de las funciones de métricas:

```c
typedef char* (*metric_func)(int size, struct order *orders);
```

Se declara un arreglo de punteros a funciones y otro de nombres de métricas. Esto permite invocar las métricas de forma dinámica comparando cadenas ingresadas por el usuario en tiempo de ejecución.

## Interacción entre Archivos

- `main.c` llama a `leer_csv()` desde `parse.c` para obtener los pedidos.
- Luego, recorre los nombres de las métricas solicitadas y usa los punteros a función definidos en `metrics.c`.
- Las funciones de `metrics.c` devuelven cadenas con los resultados.
- `parse.h` y `metrics.h` contienen las declaraciones necesarias para la interacción entre los módulos.

## Recursos Externos Utilizados

1. Documentación oficial del lenguaje C (manejo de archivos, punteros, memoria).
2. Sitios de referencia como Stack Overflow.
3. ChatGPT, como herramienta de consulta sobre temas puntuales del lenguaje C y estructuras de código.
4. GCC como compilador, y Visual Studio Code como entorno de desarrollo.

## Reflexiones Finales y Autoevaluación

### Complejidades y Desafíos

Uno de los desafíos más relevantes fue el manejo de punteros a funciones, ya que no es un recurso común en muchos lenguajes modernos. También fue desafiante trabajar con cadenas y campos que contenían separadores, como los ingredientes.

### Estrategias de Prueba y Corrección

Durante la etapa de desarrollo se utilizaron archivos de prueba pequeños y mensajes de depuración (`printf()`) para validar el contenido de las estructuras y los resultados parciales.

### Lecciones Aprendidas

El proyecto permitió consolidar conocimientos clave sobre:
- Manipulación de archivos y texto plano en C.
- Modularización efectiva en proyectos reales.
- Uso seguro de memoria dinámica.
- Aplicación de punteros a funciones para mejorar la escalabilidad.

## Compilación y Ejecución

Para compilar el proyecto, utilizar el comando:

```bash
make
```

Para ejecutar el programa con un archivo de datos y métricas específicas:

```bash
./app1 pizzas_orders.csv pms pls dms
```

Para limpiar archivos generados por la compilación:

```bash
make clean
```
## Explicación de utilización de IA

En cuanto al uso de IA's, utilizamos ChatGPT en multiples ocaciones, primero que todo para aprender a programar en C,
para aprender como se relacionan los distintos archivos entre si, tambien generamos un randomizador detos para crear
el csv completo, de 500 filas. Tambien generamos el archivo Makefile, el cual desconociamos. Y uso general para generar 
una estructura de codigo que funcione exitosamente entre sí.


## Integrantes del Grupo

- Nombre Integrante 1 – Cristóbal Meza Palacios crmeza@alumnos.uai.cl
- Nombre Integrante 2 – Vasco Vasquez Ramirez vasvasquez@alumnos.uai.cl
- Nombre Integrante 3 – Daniela Cuminao Embry dcuminao@alumnos.uai.cl
- Nombre Integrante 4 – Benjamin Garcia Muñoz benjamigarcia@alumnos.uai.cl