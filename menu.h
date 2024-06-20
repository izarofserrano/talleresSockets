#include "listaColores.h"
#include "listaServicios.h"

#ifndef MENU_H_
#define MENU_H_

//char menuCliente();
char menuPrincipal();
char menuRegistro();
char menuGuardarSalir();

//CLIENTE
char menuDecisionesCliente();
char menuVerHistorial();
char menuServicios();
char menuColor();
char menuServicios(ListaServicios lServi);

//EMPLEADO
char menuTaller();
char menuEmpleado();
char menuInventario();
char menuEstaRegistrado();
char menuColores(ListaColores lColores);

#endif /* MENU_H_ */
