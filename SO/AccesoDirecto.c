// iTz_DiLAN

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdbool.h>

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
            printf("Cargando ...\n");
            sleep(1);
        }
        printf("\n");
    }
}

FILE *abrirArchivo(const char *nombreArchivo, const char *modo){
    FILE *archivo = fopen(nombreArchivo, modo);

    if(archivo == NULL){
        perror("No se pudo abrir el archivo.");
        exit(EXIT_FAILURE);
    }
    return archivo;
}

void cerrarArchivo(FILE *archivo){
    fclose(archivo);
}

void agregarPersona(FILE *archivo, struct Persona *persona){
    fwrite(persona, sizeof(struct Persona), 1, archivo);
}

void buscarPorEmail(FILE *archivo, const char *email){
    struct Persona persona;

    fseek(archivo, 0, SEEK_SET);

    printf("\n");
    cuentaRegresiva(1);
    while(fread(&persona, sizeof(struct Persona), 1, archivo) == 1){
        if(strcmp(persona.email, email) == 0){
            printf("Persona con email '%s' SI se encontro.\n", persona.email);
            printf("Nombre: %s %s\n", persona.nombre, persona.apellido);
            printf("Email: %s\n", persona.email);
            printf("-----------------------------\n");
            return;
        }
    }

    printf("Persona con email '%s' NO encontrada.\n", persona.email);
    printf("\n");
    printf("-----------------------------\n");
}


void modificarRegistroPersona(FILE *archivo, const char *email, int campo, const char *nuevoValor) {
    struct Persona persona;

    fseek(archivo, 0, SEEK_SET);  // Ir al principio del archivo

    cuentaRegresiva(2);
    while (fread(&persona, sizeof(struct Persona), 1, archivo) == 1) {
        if (strcmp(persona.email, email) == 0) {
            // Modificar la información de la persona
            fseek(archivo, -sizeof(struct Persona), SEEK_CUR);  // Retroceder para sobrescribir el registro

            switch (campo) {
                case 1: // firstName
                    strncpy(persona.nombre, nuevoValor, sizeof(persona.nombre) - 1);
                    break;
                case 2: // lastName
                    strncpy(persona.apellido, nuevoValor, sizeof(persona.apellido) - 1);
                    break;
                case 3: // company
                    strncpy(persona.empresa, nuevoValor, sizeof(persona.empresa) - 1);
                    break;
                case 4:
                    strncpy(persona.direccion, nuevoValor, sizeof(persona.direccion) - 1);
                    break;
                case 5:
                    strncpy(persona.ciudad, nuevoValor, sizeof(persona.ciudad) - 1);
                    break;
                case 6:
                    strncpy(persona.pais, nuevoValor, sizeof(persona.pais) - 1);
                    break;
                case 7:
                    strncpy(persona.provincia, nuevoValor, sizeof(persona.provincia) - 1);
                    break;
                case 8:
                    strncpy(persona.codigoPostal, nuevoValor, sizeof(persona.codigoPostal) - 1);
                    break;
                case 9:
                    strncpy(persona.telefono1, nuevoValor, sizeof(persona.telefono1) - 1);
                    break;
                case 10:
                    strncpy(persona.telefono2, nuevoValor, sizeof(persona.telefono2) - 1);
                    break;
                case 11:
                    strncpy(persona.email, nuevoValor, sizeof(persona.email) - 1);
                    break;
                case 12:
                    strncpy(persona.web, nuevoValor, sizeof(persona.web) - 1);
                    break;
                default:
                    printf("Campo no válido.\n");
                    return;
            }

            fwrite(&persona, sizeof(struct Persona), 1, archivo);
            printf("Registro de persona modificado con éxito.\n");
            printf("-----------------------------\n");
            return;
        }
    }

    printf("Persona con email '%s' no encontrada. No se realizó ninguna modificación.\n", email);
}

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

    printf("Persona con email '%s' NO encontrada.\n", email);
}

void mostrarRegistrosPersonas(FILE *archivo) {
    struct Persona persona;

    fseek(archivo, 0, SEEK_SET);  // Ir al principio del archivo
    
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
        contador = contador + 1;
    }
}

int main(){
    const char *nombreArchivo = "registro_persona.bin";
    FILE *archivo = abrirArchivo(nombreArchivo, "wb+");

    bool flag = true;
    int opcion = 0;
    char email[50];


    while (flag) {
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
                printf("----------------------------");
                printf("\n| Agregar Registro Persona |\n");
                printf("----------------------------\n");
                int c;
                while ((c = getchar()) != '\n' && c != EOF);

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

                agregarPersona(archivo, &persona);
                break;

            case 2:
                printf("------------------------------------------");
                printf("\n| Modificar Registro Persona (por Email) |\n");
                printf("------------------------------------------\n");
                printf("\n---> Ingrese el email de la persona a modificar: ");
                scanf("%s", email);

                while ((c = getchar()) != '\n' && c != EOF);
                int campo = 0;
                
                printf("Campo 1: Nombre\nCampo 2: Apellido\nCampo 3: Empresa\nCampo 4: Direccion\nCampo 5: Ciudad");
                printf("\nCampo 6: Pais\nCampo 7: Provincia\nCampo 8: Codigo Postal\nCampo 9: Primer Telefono\nCampo 10: Segundo Telefono");
                printf("\nCampo 11: Email\nCampo 12: Web");

                printf("\n---> Ingrese el campo del registro a modificar: ");
                scanf("%d", &campo);

                char nuevo[100];
                printf("\n---> Ingrese el nuevo valor: ");
                getchar();
                fgets(nuevo, sizeof(nuevo), stdin);
                nuevo[strcspn(nuevo, "\n")] = '\0';
                modificarRegistroPersona(archivo, email, campo, nuevo);
                break;

            case 3:
                printf("------------------------------");
                printf("\n| Buscar Persona (por Email) |\n");
                printf("------------------------------\n");
                printf("\n---> Ingrese el email de la persona a buscar: ");
                scanf("%s", email);
                while ((c = getchar()) != '\n' && c != EOF);
                buscarPorEmail(archivo, email);
                break;

            case 4:
                printf("----------------------------------------");
                printf("\n| Mostrar Registro Persona (por Email) |\n");
                printf("----------------------------------------\n");
                printf("\n---> Ingrese el email de la persona a mostrar: ");
                scanf("%s", email);
                while ((c = getchar()) != '\n' && c != EOF);
                cuentaRegresiva(2);
                mostrarRegistroPersonaPorEmail(archivo, email);
                break;

            case 5:
                printf("------------------------------");
                printf("\n| Mostrar Registros Personas |\n");
                printf("------------------------------\n");
                while ((c = getchar()) != '\n' && c != EOF);
                cuentaRegresiva(2);
                mostrarRegistrosPersonas(archivo);
                break;

            case 0:
                printf("SALIENDO...");
                flag = false;
                break;
            default:
                printf("\nOpcion invalida.\n");
        }
    }
    cerrarArchivo(archivo);

    return 0;
}
