#include "listaServicios.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void volcarFicheroAListaServicios(ListaServicios *lServi, char *nomfich) {

	FILE *pf;
	Servicio serv;
	pf = fopen(nomfich,"r");
	if(pf!=(FILE*)NULL){
		while(fscanf(pf,"%i %s",&serv.id_serv,serv.nom_serv) != EOF){
			lServi->aServicios[lServi->numServ] = serv;
			lServi->numServ++;
		}
		fclose(pf);
	}
	logMessage("El fichero servicios ha sido volcado a listaServicios correctamente.");

}

void visualizarListaServicios(ListaServicios lServi){
	printf("Aqui tiene la lista de Servicios:\n");
	int i;
	for(i=0;i<lServi.numServ;i++){
		imprimirServicio(lServi.aServicios[i]);
	}
}

Servicio * reservaMemoriaListaServicios(int tam){
	Servicio * s;
	s = (Servicio*)malloc(tam*sizeof(Servicio));
	return s;


}
void liberaMemoriaListaServicios(ListaServicios *lServ){
	free(lServ->aServicios);

}

void aniadirServ(ListaServicios *lServ, Servicio serv){
	if(lServ->numServ < lServ->tamServ){
		lServ->aServicios[lServ->numServ] = serv;
		lServ->numServ++;
	}
	fflush(stdout);
}

char* devolverNombreServ(ListaServicios lServ,char id){
	char nombreServ[30];
	int id_int = id-'0';
	for (int i = 0; i < lServ.numServ; i++) {
		if (lServ.aServicios[i].id_serv == id_int) {
			if (nombreServ == NULL) {
				fprintf(stderr, "Error: No se pudo asignar memoria para el nombre del servicio.\n");
				exit(EXIT_FAILURE);
			}
			return (lServ.aServicios[i].nom_serv);
		}
	}
	return NULL;
}

