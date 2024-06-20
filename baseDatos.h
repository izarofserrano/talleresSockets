#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include "usuario.h"
#include "cliente.h"
#include "empleado.h"
#include "vehiculo.h"
#include "trabajo.h"
#include "taller.h"
#include "registro.h"
#include "inventario.h"
#include "listaVehiculos.h"
#include <winsock2.h>

#ifndef BASEDATOS_H_
#define BASEDATOS_H_


sqlite3* abrirBaseDatos();
void cerrarBaseDatos(sqlite3* db);
void ejecutarConsulta(sqlite3* db, const char* consulta);

//CREAR TABLAS
void crearTablaClientes(sqlite3* db);
void crearTablaEmpleados(sqlite3* db);
void crearTablaInventario(sqlite3* db);
void crearTablaRegistros(sqlite3* db);
void crearTablaTalleres(sqlite3* db);
void crearTablaTrabajos(sqlite3* db);
void crearTablaUsuarios(sqlite3* db);
void crearTablaVehiculos(sqlite3* db);

//MOSTRAR TABLAS
void mostrarClientes();
void mostrarEmpleados();
void mostrarInventario(SOCKET comm_socket, char *sendBuff, char* recvBuff);
void mostrarRegistros();
void mostrarTalleres();
void mostrarTrabajos();
void mostrarUsuarios();
void mostrarVehiculos();

//AGREGAR EN TABLAS
void agregarCliente(Cliente c);
void agregarEmpleado(Empleado e);
void agregarInventario(Inventario i);
void agregarRegistro(Registro r);
void agregarTaller(Taller t);
void agregarTrabajo(Trabajo t);
void agregarUsuario(Usuario u);
void agregarVehiculo(Vehiculo v);


//ELIMINAR
void eliminarCliente(int id);
void eliminarEmpleado(int id);
void eliminarInventario(int id);
void eliminarRegistro(int id);
void eliminarTaller(int id);
void eliminarTrabajo(int id);
void eliminarVehiculo(int id);

//BUSCAR ID MAXIMO
int buscarIDMaxInventario();
int buscarIDMaxRegistros();
int buscarIDMaxTalleres();
int buscarIDMaxTrabajos();
int buscarIDMaxUsuarios();
int buscarIDMaxVehiculos();

//BUSCAR
int buscarClientes(int id);
int buscarEmpleados(int id);
int buscarInventario(int id);
int buscarRegistros(int id);
int buscarTalleres(int id);
int buscarTrabajos(int id);
int buscarUsuarios(int id);
int buscarVehiculos(int id);


//BUSCAR ESPEFICIFICO
int buscarUsuarioInicio(char* usernameIntro, char*contrasenyaIntro);
int buscarTipoUsu(char* usernameIntro, char*contrasenyaIntro);
int buscarUsuarioPorDNI(char* dni);
int buscarPorMatricula(char* matricula);
int buscarDNIexiste(char* dni);

//MOSTRAR ESPECIFICO
void mostrarVehiculoDeCliente(SOCKET comm_socket, char *sendBuff, char* recvBuff, int id_cli);
void mostrarTrabajosPorClienteYRegistro(SOCKET comm_socket, char *sendBuff, char* recvBuff,int id_usuario);
Vehiculos mostrarVehiculosDeCliente2(int id_cli);


//DEVOLVER ESPECIFICO
int devolverTipoUsuario(char* usernameIntro);
int devolverIDusu(char* usernameIntro, char*contrasenyaIntro);
char* devolverTaller(int id);
int devolverIDporMatricula(char* matricula);
Cliente* devolverClientePorID(int id_cli);
char* devolverServicio(char opc);

//MODIFICAR



#endif /* BASEDATOS_H_ */
