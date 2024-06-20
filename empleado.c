#include "empleado.h"
#include "baseDatos.h"
#include <stdio.h>

Empleado pedirEmpleado(int id_user){

	Empleado emp;
	emp.id_user = id_user;

	printf("Nombre: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%s",emp.nombre_emp);

	printf("Cargo: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%s",emp.cargo);

	return emp;

}
void imprimirEmpleado(Empleado emp){
	printf("%10d%30s%30s\n",emp.id_user,emp.nombre_emp,emp.cargo);
	fflush(stdout);
}
