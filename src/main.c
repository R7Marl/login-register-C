#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "user.h"

#define FILE "data/users.txt"

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

int main() {

    int option;
    do
    {
        printf("1. Registrar usuario\n");
        printf("2. Iniciar sesión\n");
        printf("3. Salir\n");
        printf("Ingresa una opcion: ");
        scanf("%d", &option);
        fflush(stdin);
        switch (option)
        {
        case 1:
            register_promp();
            break;
        case 2:
            login_promp();
            break;
        case 3:
            printf("Saliendo...");
            break;
        default:
            break;
        }
    } while(option != 3);

    return 0;
}