#include "usuario.h"

#ifndef EMPLEADO_H_
#define EMPLEADO_H_

typedef struct{
	int id_user;
	char nombre_emp[30];
	char cargo[30];

}Empleado;

Empleado pedirEmpleado();
void imprimirEmpleado(Empleado emp);

#endif /* EMPLEADO_H_ */
