#ifndef LISTACOLORES_H_
#define LISTACOLORES_H_

#include "color.h"
#include <stdlib.h>
#include <winsock2.h>

typedef struct{
	Color * aColores;
	int tam;
	int numC;
}ListaColores;

void volcarFicheroAListaColores(ListaColores *colores, char *nomfich);
void volcarListaColoresAFichero(ListaColores colores, char *nomfich);
void visualizarListaColores(ListaColores colores);
int buscarColor(ListaColores *colores, int id_col);
void eliminarColor(ListaColores *colores, int *numC, int id_col);
Color * reservaMemoriaListaColores(int tam);
void liberaMemoriaListaColores(ListaColores *colores);
void enviarListaColores(SOCKET comm_socket, char sendBuff[512], char recvBuff[512], ListaColores colores);
#endif /* LISTACOLORES_H_ */
