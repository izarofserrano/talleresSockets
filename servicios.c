#include "servicios.h"
#include <stdio.h>

void imprimirServicio(Servicio serv){
	printf("%d. %s\n",serv.id_serv,serv.nom_serv);fflush(stdout);
}
