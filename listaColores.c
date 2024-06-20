#include "listaColores.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void volcarFicheroAListaColores(ListaColores *colores, char *nomfich){
	FILE *pf;
	Color c;
	pf = fopen(nomfich,"r");
	if(pf!=(FILE*)NULL){
		while(fscanf(pf,"%i %s",&c.id_col,c.nombre_col) != EOF){
			colores->aColores[colores->numC] = c;
			colores->numC++;
		}
		fclose(pf);
	}
	logMessage("El fichero color ha sido volcado a listaColores correctamente.");

}

void volcarListaColoresAFichero(ListaColores colores, char *nomfich){
	FILE *pf;
	int i;
	pf = fopen(nomfich,"w");
	if(pf != (FILE*)NULL){
		fprintf(pf,"%d\n",colores.tam);
		for(i=0;i<colores.numC;i++){
			fprintf(pf,"%i %s\n",colores.aColores[i].id_col,colores.aColores[i].nombre_col);
		}
		fclose(pf);
	}
}
void visualizarListaColores(ListaColores colores){
	printf("Aqui tiene la lista de colores\n");
	int i;
	for(i=0;i<colores.numC;i++){
		imprimirColor(colores.aColores[i]);
	}
}
int buscarColor(ListaColores *colores, int id_col){
	int pos=0,enc=0;
	while(!enc && pos<colores->numC){
		if(id_col==colores->aColores[pos].id_col){
			enc = 1;
		}else{
			pos++;
		}
	}
	if(enc==1){
		return pos;
	}else{
		return -1;
	}
}
void eliminarColor(ListaColores *colores, int *numC, int id_col){
	int i;
	int pos=buscarColor(colores,id_col);
	for(i=pos;i<*numC-1;i++){
		colores->aColores[i] = colores->aColores[i+1];
	}
	(*numC)--;
}

Color * reservaMemoriaListaColores(int tam){
	Color * c;
	c = (Color*)malloc(tam*sizeof(Color));
	return c;
}
void liberaMemoriaListaColores(ListaColores *colores){
	free(colores->aColores);
}
void enviarListaColores(SOCKET comm_socket, char sendBuff[512], char recvBuff[512], ListaColores colores) {

    int i;

    // Enviar número de colores
    int numC = colores.numC;
    sprintf(sendBuff,"%d",colores.numC);
    send(comm_socket,sendBuff,strlen(sendBuff),0);


    // Enviar cada color
    for (i = 0; i < numC; i++) {
        // Enviar id_col
    	sprintf(sendBuff,"%d",colores.aColores[i].id_col);
    	send(comm_socket,sendBuff,strlen(sendBuff),0);
    	sprintf(sendBuff,"%s",colores.aColores[i].nombre_col);
    	send(comm_socket,sendBuff,strlen(sendBuff),0);
    }
}
