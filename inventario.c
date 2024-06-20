#include "inventario.h"
#include "baseDatos.h"
#include <string.h>
#include <stdio.h>

//Inventario (Id_inventario, Id_taller, Material, Cantidad)

Inventario pedirInventario(int id_taller){
	Inventario inv;
	inv.id_inventario = buscarIDMaxInventario() + 1;
	inv.id_taller = id_taller;

	printf("Material: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%s",inv.material);

	printf("Cantidad: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%d",&inv.cant_inv);

	return inv;
}
void imprimirInventario(Inventario inv){
	printf("%10d%10d%30s%10d",inv.id_inventario,inv.id_taller,inv.material,inv.cant_inv);
	fflush(stdout);
}

