// iTz_DiLAN

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdbool.h>

// Estructura que permite un "tipo de contenedor" para agrupar la informacion relacionada a una persona de manera conveniente.
// Cada campo tiene una longitud maxima de "100" caracteres.
// Se utiliza con el fin de hacer mas facil la manipulacion y gestion de estos datos en el programa.
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

// Variable global: es usada en la estructura repetitiva (while) para eliminar el buffer de entrada.
int c;

// Estructura que almacena el (email) con una longitud de "100" caracteres, ademas de tener la (posicion) de tipo long.
// Con esto se busca que mediante esta estructura se pueda llevar a cabo como un mecanismo de indexación, donde se asocia
// un (email) con una posicion en el archivo, con el fin de poder acceder eficientemente al registro en el archivo principal utilizando
// el (email).
struct Indice {
    char email[100];
    long posicion;  
};

// Funcion encargada de abrir un archivo, donde por parametros se pasa el "nombre del archivo" y el "modo de apertura".
// Es una funcion que devuelve un (puntero) de tipo "FILE", ya que se esta trabajando con archivos.
FILE *abrirArchivo(const char *nombreArchivo, const char *modo) {
    // Hace uso de la funcion "fopen" para abrir el archivo, el resultado es un (puntero FILE) que se almacena en la variable (archivo).
    FILE *archivo = fopen(nombreArchivo, modo);

    if (archivo == NULL) { // Verifica si la apertura del archivo fue correcta, compara el puntero (archivo) con "NULL".
                           // En el caso de que NO se cumpla, imprime un mensaje haciendo uso de "perror", la que indicara el error en consola.
        perror("No se pudo abrir el archivo.");
        // El programa se cierra directamente haciendo uso de la funcion (exit) con codigo "EXIT_FAILURE", donde esto indica un
        // fallo en la operacion.
        exit(EXIT_FAILURE);
    }
    return archivo;
}

// Funcion encargada de cerrar un archivo haciendo uso de la funcion (fclose).
void cerrarArchivo(FILE *archivo) {
    fclose(archivo);
}

// Funcion encargada de generar una cuenta regresiva, para cada funcion que la necesite.
// Donde:
//  (1) Buscar Persona.
//  (2) Modificar Registro.
//  (3) Mostrar Registro Persona.
//  (4) Mostrar Registros Personas.
// Con finalidad unicamente estetica.
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

// Funcion encargada de agregar un registro asociada a un indice en un archivo.
// Paramtros:
// - email: representa el email que sera agregado al indice del archivo.
// - posicion: posicion en el archivo original asociada a esta direccion (email).
// - indice: puntero al archivo (indice) donde se almacenara la informacion.
void agregarAlIndice(const char *email, long posicion, FILE *indice) {
    // Estructura denominada (nuevoRegistro) la cual almacena la informacion que sera agregada al indice.
    struct Indice nuevoRegistro;

    //El (email) ingresado como argumento se copiara en el (email) de la estructura "nuevoRegistro", haciendo uso de la funcion (strcpy).
    strcpy(nuevoRegistro.email, email);
    // La posicion pasada por argumento se le asigna a (posicion) de la estructura "nuevoRegistro".
    nuevoRegistro.posicion = posicion;

    // Esta funcion lo que hace es mover el puntero de posicion del archivo (indice) al final del archivo, lo prepara para 
    // agregar un nuevo registro al final.
    //
    // parametros de fsekk:
    // - indice: puntero del archivo al cual se le ajusta la posicion, en este caso archivo (indice).
    // 0: es cero, porque se quiere ubicar el puntero directamente al final del archivo.
    // SEEK_END: indica que el desplazamiento se calcula desde el final del archivo.
    //
    // NOTA:Tambien se tiene.
    // - SEEK_SET: el desplazamiento se calcula desde el inicio del archivo.
    // - SEEK_CUR: el desplazamiento se calcula desde la posicion actual del puntero.
    fseek(indice, 0, SEEK_END);
    // Con la funcion (fwrite) escribira el registro en el archivo (indice).
    // parametros funcion (fwrite):
    //- &nuevoRegistro: proporciona la direccion de memoria del objeto (nuevoRegistro).
    //- sizeof(struct Indice): especifica el tamaño de cada elemento que se va a escribir en bytes, con esto se obtiene
    // ademas el tamaño de la estructura (Indice).
    // La funcion (sizeof) devuelve el tamaño en bytes.
    // - 1: especifica el numero de elementos que se van a escribir, en este caso es solo un elemento de tipo (struct Indice).
    // - indice: puntero al archivo (indice) donde se realizara la escritura.
    fwrite(&nuevoRegistro, sizeof(struct Indice), 1, indice);
}

// Funcion encargada de buscar la posicion asociada al (email) en el archivo (indice).
long buscarPosicionPorEmail(const char *email, FILE *indice) {
    // Se declara una estructura llamada (indiceRegistro) que almacenara los regristros leidos del archivo indice.
    struct Indice indiceRegistro;

    // Aqui cambia la posicion del puntero, con SEEK_SET esta diciendo que la busqueda comience desde el principio del archivo.
    fseek(indice, 0, SEEK_SET);
    // Este bucle (while) leera cada registro del archivo (indice).
    // Funcion (fread): lee un bloque de datos desde el archivo y avanza el puntero de posicion.
    // - &indiceRegistro: direccion de memoria donde se almacenaran los datos.
    // - sizeof(struct Indice): tamañao de cada elemento que se va a leer.
    // - 1: numero de elementos que se intentaran leer.
    // - indice: puntero al archivo desde donde se leen los datos.
    while (fread(&indiceRegistro, sizeof(struct Indice), 1, indice) == 1) {
        // verifica si la cantidad de elementos leidos por (fread) es igual a (1).
        if (strcmp(indiceRegistro.email, email) == 0) {
            // Compara el correo del registro actual con el correo que se esta buscandom, haciendo uso de la funcion (strcmp).
            // Cuando (strcmp) encuentra una coincidencia quiere decir que se encontro el (email) buscado.
            return indiceRegistro.posicion;
            // Finalmente se retorna la posicion asociada a ese (email).
        }
    }

    return -1;
    // retorna -1: cuando no se encontro el (email) buscado.
}

// Funcion encargada de almacenar los datos de una persona que seran ingresados por teclado, se pasa el puntero del archivo principal y 
// el puntero del archivo (indice).
// En el archivo principal se guardaran los registros de las personas.
// En el archivo (indice) se almacenaran los (email), lo cual es la clave para tener un acceso mas rapido despues a los registros.
void ingresarRegistroPersona(FILE *archivo, FILE *indice) {
    // Estructura donde se almacenaran los datos ingresados desde el teclado por el usuario.
    struct Persona persona;
    // Limpia el buffer de entrada, ya que lee una entrada estandar hasta encontrar un (salto de linea) o (final del archivo).
    while ((c = getchar()) != '\n' && c != EOF);

    printf("--------------------------");
    printf("| INGRESAR REGISTRO PERSONA |");
    printf("--------------------------\n");

    printf("---> Nombre: ");
    // (fgets) permite leer una linea completa desde la entrada estandar (stdin) que representa el teclado, y va almacenarlo
    // en el campo (nombre) de la estructura (persona).
    // - persona.nombre: es el destino donde se almacenara la cadena leida.
    // - sizeof(persona.nombre): asegura que el tamaño maximo leido no sobrepase el tamaño definido en el campo (nombre).
    // - (strcspn): busca el caracter de salto de linea y lo reemplazara por el caracter nulo.
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

    // Funcion (ftell) permite obtener la posicion actual en el archivo principal, y este se almacena en (nuevaPosicion).
    long nuevaPosicion = ftell(archivo);
    // (fwrite) escribira la estructura (persona) en el archivo principal.
    fwrite(&persona, sizeof(struct Persona), 1, archivo);

    // Se agrega al archivo (indice) la direccion (email) y la posicion asociada a la nueva persona ingresada.
    agregarAlIndice(persona.email, nuevaPosicion, indice);
}

// Funcion encargada de buscar el registro de la persona, haciendo uso del archivo principal donde se almacena el registro y tambien 
// haciendo uso del archivo (indice) para hacer una busqueda eficiente solo por el correo y el indice asociado.
void buscarRegistroPersona(FILE *archivo, FILE *indice) {
    // Se declara para el (email) que sera ingresado por el usuario.
    char emailBuscar[100];

    printf("-------------------------");
    printf("| BUSCAR REGISTRO PERSONA |");
    printf("-------------------------\n");
    printf("Ingrese el email a buscar: ");
    scanf("%s", emailBuscar);

    // Lama a la funcion (buscarPosicionPorEmail()), para obtener la posicion asociada al correo electronico ingresado por el usuario en el
    // archivo (indice).
    long posicion = buscarPosicionPorEmail(emailBuscar, indice);

    cuentaRegresiva(1);
    // Se verifica que el valor retornado por la funcion sea distinto de (-1), lo que indica que se encontro una coincidencia.
    if (posicion != -1) {
        // Mueve la posicion del puntero en el archivo principal, a la nueva posicion que retorna (buscarPosicionPorEmail()).
        fseek(archivo, posicion, SEEK_SET);
        // Se declara una estructura Persona llamada (personaEncontrada) la que almacenara la informacion del registro leido desde
        // el archivo principal.
        struct Persona personaEncontrada;
        // Lee la informacion de la persona desde el archivo principal en la estructura (personaEncontrada).
        fread(&personaEncontrada, sizeof(struct Persona), 1, archivo);

        printf("Persona encontrada: %s %s\n", personaEncontrada.nombre, personaEncontrada.apellido);
        printf("---------------------------------------------------\n");
    } else {
        printf("Persona NO encontrada para el email: %s\n", emailBuscar);
        printf("---------------------------------------------------\n");
    }
}

// Función para modificar un registro de persona por email y campo específico
// CONTINUAR COMENTANDO DESDE AQUI.
// Funcion encargada de modificar la informacion especifica por el usuario, hace uso del puntero al archivo principal y del puntero al
// archivo (indice).
void modificarRegistroPersona(FILE *archivo, FILE *indice) {
    // Se declara emailModificar que es la variable donde se almacena el correo ingresado desde teclado por el usuario.
    char emailModificar[100];
    // Vairable (campoModificar) permite cual de todos los campos de la informacion de (Persona) se modificara.
    int campoModificar = 0;

    printf("--------------------");
    printf("| MODIFICAR REGISTRO |");
    printf("--------------------\n");
    printf("Ingrese el email del registro a modificar: ");
    scanf("%s", emailModificar);

    // posicion almacenara el valor retornado por la funcion (buscarPosicionPorEmail()).
    long posicion = buscarPosicionPorEmail(emailModificar, indice);

    // Verifica que posicion tenga un valor diferente a (-1), lo que indica que se encontro una coincidencia.
    if (posicion != -1) {
        // Movera la posicion del puntero en el archivo principal, a la posicion indicada por la funcion (buscarPosicionPorEmail()).
        fseek(archivo, posicion, SEEK_SET);
        // Se declara una estructura "Persona" denominada (personaModificar) que almacenara la informacion del campo que sera modificado.
        struct Persona personaModificar;
        // Leera la infomacion de la persona desde el archivo principal.
        fread(&personaModificar, sizeof(struct Persona), 1, archivo);

        // Mostrar los campos al usuario.
        printf("\n(1) Nombre, (2) Apellido, (3) Empresa, (4) Direccion, (5) Ciudad, (6) Pais, (7) Provincia\n");
        printf("(8) Codigo Postal, (9) Primer Telefono, (10) Segundo Telefono, (11) Email, (12) Web\n");
        printf("Ingrese el campo a modificar: ");
        scanf("%d", &campoModificar);

        // Se utiliza la estructura de control (switch) donde usara la variable (campoModificar) para identificar que caso ejecutar.
        switch (campoModificar) {
            case 1:
                // Limpiar buffer de entrada.
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
                // Cado default mostrara el siguiente mensaje cuando el campo ingresado sea invalido.
                printf("ERROR, campo no valido.\n");
                return;
        }

        // Se posiciona el puntero del archivo principal al inicio del registro que se esta modificando.
        fseek(archivo, posicion, SEEK_SET);
        // (fwrite) escribe la informacion de (personaModifica) en el archivo principal, lo que hace la actualizacion de la informacion
        // ingresada por el usuario.
        fwrite(&personaModificar, sizeof(struct Persona), 1, archivo);

        cuentaRegresiva(2);
        // En el caso de modificar el campo se muestra el siguiente mensaje.
        printf("Registro de persona modificado con EXITO.\n\n");
        printf("---------------------------------------------------\n");
    } else {
        cuentaRegresiva(2);
        // De caso contrario se mostrara el siguiente mensjae.
        printf("Persona NO encontrada para el email: %s\n", emailModificar);
        printf("---------------------------------------------------\n");
    }
}

//Funcion que se encarga de mostrar unicamente el registro de una persona, recibe como parametros al puntero del archivo principal y el
//puntero del archivo (indice).
void mostrarRegistroPersona(FILE *archivo, FILE *indice) {
    // emailMostrar: almacenara el (email) ingresado por el usuario.
    char emailMostrar[100];
    printf("---------------------------");
    printf("| MOSTRAR REGISTRO PERSONA |");
    printf("--------------------------\n");
    printf("Ingrese el email del registro a mostrar: ");
    scanf("%s", emailMostrar);

    // posicion: almacena el valor (posicion) retornado por la funcion (buscarPosicionPorEmail()).
    long posicion = buscarPosicionPorEmail(emailMostrar, indice);

    // Verifica que la posicion sea distinto de (-1) indicando que se encontro el (email) en el archivo (indice).
    if (posicion != -1) {
        cuentaRegresiva(4);
        // Movera el puntero de posicion en el archivo principal, a la posicion indicada por la funcion (buscarPosicionPorEmail()).
        fseek(archivo, posicion, SEEK_SET);
        // Se declara una estructura "Persona" (personaMostrar) la que almacenara la informacion del registro de la persona a mostrar.
        struct Persona personaMostrar;
        // Lee la informacion del registro de la persona en el archivo principal.
        fread(&personaMostrar, sizeof(struct Persona), 1, archivo);

        // Mostrar la informacion del registro de la persona segun su correo.
        printf("Registro de persona:\n");

        printf("Nombre y Apellido: %s %s\n", personaMostrar.nombre, personaMostrar.apellido);
        printf("Direccion: %s, %s, %s, %s\n", personaMostrar.direccion, personaMostrar.ciudad, personaMostrar.provincia, personaMostrar.codigoPostal);
        printf("Pais: %s\n", personaMostrar.pais);
        printf("Telefonos: (1) %s, (2) %s\n", personaMostrar.telefono1, personaMostrar.telefono2);
        printf("Empresa: %s\n", personaMostrar.empresa);
        printf("Email: %s\n", personaMostrar.email);
        printf("Web: %s\n", personaMostrar.web);
        printf("---------------------------------------------------\n");
    } else {
        // Si no encuentra el (email) mostrara el siguiente mensaje en consola.
        printf("Persona no encontrada para el email: %s\n", emailMostrar);
        printf("---------------------------------------------------\n");
    }
}

// Funcion encargada de mostrar todos los registros de las personas, por parametros recibe el puntero del archivo principal y el puntero 
// del archivo (indice).
void mostrarRegistrosPersonas(FILE *archivo, FILE *indice) {
    // Establece la posicion del puntero del archivo (indice) al principio del archivo, esto para que se pueda leer el archivo (indice)
    // desde el principio.
    fseek(indice, 0, SEEK_SET);
    // Se declara la estructura "Indice" (indiceRegistro), que almacenara la informacion leida en el archivo (indice).
    struct Indice indiceRegistro;

    // Variable contador: sirve para enumera los registros, (registo 1, registro 2, registo etc.), proposito unicamente estetico.
    int contador = 1;
    cuentaRegresiva(3);

    // ciclo (while) leera cada informacion del archivo (indice).
    while (fread(&indiceRegistro, sizeof(struct Indice), 1, indice) == 1) {
        // Se declara la estructura "Persona" (personaMostrar) que almacenar la informacion del registro de la persona, leida
        // con (fread) desde el archivo principal.
        struct Persona personaMostrar;
        fread(&personaMostrar, sizeof(struct Persona), 1, archivo);

        // Finalmente mostrara e iterara los registros de las personas, para mostrar cada registro del archivo principal, utilizando
        // la variable (contador) para enumerar estos registros.
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
        // Se le suma (1) unidad al contador.
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

    // Se declara la variable (opcion) encargada de almacenar la "opcion = numero" ingresado por el usuario desde teclado.
    int opcion;
    // Se hace uso de un ciclo (do - while), donde se ejecutara por al menos una vez todo el (menu) con sus opciones que incluyen
    // a las funciones anteriormente declaradas.
    do {
        // Se llama funcion (mostrarMenu) para mostrarle el menu al usuario.
        mostrarMenu();
        // Se almacena la opcion ingresada por el usuario en (opcion).
        scanf("%d", &opcion);

        // Se utiliza una estructura de control (switch) donde trabaja con la variable (opcion), para identificar cual es el caso que se
        // ejecutara.
        switch (opcion) {
            case 1:
                // Se ejecuta la funcion (ingresarRegistroPersona()).
                ingresarRegistroPersona(archivo, indice);
                break;
            case 2:
                // Se ejecuta la funcion (buscarRegistroPersona()).
                buscarRegistroPersona(archivo, indice);
                break;
            case 3:
                // Se ejecuta la funcion (modificarRegistroPersona()).
                modificarRegistroPersona(archivo, indice);
                break;
            case 4:
                // Se ejecuta la funcion (mostrarRegistroPersona()).
                mostrarRegistroPersona(archivo, indice);
                break;
            case 5:
                // Se ejecuta la funcion (mostrarRegistosPersona()).
                mostrarRegistrosPersonas(archivo, indice);
                break;
            case 0:
                // En el caso de que la opcion sea igual a cero, se mostrara el siguiente mensaje.
                printf("SALIENDO DEL PROGRAMA....\n");
                break;
            default:
                // Si la opcion ingresada es invalida se mostrara el siguiente mensaje.
                printf("Opción no válida. Inténtelo de nuevo.\n");
        }
        // Se evalua que el valor de la (opcion) sea diferente de (0).
        // Si es distinto de cero el ciclo (do - while) se volvera a ejecutar, del caso contrario la estructura repetitiva se termina.
    } while (opcion != 0);

    // Finalmente se cerraran los archivo utilizados en este codigo, tanto el archivo principal como el archivo (indice).
    cerrarArchivo(archivo);
    cerrarArchivo(indice);

    return 0;
}
