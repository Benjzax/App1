#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"
#include "metrics.h"

// Prototipo de función para imprimir el resultado de una métrica
void imprimirResultado(char *resultado);

// Programa principal
int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Uso: %s <archivo.csv> <metrica1> [<metrica2> ...]\n", argv[0]);
        return 1;
    }

    // 1. Leer archivo CSV y cargar en memoria
    int num_orders = 0;
    struct order *orders = leer_csv(argv[1], &num_orders);
    if (orders == NULL) {
        fprintf(stderr, "Error leyendo el archivo CSV.\n");
        return 1;
    }

    // 2. Configurar las funciones de métricas en un arreglo
    metric_func funciones[] = {metrica_pms, metrica_pls, metrica_dms, metrica_dls,
                               metrica_dmsp, metrica_dlsp, metrica_apo, metrica_apd,
                               metrica_ims, metrica_hp};

    // Nombre de cada métrica (debe mantener el orden)
    const char *nombres_metricas[] = {"pms", "pls", "dms", "dls", "dmsp", "dlsp",
                                      "apo", "apd", "ims", "hp"};

    int total_metricas = 10;

    // 3. Procesar cada parámetro de métrica en orden
    for (int i = 2; i < argc; i++) {
        int encontrada = 0;
        for (int j = 0; j < total_metricas; j++) {
            if (strcmp(argv[i], nombres_metricas[j]) == 0) {
                // Llamamos a la función de la métrica correspondiente
                char *resultado = funciones[j](num_orders, orders);
                imprimirResultado(resultado);
                free(resultado); // se libera la memoria devuelta por la métrica
                encontrada = 1;
                break;
            }
        }
        if (!encontrada) {
            printf("Métrica '%s' no reconocida. Se omite.\n", argv[i]);
        }
    }

    // 4. Liberar memoria de las órdenes
    free(orders);
    return 0;
}

void imprimirResultado(char *resultado) {
    if (resultado != NULL) {
        printf("%s\n", resultado);
    } else {
        printf("No se obtuvo resultado para esta métrica.\n");
    }
}
