#include "cliente.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
Cliente pedirCliente(int id_user){
	Cliente c;
	c.id_user = id_user;

	printf("Nombre: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%s",c.nombre_cli);

	printf("Apellido: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%s",c.apellido_cli);

	printf("DNI: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%s",c.dni_cli);

	printf("Email: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%s",c.email_cli);

	printf("Telefono: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%d",&c.tlf_cli);

	return c;
}


void imprimirCliente(Cliente c){

	printf("ID Usuario: %d, Nombre: %s, Apellido: %s, DNI: %s, Email: %s, Teléfono: %d\n",c.id_user,c.nombre_cli,c.apellido_cli,c.dni_cli,c.email_cli,c.tlf_cli);
	fflush(stdout);
}

char* pedirDNI() {
    char dni_cli[10];
    printf("DNI: ");
    fflush(stdout);
    fflush(stdin);
    scanf("%9s", dni_cli);  // Asegúrate de limitar la entrada a 9 caracteres para evitar desbordamientos de búfer
    char* dni_copia = strdup(dni_cli);
    if (dni_copia == NULL) {
        fprintf(stderr, "Error: No se pudo asignar memoria.\n");
        exit(EXIT_FAILURE);
    }

    return dni_copia; // Devuelve la copia, no la dirección de la variable local
}

