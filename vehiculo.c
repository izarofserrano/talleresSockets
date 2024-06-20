#include "vehiculo.h"
#include "baseDatos.h"
#include "menu.h"
#include <stdio.h>

Vehiculo pedirVehiculo(int id_cli, ListaColores lColores){
	Vehiculo v;
	char opc;
	int op;
	v.id_vehiculo=buscarIDMaxVehiculos()+1;
	v.id_cli =

	printf("Numero de seguro: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%s",v.numSeguro);

	printf("Anyo de fabricacion: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%d",&v.anyoFabricacion);

	printf("Matricula: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%s",v.matricula);

	printf("Marca: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%s",v.marca);

	printf("Modelo: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%s",v.modelo);

	opc=menuColores(lColores);
	op=opc-'0';

	v.id_color=op;

	return v;
}

char* pedirMatriculaVehiculo(){
	char* matricula = (char*)malloc(10 * sizeof(char));
	printf("Matricula: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%s",matricula);

	return matricula;
}


void imprimirVehiculo(Vehiculo v){
	printf("%10d%10d%20s%4d%10s%30s%30s%10d",v.id_vehiculo,v.id_cli,v.numSeguro,v.anyoFabricacion,v.matricula,v.marca,v.modelo,v.id_color);
	fflush(stdout);
}

