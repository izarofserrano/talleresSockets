#include "listaColores.h"
#ifndef VEHICULO_H_
#define VEHICULO_H_

typedef struct{
	int id_vehiculo;
	int id_cli;
	char numSeguro[20];
	int anyoFabricacion;
	char matricula[10];
	char marca[30];
	char modelo[30];
	int id_color;
}Vehiculo;

Vehiculo pedirVehiculo(int id_cli, ListaColores lColores);
char* pedirMatriculaVehiculo();
void imprimirVehiculo(Vehiculo v);



#endif /* VEHICULO_H_ */
