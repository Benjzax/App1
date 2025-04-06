#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "metrics.h"

/*
 * Cada función retorna un string dinámico
 * que luego es impreso y liberado en main.
 *
 * Se muestran ejemplos simples, deberás
 * completarlas adecuadamente.
 */

// 1. pms: Pizza más vendida (en cantidad total)
char* metrica_pms(int size, struct order *orders) {
    // Usaremos un mapa de <pizza_name> -> suma de quantity
    // Aquí, de forma sencilla, usaremos arreglos paralelos para no complicar:
    char nombres[1000][100];
    float acumulados[1000];
    int contador = 0;

    for (int i = 0; i < size; i++) {
        // Buscar si ya existe la pizza
        int found = -1;
        for (int j = 0; j < contador; j++) {
            if (strcmp(nombres[j], orders[i].pizza_name) == 0) {
                found = j;
                break;
            }
        }
        if (found == -1) {
            // nueva entrada
            strncpy(nombres[contador], orders[i].pizza_name, 99);
            nombres[contador][99] = '\0';
            acumulados[contador] = orders[i].quantity;
            contador++;
        } else {
            acumulados[found] += orders[i].quantity;
        }
    }

    // Encontrar la de mayor cantidad
    float max_val = acumulados[0];
    int idx_max = 0;
    for (int j = 1; j < contador; j++) {
        if (acumulados[j] > max_val) {
            max_val = acumulados[j];
            idx_max = j;
        }
    }

    // Construir el string de salida
    char *resultado = (char *)malloc(300 * sizeof(char));
    snprintf(resultado, 300, "Pizza más vendida: %s (Cantidad vendida: %.2f)",
             nombres[idx_max], max_val);

    return resultado;
}

// 2. pls: Pizza menos vendida
char* metrica_pls(int size, struct order *orders) {
    // Similar lógica a pms
    char nombres[1000][100];
    float acumulados[1000];
    int contador = 0;

    for (int i = 0; i < size; i++) {
        int found = -1;
        for (int j = 0; j < contador; j++) {
            if (strcmp(nombres[j], orders[i].pizza_name) == 0) {
                found = j;
                break;
            }
        }
        if (found == -1) {
            strncpy(nombres[contador], orders[i].pizza_name, 99);
            nombres[contador][99] = '\0';
            acumulados[contador] = orders[i].quantity;
            contador++;
        } else {
            acumulados[found] += orders[i].quantity;
        }
    }

    float min_val = acumulados[0];
    int idx_min = 0;
    for (int j = 1; j < contador; j++) {
        if (acumulados[j] < min_val) {
            min_val = acumulados[j];
            idx_min = j;
        }
    }

    char *resultado = (char *)malloc(300 * sizeof(char));
    snprintf(resultado, 300, "Pizza menos vendida: %s (Cantidad vendida: %.2f)",
             nombres[idx_min], min_val);

    return resultado;
}

// 3. dms: Fecha con más ventas en términos de dinero
char* metrica_dms(int size, struct order *orders) {
    // <date> -> sum of total_price
    char fechas[1000][30];
    float sumas[1000];
    int contador = 0;

    for (int i = 0; i < size; i++) {
        int found = -1;
        for (int j = 0; j < contador; j++) {
            if (strcmp(fechas[j], orders[i].order_date) == 0) {
                found = j;
                break;
            }
        }
        if (found == -1) {
            strncpy(fechas[contador], orders[i].order_date, 29);
            fechas[contador][29] = '\0';
            sumas[contador] = orders[i].total_price;
            contador++;
        } else {
            sumas[found] += orders[i].total_price;
        }
    }

    float max_val = sumas[0];
    int idx_max = 0;
    for (int j = 1; j < contador; j++) {
        if (sumas[j] > max_val) {
            max_val = sumas[j];
            idx_max = j;
        }
    }

    char *resultado = (char *)malloc(200 * sizeof(char));
    snprintf(resultado, 200, "Fecha con más ventas (dinero): %s (Total: %.2f)",
             fechas[idx_max], max_val);

    return resultado;
}

// 4. dls: Fecha con menos ventas en términos de dinero
char* metrica_dls(int size, struct order *orders) {
    // Similar a dms
    char fechas[1000][30];
    float sumas[1000];
    int contador = 0;

    for (int i = 0; i < size; i++) {
        int found = -1;
        for (int j = 0; j < contador; j++) {
            if (strcmp(fechas[j], orders[i].order_date) == 0) {
                found = j;
                break;
            }
        }
        if (found == -1) {
            strncpy(fechas[contador], orders[i].order_date, 29);
            fechas[contador][29] = '\0';
            sumas[contador] = orders[i].total_price;
            contador++;
        } else {
            sumas[found] += orders[i].total_price;
        }
    }

    float min_val = sumas[0];
    int idx_min = 0;
    for (int j = 1; j < contador; j++) {
        if (sumas[j] < min_val) {
            min_val = sumas[j];
            idx_min = j;
        }
    }

    char *resultado = (char *)malloc(200 * sizeof(char));
    snprintf(resultado, 200, "Fecha con menos ventas (dinero): %s (Total: %.2f)",
             fechas[idx_min], min_val);

    return resultado;
}

// 5. dmsp: Fecha con más ventas (cantidad de pizzas)
char* metrica_dmsp(int size, struct order *orders) {
    // <date> -> sum of quantity
    char fechas[1000][30];
    float sumas[1000];
    int contador = 0;

    for (int i = 0; i < size; i++) {
        int found = -1;
        for (int j = 0; j < contador; j++) {
            if (strcmp(fechas[j], orders[i].order_date) == 0) {
                found = j;
                break;
            }
        }
        if (found == -1) {
            strncpy(fechas[contador], orders[i].order_date, 29);
            fechas[contador][29] = '\0';
            sumas[contador] = orders[i].quantity;
            contador++;
        } else {
            sumas[found] += orders[i].quantity;
        }
    }

    float max_val = sumas[0];
    int idx_max = 0;
    for (int j = 1; j < contador; j++) {
        if (sumas[j] > max_val) {
            max_val = sumas[j];
            idx_max = j;
        }
    }

    char *resultado = (char *)malloc(200 * sizeof(char));
    snprintf(resultado, 200, "Fecha con más ventas (pizzas): %s (Total: %.2f)",
             fechas[idx_max], max_val);

    return resultado;
}

// 6. dlsp: Fecha con menos ventas (cantidad de pizzas)
char* metrica_dlsp(int size, struct order *orders) {
    char fechas[1000][30];
    float sumas[1000];
    int contador = 0;

    for (int i = 0; i < size; i++) {
        int found = -1;
        for (int j = 0; j < contador; j++) {
            if (strcmp(fechas[j], orders[i].order_date) == 0) {
                found = j;
                break;
            }
        }
        if (found == -1) {
            strncpy(fechas[contador], orders[i].order_date, 29);
            fechas[contador][29] = '\0';
            sumas[contador] = orders[i].quantity;
            contador++;
        } else {
            sumas[found] += orders[i].quantity;
        }
    }

    float min_val = sumas[0];
    int idx_min = 0;
    for (int j = 1; j < contador; j++) {
        if (sumas[j] < min_val) {
            min_val = sumas[j];
            idx_min = j;
        }
    }

    char *resultado = (char *)malloc(200 * sizeof(char));
    snprintf(resultado, 200, "Fecha con menos ventas (pizzas): %s (Total: %.2f)",
             fechas[idx_min], min_val);

    return resultado;
}

// 7. apo: Promedio de pizzas por orden
char* metrica_apo(int size, struct order *orders) {
    // Se asume que "order_id" identifica a una orden
    // Calculamos total de pizzas / total de órdenes únicas
    // (muy simplificado)

    float total_pizzas = 0.0f;
    // Para contar órdenes únicas, podemos usar un arreglo de IDs o un método similar
    float ordenes_unicas[1000];
    int count_ordenes = 0;

    for (int i = 0; i < size; i++) {
        total_pizzas += orders[i].quantity;

        // Ver si esta orden ya existe
        int found = 0;
        for (int j = 0; j < count_ordenes; j++) {
            if (ordenes_unicas[j] == orders[i].order_id) {
                found = 1;
                break;
            }
        }
        if (!found) {
            ordenes_unicas[count_ordenes] = orders[i].order_id;
            count_ordenes++;
        }
    }

    float promedio = 0.0f;
    if (count_ordenes > 0) {
        promedio = total_pizzas / count_ordenes;
    }

    char *resultado = (char *)malloc(200 * sizeof(char));
    snprintf(resultado, 200, "Promedio de pizzas por orden: %.2f", promedio);

    return resultado;
}

// 8. apd: Promedio de pizzas por día
char* metrica_apd(int size, struct order *orders) {
    // <date> -> sum quantity
    char fechas[1000][30];
    float sumas[1000];
    int contador = 0;

    for (int i = 0; i < size; i++) {
        int found = -1;
        for (int j = 0; j < contador; j++) {
            if (strcmp(fechas[j], orders[i].order_date) == 0) {
                found = j;
                break;
            }
        }
        if (found == -1) {
            strncpy(fechas[contador], orders[i].order_date, 29);
            fechas[contador][29] = '\0';
            sumas[contador] = orders[i].quantity;
            contador++;
        } else {
            sumas[found] += orders[i].quantity;
        }
    }

    float total_pizzas = 0.0f;
    for (int i = 0; i < contador; i++) {
        total_pizzas += sumas[i];
    }

    // Promedio total de pizzas / número de días
    float promedio = 0.0f;
    if (contador > 0) {
        promedio = total_pizzas / contador;
    }

    char *resultado = (char *)malloc(200 * sizeof(char));
    snprintf(resultado, 200, "Promedio de pizzas por día: %.2f", promedio);

    return resultado;
}

// 9. ims: Ingrediente más vendido
char* metrica_ims(int size, struct order *orders) {
    // Proceso simplificado: cada 'order' tiene pizza_ingredients con formato "IngredienteA, IngredienteB, ..."
    // Sumar la 'quantity' de cada ingrediente.
    // Nota: en un caso real, habría que partir la cadena de ingredientes
    // y acumular en un map la cantidad total.

    char ingredientes[5000][100];
    float cantidades[5000];
    int contador = 0;

    for (int i = 0; i < size; i++) {
        // Separar los ingredientes
        char temp[300];
        strncpy(temp, orders[i].pizza_ingredients, 299);
        temp[299] = '\0';

        char *token = strtok(temp, ";,"); // asumiendo ; o , como separadores
        while (token != NULL) {
            // Quitar espacios en blanco iniciales/finales si es necesario
            while (*token == ' ') token++; // muy rudimentario

            // Buscar si ya existe
            int found = -1;
            for (int j = 0; j < contador; j++) {
                if (strcmp(ingredientes[j], token) == 0) {
                    found = j;
                    break;
                }
            }
            if (found == -1) {
                strncpy(ingredientes[contador], token, 99);
                ingredientes[contador][99] = '\0';
                cantidades[contador] = orders[i].quantity;
                contador++;
            } else {
                cantidades[found] += orders[i].quantity;
            }

            token = strtok(NULL, ";,");
        }
    }

    // Encontrar ingrediente con mayor cantidad acumulada
    float max_val = 0.0f;
    int idx_max = 0;
    for (int j = 0; j < contador; j++) {
        if (cantidades[j] > max_val) {
            max_val = cantidades[j];
            idx_max = j;
        }
    }

    char *resultado = (char *)malloc(300 * sizeof(char));
    snprintf(resultado, 300, "Ingrediente más vendido: %s (Cantidad asociada: %.2f)",
             ingredientes[idx_max], max_val);

    return resultado;
}

// 10. hp: Cantidad de pizzas por categoría vendidas
char* metrica_hp(int size, struct order *orders) {
    // <categoria> -> sum of quantity
    char categorias[1000][50];
    float sumas[1000];
    int contador = 0;

    for (int i = 0; i < size; i++) {
        int found = -1;
        for (int j = 0; j < contador; j++) {
            if (strcmp(categorias[j], orders[i].pizza_category) == 0) {
                found = j;
                break;
            }
        }
        if (found == -1) {
            strncpy(categorias[contador], orders[i].pizza_category, 49);
            categorias[contador][49] = '\0';
            sumas[contador] = orders[i].quantity;
            contador++;
        } else {
            sumas[found] += orders[i].quantity;
        }
    }

    // Construir un string con la cantidad de cada categoría
    // p.ej. "Classic: 30, Veggie: 12, etc."
    char *resultado = (char*) malloc(1000 * sizeof(char));
    strcpy(resultado, "Cantidad de pizzas por categoría:\n");

    char linea[100];
    for (int j = 0; j < contador; j++) {
        snprintf(linea, 100, "  %s: %.2f\n", categorias[j], sumas[j]);
        strcat(resultado, linea);
    }

    return resultado;
}
