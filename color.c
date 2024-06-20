#include "color.h"
#include <stdio.h>
Color pedirColor(int id_col){
	Color c;

	c.id_col=id_col;

	printf("Nombre del Color: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%s",c.nombre_col);

	return c;
}
void imprimirColor(Color c){
	printf("%d. %s\n",c.id_col,c.nombre_col);
	fflush(stdout);
}



