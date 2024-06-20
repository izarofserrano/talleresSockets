#include <stdio.h>
#include "baseDatos.h"
#include "registro.h"

Registro pedirRegistro(int id_trabajo, int id_cliente){
	Registro reg;
	reg.id_registro = buscarIDMaxRegistros()+1;
	reg.id_trabajo=id_trabajo;
	reg.id_cliente = id_cliente;

	printf("Fecha: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%s",reg.fecha_hora);


	return reg;
}
void imprimirRegistro (Registro reg){
	printf("%10d%10d%10d%s\n",reg.id_registro,reg.id_cliente,reg.id_trabajo,reg.fecha_hora);
	fflush(stdout);
}


