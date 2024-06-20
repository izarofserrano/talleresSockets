#include "menu.h"
#include "baseDatos.h"
#include <stdio.h>

char menuPrincipal(){
	char opcion;
	printf("TALLERES\n");
	printf("--------\n");
	printf("1. Iniciar Sesion\n");
	printf("2. Registrarse\n");
	printf("0. Salir\n");
	printf("Elige una opcion: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%c",&opcion);
	return opcion;
}

char menuRegistro(){
	char opcion;
	printf("Tipo de usuario: \n");
	printf("1. Cliente\n");
	printf("2. Empleado\n");
	printf("Elige una opcion: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%c",&opcion);
	return opcion;
}
char menuGuardarSalir(){
	char opcion;
	printf("1. Guardar\n");
	printf("2. Salir\n");
	printf("Elige una opcion: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%c",&opcion);
	return opcion;
}


//CLIENTE



char menuVerHistorial(){
	char opcion;
	printf("TALLERES\n");
	printf("--------\n");
	printf("CLIENTE: MENU-->VER HISTORIAL\n");
	printf("1. Ver historial del coche introducido\n");
	printf("2. Ver historial de todos tus coches\n");
	printf("0. Salir\n");
	printf("Elige una opcion: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%c",&opcion);
	return opcion;
}

char menuDecisionesCliente(){
	char opcion;
	printf("TALLERES\n");
	printf("--------\n");
	printf("CLIENTE: MENU\n");
	printf("1. Tus datos\n");
	printf("2. Ver historial de todos los servicios\n");
	printf("3. Solicitar servicios\n");
	printf("0. Salir\n");
	printf("Elige una opcion: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%c",&opcion);
	return opcion;
}
char menuServicios(ListaServicios lServi){
	char opcion;
	printf("TALLERES\n");
	printf("--------\n");
	visualizarListaServicios(lServi);
	printf("0. Salir\n");
	printf("Elige el servicio que necesita: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%c",&opcion);
	return opcion;
}

//EMPLEADO

char menuTaller(){
	char opcion;
	printf("TALLERES\n");
	printf("--------\n");
	printf("EMPLEADO\n");
	printf("Elige sucursal:\n");
	printf("1. Bilbao\n");
	printf("2. Barcelona\n");
	printf("3. Madrid\n");
	printf("0. Salir\n");
	printf("Elige una opcion: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%c",&opcion);
	return opcion;
}

char menuColor(){
	char opcion;
	printf("TALLERES JAVADICTXS\n");
	printf("-------------------\n");
	printf("CLIENTE: MENU-->SERVICIOS\n");
	printf("Chapa y Pintura:\n");
	printf("1. Rojo\n");
	printf("2. Verde\n");
	printf("3. Gris\n");
	printf("4. Blanco\n");
	printf("5. Marron\n");
	printf("6. Negro\n");
	printf("7. Rosa\n");
	printf("8. Azul\n");
	printf("0. Salir\n");
	printf("Elige una opcion: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%c",&opcion);
	return opcion;
}
char menuEmpleado(){
	char opcion;
	printf("TALLERES \n");
	printf("----------\n");
	printf("1. Inventario\n");
	printf("2. Registro del servicio\n");
	printf("0. Salir\n");
	printf("Elige una opcion: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%c",&opcion);
	return opcion;
}
char menuInventario(){
	char opcion;
	printf("TALLERES\n");
	printf("----------\n");
	printf("EMPLEADO: MENU-->INVENTARIO\n");
	printf("***************************\n");
	printf("1. Aniadir producto\n");
	printf("2. Eliminar producto\n");
	printf("0. Salir\n");
	printf("Elige una opcion: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%c",&opcion);
	return opcion;
}
char menuEstaRegistrado(){
	char opcion;
	printf("¿Esta el dueño registrado?\n");
	printf("1. Si\n");
	printf("2. No\n");
	printf("Elige una opcion: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%c",&opcion);
	return opcion;
}

char menuColores(ListaColores lColores){
	char opcion;
	visualizarListaColores(lColores);
	fflush(stdout);
	fflush(stdin);
	printf("Elige el color de tu coche: ");
	scanf("%c",&opcion);
	return opcion;
}
