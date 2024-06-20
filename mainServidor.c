#include "baseDatos.h"
#include "menu.h"
#include "listaColores.h"
#include "listaServicios.h"
#include <stdio.h>
#include "logger.h"
#include "listaVehiculos.h"
#include <winsock2.h>
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000

void removeNewline(char* str) {
    char *pos;
    if ((pos = strchr(str, '\n')) != NULL) {
        *pos = '\0';
    }
}

int main(){
	sqlite3 *db;
	WSADATA wsaData;
	SOCKET conn_socket; //el que lleva la conexion
	SOCKET comm_socket; //el que lo comunica
	struct sockaddr_in server;
	struct sockaddr_in client;
	char sendBuff[512], recvBuff[512]; // lo que yo envio, lo que yo recibo
	logMessage("Starting server...");

	printf("\nInitialising Winsock...\n"); // inicializa la libreria
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        logMessage("WSAStartup failed");
		printf("Failed. Error Code : %d", WSAGetLastError());
		return -1;
	}

	printf("Initialised.\n");

	//SOCKET creation creacion del socket( la primera estructura
	if ((conn_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		printf("Could not create socket : %d", WSAGetLastError());
		logMessage("Socket creation failed");
		WSACleanup();
		return -1;
	}
	logMessage("Socket created.");
	//printf("Socket created.\n");
	// cual es la ip y cual es el puerto
	server.sin_addr.s_addr = inet_addr(SERVER_IP); //INADDR_ANY;
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	//BIND (the IP/port with socket)
	if (bind(conn_socket, (struct sockaddr*) &server,
			sizeof(server)) == SOCKET_ERROR) {
		//printf("Bind failed with error code: %d", WSAGetLastError());
		logMessage("Bind failed");
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

	printf("Bind done.\n"); //DEJAR EL SOCKET EN ESPERA
	logMessage("Bind done. ");

	//LISTEN to incoming connections (socket server moves to listening mode)
	if (listen(conn_socket, 1) == SOCKET_ERROR) {
		printf("Listen failed with error code: %d", WSAGetLastError());
		logMessage("Listen failed with error code. ");
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

	//ACCEPT incoming connections (server keeps waiting for them)
	printf("Waiting for incoming connections...\n");
    logMessage("Waiting for client connection...");

	int stsize = sizeof(struct sockaddr);
	comm_socket = accept(conn_socket, (struct sockaddr*) &client, &stsize);
	// Using comm_socket is able to send/receive data to/from connected client
	if (comm_socket == INVALID_SOCKET) {
		printf("accept failed with error code : %d", WSAGetLastError());
		logMessage("Accept failed");
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}
	logMessage("Client connected");
	printf("Incomming connection from: %s (%d)\n", inet_ntoa(client.sin_addr),
			ntohs(client.sin_port));

	// Closing the listening sockets (is not going to be used anymore)
	closesocket(conn_socket);

	db = abrirBaseDatos();
    crearTablaClientes(db);
    crearTablaEmpleados(db);
    crearTablaInventario(db);
    crearTablaRegistros(db);
    crearTablaTalleres(db);
    crearTablaTrabajos(db);
    crearTablaUsuarios(db);
    crearTablaVehiculos(db);

    ListaColores lColores;
    lColores.numC=0;
    lColores.aColores=reservaMemoriaListaColores(15);
    volcarFicheroAListaColores(&lColores,"ficheroColores.txt");
    enviarListaColores(conn_socket, sendBuff, recvBuff,lColores);
    ListaServicios lServ;
    lServ.numServ=0;
    lServ.aServicios=reservaMemoriaListaServicios(10);
    volcarFicheroAListaServicios(&lServ,"ficheroServicios.txt");



    //char opcion_prin, opcion_cli, opcion_emp, opcion_color, opcion_reg, opcion_v, opcion_taller, opcion_inv, opcion_gs;
    char opcion_prin, opcion_emp, opcion_taller,opcion_inv,opcion_decisiones,opcion_serv;
    char opc_elim, equis_elim;
    char*dni;
    char matricula[10];
    Usuario user_new;
    Empleado emp;
    Trabajo tra;
    Inventario inv;
    Cliente cli;
    Vehiculo v;
    Registro reg;
    int enc, id_maxTra,existe,recvLen,id_cli,id_maxV, id_maxReg,n;
    sprintf(sendBuff,"HOLA\n");
    send(comm_socket,sendBuff,strlen(sendBuff),0);

    do {
    	recv(comm_socket,recvBuff,sizeof(recvBuff),0);
    	sscanf(recvBuff,"%c",&opcion_prin);
    	//SWITCH 1
    	switch (opcion_prin) {
    	printf("USER:");
    	case '0':{
    		sprintf(sendBuff,"Gracias por confiar en nosotros . Hasta la próxima.\n");
    		send(comm_socket,sendBuff,strlen(sendBuff),0);
    		break;
    	}
    	case '1':{ // INICIAR SESION
    		Usuario u;
    		recvLen = recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
    		if (recvLen > 0) {
    			recvBuff[recvLen] = '\0';
    			removeNewline(recvBuff);
    			strcpy(u.username, recvBuff);
    		}

    		recvLen = recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
    		if (recvLen > 0) {
    			recvBuff[recvLen] = '\0';
    			removeNewline(recvBuff);
    			strcpy(u.contrasenya, recvBuff);
    		}


    		enc = buscarUsuarioInicio(u.username, u.contrasenya);
    		sprintf(sendBuff, "%d", enc);
    		send(comm_socket,sendBuff,strlen(sendBuff),0);

    		if (enc == -1) {

    		} else {
    			logMessage("Usuario encontrado.");
    			u.tipo_user = devolverTipoUsuario(u.username);
    			u.id_user = devolverIDusu(u.username,u.contrasenya);

    			sprintf(sendBuff,"%d",u.tipo_user);
    			send(comm_socket,sendBuff,strlen(sendBuff),0);


    			if (u.tipo_user == 1) {
    				logMessage("Cliente %s ha iniciado sesion",u.username);
    				// CLIENTE
    				do{
    					Cliente * clien = devolverClientePorID(u.id_user);
    					recv(comm_socket,recvBuff,sizeof(recvBuff),0);
    					sscanf(recvBuff,"%c",&opcion_decisiones);
    					switch (opcion_decisiones) {
    					case '0':

    						break;
    					case '1':{
    						sprintf(sendBuff,"ID Usuario: %d, Nombre: %s, Apellido: %s, DNI: %s, Email: %s, Teléfono: %d\n",
    								clien->id_user,clien->nombre_cli,clien->apellido_cli,clien->dni_cli,clien->email_cli,clien->tlf_cli);
    						send(comm_socket,sendBuff,strlen(sendBuff),0);

    						sprintf(sendBuff,"%d",clien->id_user);
    						send(comm_socket,sendBuff,strlen(sendBuff),0);
    						sprintf(sendBuff,"%s",clien->nombre_cli);
    						send(comm_socket,sendBuff,strlen(sendBuff),0);
    						sprintf(sendBuff,"%s",clien->apellido_cli);
    						send(comm_socket,sendBuff,strlen(sendBuff),0);
    						sprintf(sendBuff,"%s",clien->dni_cli);
    						send(comm_socket,sendBuff,strlen(sendBuff),0);
    						sprintf(sendBuff,"%s",clien->email_cli);
    						send(comm_socket,sendBuff,strlen(sendBuff),0);
    						sprintf(sendBuff,"%d",clien->tlf_cli);
    						send(comm_socket,sendBuff,strlen(sendBuff),0);
    						sprintf(sendBuff,"%d",u.tipo_user);
    						send(comm_socket,sendBuff,strlen(sendBuff),0);

    						mostrarVehiculoDeCliente(comm_socket,sendBuff,recvBuff,u.id_user);

    						break;
    					}

    					//HASTA AQUI OK
    					case '2':{
    						mostrarTrabajosPorClienteYRegistro(comm_socket,sendBuff,recvBuff,u.id_user);
    						break;
    					}

    					case '3':{
    						recv(comm_socket,recvBuff,sizeof(recvBuff),0);
    						sscanf(recvBuff,"%c",&opcion_serv);
    						mostrarVehiculoDeCliente(comm_socket,sendBuff,recvBuff,u.id_user);
    						n=recv(comm_socket,recvBuff,sizeof(recvBuff),0);
    						recvBuff[n]='\0';
    						sprintf(matricula,"%s",recvBuff);
    						enc=buscarPorMatricula(matricula);
    						sprintf(sendBuff,"%d",enc);
    						send(comm_socket,sendBuff,strlen(sendBuff),0);
    						if(enc==1){
    							char* nom_serv = devolverNombreServ(lServ,opcion_serv);
    							sprintf(sendBuff,nom_serv);
    							send(comm_socket,sendBuff,strlen(sendBuff),0);
    						}else{
    						}

    						break;
    					}

    					default:
    						break;
    					}//
    				}while(opcion_decisiones!='0');



    			} else {
    				// EMPLEADO
    				logMessage("Empleado ha iniciado sesion.");
    				recv(comm_socket,recvBuff,sizeof(recvBuff),0);
    				sscanf(recvBuff,"%c",&opcion_taller);
    				int opc_taller = opcion_taller - '0';

    				sprintf(sendBuff,"%s",devolverTaller(opc_taller)); //NO FUNCIONA( porque solo lee solo hasta el espacio)
    				send(comm_socket,sendBuff,strlen(sendBuff),0);

    				do{
    					recv(comm_socket,recvBuff,sizeof(recvBuff),0);
    					sscanf(recvBuff,"%c",&opcion_emp);
    					switch (opcion_emp) {

    					case '0':
    						break;
    					case '1': { // INVENTARIO

    						mostrarInventario(comm_socket,sendBuff,recvBuff);
    						recv(comm_socket,recvBuff,sizeof(recvBuff),0);
    						sscanf(recvBuff,"%c",&opcion_inv);
    						do{
    							switch (opcion_inv) { // OPCIONES DENTRO DE INVENTARIO
    							case '0':
    								break;
    							case '1': // agregar material
    								inv.id_inventario = buscarIDMaxInventario();
    								sprintf(sendBuff,"%d",inv.id_inventario);
    								send(comm_socket,sendBuff,strlen(sendBuff),0);

    								recv(comm_socket,recvBuff,sizeof(recvBuff),0);
    								sscanf(recvBuff,"%d",&inv.id_inventario);
    								recv(comm_socket,recvBuff,sizeof(recvBuff),0);
    								sscanf(recvBuff,"%d",&inv.id_taller);
    								//recibir material
    								recvLen = recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
    								if (recvLen > 0) {
    									recvBuff[recvLen] = '\0';  // Asegurarse de que sea una cadena null-terminated
    									removeNewline(recvBuff);   // Eliminar el carácter de nueva línea
    									strcpy(inv.material, recvBuff);
    								}
    								recv(comm_socket,recvBuff,sizeof(recvBuff),0);
    								sscanf(recvBuff,"%d",&inv.cant_inv);

    								agregarInventario(inv);
    								break;

    							case '2': { // eliminar material
    								//mostrarInventario();
    								recv(comm_socket,recvBuff,sizeof(recvBuff),0);
    								sscanf(recvBuff,"%c",&equis_elim);


    								if (equis_elim == 'x' || equis_elim == 'X') {
    									recv(comm_socket,recvBuff,sizeof(recvBuff),0);
    									sscanf(recvBuff,"%c",&opc_elim);
    									int opc = opc_elim -'\0';
    									eliminarInventario(opc);
    								}
    								break;
    							}
    							}
    						}while(opcion_inv!='0');
    						break;
    					}
    					break;

    					case '2': { // REGISTRO DE SERVICIO
    						dni=NULL;
    						recvLen = recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
    						sscanf(recvBuff,dni);
    						existe = buscarDNIexiste(dni);
    						sprintf(sendBuff, "%d", existe);
    						send(comm_socket, sendBuff, strlen(sendBuff), 0);

    						if(existe==1){
    							printf("El cliente existe\n");
    							id_cli = buscarUsuarioPorDNI(dni);
    							sprintf(sendBuff,"%d",id_cli);
    							send(comm_socket,sendBuff,strlen(sendBuff),0);

    						}else{
    							user_new.id_user = buscarIDMaxUsuarios();
    							sprintf(sendBuff,"%d",inv.id_inventario);
    							send(comm_socket,sendBuff,strlen(sendBuff),0);
    							recvLen = recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
    							if (recvLen > 0) {
    								recvBuff[recvLen] = '\0';
    								removeNewline(recvBuff);
    								strcpy(user_new.username, recvBuff);
    							}
    							recvLen = recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
    							if (recvLen > 0) {
    								recvBuff[recvLen] = '\0';
    								removeNewline(recvBuff);
    								strcpy(user_new.contrasenya, recvBuff);
    							}
    							recv(comm_socket,recvBuff,sizeof(recvBuff),0);
    							sscanf(recvBuff,"%s",dni);

    							agregarUsuario(user_new);

    						}

    						char* matricula;

    						recv(comm_socket,recvBuff,sizeof(recvBuff),0);
    						sscanf(recvBuff,"%s",matricula);

    						int enc = buscarPorMatricula(matricula);
    						sprintf(sendBuff,"%d", enc);
    						send(comm_socket,sendBuff,strlen(sendBuff),0);

    						id_maxTra = buscarIDMaxTrabajos();
    						sprintf(sendBuff,"%d", enc);
    						send(comm_socket,sendBuff,strlen(sendBuff),0);

    						if (enc == 1) {

    							sprintf(sendBuff,"%d", u.id_user);
    							send(comm_socket,sendBuff,strlen(sendBuff),0);
    							sprintf(sendBuff,"%d",devolverIDporMatricula(matricula) );
    							send(comm_socket,sendBuff,strlen(sendBuff),0);

    						}else{
    							id_maxV = buscarIDMaxVehiculos();
    							sprintf(sendBuff,"%d", id_maxV);
    							send(comm_socket,sendBuff,strlen(sendBuff),0);

    							recv(comm_socket,recvBuff,sizeof(recvBuff),0);
    							sscanf(recvBuff,"%d",&v.id_vehiculo);
    							recv(comm_socket,recvBuff,sizeof(recvBuff),0);
    							sscanf(recvBuff,"%d",&v.id_cli);
    							recv(comm_socket,recvBuff,sizeof(recvBuff),0);
    							sscanf(recvBuff,"%s",v.numSeguro);
    							recv(comm_socket,recvBuff,sizeof(recvBuff),0);
    							sscanf(recvBuff,"%d",&v.anyoFabricacion);
    							recv(comm_socket,recvBuff,sizeof(recvBuff),0);
    							sscanf(recvBuff,"%s",v.matricula);
    							recv(comm_socket,recvBuff,sizeof(recvBuff),0);
    							sscanf(recvBuff,"%s",v.marca);
    							recv(comm_socket,recvBuff,sizeof(recvBuff),0);
    							sscanf(recvBuff,"%s",v.modelo);
    							recv(comm_socket,recvBuff,sizeof(recvBuff),0);
    							sscanf(recvBuff,"%d",&v.id_color);
    							agregarVehiculo(v);


    						}


    						recv(comm_socket,recvBuff,sizeof(recvBuff),0);
    						sscanf(recvBuff,"%d",&tra.id_trabajo);
    						recv(comm_socket,recvBuff,sizeof(recvBuff),0);
    						sscanf(recvBuff,"%d",&tra.id_vehiculo);
    						recv(comm_socket,recvBuff,sizeof(recvBuff),0);
    						sscanf(recvBuff,"%d",&tra.id_emp);
    						recv(comm_socket,recvBuff,sizeof(recvBuff),0);
    						sscanf(recvBuff,"%s",tra.fecha_tra);
    						recv(comm_socket,recvBuff,sizeof(recvBuff),0);
    						sscanf(recvBuff,"%s",tra.descripcion_tra);

    						agregarTrabajo(tra);
    						id_maxReg = buscarIDMaxRegistros();
    						sprintf(sendBuff,"%d",id_maxReg);
    						send(comm_socket,sendBuff,strlen(sendBuff),0);


    						reg.id_registro=id_maxReg;
    						reg.id_cliente=id_cli;
    						reg.id_trabajo=tra.id_trabajo;
    						strcpy(reg.fecha_hora,tra.fecha_tra);

    						agregarRegistro(reg);
    						break;
    					}
    					}
    				}while(opcion_emp!='0');
    			}

    		}
    		break;
    	}
    	case '2':{ // REGISTRO
    		Usuario u;
    		u = pedirUsuarioRegistro();
    		int enc = buscarUsuarioInicio(u.username,u.contrasenya);
    		if(enc==1){
    			printf("Este usuario ya exite. Prueba de nuevo :)");

    		}else{

    			agregarUsuario(u);
    			if(u.tipo_user==1){
    				cli = pedirCliente(u.id_user);
    				agregarCliente(cli);
    				logMessage("Cliente registrado correctamente.");
    			}else{

    				emp=pedirEmpleado(u.id_user);
    				agregarEmpleado(emp);
    				logMessage("Empleado registrado correctamente.");
    			}
    			mostrarUsuarios();
    			mostrarClientes();
    			mostrarEmpleados();
    		}
    	}


    	break;
    	}
    } while (opcion_prin != '0');


    //NO FUNCIONA (Ver como mandar esto al cliente)

    sqlite3_close(db);
    // CLOSING the sockets and cleaning Winsock...
    closesocket(comm_socket);
    WSACleanup();
    logMessage("CLOSING the sockets and cleaning Winsock...");
    logMessage("Final del programa.");

    return 0;
}

