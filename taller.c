#include "taller.h"
#include "baseDatos.h"
#include <stdio.h>

Taller pedirTaller(){
	Taller ta;

	printf("Nombre: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%s",ta.nombre_taller);

	printf("Direccion: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%s",ta.dir_taller);

	printf("Ciudad: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%s",ta.ciudad);

	printf("Telefono: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%d",&ta.tlf_taller);

	return ta;

}
void imprimirTaller(Taller ta){

	printf("%10d%30s%30s%30s%10d\n",ta.id_taller,ta.nombre_taller,ta.dir_taller,ta.ciudad,ta.tlf_taller);
	fflush(stdout);
}

void imprimirCabeceraTaller(int id){
	printf("TALLER %s\n", devolverTaller(id));
	printf("------------------------------\n");
	fflush(stdout);

}

