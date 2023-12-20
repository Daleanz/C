// iTz_DILAN

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdbool.h>

struct Persona {
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
int c;

struct Indice {
    char email[100];
    long posicion;  // posición en el archivo principal
};

FILE *abrirArchivo(const char *nombreArchivo, const char *modo) {
    FILE *archivo = fopen(nombreArchivo, modo);

    if (archivo == NULL) {
        perror("No se pudo abrir el archivo.");
        exit(EXIT_FAILURE);
    }
    return archivo;
}

void cerrarArchivo(FILE *archivo) {
    fclose(archivo);
}
void cuentaRegresiva(int valor){
    if(valor == 1){
        for(int i = 3; i > 0; i --){
            printf("Buscando ...\n");
            sleep(1);
        }
        printf("\n");
    }

    if(valor == 2){
        for(int i = 3; i > 0 ; i --){
            printf("Modificando ...\n");
            sleep(1);
        }
        printf("\n");
    }

    if(valor == 3){
        for(int i = 3; i > 0 ; i --){
            printf("Cargando registros ...\n");
            sleep(1);
        }
        printf("\n");
    }

    if(valor == 4){
        for(int i = 3; i > 0 ; i --){
            printf("Cargando registro ...\n");
            sleep(1);
        }
        printf("\n");
    }
}

void agregarAlIndice(const char *email, long posicion, FILE *indice) {
    struct Indice nuevoRegistro;
    strcpy(nuevoRegistro.email, email);
    nuevoRegistro.posicion = posicion;

    fseek(indice, 0, SEEK_END);
    fwrite(&nuevoRegistro, sizeof(struct Indice), 1, indice);
}

long buscarPosicionPorEmail(const char *email, FILE *indice) {
    struct Indice indiceRegistro;

    fseek(indice, 0, SEEK_SET);
    while (fread(&indiceRegistro, sizeof(struct Indice), 1, indice) == 1) {
        if (strcmp(indiceRegistro.email, email) == 0) {
            return indiceRegistro.posicion;
        }
    }

    return -1;
}

void ingresarRegistroPersona(FILE *archivo, FILE *indice) {
    struct Persona persona;
    while ((c = getchar()) != '\n' && c != EOF);

    printf("--------------------------");
    printf("| INGRESAR REGISTRO PERSONA |");
    printf("--------------------------\n");

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

    long nuevaPosicion = ftell(archivo);
    fwrite(&persona, sizeof(struct Persona), 1, archivo);

    agregarAlIndice(persona.email, nuevaPosicion, indice);
}

void buscarRegistroPersona(FILE *archivo, FILE *indice) {
    char emailBuscar[100];

    printf("-------------------------");
    printf("| BUSCAR REGISTRO PERSONA |");
    printf("-------------------------\n");
    printf("Ingrese el email a buscar: ");
    scanf("%s", emailBuscar);

    long posicion = buscarPosicionPorEmail(emailBuscar, indice);

    cuentaRegresiva(1);
    if (posicion != -1) {
        fseek(archivo, posicion, SEEK_SET);
        struct Persona personaEncontrada;
        fread(&personaEncontrada, sizeof(struct Persona), 1, archivo);

        printf("Persona encontrada: %s %s\n", personaEncontrada.nombre, personaEncontrada.apellido);
        printf("---------------------------------------------------\n");
    } else {
        printf("Persona NO encontrada para el email: %s\n", emailBuscar);
        printf("---------------------------------------------------\n");
    }
}

// Función para modificar un registro de persona por email y campo específico
void modificarRegistroPersona(FILE *archivo, FILE *indice) {
    char emailModificar[100];
    int campoModificar = 0;

    printf("--------------------");
    printf("| MODIFICAR REGISTRO |");
    printf("--------------------\n");
    printf("Ingrese el email del registro a modificar: ");
    scanf("%s", emailModificar);

    long posicion = buscarPosicionPorEmail(emailModificar, indice);

    if (posicion != -1) {
        fseek(archivo, posicion, SEEK_SET);
        struct Persona personaModificar;
        fread(&personaModificar, sizeof(struct Persona), 1, archivo);

        printf("\n(1) Nombre, (2) Apellido, (3) Empresa, (4) Direccion, (5) Ciudad, (6) Pais, (7) Provincia\n");
        printf("(8) Codigo Postal, (9) Primer Telefono, (10) Segundo Telefono, (11) Email, (12) Web\n");
        printf("Ingrese el campo a modificar: ");
        scanf("%d", &campoModificar);

        // Utilizar estructura switch para manejar diferentes campos
        switch (campoModificar) {
            case 1:
                while ((c = getchar()) != '\n' && c != EOF);

                printf("Ingrese el nuevo nombre: ");

                fgets(personaModificar.nombre, sizeof(personaModificar.nombre), stdin);
                personaModificar.nombre[strcspn(personaModificar.nombre, "\n")] = '\0';

                break;
            case 2:
                while ((c = getchar()) != '\n' && c != EOF);

                printf("Ingrese el nuevo apellido: ");

                fgets(personaModificar.apellido, sizeof(personaModificar.apellido), stdin);
                personaModificar.apellido[strcspn(personaModificar.apellido, "\n")] = '\0';

                break;
            case 3:
                while ((c = getchar()) != '\n' && c != EOF);

                printf("Ingrese la nueva empresa: ");

                fgets(personaModificar.empresa, sizeof(personaModificar.empresa), stdin);
                personaModificar.empresa[strcspn(personaModificar.empresa, "\n")] = '\0';

                break;
            // Puedes agregar más casos para otros campos
            case 4:
                while ((c = getchar()) != '\n' && c != EOF);
                printf("Ingrese la nueva direccion: ");

                fgets(personaModificar.direccion, sizeof(personaModificar.direccion), stdin);
                personaModificar.direccion[strcspn(personaModificar.direccion, "\n")] = '\0';

                break;
            case 5:
                while ((c = getchar()) != '\n' && c != EOF);
                printf("Ingrese la nueva ciudad: ");

                fgets(personaModificar.ciudad, sizeof(personaModificar.ciudad), stdin);
                personaModificar.ciudad[strcspn(personaModificar.ciudad, "\n")] = '\0';

                break;
            case 6:
                while ((c = getchar()) != '\n' && c != EOF);
                printf("Modificar pais: ");

                fgets(personaModificar.pais, sizeof(personaModificar.pais), stdin);
                personaModificar.pais[strcspn(personaModificar.pais, "\n")] = '\0';

                break;
            case 7:
                while ((c = getchar()) != '\n' && c != EOF);
                printf("Modificar provincia: ");

                fgets(personaModificar.provincia, sizeof(personaModificar.provincia), stdin);
                personaModificar.provincia[strcspn(personaModificar.provincia, "\n")] = '\0';

                break;
            case 8:
                while ((c = getchar()) != '\n' && c != EOF);
                printf("Modificar codigo postal: ");

                fgets(personaModificar.codigoPostal, sizeof(personaModificar.codigoPostal), stdin);
                personaModificar.codigoPostal[strcspn(personaModificar.codigoPostal, "\n")] = '\0';

                break;
            case 9:
                while ((c = getchar()) != '\n' && c != EOF);
                printf("Modificar primer telefono: ");

                fgets(personaModificar.telefono1, sizeof(personaModificar.telefono1), stdin);
                personaModificar.telefono1[strcspn(personaModificar.telefono1, "\n")] = '\0';

                break;
            case 10:
                while ((c = getchar()) != '\n' && c != EOF);
                printf("Modificar segundo telefono: ");

                fgets(personaModificar.telefono2, sizeof(personaModificar.telefono2), stdin);
                personaModificar.telefono2[strcspn(personaModificar.telefono2, "\n")] = '\0';

                break;
            case 11:
                while ((c = getchar()) != '\n' && c != EOF);
                printf("Modificar email: ");

                fgets(personaModificar.email, sizeof(personaModificar.email), stdin);
                personaModificar.email[strcspn(personaModificar.email, "\n")] = '\0';

                break;
            case 12:
                while ((c = getchar()) != '\n' && c != EOF);
                printf("Modificar web: ");

                fgets(personaModificar.web, sizeof(personaModificar.web), stdin);
                personaModificar.web[strcspn(personaModificar.web, "\n")] = '\0';

                break;
            default:
                printf("ERROR, campo no valido.\n");
                return;
        }

        fseek(archivo, posicion, SEEK_SET);
        fwrite(&personaModificar, sizeof(struct Persona), 1, archivo);

        cuentaRegresiva(2);
        printf("Registro de persona modificado con EXITO.\n\n");
        printf("---------------------------------------------------\n");
    } else {
        cuentaRegresiva(2);
        printf("Persona NO encontrada para el email: %s\n", emailModificar);
        printf("---------------------------------------------------\n");
    }
}

// Función para mostrar únicamente el registro de una persona por email
void mostrarRegistroPersona(FILE *archivo, FILE *indice) {
    char emailMostrar[100];
    printf("---------------------------");
    printf("| MOSTRAR REGISTRO PERSONA |");
    printf("--------------------------\n");
    printf("Ingrese el email del registro a mostrar: ");
    scanf("%s", emailMostrar);

    long posicion = buscarPosicionPorEmail(emailMostrar, indice);

    if (posicion != -1) {
        cuentaRegresiva(4);
        fseek(archivo, posicion, SEEK_SET);
        struct Persona personaMostrar;
        fread(&personaMostrar, sizeof(struct Persona), 1, archivo);

        printf("Registro de persona:\n");

        printf("Nombre y Apellido: %s %s\n", personaMostrar.nombre, personaMostrar.apellido);
        printf("Direccion: %s, %s, %s, %s\n", personaMostrar.direccion, personaMostrar.ciudad, personaMostrar.provincia, personaMostrar.codigoPostal);
        printf("Pais: %s\n", personaMostrar.pais);
        printf("Telefonos: (1) %s, (2) %s\n", personaMostrar.telefono1, personaMostrar.telefono2);
        printf("Empresa: %s\n", personaMostrar.empresa);
        printf("Email: %s\n", personaMostrar.email);
        printf("Web: %s\n", personaMostrar.web);
        printf("---------------------------------------------------\n");
        // Puedes continuar mostrando los demás campos de la persona
    } else {
        printf("Persona no encontrada para el email: %s\n", emailMostrar);
        printf("---------------------------------------------------\n");
    }
}

// Función para mostrar todos los registros de personas
void mostrarRegistrosPersonas(FILE *archivo, FILE *indice) {
    fseek(indice, 0, SEEK_SET);
    struct Indice indiceRegistro;

    int contador = 1;
    cuentaRegresiva(3);
    while (fread(&indiceRegistro, sizeof(struct Indice), 1, indice) == 1) {
        struct Persona personaMostrar;
        fread(&personaMostrar, sizeof(struct Persona), 1, archivo);

        printf("REGISTRO DE PERSONA %d\n", contador);

        printf("Nombre y Apellido: %s %s\n", personaMostrar.nombre, personaMostrar.apellido);
        printf("Direccion: %s, %s, %s, %s\n", personaMostrar.direccion, personaMostrar.ciudad, personaMostrar.provincia, personaMostrar.codigoPostal);
        printf("Pais: %s\n", personaMostrar.pais);
        printf("Telefonos: (1) %s, (2) %s\n", personaMostrar.telefono1, personaMostrar.telefono2);
        printf("Empresa: %s\n", personaMostrar.empresa);
        printf("Email: %s\n", personaMostrar.email);
        printf("Web: %s\n", personaMostrar.web);

        printf("\n");
        printf("---------------------------------------------------\n");
        contador ++;
    }
}

// Funcion: mostrarMenu
// Parametros: ninguno
// Descripcion: mostrar el menu de opciones al usuario.
void mostrarMenu() {
    printf("1. Ingresar nuevo registro de persona\n");
    printf("2. Buscar registro de persona (por email)\n");
    printf("3. Modificar registro de persona (por email)\n");
    printf("4. Mostrar registro de persona (por email)\n");
    printf("5. Mostrar todos los registros de personas\n");
    printf("0. Salir\n");
    printf("Ingrese la opción deseada: ");
}

// Funcion: main
// Parametros: ninguno.
// Descripcion: encargada de ejecutar el programa, aqui se abren y crean los dos archivos a utilizar,
// mostrara el menu y se utilizaran las funciones declaradas anteriormente mediante una estructura
// repetitiva while haciendo uso de una estructura de control switch.
int main() {
    // se crean 2 punteros de tipo FILE, para poder acceder, abrir y/o crear los archivos binarios,
    // registro_personas.bin
    // indice_email_persona.bin
    FILE *archivo = abrirArchivo("registro_personas.bin", "wb+");  // Archivo principal
    FILE *indice = abrirArchivo("indice_email_personas.bin", "wb+");   // Archivo de índice

    int opcion;
    do {
        mostrarMenu();
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                ingresarRegistroPersona(archivo, indice);
                break;
            case 2:
                buscarRegistroPersona(archivo, indice);
                break;
            case 3:
                modificarRegistroPersona(archivo, indice);
                break;
            case 4:
                mostrarRegistroPersona(archivo, indice);
                break;
            case 5:
                mostrarRegistrosPersonas(archivo, indice);
                break;
            case 0:
                printf("SALIENDO DEL PROGRAMA....\n");
                break;
            default:
                printf("Opción no válida. Inténtelo de nuevo.\n");
        }
    } while (opcion != 0);

    // Se cierran los archivos despues de hacer uso de ellos.
    cerrarArchivo(archivo);
    cerrarArchivo(indice);

    return 0;
}
