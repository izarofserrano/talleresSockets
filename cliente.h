#ifndef CLIENTE_H_
#define CLIENTE_H_

typedef struct {
	int id_user;
	char nombre_cli[30];
	char apellido_cli[30];
	char dni_cli[10];
	char email_cli[40];
	int tlf_cli;
}Cliente;

Cliente pedirCliente();
char* pedirDNI();
void imprimirCliente(Cliente c);



#endif /* CLIENTE_H_ */
