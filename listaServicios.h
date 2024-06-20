

#ifndef LISTASERVICIOS_H_
#define LISTASERVICIOS_H_

#include "servicios.h"

typedef struct{
	Servicio *aServicios;
	int numServ;
	int tamServ;

}ListaServicios;

void volcarFicheroAListaServicios(ListaServicios *lServ, char *nomfich);
void visualizarListaServicios(ListaServicios lServ);
Servicio * reservaMemoriaListaServicios(int tam);
void liberaMemoriaListaServicios(ListaServicios *lServ);
void aniadirServ(ListaServicios *lServ, Servicio serv);
char* devolverNombreServ(ListaServicios lServ,char id);
#endif /* LISTASERVICIOS_H_ */
