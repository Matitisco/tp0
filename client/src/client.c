#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */


	
	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"

	logger = iniciar_logger();

	log_info( logger, "Hola! Soy un log");


	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();

	if (config == NULL) {
    // ¡No se pudo crear el config!
    // Terminemos el programa
		terminar_programa(conexion,logger,config);
	}

	

	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'
	
	ip=config_get_string_value(config,"IP");
	puerto=config_get_string_value(config,"PUERTO");


	// Loggeamos el valor de config

	char* clave = config_get_string_value(config, "CLAVE");

	log_info(logger,("%c",clave));

	/* ---------------- LEER DE CONSOLA ---------------- */

	//leer_consola(logger);


	
	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor, devuleve el socket del cliente
	conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje

	enviar_mensaje( ("%c",clave),conexion);

	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}








t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;

	nuevo_logger = log_create("../client/tp0.log", "prueba", true, LOG_LEVEL_INFO);

	return nuevo_logger;
}

t_config* iniciar_config(void)
{	
	t_config* nuevo_config;

	nuevo_config = config_create("../client/cliente.config");

		

	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	// La primera te la dejo de yapa
	leido = readline("> ");
	log_info(logger,leido);

	// El resto, las vamos leyendo y logueando hasta recibir un string vacío

	// ¡No te olvides de liberar las lineas antes de regresar!
	while(leido[0] != '\0'){
		leido = readline("> ");
		log_info(logger,leido);
	}


}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete;

	// Leemos y esta vez agregamos las lineas al paquete

	paquete = crear_paquete();

	leido = readline("> ");
	agregar_a_paquete(paquete, leido, strlen(leido)+1);

	while(leido[0] != '\0'){
		leido = readline("> ");
		agregar_a_paquete(paquete, leido, strlen(leido)+1);		//le sumo 1 por el caracter centinela '\0'
	}

	//envio el paquete
	enviar_paquete(paquete,conexion);

	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	eliminar_paquete(paquete);
	
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{	
	log_destroy(logger);
	config_destroy(config);
	liberar_conexion(conexion);
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
}
