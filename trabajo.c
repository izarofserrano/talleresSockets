#include "trabajo.h"
#include "baseDatos.h"
#include <stdio.h>

//Trabajo (Id_trabajo, Id_vehiculo, Id_empleado, Fecha, Descripcion)

Trabajo pedirTrabajo(int id_emp, int id_v){
	Trabajo tra;

	tra.id_trabajo = buscarIDMaxTrabajos()+1;
	tra.id_emp=id_emp;
	tra.id_vehiculo = id_v;


	printf("Fecha: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%s",tra.fecha_tra);

	printf("Descripcion: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%s",tra.descripcion_tra);

	return tra;
}
void imprimirTrabajo(Trabajo tra){
	 printf("ID Trabajo: %d, ID Vehiculo: %d, ID Empleado: %d, Fecha: %s, Descripcion: %s\n", tra.id_trabajo, tra.id_vehiculo, tra.id_emp, tra.fecha_tra, tra.descripcion_tra);
	fflush(stdout);
}
