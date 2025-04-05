#ifndef METRICS_H
#define METRICS_H

#include "parse.h"

// Para punteros a funciones de métricas:
typedef char* (*metric_func)(int size, struct order *orders);

// Prototipos de las funciones de métricas
char* metrica_pms(int size, struct order *orders);
char* metrica_pls(int size, struct order *orders);
char* metrica_dms(int size, struct order *orders);
char* metrica_dls(int size, struct order *orders);
char* metrica_dmsp(int size, struct order *orders);
char* metrica_dlsp(int size, struct order *orders);
char* metrica_apo(int size, struct order *orders);
char* metrica_apd(int size, struct order *orders);
char* metrica_ims(int size, struct order *orders);
char* metrica_hp(int size, struct order *orders);

#endif
