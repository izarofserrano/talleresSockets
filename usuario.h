#ifndef USUARIO_H_
#define USUARIO_H_
#include <winsock2.h>


typedef struct{
	int id_user;
	char username[40];
	char contrasenya[40];
	int tipo_user;
}Usuario;

Usuario pedirUsuarioRegistro( );
Usuario pedirUsuarioIniciarSesion();
int contrasenyaCorrecta(char*contraCorrecta,char *contraIntro);

#endif /* USUARIO_H_ */
