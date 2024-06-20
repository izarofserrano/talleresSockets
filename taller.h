
#ifndef TALLER_H_
#define TALLER_H_

typedef struct{
	int id_taller;
	char nombre_taller[30];
	char dir_taller[30];
	char ciudad[30];
	int tlf_taller;
}Taller;

Taller pedirTaller();
void imprimirTaller(Taller ta);
void imprimirCabeceraTaller(int id);
#endif /* TALLER_H_ */
