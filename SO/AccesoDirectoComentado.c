// iTz_DiLAN

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdbool.h>

// Se hace uso de struct para poder almacenar todos los datos (atributos) de una persona.
struct Persona{
    char nombre[100];
    char apellido[100];
    char empresa[100];
    char direccion[100];
    char ciudad[100];
    char pais[100];
    char provincia[100];
    char codigoPostal[100];
    char telefono1[100];
    char telefono2[100];
    char email[100];
    char web[100];
};

// Funcion que se encarga de hacer una cuenta regresiva, es utilizado en otras funciones.
// Tiene la finalidad de forma estetica solamente.
void cuentaRegresiva(int valor){
    // Para valor = 1, es para ser utilizada por la funcion buscarPorEmail().
    if(valor == 1){
        for(int i = 3; i > 0; i --){
            printf("Buscando ...\n");
            sleep(1);
        }
        printf("\n");
    }

    // Para valor = 2, es para ser utilizada por la funcion modificarRegistroPersona().
    if(valor == 2){
        for(int i = 3; i > 0 ; i --){
            printf("Cargando ...\n");
            sleep(1);
        }
        printf("\n");
    }
}

// Función: abrirArchivo
// Descripción: Abre un archivo con el nombre especificado y el modo dado.
// Parámetros:
// - nombreArchivo: Nombre del archivo a abrir.
// - modo: Modo de apertura del archivo (por ejemplo, "r" para lectura, "w" para escritura).
// Retorna:
// - FILE*: Puntero al archivo abierto.
FILE *abrirArchivo(const char *nombreArchivo, const char *modo){
    // Intenta abrir el archivo con el nombre y el modo especificado en los parametros.
    FILE *archivo = fopen(nombreArchivo, modo);

    // Verifica si se abrio correctamente el archivo.
    if(archivo == NULL){
        // En el caso de que no se pueda abrir, imprime un mensaje de error.
        perror("No se pudo abrir el archivo.");
        // Termina el programa donde indica el fallo en la ejecucion.
        exit(EXIT_FAILURE);
    }
    return archivo;
}

// Funcion: cerrarArchivo
// Descripcion: cierra un archivo especificado por parametro.
// Parametros:
// - archivo: es el nombre del archivo.
void cerrarArchivo(FILE *archivo){
    // Se cierra el archivo especificado.
    fclose(archivo);
}
// Función: agregarPersona
// Descripción: Escribe la información de una persona en un archivo.
// Parámetros:
// - archivo: Puntero al archivo en el que se escribirá la información.
// - persona: Puntero a la estructura de datos que contiene la información de la persona.
void agregarPersona(FILE *archivo, struct Persona *persona) {
    // Utiliza la función fwrite para escribir la información de la persona en el archivo.
    // Parámetros de fwrite:
    //   - persona: Puntero a los datos que se van a escribir.
    //   - sizeof(struct Persona): Tamaño en bytes de la estructura Persona.
    //   - 1: Número de elementos que se van a escribir.
    //   - archivo: Puntero al archivo en el que se escribirán los datos.
    fwrite(persona, sizeof(struct Persona), 1, archivo);
}

// Función: buscarPorEmail
// Descripción: Busca una persona en un archivo por su dirección de correo electrónico.
// Parámetros:
// - archivo: Puntero al archivo en el que se realizará la búsqueda.
// - email: Dirección de correo electrónico de la persona que se está buscando.
void buscarPorEmail(FILE *archivo, const char *email) {
    // Estructura para almacenar temporalmente la información de una persona.
    struct Persona persona;

    // Mueve el puntero de posición en el archivo al principio (inicio del archivo).
    fseek(archivo, 0, SEEK_SET);

    // Imprime una cuenta regresiva, asumiendo que la función está definida.
    printf("\n");
    cuentaRegresiva(1);

    // Itera sobre las personas en el archivo.
    while (fread(&persona, sizeof(struct Persona), 1, archivo) == 1) {
        // Compara el email de la persona actual con el email buscado.
        if (strcmp(persona.email, email) == 0) {
            // Si se encuentra la persona, imprime su información y termina la función.
            printf("Persona con email '%s' SI se encontró.\n", persona.email);
            printf("Nombre: %s %s\n", persona.nombre, persona.apellido);
            printf("Email: %s\n", persona.email);
            printf("-----------------------------\n");
            return;
        }
    }

    // Si el bucle termina y no se encuentra la persona, imprime un mensaje indicando eso.
    printf("Persona con email '%s' NO encontrada.\n", email);
    printf("\n");
    printf("-----------------------------\n");
}

// Función: modificarRegistroPersona
// Descripción: Modifica un registro de persona en un archivo basado en su dirección de correo electrónico.
// Parámetros:
// - archivo: Puntero al archivo en el que se realizará la modificación.
// - email: Dirección de correo electrónico de la persona cuyo registro se va a modificar.
// - campo: Número que representa el campo a modificar.
// - nuevoValor: Nuevo valor que se utilizará para actualizar el campo seleccionado.
void modificarRegistroPersona(FILE *archivo, const char *email, int campo, const char *nuevoValor) {
    // Estructura para almacenar temporalmente la información de una persona.
    struct Persona persona;

    // Mueve el puntero de posición en el archivo al principio (inicio del archivo).
    fseek(archivo, 0, SEEK_SET);

    cuentaRegresiva(2);
    // Itera sobre las personas que estan en el archivo.
    while (fread(&persona, sizeof(struct Persona), 1, archivo) == 1) {
        // Compara el email de la persona actual con el email buscado.
        if (strcmp(persona.email, email) == 0) {
            // Modificar la información de la persona
            fseek(archivo, -sizeof(struct Persona), SEEK_CUR);  // Retroceder para sobrescribir el registro

            // Realiza la modificación en función del campo seleccionado.
            switch (campo) {
                case 1: // nombre
                    strncpy(persona.nombre, nuevoValor, sizeof(persona.nombre) - 1);
                    break;
                case 2: // apellido
                    strncpy(persona.apellido, nuevoValor, sizeof(persona.apellido) - 1);
                    break;
                case 3: // empresa
                    strncpy(persona.empresa, nuevoValor, sizeof(persona.empresa) - 1);
                    break;
                case 4: // direccion
                    strncpy(persona.direccion, nuevoValor, sizeof(persona.direccion) - 1);
                    break;
                case 5: // ciudad
                    strncpy(persona.ciudad, nuevoValor, sizeof(persona.ciudad) - 1);
                    break;
                case 6: // pais
                    strncpy(persona.pais, nuevoValor, sizeof(persona.pais) - 1);
                    break;
                case 7: // provincia
                    strncpy(persona.provincia, nuevoValor, sizeof(persona.provincia) - 1);
                    break;
                case 8: // codigo postal
                    strncpy(persona.codigoPostal, nuevoValor, sizeof(persona.codigoPostal) - 1);
                    break;
                case 9: // primer telefono
                    strncpy(persona.telefono1, nuevoValor, sizeof(persona.telefono1) - 1);
                    break;
                case 10: // segundo telefono
                    strncpy(persona.telefono2, nuevoValor, sizeof(persona.telefono2) - 1);
                    break;
                case 11: // email
                    strncpy(persona.email, nuevoValor, sizeof(persona.email) - 1);
                    break;
                case 12: // web
                    strncpy(persona.web, nuevoValor, sizeof(persona.web) - 1);
                    break;
                default:
                    // Imprime un mensaje si el campo no es válido.
                    printf("Campo no válido.\n");
                    return;
            }
            // Escribe la información actualizada en el archivo.
            fwrite(&persona, sizeof(struct Persona), 1, archivo);
            printf("Registro de persona modificado con éxito.\n");
            printf("-----------------------------\n");
            return;
        }
    }
    // Si el bucle termina y no se encuentra la persona, imprime un mensaje indicando eso.
    printf("Persona con email '%s' no encontrada. No se realizó ninguna modificación.\n", email);
}

// Función: mostrarRegistroPersonaPorEmail
// Descripción: Muestra la información de una persona en el archivo basado en su dirección de correo electrónico.
// Parámetros:
// - archivo: Puntero al archivo del que se leerá la información.
// - email: Dirección de correo electrónico de la persona cuyo registro se va a mostrar.
void mostrarRegistroPersonaPorEmail(FILE *archivo, const char *email) {
    struct Persona persona;

    fseek(archivo, 0, SEEK_SET);  // Ir al principio del archivo

    while (fread(&persona, sizeof(struct Persona), 1, archivo) == 1) {
        if (strcmp(persona.email, email) == 0) {
            // Persona encontrada, mostrar el registro
            printf("Nombre: %s %s\n", persona.nombre, persona.apellido);
            printf("Email: %s\n", persona.email);
            printf("Compañía: %s\n", persona.empresa);
            printf("Dirección: %s, %s, %s, %s, %s\n", persona.direccion, persona.ciudad, persona.pais, persona.provincia, persona.codigoPostal);
            printf("Teléfono 1: %s\n", persona.telefono1);
            printf("Teléfono 2: %s\n", persona.telefono2);
            printf("Sitio web: %s\n", persona.web);
            printf("-----------------------------\n");
            return;  // Salir del bucle después de mostrar el registro
        }
    }
    // Si el bucle termina y no se encuentra la persona, imprime un mensaje indicando eso.
    printf("Persona con email '%s' NO encontrada.\n", email);
}

// Función: mostrarRegistrosPersonas
// Descripción: Muestra todos los registros de personas almacenados en el archivo.
// Parámetros:
// - archivo: Puntero al archivo del que se leerá la información.
void mostrarRegistrosPersonas(FILE *archivo) {
    struct Persona persona;

    fseek(archivo, 0, SEEK_SET);  // Ir al principio del archivo
    
    // Contador que permite identificar cada registro persona.
    int contador = 1;
    while (fread(&persona, sizeof(struct Persona), 1, archivo) == 1) {
        // Mostrar el registro de la persona
        printf("Registro de persona %d:\n", contador);
        printf("Nombre: %s %s\n", persona.nombre, persona.apellido);
        printf("Email: %s\n", persona.email);
        printf("Compañía: %s\n", persona.empresa);
        printf("Dirección: %s, %s, %s, %s, %s\n", persona.direccion, persona.ciudad, persona.pais, persona.provincia, persona.codigoPostal);
        printf("Teléfono 1: %s\n", persona.telefono1);
        printf("Teléfono 2: %s\n", persona.telefono2);
        printf("Sitio web: %s\n", persona.web);
        printf("-----------------------------\n");
        // Incrementa el contador para el siguiente registro.
        contador = contador + 1;
    }
}

int main(){
    // Nombre del archivo donde se almacenarán los registros de personas.
    const char *nombreArchivo = "registro_persona.bin";
    // Abre el archivo en modo lectura / escritura binaria (wb+)
    FILE *archivo = abrirArchivo(nombreArchivo, "wb+");

    // Variables para controlar el flujo del programa.
    bool flag = true;
    int opcion = 0;
    char email[50];

    // Bucle while (principal) del programa.
    while (flag) {
        // Menu de opciones para el usuario.
        printf("-------------- Menú ---------------\n\n");
        printf("(1) Agregar Registro Persona\n");
        printf("(2) Modificar Registro Persona (por Email)\n");
        printf("(3) Buscar Persona (por Email)\n");
        printf("(4) Mostrar Registro Persona (por Email)\n");
        printf("(5) Mostrar Registros Personas\n");
        printf("(0) Salir\n");
        printf("Ingrese una opción: ");
        scanf("%d", &opcion);

        struct Persona persona;
        switch (opcion) {
            case 1:
                // Opción para agregar un nuevo registro de persona.
                // Se solicita al usuario que ingrese información y se utiliza la función agregarPersona.
                // Cada campo se obtiene con fgets para manejar correctamente la entrada del usuario.
                printf("----------------------------");
                printf("\n| Agregar Registro Persona |\n");
                printf("----------------------------\n");

                // Limpia el buffer de entrada.
                int c;
                while ((c = getchar()) != '\n' && c != EOF);

                // Solicitar información al usuario y almacenarla en la estructura persona.
                // Se utiliza fgets para manejar correctamente los espacios en blanco.
                printf("---> Nombre: ");
                fgets(persona.nombre, sizeof(persona.nombre), stdin);
                persona.nombre[strcspn(persona.nombre, "\n")] = '\0';

                printf("---> Apellido: ");
                fgets(persona.apellido, sizeof(persona.apellido), stdin);
                persona.apellido[strcspn(persona.apellido, "\n")] = '\0';

                printf("---> Empresa: ");
                fgets(persona.empresa, sizeof(persona.empresa), stdin);
                persona.empresa[strcspn(persona.empresa, "\n")] = '\0';

                printf("---> Direccion: ");
                fgets(persona.direccion, sizeof(persona.direccion), stdin);
                persona.direccion[strcspn(persona.direccion, "\n")] = '\0';

                printf("---> Ciudad: ");
                fgets(persona.ciudad, sizeof(persona.ciudad), stdin);
                persona.ciudad[strcspn(persona.ciudad, "\n")] = '\0';

                printf("---> Pais: ");
                fgets(persona.pais, sizeof(persona.pais), stdin);
                persona.pais[strcspn(persona.pais, "\n")] = '\0';

                printf("---> Provincia: ");
                fgets(persona.provincia, sizeof(persona.provincia), stdin);
                persona.provincia[strcspn(persona.provincia, "\n")] = '\0';

                printf("---> Codigo Postal: ");
                fgets(persona.codigoPostal, sizeof(persona.codigoPostal), stdin);
                persona.codigoPostal[strcspn(persona.codigoPostal, "\n")] = '\0';

                printf("---> Primer Telefono: ");
                fgets(persona.telefono1, sizeof(persona.telefono1), stdin);
                persona.telefono1[strcspn(persona.telefono1, "\n")] = '\0';

                printf("---> Segundo Telefono: ");
                fgets(persona.telefono2, sizeof(persona.telefono2), stdin);
                persona.telefono2[strcspn(persona.telefono2, "\n")] = '\0';

                printf("---> Email: ");
                fgets(persona.email, sizeof(persona.email), stdin);
                persona.email[strcspn(persona.email, "\n")] = '\0';

                printf("---> Web: ");
                fgets(persona.web, sizeof(persona.web), stdin);
                persona.web[strcspn(persona.web, "\n")] = '\0';

                // Luego, se utiliza la función agregarPersona para agregar la nueva persona al archivo.
                agregarPersona(archivo, &persona);
                break;

            case 2:
                // Opción para modificar un registro de persona por email y campo específico.
                // Se solicita al usuario que ingrese el email, el campo y el nuevo valor.
                // Luego, se utiliza la función modificarRegistroPersona para realizar la modificación.
                printf("------------------------------------------");
                printf("\n| Modificar Registro Persona (por Email) |\n");
                printf("------------------------------------------\n");
                
                // Solicitar la informacion al usuario.
                printf("\n---> Ingrese el email de la persona a modificar: ");
                scanf("%s", email);

                // Limpia el buffer de entrada.
                while ((c = getchar()) != '\n' && c != EOF);
                int campo = 0;
                
                printf("Campo 1: Nombre\nCampo 2: Apellido\nCampo 3: Empresa\nCampo 4: Direccion\nCampo 5: Ciudad");
                printf("\nCampo 6: Pais\nCampo 7: Provincia\nCampo 8: Codigo Postal\nCampo 9: Primer Telefono\nCampo 10: Segundo Telefono");
                printf("\nCampo 11: Email\nCampo 12: Web");

                // Solicita el campo al usuario.
                printf("\n---> Ingrese el campo del registro a modificar: ");
                scanf("%d", &campo);

                char nuevo[100];
                // Solicita el nuevo valor al usuario.
                printf("\n---> Ingrese el nuevo valor: ");
                getchar();
                fgets(nuevo, sizeof(nuevo), stdin);
                nuevo[strcspn(nuevo, "\n")] = '\0';

                // Realizar la modificación utilizando la función modificarRegistroPersona.
                modificarRegistroPersona(archivo, email, campo, nuevo);
                break;

            case 3:
                // Opción para buscar una persona por email y mostrar su información.
                // Se solicita al usuario que ingrese el email y se utiliza la función buscarPorEmail.
                printf("------------------------------");
                printf("\n| Buscar Persona (por Email) |\n");
                printf("------------------------------\n");

                // Solicita la informacion al usuario.
                printf("\n---> Ingrese el email de la persona a buscar: ");
                scanf("%s", email);

                // Limpia el buffer de entrada.
                while ((c = getchar()) != '\n' && c != EOF);

                // Realizar la búsqueda utilizando la función buscarPorEmail.
                buscarPorEmail(archivo, email);
                break;
            case 4:
                // Opción para mostrar la información de una persona por email.
                // Se solicita al usuario que ingrese el email y se utiliza la función mostrarRegistroPersonaPorEmail.
                printf("----------------------------------------");
                printf("\n| Mostrar Registro Persona (por Email) |\n");
                printf("----------------------------------------\n");

                // Solicitar email al usuario.
                printf("\n---> Ingrese el email de la persona a mostrar: ");
                scanf("%s", email);

                // Limpia el buffer de entrada.
                while ((c = getchar()) != '\n' && c != EOF);
                cuentaRegresiva(2);

                // Realizar la muestra utilizando la función mostrarRegistroPersonaPorEmail.
                cuentaRegresiva(2);
                mostrarRegistroPersonaPorEmail(archivo, email);
                break;

            case 5:
                // Opción para mostrar todos los registros de personas en el archivo.
                // Utiliza la función mostrarRegistrosPersonas.
                printf("------------------------------");
                printf("\n| Mostrar Registros Personas |\n");
                printf("------------------------------\n");

                // Limpia el bufffer de entrada.
                while ((c = getchar()) != '\n' && c != EOF);
                cuentaRegresiva(2);

                // Mostrar todos los registros utilizando la función mostrarRegistrosPersonas.
                mostrarRegistrosPersonas(archivo);
                break;

            case 0:
                // Opcion para salir del programa.
                printf("SALIENDO...");
                flag = false;
                break;
            default:
                // Opcion invalida.
                printf("\nOpcion invalida.\n");
        }
    }

    // Cerrar el archivo despues de su uso.
    cerrarArchivo(archivo);

    return 0;
}
