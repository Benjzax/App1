#ifndef PARSE_H
#define PARSE_H

// Estructura básica para almacenar un registro de venta
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

// Prototipo de la función para leer el CSV
struct order* leer_csv(const char *filename, int *num_orders);

#endif
