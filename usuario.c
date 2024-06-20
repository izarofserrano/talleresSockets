#include "usuario.h"
#include "baseDatos.h"
#include "menu.h"
#include <stdio.h>
#include <string.h>
#include <winsock2.h>


Usuario pedirUsuarioRegistro(){
	Usuario u;
	char opc;
	int num;

	u.id_user = buscarIDMaxUsuarios()+1;

	printf("USERNAME: ");
	fflush(stdout);
	fflush(stdin);
	gets(u.username);

	printf("CONTRASENYA: ");
	fflush(stdout);
	fflush(stdin);
	gets(u.contrasenya);

	opc = menuRegistro();
	num = opc - '0';
	u.tipo_user= num;



	return u;


}

Usuario pedirUsuarioIniciarSesion(){
	Usuario u;


	printf("USERNAME: ");
	fflush(stdout);
	fflush(stdin);
	gets(u.username);

	printf("CONTRASENYA: ");
	fflush(stdout);
	fflush(stdin);
	gets(u.contrasenya);

	u.id_user = devolverIDusu(u.username,u.contrasenya);


	return u;


}
int contrasenyaCorrecta(char*contraCorrecta,char *contraIntro){
	int correcta=0;
	if(strcmp(contraCorrecta,contraIntro)==0){
		correcta=1;
	}
	return correcta;
}
