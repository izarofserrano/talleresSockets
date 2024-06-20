#ifndef TRABAJO_H_
#define TRABAJO_H_

typedef struct {
	int id_trabajo;
	int id_vehiculo;
	int id_emp;
	char fecha_tra[11];
	char descripcion_tra[50];

}Trabajo;

Trabajo pedirTrabajo(int id_emp, int id_v);
void imprimirTrabajo(Trabajo tra);



#endif /* TRABAJO_H_ */
