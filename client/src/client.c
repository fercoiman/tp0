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
	
	

	logger = iniciar_logger();
	


	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"
	log_info(logger,"Hola! Soy un log");

	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();
	ip = config_get_string_value(config,"IP");
	puerto = config_get_string_value(config,"PUERTO");
	valor = config_get_string_value(config,"CLAVE");

	log_info(logger,"valores de la config >>> IP=%s PUERTO=%s CLAVE= %s", ip,puerto,valor);
	// log_info(logger,"valor leido: %s", puerto);
	// log_info(logger,"valor leido: %s", valor);
	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'

	// Loggeamos el valor de config


	/* ---------------- LEER DE CONSOLA ---------------- */

	leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él
		
	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	//  if(connect(conexion, server_info->ai_addr, server_info->ai_addrlen) != 0) {
	//  	perror("NO SE HA PODIDO CONECTAR AL SERVIDOR");
	//  	exit(EXIT_FAILURE);
	//  }

	// Enviamos al servidor el valor de CLAVE como mensaje
	
	enviar_mensaje(valor,conexion);
	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	//t_log* nuevo_logger;
	t_log* nuevo_logger = log_create("client.log","client.proc",1,LOG_LEVEL_INFO);
	
	if(nuevo_logger == NULL){
			perror("!! Se ha detectado un error en la creacion del log !!");
			exit(EXIT_FAILURE);
	}
	
	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config = config_create("tp0-client.config");
	if(nuevo_config == NULL){
		perror("No se pudo leer el archivo de configuracion del cliente");
		exit(EXIT_FAILURE);
	}
	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	// La primera te la dejo de yapa
	leido = readline("> ");
	log_info(logger,"LEIDO DESDE CONSOLA>>> %s",leido);
	// El resto, las vamos leyendo y logueando hasta recibir un string vacío
	size_t largo;

	while(strcmp(leido,"")!= 0){
		free(leido);
		leido = readline("> ");
		largo = strlen(leido);
	
		if( largo==0 ){ 
			log_info(logger,"SE INGRESO UNA LINEA VACIA! SALIENDO!!\n");
			break;
		}
			log_info(logger,"LEIDO DESDE CONSOLA>>> %s",leido);
			
	}
	// ¡No te olvides de liberar las lineas antes de regresar!
	free(leido);
}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete;

	// Leemos y esta vez agregamos las lineas al paquete


	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
	if(logger != NULL){
		log_destroy(logger);
	}
	if(config != NULL){
		config_destroy(config);
		}



}
