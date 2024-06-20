
#ifndef REGISTRO_H_
#define REGISTRO_H_

typedef struct{
	int id_registro;
	int id_cliente;
	int id_trabajo;
	char fecha_hora[20];
}Registro;

Registro pedirRegistro(int id_trabajo, int id_cliente);
void imprimirRegistro (Registro reg);

#endif /* REGISTRO_H_ */
