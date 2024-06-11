#include "../include/user.h"
#include "user.c"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define FILE "../data/users.txt"

// prototipos de funciones del main para usarse
// con el menu
void register_promp();
void login_promp();
void buscar_cuentas_por_id_promp();

int main() {
    // pantalla de color azul y letras verdes
    system("color 9A");
    int option;
    char input[3];
    do
    {
        printf("1. Registrar usuario\n");
        printf("2. Login \n");
        printf("3. Buscar cuenta por ID\n");
        printf("4. Salir\n");
        printf("Ingresa una opcion: ");
        // cambié scanf por fgets para tener mejor control del buffer de entrada
        fgets(input, sizeof(input), stdin);
        // condicion de que lo ingresado por el usuario sea un digito y no una letra o simbolo para no
        // generar errores luego.
        if(sscanf(input,"%d", &option)!=1){
            printf("\nNo es un numero lo que se ha ingresado, introduzca por favor un numero entero.\n");
            // el continue regresa al comienzo para
            // mostrar de nuevo el menu y asi poder
            // ingresar una opcion otra vez
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
            printf("\nSaliendo...\n");
            break;
        default:
            printf("\nOpcion no valida, elija una de las opciones mencionadas.\n");
            break;
        }
    } while(option != 4);

    return 0;
}

// funcion para registrar una cuenta con nombre
// de usuario y clave. Se genera un ID unico para
// la cuenta creada
void register_promp() {
    User *user = (User *)malloc(sizeof(User));
    if(user == NULL) {
        printf("Error al crear el usuario\n");
        return;
    }

    printf("Ingrese el usuario : ");
    fgets(user->username, sizeof(user->username), stdin);
    user->username[strcspn(user->username, "\n")] = '\0';

    printf("Ingrese la clave : ");
    fgets(user->password, sizeof(user->password), stdin);
    user->password[strcspn(user->password, "\n")] = '\0';
    // pido que la clave sea de 10 caracteres
        if (strlen(user->password) != 10) {
        printf("La clave debe contener 10 caracteres\n");
        free(user);
        return;
    }
    int result = register_user(FILE, user);
    if(result == 0) {
        printf("El usuario ha sido creado con exito\n");
    } else {
        printf("Hubo un error al crear el usuario\n");
    }

    free(user);
}

// el usuario ingresa el nombre de usuario y la clave
// si hay una cuenta con datos coincidentes se inicia sesion
void login_promp() {
    User *user = (User *)malloc(sizeof(User));
    if(user == NULL) {
        printf("Error al crear el usuario\n");
        return;
    }
    printf("Ingrese el usuario : ");
    fgets(user->username, sizeof(user->username), stdin);
    user->username[strcspn(user->username, "\n")] = '\0';
    printf("Ingrese la clave : ");
    fgets(user->password, sizeof(user->password), stdin);
    user->password[strcspn(user->password, "\n")] = '\0';
    // una validacion para que lo ingresado no este vacio
    if (strlen(user->username) == 0 || strlen(user->password) == 0) {
        printf("Usuario o clave vacios\n");
        free(user);
        return;
    }
    // si es exitoso el login o no, se libera la memoria
    int result = login_user(FILE, user);
    if(result == 0) {
        printf("\nSe ha iniciado sesion\n\n");
    } else {
        printf("\nHubo un error al iniciar sesion\n\n");
    }
    free(user);
}

// el usuario ingresa un numero entero y el programa busca
// coincidencias con las cuentas registradas
void buscar_cuentas_por_id_promp() {
    User *user = (User *)malloc(sizeof(User));
    if (user == NULL) {
        printf("\nError al crear el usuario\n");
        return;
    }
    printf("Ingrese el ID que desea buscar: ");
    scanf("%d", &(user->id));
    fflush(stdin);
    // si es exitosa la busqueda o no, se libera la memoria
    int result = buscar_cuentas_por_id(FILE, user);
    if (result == 0) {
        printf("Se encontro el ID\n");
    } else {
        printf("No se encontraron usuarios con este ID : %d\n", user->id);
    }
    free(user);
}
