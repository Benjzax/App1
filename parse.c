#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"

struct order* leer_csv(const char *filename, int *num_orders) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("No se pudo abrir el archivo CSV");
        return NULL;
    }

    // Se asume que no hay líneas vacías ni encabezados extraños
    // Leemos la primera línea (cabecera) y la descartamos
    char buffer[1024];
    if (!fgets(buffer, sizeof(buffer), fp)) {
        fclose(fp);
        return NULL;
    }

    // Reservamos memoria dinámica para las órdenes.
    // Si no conoces cuántas líneas hay, podrías hacer una primera pasada
    // para contarlas o ir aumentando con realloc. Aquí usaremos un ejemplo simple.
    int capacidad = 1000; // supongamos hasta 1000 filas
    struct order *orders = (struct order*) malloc(sizeof(struct order) * capacidad);
    if (!orders) {
        fclose(fp);
        return NULL;
    }

    int index = 0;
    while (fgets(buffer, sizeof(buffer), fp)) {
        // Ajusta los separadores según el CSV real
        // Ejemplo: pizza_id,order_id,pizza_name_id,quantity,order_date,order_time,unit_price,total_price,pizza_size,pizza_category,pizza_ingredients,pizza_name
        // Usamos strtok para dividir
        char *token = strtok(buffer, ",");
        if (!token) continue;
        orders[index].pizza_id = atof(token);

        token = strtok(NULL, ",");
        if (!token) continue;
        orders[index].order_id = atof(token);

        token = strtok(NULL, ",");
        if (!token) continue;
        strncpy(orders[index].pizza_name_id, token, 49);
        orders[index].pizza_name_id[49] = '\0';

        token = strtok(NULL, ",");
        if (!token) continue;
        orders[index].quantity = atof(token);

        token = strtok(NULL, ",");
        if (!token) continue;
        strncpy(orders[index].order_date, token, 29);
        orders[index].order_date[29] = '\0';

        token = strtok(NULL, ",");
        if (!token) continue;
        strncpy(orders[index].order_time, token, 29);
        orders[index].order_time[29] = '\0';

        token = strtok(NULL, ",");
        if (!token) continue;
        orders[index].unit_price = atof(token);

        token = strtok(NULL, ",");
        if (!token) continue;
        orders[index].total_price = atof(token);

        token = strtok(NULL, ",");
        if (!token) continue;
        strncpy(orders[index].pizza_size, token, 4);
        orders[index].pizza_size[4] = '\0';

        token = strtok(NULL, ",");
        if (!token) continue;
        strncpy(orders[index].pizza_category, token, 49);
        orders[index].pizza_category[49] = '\0';

        token = strtok(NULL, ",");
        if (!token) continue;
        strncpy(orders[index].pizza_ingredients, token, 199);
        orders[index].pizza_ingredients[199] = '\0';

        // Lo que reste suele ser el nombre completo de la pizza, incluyendo comillas
        token = strtok(NULL, "\n");
        if (!token) continue;
        strncpy(orders[index].pizza_name, token, 99);
        orders[index].pizza_name[99] = '\0';

        index++;

        if (index >= capacidad) {
            // Podríamos usar realloc, pero para simplicidad, detenemos.
            printf("Se alcanzó la capacidad máxima de %d órdenes.\n", capacidad);
            break;
        }
    }
    fclose(fp);

    *num_orders = index;
    return orders;
}
