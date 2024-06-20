#include "baseDatos.h"
#include <stdlib.h>
#include <string.h>
#include "usuario.h"
#include <winsock2.h>
#define DATABASE_NAME "taller.db"


sqlite3* abrirBaseDatos(){
	sqlite3 *db;
	int resultado = sqlite3_open(DATABASE_NAME,&db);
	if(resultado != SQLITE_OK){
		fprintf(stderr,"Error al abrir la base de datos: %s\n",sqlite3_errmsg(db));
		logMessage("Error al abrir la base de datos.");
		sqlite3_close(db);
		exit(EXIT_FAILURE);
	}
	logMessage("BBDD abierto correctamente.");
	return db;
}

void cerrarBaseDatos(sqlite3* db){
	sqlite3_close(db);
	logMessage("BBDD cerrado.");
}

void ejecutarConsulta(sqlite3* db, const char* consulta){
	/*char *errorMensaje = 0;
	int resultado = sqlite3_exec(db, consulta, 0, 0, &errorMensaje);
	if (resultado != SQLITE_OK) {
		fprintf(stderr, "Error al ejecutar la consulta: %s\n", errorMensaje);
		sqlite3_free(errorMensaje);
		exit(EXIT_FAILURE);
	}*/
	sqlite3_stmt *stmt;
	sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL); //Preparar la sentencia
	sqlite3_step(stmt); //Ejecutar la sentencia
	sqlite3_finalize(stmt);
}

//CREAR TABLAS
void crearTablaClientes(sqlite3* db) {
	const char* consulta = "CREATE TABLE IF NOT EXISTS Cliente ("
			"Id_usuario INTEGER PRIMARY KEY,"
			"Nombre TEXT NOT NULL,"
			"Apellido TEXT NOT NULL,"
			"DNI TEXT NOT NULL,"
			"Email TEXT NOT NULL,"
			"Telefono INTEGER NOT NULL"
			");";
	ejecutarConsulta(db, consulta);

    const char* consultaInsert = "INSERT INTO Cliente (Id_usuario, Nombre, Apellido, DNI, Email, Telefono) VALUES"
    "(1, 'Juan', 'Gomez', '12345678A', 'juan@gmail.com', 123456789),"
    "(2, 'Maria', 'Lopez', '87654321B', 'maria@gmail.com', 987654321),"
    "(3, 'Pedro', 'Martinez', '13579246C', 'pedro@gmail.com', 456123789),"
    "(4, 'Ana', 'Sanchez', '98765432D', 'ana@gmail.com', 789456123),"
    "(5, 'Luis', 'Rodriguez', '24681357E', 'luis@gmail.com', 159357486),"
    "(6, 'Laura', 'Diaz', '98765432F', 'laura@gmail.com', 753159852),"
    "(7, 'Carlos', 'Fernandez', '98765432G', 'carlos@gmail.com', 951357486),"
    "(8, 'Sofia', 'Garcia', '12345678H', 'sofia@gmail.com', 654987321),"
    "(9, 'Pablo', 'Ruiz', '12345678I', 'pablo@gmail.com', 852369741),"
    "(10,'Marta', 'Jimenez', '12345678J', 'marta@gmail.com', 369852147);"
            ;
    ejecutarConsulta(db, consultaInsert);
}

void crearTablaEmpleados(sqlite3* db) {
    const char* consulta = "CREATE TABLE IF NOT EXISTS Empleado ("
        "Id_usuario INTEGER PRIMARY KEY,"
        "Nombre TEXT NOT NULL,"
        "Cargo TEXT NOT NULL"
        ");";
    ejecutarConsulta(db, consulta);
    const char* consultaInsert = "INSERT INTO Empleado (Id_usuario, Nombre, Cargo) VALUES"
    "(11, 'Carlos Gonzalez', 'Mecánico'),"
    "(12, 'Laura Martinez', 'Recepcionista'),"
    "(13, 'Juan Rodriguez', 'Electricista'),"
    "(14, 'Maria Sanchez', 'Contable'),"
    "(15, 'David Lopez', 'Administrador'),"
    "(16, 'Ana Ruiz', 'Jefe de Taller'),"
    "(17, 'Javier Gomez', 'Limpiador'),"
    "(18, 'Elena Martin', 'Encargado de Almacén'),"
    "(19, 'Luisa Rodriguez', 'Secretaria'),"
    "(20, 'Alberto Diaz', 'Gerente');";
    ejecutarConsulta(db, consultaInsert);
}

void crearTablaInventario(sqlite3* db) {
    const char* consulta = "CREATE TABLE IF NOT EXISTS Inventario ("
        "Id_inventario INTEGER PRIMARY KEY,"
        "Id_taller INTEGER NOT NULL,"
        "Material TEXT NOT NULL,"
        "Cantidad INTEGER NOT NULL"
        ");";
    ejecutarConsulta(db, consulta);
    const char* consultaInsert = "INSERT INTO Inventario (Id_inventario, Id_taller, Material, Cantidad) VALUES"
    "(1, 1, 'Aceite', 10),"
    "(2, 1, 'Filtros', 20),"
    "(3, 2, 'Llantas', 15),"
    "(4, 3, 'Bombillas', 25),"
    "(5, 3, 'Escobillas', 30),"
    "(6, 2, 'Baterias', 12),"
    "(7, 1, 'Limpiaparabrisas', 18),"
    "(8, 1, 'Neumaticos', 22),"
    "(9, 2, 'LiquidoFrenos', 17),"
    "(10, 3, 'PastillasFrenos', 28),"
    "(11, 1, 'Radiadores', 21),"
    "(12, 1, 'Alternadores', 14),"
    "(13, 2, 'Embragues', 19),"
    "(14, 3, 'CorreasDistribucion', 26),"
    "(15, 1, 'LiquidoRefrigerante', 23),"
    "(16, 2, 'Anticongelante', 16),"
    "(17, 3, 'Amortiguadores', 24),"
    "(18, 2, 'DiscosFrenos', 27),"
    "(19, 1, 'Ruedas', 31),"
    "(20, 1, 'Manguitos', 36),"
    "(21, 2, 'FiltrosAire', 40),"
    "(22, 2, 'FiltrosAceite', 38),"
    "(23, 1, 'FiltrosCombustible', 34),"
    "(24, 3, 'FiltrosPolen', 37),"
    "(25, 3, 'FiltrosHabitaculo', 33);";
    ejecutarConsulta(db, consultaInsert);
}

void crearTablaRegistros(sqlite3* db) {
	const char* consulta = "CREATE TABLE IF NOT EXISTS Registros ("
			"Id_registro INTEGER PRIMARY KEY,"
			"Id_cliente INTEGER NOT NULL,"
			"Id_trabajo INTEGER NOT NULL,"
			"FechaHora TEXT NOT NULL"
			");";
	ejecutarConsulta(db, consulta);

	const char* consultaInsert = "INSERT INTO Registros (Id_registro, Id_cliente, Id_trabajo, FechaHora) VALUES"
			"(1, 1, 1, '2024/05/01'),"
			"(2, 21, 7, '20240501'),"
			"(3, 3, 3, '20240502'),"
			"(4, 4, 1, '20240502'),"
			"(5, 21, 2, '20240503'),"
			"(6, 6, 3, '20240503'),"
			"(7, 7, 1, '20240503');";
	ejecutarConsulta(db, consultaInsert);
}


void crearTablaTalleres(sqlite3* db) {
    const char* consulta = "CREATE TABLE IF NOT EXISTS Talleres ("
        "Id_taller INTEGER PRIMARY KEY,"
        "Nombre TEXT NOT NULL,"
        "Direccion TEXT NOT NULL,"
        "Ciudad TEXT NOT NULL,"
        "Tlf_taller INTEGER NOT NULL"
        ");";
    ejecutarConsulta(db, consulta);
    const char* consultaInsert = "INSERT INTO Talleres (Id_taller, Nombre, Direccion, Ciudad, Tlf_taller) VALUES"
    "(1, 'Taller Bilbao', 'CalleBilbao123', 'Bilbao', 123456789),"
    "(2, 'Taller Barcelona', 'AvenidaDiagonal456', 'Barcelona', 987654321),"
    "(3, 'Taller Madrid', 'CalleGranVía789', 'Madrid', 555666777);";
    ejecutarConsulta(db, consultaInsert);
}

void crearTablaTrabajos(sqlite3* db) {
    const char* consulta = "CREATE TABLE IF NOT EXISTS Trabajo ("
        "Id_trabajo INTEGER PRIMARY KEY,"
        "Id_vehiculo INTEGER NOT NULL,"
        "Id_empleado INTEGER NOT NULL,"
        "Fecha TEXT NOT NULL,"
        "Descripcion TEXT NOT NULL"
        ");";
    ejecutarConsulta(db, consulta);
    const char* consultaInsert = "INSERT INTO Trabajo (Id_trabajo, Id_vehiculo, Id_empleado, Fecha, Descripcion) VALUES"
    "(1, 1, 1, '20240505', 'CambioDeAceiteYFiltros'),"
    "(2, 2, 2, '20240506', 'RevisiónAnual'),"
    "(3, 3, 3, '20240507', 'ReparaciónDeFalloElectrico'),"
    "(4, 4, 4, '20240508', 'SustituciónDeNeumáticos'),"
    "(5, 5, 5, '20240509', 'ReparaciónDeMotor'),"
    "(6, 6, 6, '20240510', 'MantenimientoPreventivo'),"
    "(7, 7, 7, '20240511', 'CambioDeCorreaDeDistribución'),"
    "(8, 8, 8, '20240512', 'AlineaciónDeDirección'),"
    "(9, 9, 9, '20240513', 'CambioDePastillasDeFreno'),"
    "(10, 10, 10, '20240514', 'CambioDeBatería'),"
    "(11, 11, 11, '20240515', 'ReparaciónDeSistemaDeEscape'),"
    "(12, 12, 12, '20240516', 'CambioDeAceiteYFiltros');";
    ejecutarConsulta(db, consultaInsert);
}

void crearTablaUsuarios(sqlite3* db) {
    const char* consulta = "CREATE TABLE IF NOT EXISTS Usuarios ("
        "Id_usuario INTEGER PRIMARY KEY,"
        "Username TEXT NOT NULL,"
        "Contrasenya TEXT NOT NULL,"
        "Tipo_usuario INTEGER NOT NULL"
        ");";
    ejecutarConsulta(db, consulta);
    const char* consultaInsert = "INSERT INTO Usuarios (Id_usuario, Username, Contrasenya, Tipo_usuario) VALUES"
    "(1, 'carlosGonzalez123', 'meaja829', 1),"
    "(2, 'lauraMartinez456', 'holahola123', 1),"
    "(3, 'juanRodriguez789', 'juan901', 1),"
    "(4, 'mariaSanchez012', 'sancheZ91', 1),"
    "(5, 'davidLopez345', 'lopez203', 1),"
    "(6, 'anaRuiz678', 'anita673', 1),"
    "(7, 'javierGomez901', 'gomezjavier901', 1),"
    "(8, 'elenaMartin234', 'martin398', 1),"
    "(9, 'luisaRodriguez567', 'jellou567', 1),"
    "(10, 'albertoDiaz890', 'alberto9876', 1),"
    "(11, 'antonioPerez1234', 'antonio1234', 2),"
    "(12, 'mariaLopez5678', 'maria5678', 2),"
    "(13, 'juanGarcia9012', 'juan9012', 2),"
    "(14, 'lauraGonzalez3456', 'laura3456', 2),"
    "(15, 'pedroMartinez7890', 'pedro7890', 2),"
    "(16, 'carmenSanchez1234', 'carmen1234', 2),"
    "(17, 'diegoRuiz5678', 'diego5678', 2),"
    "(18, 'elenaGomez9012', 'elena9012', 2),"
    "(19, 'pabloDiaz3456', 'pablo3456', 2),"
    "(20, 'luciaPerez7890', 'lucia7890', 2);";
    ejecutarConsulta(db, consultaInsert);
}

void crearTablaVehiculos(sqlite3* db) {
    const char* consulta = "CREATE TABLE IF NOT EXISTS Vehiculos ("
        "Id_vehiculo INTEGER PRIMARY KEY,"
        "Id_cliente INTEGER NOT NULL,"
        "Num_seguro TEXT NOT NULL,"
        "Anyo_fabricacion INTEGER NOT NULL,"
        "Matricula TEXT NOT NULL,"
        "Marca TEXT NOT NULL,"
        "Modelo TEXT NOT NULL,"
        "Id_color INTEGER NOT NULL"
        ");";
    ejecutarConsulta(db, consulta);
    const char* consultaInsert = "INSERT INTO Vehiculos (Id_vehiculo, Id_cliente, Num_seguro, Anyo_fabricacion, Matricula, Marca, Modelo, Id_color) VALUES"
    "(1, 1, 'ABC12345678901234567', 2019, 'ABC1234', 'Toyota', 'Corolla', 1),"
    "(2, 1, 'DEF23456789012345678', 2020, 'DEF5678', 'Honda', 'Civic', 2),"
    "(3, 2, 'GHI34567890123456789', 2018, 'GHI9012', 'Ford', 'Focus', 3),"
    "(4, 3, 'JKL45678901234567890', 2017, 'JKL3456', 'Chevrolet', 'Cruze', 1),"
    "(5, 4, 'MNO56789012345678901', 2016, 'MNO6789', 'Nissan', 'Sentra', 2),"
    "(6, 5, 'PQR67890123456789012', 2015, 'PQR7890', 'Hyundai', 'Elantra', 3),"
    "(7, 6, 'STU78901234567890123', 2014, 'STU8901', 'Volkswagen', 'Jetta', 1),"
    "(8, 7, 'VWX89012345678901234', 2013, 'VWX9012', 'Kia', 'Forte', 2),"
    "(9, 8, 'YZA90123456789012345', 2012, 'YZA1234', 'Mazda', 'Auris', 3),"
    "(10, 9, 'BCD01234567890123456', 2011, 'BCD2345', 'Honda', 'Accord', 1),"
    "(11, 10, 'CDE12345678901234567', 2010, 'CDE3456', 'Toyota', 'Camry', 2),"
    "(12, 11, 'DEF23456789012345678', 2009, 'DEF4567', 'Ford', 'Fusion', 3),"
    "(13, 12, 'EFG34567890123456789', 2008, 'EFG5678', 'Chevrolet', 'Malibu', 1),"
    "(14, 13, 'FGH45678901234567890', 2007, 'FGH6789', 'Nissan', 'Altima', 2),"
    "(15, 14, 'GHI56789012345678901', 2006, 'GHI7890', 'Hyundai', 'Sonata', 3),"
    "(16, 15, 'HIJ67890123456789012', 2005, 'HIJ8901', 'Volkswagen', 'Passat', 1),"
    "(17, 16, 'IJK78901234567890123', 2004, 'IJK9012', 'Kia', 'Optima', 2),"
    "(18, 17, 'JKL89012345678901234', 2003, 'JKL0123', 'Mazda', 'Au', 3),"
    "(19, 18, 'KLM90123456789012345', 2002, 'KLM1234', 'Honda', 'CRV', 1),"
    "(20, 19, 'LMN01234567890123456', 2001, 'LMN2345', 'Toyota', 'RAV4', 2),"
    "(21, 20, 'MNO12345678901234567', 2000, 'MNO3456', 'Ford', 'Explorer', 3),"
    "(22, 21, 'NOP23456789012345678', 1999, 'NOP4567', 'Chevrolet', 'Tahoe', 1),"
    "(23, 22, 'OPQ34567890123456789', 1998, 'OPQ5678', 'Nissan', 'Pathfinder', 2),"
    "(24, 23, 'PQR45678901234567890', 1997, 'PQR6789', 'Hyundai', 'SantaFe', 3),"
    "(25, 24, 'QRS56789012345678901', 1996, 'QRS7890', 'Volkswagen', 'Tiguan', 1),"
    "(26, 25, 'RST67890123456789012', 1995, 'RST8901', 'Kia', 'Sorento', 2),"
    "(27, 26, 'STU78901234567890123', 1994, 'STU9012', 'Mazda', 'CX5', 3),"
    "(28, 27, 'TUV89012345678901234', 1993, 'TUV0123', 'Honda', 'Pilot', 1),"
    "(29, 26, 'UVW90123456789012345', 1992, 'UVW1234', 'Toyota', 'Highlander', 2),"
    "(30, 29, 'VWX01234567890123456', 1991, 'VWX2345', 'Ford', 'Edge', 3),"
    "(31, 1, 'WXY12345678901234567', 1990, 'WXY3456', 'Chevrolet', 'Traverse', 1),"
    "(32, 3, 'XYZ23456789012345678', 1989, 'XYZ4567', 'Nissan', 'Rogue', 2),"
    "(33, 2, 'YZA34567890123456789', 1988, 'YZA5678', 'Hyundai', 'Tucson', 3),"
    "(34, 3, 'ZAB45678901234567890', 1987, 'ZAB6789', 'Volkswagen', 'Atlas', 1),"
    "(35, 4, 'ABC56789012345678901', 1986, 'ABC7890', 'Kia', 'Telluride', 2),"
    "(36, 5, 'BCD67890123456789012', 1985, 'BCD8901', 'Mazda', 'CX9', 3),"
    "(37, 6, 'CDE78901234567890123', 1984, 'CDE9012', 'Honda', 'HRV', 1),"
    "(38, 7, 'DEF89012345678901234', 1983, 'DEF0123', 'Toyota', 'CHR', 2),"
    "(39, 8, 'EFG90123456789012345', 1982, 'EFG1234', 'Ford', 'Bronco Sport', 3),"
    "(40, 9, 'FGH01234567890123456', 1981, 'FGH2345', 'Chevrolet', 'Blazer', 1),"
    "(41, 10, 'GHI12345678901234567', 1980, 'GHI3456', 'Nissan', 'Kicks', 2),"
    "(42, 11, 'HIJ23456789012345678', 1979, 'HIJ4567', 'Hyundai', 'Kona', 3),"
    "(43, 12, 'IJK34567890123456789', 1978, 'IJK5678', 'Volkswagen', 'ID4', 1),"
    "(44, 13, 'JKL45678901234567890', 1977, 'JKL6789', 'Kia', 'Sportage', 2),"
    "(45, 14, 'KLM56789012345678901', 1976, 'KLM7890', 'Mazda', 'MX30', 3),"
    "(46, 15, 'LMN67890123456789012', 1975, 'LMN8901', 'Honda', 'Hybrid', 1),"
    "(47, 16, 'MNO78901234567890123', 1974, 'MNO9012', 'Toyota', 'RAV4Prime', 2),"
    "(48, 17, 'NOP89012345678901234', 1973, 'NOP0123', 'Ford', 'EscapePHEV', 3),"
    "(49, 18, 'OPQ90123456789012345', 1972, 'OPQ1234', 'Chevrolet', 'Equinox', 1),"
    "(50, 22, 'PQR01234567890123456', 1971, 'PQR2345', 'Nissan', 'RogueSport', 2);";
    ejecutarConsulta(db, consultaInsert);
}




//MOSTRAR CLIENTES
void mostrarClientes() {
    sqlite3* db = abrirBaseDatos();
    sqlite3_stmt *stmt;

    const char* consulta = "SELECT Id_usuario, Nombre, Apellido, DNI, Email, Telefono FROM Cliente";
    int resultado = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
    if (resultado != SQLITE_OK) {
        fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    printf("Clientes:\n");
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id_usuario = sqlite3_column_int(stmt, 0);
        const unsigned char* nombre = sqlite3_column_text(stmt, 1);
        const unsigned char* apellido = sqlite3_column_text(stmt, 2);
        const unsigned char* dni = sqlite3_column_text(stmt, 3);
        const unsigned char* email = sqlite3_column_text(stmt, 4);
        int telefono = sqlite3_column_int(stmt, 5);
        printf("ID Usuario: %d, Nombre: %s, Apellido: %s, DNI: %s, Email: %s, Teléfono: %d\n", id_usuario, nombre, apellido, dni, email, telefono);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void mostrarEmpleados() {
    sqlite3* db = abrirBaseDatos();
    sqlite3_stmt *stmt;

    const char* consulta = "SELECT Id_usuario, Nombre, Cargo FROM Empleado";
    int resultado = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
    if (resultado != SQLITE_OK) {
        fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    printf("Empleados:\n");
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id_usuario = sqlite3_column_int(stmt, 0);
        const unsigned char* nombre = sqlite3_column_text(stmt, 1);
        const unsigned char* cargo = sqlite3_column_text(stmt, 2);
        printf("ID Usuario: %d, Nombre: %s, Cargo: %s\n", id_usuario, nombre, cargo);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void mostrarInventario(SOCKET comm_socket, char *sendBuff, char* recvBuff) {
    sqlite3* db = abrirBaseDatos();
    sqlite3_stmt *stmt;

    const char* consulta = "SELECT Id_inventario, Id_taller, Material, Cantidad FROM Inventario";
    int resultado = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
    if (resultado != SQLITE_OK) {
        fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }
    int resul = sqlite3_step(stmt);
    while (resul == SQLITE_ROW) {
    	Inventario inv;
        inv.id_inventario = sqlite3_column_int(stmt, 0);
        inv.id_taller = sqlite3_column_int(stmt, 1);
        strcpy(inv.material,sqlite3_column_text(stmt, 2));
        inv.cant_inv = sqlite3_column_int(stmt, 3);

        sprintf(sendBuff,"%d",inv.id_inventario);
        send(comm_socket, sendBuff, strlen(sendBuff), 0);
        sprintf(sendBuff,"%d",inv.id_taller);
        send(comm_socket, sendBuff, strlen(sendBuff), 0);
        sprintf(sendBuff,"%d",inv.material);
        send(comm_socket, sendBuff, strlen(sendBuff), 0);
        sprintf(sendBuff, "%d", inv.cant_inv);
        send(comm_socket, sendBuff, strlen(sendBuff), 0);
        resul = sqlite3_step(stmt);

    }
    sprintf(sendBuff,  "FIN");
    send(comm_socket, sendBuff, strlen(sendBuff), 0);

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void mostrarRegistros() {
    sqlite3* db = abrirBaseDatos();
    sqlite3_stmt *stmt;

    const char* consulta = "SELECT Id_registro, Id_cliente, Id_trabajo, FechaHora FROM Registros";
    int resultado = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
    if (resultado != SQLITE_OK) {
        fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    printf("Registros:\n");
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id_registro = sqlite3_column_int(stmt, 0);
        int id_cliente = sqlite3_column_int(stmt, 1);
        int id_trabajo = sqlite3_column_int(stmt, 2);
        const unsigned char* fechahora = sqlite3_column_text(stmt, 3);
        printf("ID Registro: %d, ID Cliente: %d, ID Trbajo: %d, Fecha y hora: %s\n", id_registro, id_cliente, id_trabajo, fechahora);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}



void mostrarTalleres() {
    sqlite3* db = abrirBaseDatos();
    sqlite3_stmt *stmt;

    const char* consulta = "SELECT Id_taller, Nombre, Direccion, Ciudad, Tlf_taller FROM Talleres";
    int resultado = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
    if (resultado != SQLITE_OK) {
        fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    printf("Talleres:\n");
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id_taller = sqlite3_column_int(stmt, 0);
        const unsigned char* nombre = sqlite3_column_text(stmt, 1);
        const unsigned char* direccion = sqlite3_column_text(stmt, 2);
        const unsigned char* ciudad = sqlite3_column_text(stmt, 3);
        int telefono = sqlite3_column_int(stmt, 4);
        printf("ID Taller: %d, Nombre: %s, Direccion: %s, Ciudad: %s, Teléfono: %d\n", id_taller, nombre, direccion, ciudad, telefono);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void mostrarTrabajos() {
    sqlite3* db = abrirBaseDatos();
    sqlite3_stmt *stmt;

    const char* consulta = "SELECT Id_trabajo, Id_vehiculo, Id_empleado, Fecha, Descripcion FROM Trabajo";
    int resultado = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
    if (resultado != SQLITE_OK) {
        fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    printf("Trabajos:\n");
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id_trabajo = sqlite3_column_int(stmt, 0);
        int id_vehiculo = sqlite3_column_int(stmt, 1);
        int id_empleado = sqlite3_column_int(stmt, 2);
        const unsigned char* fecha = sqlite3_column_text(stmt, 3);
        const unsigned char* descripcion = sqlite3_column_text(stmt, 4);
        printf("ID Trabajo: %d, ID Vehiculo: %d, ID Empleado: %d, Fecha: %s, Descripcion: %s\n", id_trabajo, id_vehiculo, id_empleado, fecha, descripcion);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void mostrarUsuarios() {
    sqlite3* db = abrirBaseDatos();
    sqlite3_stmt *stmt;

    const char* consulta = "SELECT Id_usuario, Username, Contrasenya, Tipo_usuario FROM Usuarios";
    int resultado = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
    if (resultado != SQLITE_OK) {
        fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    printf("Usuarios:\n");
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id_usuario = sqlite3_column_int(stmt, 0);
        const unsigned char* username = sqlite3_column_text(stmt, 1);
        const unsigned char* contrasenya = sqlite3_column_text(stmt, 2);
        int tipo_usu = sqlite3_column_int(stmt, 3);
        if(tipo_usu==1){
        	printf("ID Usuario: %d, Username: %s, Contraseña: %s, Tipo usuario: %s\n", id_usuario, username, contrasenya, "CLIENTE");
        }else{
        	printf("ID Usuario: %d, Username: %s, Contraseña: %s, Tipo usuario: %s\n", id_usuario, username, contrasenya, "EMPLEADO");
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void mostrarVehiculos() {
    sqlite3* db = abrirBaseDatos();
    sqlite3_stmt *stmt;

    const char* consulta = "SELECT Id_vehiculo, Id_cliente, Num_seguro, Anyo_fabricacion, Matricula, Marca, Modelo, Id_color FROM Vehiculos";
    int resultado = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
    if (resultado != SQLITE_OK) {
        fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    printf("Vehiculos:\n");
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id_vehiculo = sqlite3_column_int(stmt, 0);
        int id_cliente = sqlite3_column_int(stmt, 1);
        const unsigned char* num_seguro = sqlite3_column_text(stmt, 2);
        int anyo_fabricacion = sqlite3_column_int(stmt, 3);
        const unsigned char* matricula = sqlite3_column_text(stmt, 4);
        const unsigned char* marca = sqlite3_column_text(stmt, 5);
        const unsigned char* modelo = sqlite3_column_text(stmt, 6);
        int id_color = sqlite3_column_int(stmt, 7);
        printf("ID Vehiculo: %d, ID Cliente: %d, Numero seguro: %s, Año fabricacion: %d, Matricula: %s, Marca: %s, Modelo: %s, ID Color: %d\n", id_vehiculo, id_cliente, num_seguro, anyo_fabricacion, matricula, marca, modelo, id_color);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

//AGREGAR
void agregarCliente(Cliente c) {
    sqlite3* db = abrirBaseDatos();
    sqlite3_stmt *stmt;

    const char* consulta = "INSERT INTO Cliente (Id_usuario, Nombre, Apellido, DNI, Email, Telefono) VALUES (?, ?, ?, ?, ?, ?)";
    int resultado = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
    if (resultado != SQLITE_OK) {
        fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    sqlite3_bind_int(stmt, 1, c.id_user);
    sqlite3_bind_text(stmt, 2, c.nombre_cli, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, c.apellido_cli, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, c.dni_cli, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, c.email_cli, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 6, c.tlf_cli);

    resultado = sqlite3_step(stmt);
    if (resultado != SQLITE_DONE) {
        fprintf(stderr, "Error al insertar el cliente: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    logMessage("Cliente agregado correctamente.");
}
void agregarEmpleado(Empleado e){
	sqlite3* db = abrirBaseDatos();
	sqlite3_stmt *stmt;

	const char* consulta = "INSERT INTO Empleado (Id_usuario, Nombre, Cargo) VALUES (?, ?, ?)";
	int resultado = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
	if (resultado != SQLITE_OK) {
		fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(EXIT_FAILURE);
	}
	sqlite3_bind_int(stmt, 1, e.id_user);
	sqlite3_bind_text(stmt, 2, e.nombre_emp, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 3, e.cargo, -1, SQLITE_STATIC);
	resultado = sqlite3_step(stmt);
	if (resultado != SQLITE_DONE) {
		fprintf(stderr, "Error al insertar el cliente: %s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		exit(EXIT_FAILURE);
	}
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	logMessage("Empleado agregado correctamente.");
}
void agregarInventario(Inventario i){
	sqlite3* db = abrirBaseDatos();
	sqlite3_stmt *stmt;

	const char* consulta = "INSERT INTO Inventario (Id_inventario, Id_taller, Material, Cantidad) VALUES (?, ?, ?, ?)";
	int resultado = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
	if (resultado != SQLITE_OK) {
		fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(EXIT_FAILURE);
	}
	sqlite3_bind_int(stmt, 1, i.id_inventario);
	sqlite3_bind_int(stmt, 2, i.id_taller);
	sqlite3_bind_text(stmt, 3, i.material, -1, SQLITE_STATIC);
	sqlite3_bind_int(stmt, 4, i.id_taller);

	resultado = sqlite3_step(stmt);
	if (resultado != SQLITE_DONE) {
		fprintf(stderr, "Error al insertar el cliente: %s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		exit(EXIT_FAILURE);
	}
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	fprintf(stderr, "%s agregado correctamente\n",i.material);
	logMessage("Inventario agregado correctamente.");
}

void agregarRegistro(Registro r){
	sqlite3* db = abrirBaseDatos();
	sqlite3_stmt *stmt;

	const char* consulta = "INSERT INTO Registros (Id_registro, Id_cliente, Id_trabajo, FechaHora) VALUES (?, ?, ?, ?)";
	int resultado = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
	if (resultado != SQLITE_OK) {
		fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(EXIT_FAILURE);
	}
	sqlite3_bind_int(stmt, 1, r.id_registro);
	sqlite3_bind_int(stmt, 2, r.id_cliente);
	sqlite3_bind_int(stmt, 3, r.id_trabajo);
	sqlite3_bind_text(stmt, 4, r.fecha_hora, -1, SQLITE_STATIC);

	resultado = sqlite3_step(stmt);
	if (resultado != SQLITE_DONE) {
		fprintf(stderr, "Error al insertar el Registro: %s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		exit(EXIT_FAILURE);
	}
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	logMessage("Registro agregado correctamente.");
}


void agregarTaller(Taller t){
	sqlite3* db = abrirBaseDatos();
	sqlite3_stmt *stmt;

	const char* consulta = "INSERT INTO Talleres (Id_taller, Nombre, Direccion, Ciudad, Tlf_taller) VALUES (?, ?, ?, ?, ?)";
	int resultado = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
	if (resultado != SQLITE_OK) {
		fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(EXIT_FAILURE);
	}
	sqlite3_bind_int(stmt, 1, t.id_taller);
	sqlite3_bind_text(stmt, 2, t.nombre_taller, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 3, t.dir_taller, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 4, t.ciudad, -1, SQLITE_STATIC);
	sqlite3_bind_int(stmt, 5, t.tlf_taller);
	resultado = sqlite3_step(stmt);
	if (resultado != SQLITE_DONE) {
		fprintf(stderr, "Error al insertar el cliente: %s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		exit(EXIT_FAILURE);
	}
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	logMessage("Taller agregado correctamente.");
}
void agregarTrabajo(Trabajo t){
	sqlite3* db = abrirBaseDatos();
	sqlite3_stmt *stmt;

	const char* consulta = "INSERT INTO Trabajo (Id_trabajo, Id_vehiculo, Id_empleado, Fecha, Descripcion) VALUES (?, ?, ?, ?, ?)";
	int resultado = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
	if (resultado != SQLITE_OK) {
		fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(EXIT_FAILURE);
	}
	sqlite3_bind_int(stmt, 1, t.id_trabajo);
	sqlite3_bind_int(stmt, 2, t.id_vehiculo);
	sqlite3_bind_int(stmt, 3, t.id_emp);
	sqlite3_bind_text(stmt, 4, t.fecha_tra, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 5, t.descripcion_tra, -1, SQLITE_STATIC);
	resultado = sqlite3_step(stmt);
	if (resultado != SQLITE_DONE) {
		fprintf(stderr, "Error al insertar el cliente: %s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		exit(EXIT_FAILURE);
	}
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	logMessage("Trabajo agregado correctamente.");
}
void agregarUsuario(Usuario u){
	sqlite3* db = abrirBaseDatos();
	sqlite3_stmt *stmt;

	const char* consulta = "INSERT INTO Usuarios (Id_usuario, Username, Contrasenya, Tipo_usuario) VALUES (?, ?, ?, ?)";
	int resultado = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
	if (resultado != SQLITE_OK) {
		fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(EXIT_FAILURE);
	}
	sqlite3_bind_int(stmt, 1, u.id_user);
	sqlite3_bind_text(stmt, 2, u.username, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 3, u.contrasenya, -1, SQLITE_STATIC);
	sqlite3_bind_int(stmt, 4, u.tipo_user);
	resultado = sqlite3_step(stmt);
	if (resultado != SQLITE_DONE) {
		fprintf(stderr, "Error al insertar el usuario: %s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		exit(EXIT_FAILURE);
	}
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	logMessage("Usuario agregado correctamente.");
}
void agregarVehiculo(Vehiculo v){
	sqlite3* db = abrirBaseDatos();
	sqlite3_stmt *stmt;

	const char* consulta = "INSERT INTO Vehiculos (Id_vehiculo, Id_cliente, Num_seguro, Anyo_fabricacion, Matricula, Marca, Modelo, Id_color) VALUES (?, ?, ?, ?, ?, ?, ?, ?)";
	int resultado = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
	if (resultado != SQLITE_OK) {
		fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(EXIT_FAILURE);
	}
	sqlite3_bind_int(stmt, 1, v.id_vehiculo);
	sqlite3_bind_int(stmt, 2, v.id_cli);
	sqlite3_bind_text(stmt, 3, v.numSeguro, -1, SQLITE_STATIC);
	sqlite3_bind_int(stmt, 4, v.anyoFabricacion);
	sqlite3_bind_text(stmt, 5, v.matricula, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 6, v.marca, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 7, v.modelo, -1, SQLITE_STATIC);
	sqlite3_bind_int(stmt, 8, v.id_color);
	resultado = sqlite3_step(stmt);
	if (resultado != SQLITE_DONE) {
		fprintf(stderr, "Error al insertar el cliente: %s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		exit(EXIT_FAILURE);
	}
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	logMessage("Vehiculo agregado correctamente.");
}

//ELIMNAR
void eliminarCliente(int id){
    sqlite3* db = abrirBaseDatos();
    sqlite3_stmt *stmt;

    const char* consulta = "DELETE FROM Cliente WHERE Id_cliente = ?";
    int resultado = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
    if (resultado != SQLITE_OK) {
        fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }
    sqlite3_bind_int(stmt, 1, id);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    logMessage("Cliente eliminado correctamente.");
}


void eliminarEmpleado(int id){
    sqlite3* db = abrirBaseDatos();
    sqlite3_stmt *stmt;

    const char* consulta = "DELETE FROM Empleado WHERE Id_usuario = ?";
    int resultado = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
    if (resultado != SQLITE_OK) {
        fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }
    sqlite3_bind_int(stmt, 1, id);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    logMessage("Empleado eliminado correctamente.");
}
void eliminarInventario(int id){
    sqlite3* db = abrirBaseDatos();
    sqlite3_stmt *stmt;

    const char* consulta = "DELETE FROM Inventario WHERE Id_inventario = ?";
    int resultado = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
    if (resultado != SQLITE_OK) {
        fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }
    sqlite3_bind_int(stmt, 1, id);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    logMessage("Inventario eliminado correctamente.");
}

void eliminarRegistro(int id){
    sqlite3* db = abrirBaseDatos();
    sqlite3_stmt *stmt;

    const char* consulta = "DELETE FROM Registros WHERE Id_registro = ?";
    int resultado = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
    if (resultado != SQLITE_OK) {
        fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }
    sqlite3_bind_int(stmt, 1, id);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    logMessage("Registro eliminado correctamente.");
}

void eliminarTaller(int id){
    sqlite3* db = abrirBaseDatos();
    sqlite3_stmt *stmt;

    const char* consulta = "DELETE FROM Talleres WHERE Id_taller = ?";
    int resultado = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
    if (resultado != SQLITE_OK) {
        fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }
    sqlite3_bind_int(stmt, 1, id);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    logMessage("Taller eliminado correctamente.");
}

void eliminarTrabajo(int id){
    sqlite3* db = abrirBaseDatos();
    sqlite3_stmt *stmt;

    const char* consulta = "DELETE FROM Trabajo WHERE Id_trabajo = ?";
    int resultado = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
    if (resultado != SQLITE_OK) {
        fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }
    sqlite3_bind_int(stmt, 1, id);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    logMessage("Trabajo eliminado correctamente.");
}

void eliminarUsuario(int id){
    sqlite3* db = abrirBaseDatos();
    sqlite3_stmt *stmt;

    const char* consulta = "DELETE FROM Usuarios WHERE Id_usuario = ?";
    int resultado = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
    if (resultado != SQLITE_OK) {
        fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }
    sqlite3_bind_int(stmt, 1, id);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    logMessage("Usuario eliminado correctamente.");
}

void eliminarVehiculo(int id){
    sqlite3* db = abrirBaseDatos();
    sqlite3_stmt *stmt;

    const char* consulta = "DELETE FROM Vehiculos WHERE Id_vehiculo = ?";
    int resultado = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
    if (resultado != SQLITE_OK) {
        fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }
    sqlite3_bind_int(stmt, 1, id);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

//BUSCAR ID MAXIMO

int buscarIDMaxInventario(){
	sqlite3* db = abrirBaseDatos();
	sqlite3_stmt *stmt;

	int maxID=0;
	const char* consulta = "SELECT MAX(Id_inventario) FROM Inventario";
	int resultado = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
	if (resultado != SQLITE_OK) {
		fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(EXIT_FAILURE);
	}
	sqlite3_bind_int(stmt, 1, maxID);
	if (sqlite3_step(stmt) == SQLITE_ROW) {
		maxID = sqlite3_column_int(stmt, 0);

	}else{
		maxID = -1;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return maxID;
}

int buscarIDMaxRegistros(){
	sqlite3* db = abrirBaseDatos();
	sqlite3_stmt *stmt;

	int maxID=0;
	const char* consulta = "SELECT MAX(Id_registro) FROM Registros";
	int resultado = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
	if (resultado != SQLITE_OK) {
		fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(EXIT_FAILURE);
	}
	sqlite3_bind_int(stmt, 1, maxID);
	if (sqlite3_step(stmt) == SQLITE_ROW) {
		maxID = sqlite3_column_int(stmt, 0);

	}else{
		maxID = -1;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return maxID;

}

int buscarIDMaxTalleres(){
	sqlite3* db = abrirBaseDatos();
	sqlite3_stmt *stmt;

	int maxID=0;
	const char* consulta = "SELECT MAX(Id_taller) FROM Talleres";
	int resultado = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
	if (resultado != SQLITE_OK) {
		fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(EXIT_FAILURE);
	}
	sqlite3_bind_int(stmt, 1, maxID);
	if (sqlite3_step(stmt) == SQLITE_ROW) {
		maxID = sqlite3_column_int(stmt, 0);

	}else{
		maxID = -1;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return maxID;

}
int buscarIDMaxTrabajos(){
	sqlite3* db = abrirBaseDatos();
	sqlite3_stmt *stmt;

	int maxID=0;
	const char* consulta = "SELECT MAX(Id_trabajo) FROM Trabajo";
	int resultado = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
	if (resultado != SQLITE_OK) {
		fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(EXIT_FAILURE);
	}
	sqlite3_bind_int(stmt, 1, maxID);
	if (sqlite3_step(stmt) == SQLITE_ROW) {
		maxID = sqlite3_column_int(stmt, 0);

	}else{
		maxID = -1;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return maxID;

}

int buscarIDMaxUsuarios(){
	sqlite3* db = abrirBaseDatos();
	sqlite3_stmt *stmt;

	int maxID=0;
	const char* consulta = "SELECT MAX(Id_usuario) FROM Usuarios";
	int resultado = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
	if (resultado != SQLITE_OK) {
		fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(EXIT_FAILURE);
	}
	sqlite3_bind_int(stmt, 1, maxID);
	if (sqlite3_step(stmt) == SQLITE_ROW) {
		maxID = sqlite3_column_int(stmt, 0);

	}else{
		maxID = -1;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return maxID;
}
int buscarIDMaxVehiculos(){
	sqlite3* db = abrirBaseDatos();
	sqlite3_stmt *stmt;

	int maxID=0;
	const char* consulta = "SELECT MAX(Id_Vehiculo) FROM Vehiculos";
	int resultado = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
	if (resultado != SQLITE_OK) {
		fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(EXIT_FAILURE);
	}
	sqlite3_bind_int(stmt, 1, maxID);
	if (sqlite3_step(stmt) == SQLITE_ROW) {
		maxID = sqlite3_column_int(stmt, 0);

	}else{
		maxID = -1;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return maxID;
}

//BUSCAR
int buscarClientes(int id) {
    int enc = 0;

    sqlite3* db = abrirBaseDatos();
    sqlite3_stmt *stmt;
    const char* consulta = "SELECT Id_usuario FROM Cliente WHERE Id_usuario=?";
    int resultado = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
    if (resultado != SQLITE_OK) {
        fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    sqlite3_bind_int(stmt, 1, id);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        enc = 1;
    } else {
        enc = -1;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return enc;
}

int buscarEmpleados(int id){
	int enc = 0;
	sqlite3* db = abrirBaseDatos();
	sqlite3_stmt *stmt;
	const char* consulta = "SELECT Id_usuario FROM Empleado WHERE Id_usuario=?";
	int resultado = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
	if (resultado != SQLITE_OK) {
		fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(EXIT_FAILURE);
	}

	sqlite3_bind_int(stmt, 1, id);

	if (sqlite3_step(stmt) == SQLITE_ROW) {
		enc = 1;
	} else {
		enc = -1;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return enc;
}
int buscarInventario(int id){
	int enc = 0;

	sqlite3* db = abrirBaseDatos();
	sqlite3_stmt *stmt;
	const char* consulta = "SELECT Id_inventario FROM Inventario WHERE Id_inventario=?";
	int resultado = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
	if (resultado != SQLITE_OK) {
		fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(EXIT_FAILURE);
	}

	sqlite3_bind_int(stmt, 1, id);

	if (sqlite3_step(stmt) == SQLITE_ROW) {
		enc = 1;
	} else {
		enc = -1;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return enc;
}


int buscarRegistros(int id){
	int enc = 0;

	sqlite3* db = abrirBaseDatos();
	sqlite3_stmt *stmt;
	const char* consulta = "SELECT Id_registro FROM Registros WHERE Id_registro=?";
	int resultado = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
	if (resultado != SQLITE_OK) {
		fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(EXIT_FAILURE);
	}

	sqlite3_bind_int(stmt, 1, id);

	if (sqlite3_step(stmt) == SQLITE_ROW) {
		enc = 1;
	} else {
		enc = -1;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return enc;
}


int buscarTalleres(int id){
	int enc = 0;

	sqlite3* db = abrirBaseDatos();
	sqlite3_stmt *stmt;
	const char* consulta = "SELECT Id_taller FROM Talleres WHERE Id_taller=?";
	int resultado = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
	if (resultado != SQLITE_OK) {
		fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(EXIT_FAILURE);
	}

	sqlite3_bind_int(stmt, 1, id);

	if (sqlite3_step(stmt) == SQLITE_ROW) {
		enc = 1;
	} else {
		enc = -1;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return enc;
}
int buscarTrabajos(int id){
	int enc = 0;

	sqlite3* db = abrirBaseDatos();
	sqlite3_stmt *stmt;
	const char* consulta = "SELECT Id_trabajo FROM Trabajo WHERE Id_trabajo=?";
	int resultado = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
	if (resultado != SQLITE_OK) {
		fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(EXIT_FAILURE);
	}

	sqlite3_bind_int(stmt, 1, id);

	if (sqlite3_step(stmt) == SQLITE_ROW) {
		enc = 1;
	} else {
		enc = -1;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return enc;
}
int buscarUsuarios(int id){
	int enc = 0;

	sqlite3* db = abrirBaseDatos();
	sqlite3_stmt *stmt;
	const char* consulta = "SELECT Id_usuario FROM Usuarios WHERE Id_usuario=?";
	int resultado = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
	if (resultado != SQLITE_OK) {
		fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(EXIT_FAILURE);
	}

	sqlite3_bind_int(stmt, 1, id);

	if (sqlite3_step(stmt) == SQLITE_ROW) {
		enc = 1;
	} else {
		enc = -1;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return enc;
}
int buscarVehiculos(int id){
	int enc = 0;

	sqlite3* db = abrirBaseDatos();
	sqlite3_stmt *stmt;
	const char* consulta = "SELECT Id_vehiculo FROM Vehiculos WHERE Id_vehiculo=?";
	int resultado = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
	if (resultado != SQLITE_OK) {
		fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(EXIT_FAILURE);
	}

	sqlite3_bind_int(stmt, 1, id);

	if (sqlite3_step(stmt) == SQLITE_ROW) {
		enc = 1;
	} else {
		enc = -1;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return enc;
}

//BUSCAR ESPECIFICO
int buscarUsuarioInicio(char* usernameIntro, char*contrasenyaIntro){
	Usuario u;
	int enc = 0;

	sqlite3* db = abrirBaseDatos();
	sqlite3_stmt *stmt;
	const char* consulta = "SELECT Id_usuario, Username, Contrasenya, Tipo_usuario FROM Usuarios WHERE Username=? AND Contrasenya=?";
	int resultado = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
	if (resultado != SQLITE_OK) {
		fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(EXIT_FAILURE);
	}

	sqlite3_bind_text(stmt, 1, usernameIntro, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, contrasenyaIntro, -1, SQLITE_STATIC);

	if (sqlite3_step(stmt) == SQLITE_ROW) {
		u.id_user = sqlite3_column_int(stmt, 0);
		sprintf(u.username, "%s", sqlite3_column_text(stmt, 1));
		sprintf(u.contrasenya, "%s", sqlite3_column_text(stmt, 2));
		u.tipo_user = sqlite3_column_int(stmt, 3);

		enc = 1;
	} else {
		enc = -1;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return enc;
}

int buscarUsuarioPorDNI(char* dni){
	int id_cli=-1;
	sqlite3* db = abrirBaseDatos();
	sqlite3_stmt *stmt;

	const char* consulta = "SELECT Id_usuario FROM Cliente WHERE DNI=?";
	int resultado = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
	if (resultado != SQLITE_OK) {
		fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(EXIT_FAILURE);
	}
	sqlite3_bind_text(stmt, 1, dni, -1, SQLITE_STATIC);
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		id_cli = sqlite3_column_int(stmt, 0);
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return id_cli;
}
int buscarDNIexiste(char* dni){
	int enc;
	sqlite3* db = abrirBaseDatos();
	sqlite3_stmt *stmt;

	const char* consulta = "SELECT Id_usuario FROM Cliente WHERE DNI=?";
	int resultado = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
	if (resultado != SQLITE_OK) {
		fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(EXIT_FAILURE);
	}


	sqlite3_bind_text(stmt, 1, dni, -1, SQLITE_STATIC);
	if (sqlite3_step(stmt) == SQLITE_ROW) {

		enc=1;
	}else{
		enc=-1;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return enc;
}

int buscarPorMatricula(char* matricula){
	int enc = 0;

	sqlite3* db = abrirBaseDatos();
	sqlite3_stmt *stmt;
	const char* consulta = "SELECT Id_vehiculo FROM Vehiculos WHERE Matricula = ?";
	int resultado = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
	if (resultado != SQLITE_OK) {
		fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(EXIT_FAILURE);
	}

	sqlite3_bind_text(stmt, 1, matricula, -1, SQLITE_STATIC);

	if (sqlite3_step(stmt) == SQLITE_ROW) {
		enc = 1;
	} else {
		enc = -1;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return enc;
}

//MOSTRAR ESPECIFICO
void mostrarVehiculoDeCliente(SOCKET comm_socket, char *sendBuff, char* recvBuff, int id_cli){
	sqlite3* db = abrirBaseDatos();
	sqlite3_stmt *stmt;

	const char* consulta = "SELECT Id_vehiculo, Id_cliente, Num_seguro, Anyo_fabricacion, Matricula, Marca, Modelo, Id_color FROM Vehiculos WHERE Id_cliente=?";
	int resultado = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
	if (resultado != SQLITE_OK) {
		fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(EXIT_FAILURE);
	}
	sqlite3_bind_int(stmt, 1, id_cli);
	//printf("Vehiculos de %d:\n",id_cli);
	int resul = sqlite3_step(stmt);
	while (resul == SQLITE_ROW) {
		Vehiculo v;
		v.id_vehiculo = sqlite3_column_int(stmt, 0);
		v.id_cli = sqlite3_column_int(stmt, 1);
		strcpy(v.numSeguro,sqlite3_column_text(stmt, 2));
		v.anyoFabricacion = sqlite3_column_int(stmt, 3);
		strcpy(v.matricula,sqlite3_column_text(stmt, 4));
		strcpy(v.marca,sqlite3_column_text(stmt, 5));
		strcpy(v.modelo, sqlite3_column_text(stmt, 6));
		v.id_color = sqlite3_column_int(stmt, 7);
		//printf("ID Vehiculo: %d, ID Cliente: %d, Numero seguro: %s, Año fabricacion: %d, Matricula: %s, Marca: %s, Modelo: %s, ID Color: %d\n", id_vehiculo, id_cliente, num_seguro, anyo_fabricacion, matricula, marca, modelo, id_color);

		sprintf(sendBuff, "%d", v.id_vehiculo);
		send(comm_socket, sendBuff, strlen(sendBuff), 0);

		sprintf(sendBuff, "%d", v.id_cli);
		send(comm_socket, sendBuff, strlen(sendBuff), 0);

		sprintf(sendBuff, "%s", v.numSeguro);
		send(comm_socket, sendBuff, strlen(sendBuff), 0);

		sprintf(sendBuff, "%d", v.anyoFabricacion);
		send(comm_socket, sendBuff, strlen(sendBuff), 0);

		sprintf(sendBuff, "%s", v.matricula);
		send(comm_socket, sendBuff, strlen(sendBuff), 0);

		sprintf(sendBuff, "%s", v.marca);
		send(comm_socket, sendBuff, strlen(sendBuff), 0);

		sprintf(sendBuff, "%s", v.modelo);
		send(comm_socket, sendBuff, strlen(sendBuff), 0);

		sprintf(sendBuff, "%d", v.id_color);
		send(comm_socket, sendBuff, strlen(sendBuff), 0);
		resul = sqlite3_step(stmt);

	}
	sprintf(sendBuff,  "FIN");
	send(comm_socket, sendBuff, strlen(sendBuff), 0);

	sqlite3_finalize(stmt);
	sqlite3_close(db);
}

Vehiculos mostrarVehiculosDeCliente2(int id_cli) {
    sqlite3* db = abrirBaseDatos();
    sqlite3_stmt *stmt;
    Vehiculos vehiculos = { NULL, 0 };

    const char* consulta = "SELECT Id_vehiculo, Id_cliente, Num_seguro, Anyo_fabricacion, Matricula, Marca, Modelo, Id_color FROM Vehiculos WHERE Id_cliente=?";
    int resultado = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
    if (resultado != SQLITE_OK) {
        fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    sqlite3_bind_int(stmt, 1, id_cli);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        vehiculos.vehiculos = realloc(vehiculos.vehiculos, (vehiculos.count + 1) * sizeof(Vehiculo));
        Vehiculo* v = &vehiculos.vehiculos[vehiculos.count];

        v->id_vehiculo = sqlite3_column_int(stmt, 0);
        v->id_cli = sqlite3_column_int(stmt, 1);
        strcpy(v->numSeguro, (const char*)sqlite3_column_text(stmt, 2));
        v->anyoFabricacion = sqlite3_column_int(stmt, 3);
        strcpy(v->matricula, (const char*)sqlite3_column_text(stmt, 4));
        strcpy(v->marca, (const char*)sqlite3_column_text(stmt, 5));
        strcpy(v->modelo, (const char*)sqlite3_column_text(stmt, 6));
        v->id_color = sqlite3_column_int(stmt, 7);

        vehiculos.count++;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return vehiculos;
}

void mostrarTrabajosPorClienteYRegistro(SOCKET comm_socket, char *sendBuff, char* recvBuff, int id_usuario) {
    sqlite3* db = abrirBaseDatos(); // Abre la base de datos
    sqlite3_stmt *stmt;

    const char* consulta = "SELECT t.Id_trabajo, t.Id_vehiculo, t.Id_empleado, t.Fecha, t.Descripcion "
                           "FROM Trabajo t "
                           "JOIN Registros r ON t.Id_trabajo = r.Id_trabajo "
                           "WHERE r.Id_cliente = ?";

    int resultado = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
    if (resultado != SQLITE_OK) {
        fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
        cerrarBaseDatos(db);
        exit(EXIT_FAILURE);
    }

    sqlite3_bind_int(stmt, 1, id_usuario);

    int cantidadTrabajos = 0;
    int resul = sqlite3_step(stmt);
    while (resul == SQLITE_ROW) {
        Trabajo trabajo;
        trabajo.id_trabajo = sqlite3_column_int(stmt, 0);
        trabajo.id_vehiculo = sqlite3_column_int(stmt, 1);
        trabajo.id_emp = sqlite3_column_int(stmt, 2);

        const unsigned char* fecha = sqlite3_column_text(stmt, 3);
        const unsigned char* descripcion = sqlite3_column_text(stmt, 4);

        if (fecha) {
            snprintf(trabajo.fecha_tra, sizeof(trabajo.fecha_tra), "%s", fecha);
        } else {
            trabajo.fecha_tra[0] = '\0'; // Asegúrate de que esté vacío si es NULL
        }

        if (descripcion) {
            snprintf(trabajo.descripcion_tra, sizeof(trabajo.descripcion_tra), "%s", descripcion);
        } else {
            trabajo.descripcion_tra[0] = '\0'; // Asegúrate de que esté vacío si es NULL
        }

        // Envía cada campo individualmente
        sprintf(sendBuff, "%d", trabajo.id_trabajo);
        send(comm_socket, sendBuff, strlen(sendBuff), 0);

        sprintf(sendBuff, "%d", trabajo.id_vehiculo);
        send(comm_socket, sendBuff, strlen(sendBuff), 0);

        sprintf(sendBuff, "%d", trabajo.id_emp);
        send(comm_socket, sendBuff, strlen(sendBuff), 0);

        sprintf(sendBuff, "%s", trabajo.fecha_tra);
        send(comm_socket, sendBuff, strlen(sendBuff), 0);

        sprintf(sendBuff, "%s", trabajo.descripcion_tra);
        send(comm_socket, sendBuff, strlen(sendBuff), 0);

        cantidadTrabajos++;
        resul = sqlite3_step(stmt);
    }

    if (cantidadTrabajos == 0) {
        printf("No se encontraron trabajos para el cliente con ID %d.\n", id_usuario);
    }

    printf("Ha llegado a su fin\n");  // Solo una vez aquí

    // Enviar la señal de FIN al cliente
    sprintf(sendBuff, "FIN");
    send(comm_socket, sendBuff, strlen(sendBuff), 0);

    sqlite3_finalize(stmt);
    cerrarBaseDatos(db);
}


//DEVOLVER ESPECIFICO
int devolverTipoUsuario(char* usernameIntro){
	int tipo_usu;
	sqlite3* db = abrirBaseDatos();
	sqlite3_stmt *stmt;

	const char* consulta = "SELECT Tipo_usuario FROM Usuarios WHERE Username=?";
	int resultado = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
	if (resultado != SQLITE_OK) {
		fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(EXIT_FAILURE);
	}
	sqlite3_bind_text(stmt, 1, usernameIntro, -1, SQLITE_STATIC);
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		tipo_usu = sqlite3_column_int(stmt, 0);
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return tipo_usu;
}

int devolverIDusu(char* usernameIntro, char*contrasenyaIntro){
	int id_usu;
	sqlite3* db = abrirBaseDatos();
	sqlite3_stmt *stmt;

	const char* consulta = "SELECT Id_usuario FROM Usuarios WHERE Username=? AND Contrasenya=?";
	int resultado = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
	if (resultado != SQLITE_OK) {
		fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(EXIT_FAILURE);
	}
	sqlite3_bind_text(stmt, 1, usernameIntro, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, contrasenyaIntro, -1, SQLITE_STATIC);
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		id_usu = sqlite3_column_int(stmt, 0);
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);



	return id_usu;
}



char* devolverTaller(int id) {
    sqlite3* db = abrirBaseDatos();
    char* nombre_taller = NULL;

    char consulta[100];  // Declaración de un buffer para almacenar la consulta SQL
    sprintf(consulta, "SELECT Nombre FROM Talleres WHERE Id_taller=%d", id);

    sqlite3_stmt *stmt;
    int resultado = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
    if (resultado != SQLITE_OK) {
        fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
        logMessage("Error al preparar la consulta");
        cerrarBaseDatos(db);
        exit(EXIT_FAILURE);
    }

    resultado = sqlite3_step(stmt);
    if (resultado == SQLITE_ROW) {
        const unsigned char* nombre = sqlite3_column_text(stmt, 0);
        nombre_taller = strdup((const char*)nombre);
        if (nombre_taller == NULL) {
            fprintf(stderr, "Error: No se pudo asignar memoria.\n");
            logMessage("Error: No se pudo asignar memoria.");
            sqlite3_finalize(stmt);
            cerrarBaseDatos(db);
            exit(EXIT_FAILURE);
        }
    }

    sqlite3_finalize(stmt);
    cerrarBaseDatos(db);

    return nombre_taller;
}

int devolverIDporMatricula(char* matricula){
	int id;
	sqlite3* db = abrirBaseDatos();
	sqlite3_stmt *stmt;
	const char* consulta = "SELECT Id_vehiculo FROM Vehiculos WHERE Matricula = ?";
	int resultado = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
	if (resultado != SQLITE_OK) {
		fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(EXIT_FAILURE);
	}

	sqlite3_bind_text(stmt, 1, matricula, -1, SQLITE_STATIC);

	while (sqlite3_step(stmt) == SQLITE_ROW) {
		id = sqlite3_column_int(stmt, 0);

	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);


	return id;
}

Cliente* devolverClientePorID(int id_cli) {
    sqlite3* db = abrirBaseDatos();
    sqlite3_stmt *stmt;
    Cliente* cli = malloc(sizeof(Cliente));
    if (cli == NULL) {
        fprintf(stderr, "Error: No se pudo asignar memoria para el cliente.\n");
        exit(EXIT_FAILURE);
    }

    const char* consulta = "SELECT Id_usuario, Nombre, Apellido, DNI, Email, Telefono FROM Cliente WHERE Id_usuario=?";
    int resultado = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
    if (resultado != SQLITE_OK) {
        fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        free(cli);
        exit(EXIT_FAILURE);
    }

    sqlite3_bind_int(stmt, 1, id_cli);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        cli->id_user = id_cli;
        snprintf(cli->nombre_cli, sizeof(cli->nombre_cli), "%s", sqlite3_column_text(stmt, 1));
        snprintf(cli->apellido_cli, sizeof(cli->apellido_cli), "%s", sqlite3_column_text(stmt, 2));
        snprintf(cli->dni_cli, sizeof(cli->dni_cli), "%s", sqlite3_column_text(stmt, 3));
        snprintf(cli->email_cli, sizeof(cli->email_cli), "%s", sqlite3_column_text(stmt, 4));
        cli->tlf_cli = sqlite3_column_int(stmt, 5);
    } else {
        free(cli);
        cli = NULL;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return cli;
}
