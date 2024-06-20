
#ifndef INVENTARIO_H_
#define INVENTARIO_H_

typedef struct{
	int id_inventario;
	int id_taller;
	char material[30];
	int cant_inv;
}Inventario;

Inventario pedirInventario(int id_taller);
void imprimirInventario(Inventario inv);
#endif /* INVENTARIO_H_ */
