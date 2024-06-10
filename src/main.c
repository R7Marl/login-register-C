#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// para leer caracteres en español
//#include <windows.h>
#include <locale.h>
//
#include "user.c"

#define FILE "users.txt"

// prototipos de funciones
void register_promp();
void login_promp();
void buscar_cuentas_por_id_promp();

int main() {
    // 3 líneas de código para que puedan leerse caracteres en español
   /* setlocale(LC_ALL, "");
    SetConsoleCP(1252);
    SetConsoleOutputCP(1252);*/
    int option;
    char input[50];
    do
    {
        printf("1. Registrar usuario\n");
        printf("2. Iniciar sesión\n");
        printf("3. Buscar cuenta por ID\n");
        printf("4. Salir\n");
        printf("Ingresa una opcion: ");
        // cambié scanf por fgets para tener mejor control del buffer de entrada
        fgets(input, sizeof(input), stdin);
        // condicion de que lo ingresado por el usuario sea un digito y no una letra o simbolo para no
        // generar errores luego.
        // por ej., tras ingresar la opcion 1 con scanf y ejecutar el inicio de sesion y regresar al menu
        // el 1 permaneció en el buffer de entrada cuando luego ingresé letras y volvió a ejecutarse
        // la opción 1 de forma errónea
        if(sscanf(input,"%d", &option)!=1){
            printf("Entrada no valida, introduzca un numero.\n");
            continue;
        }
        switch (option)
        {
        case 1:
            register_promp();
            break;
        case 2:
            login_promp();
            break;
        case 3:
            buscar_cuentas_por_id_promp();
            break;
        case 4:
            printf("Saliendo...");
        default:
            printf("Opcion no valida\n");
            break;
        }
    } while(option != 4);

    return 0;
}

void register_promp() {
    User *user = (User *)malloc(sizeof(User));
    if(user == NULL) {
        printf("Error al crear el usuario\n");
        return;
    }
    printf("Ingresa el usuario: ");
    scanf("%49s", user->username);
    fflush(stdin);
    printf("Ingresa la contraseña: ");
    scanf("%49s", user->password);
    fflush(stdin);
    int result = register_user(FILE, user);
    if(result == 0) {
        printf("El usuario ha sido creado con éxito\n");
    } else {
        printf("Hubo un error al crear el usuario\n");
    }
    free(user);
}
void login_promp() {
    User *user = (User *)malloc(sizeof(User));
    if(user == NULL) {
        printf("Error al crear el usuario\n");
        return;
    }
    printf("Ingresa el usuario: ");
    scanf("%49s", user->username);
    fflush(stdin);
    printf("Ingresa la contraseña: ");
    scanf("%49s", user->password);
    fflush(stdin);
    int result = login_user(FILE, user);
    if(result == 0) {
        printf("Se ha iniciado sesión\n");
    } else {
        printf("Hubo un error al iniciar sesión\n");
    }
    free(user);
}


void buscar_cuentas_por_id_promp() {
    User *user = (User *)malloc(sizeof(User));
    if (user == NULL) {
        printf("Error al crear el usuario\n");
        return;
    }
    printf("Ingresa el ID a buscar: ");
    scanf("%d", &(user->id));
    fflush(stdin);
    int result = buscar_cuentas_por_id(FILE, user);
    if (result == 0) {
        printf("Búsqueda completada con éxito\n");
    } else {
        printf("No se encontraron usuarios con el ID %d\n", user->id);
    }
    free(user);
}
