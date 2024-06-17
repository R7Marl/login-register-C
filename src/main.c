#include "../include/user.h"
#include "user.c"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define FILE "../data/users.txt"

// prototipos de funciones del main para usarse
// con el menu correspondiente

// para menu principal
void register_promp();
void login_promp();

// para menu de administrador
void buscar_cuentas_por_id_promp();
// prototipos de funciones del main para
// 3 menues distintos
// el principal es el primero en ejecutarse
// el de usuario y el de administrador se
// ejecutan si la cuenta que inicia sesion
// es de tipo administrador o no
void menu_principal();
void menu_usuario();
void menu_administrador();



int main() {
    // pantalla de color rojo y letras rojas
    system("color 4F");
    // para limpiar el buffer al inicio del programa, necesario
    fflush(stdin);
//    char input[3];
//    fgets(input, sizeof(input),stdin);
    menu_principal();
    return 0;
}
// este es el menu que se ejecuta en el main para funciones de registro
// e inicio de sesion
void menu_principal(){
    int option;
    char input[3];
        printf("1. Registrar usuario\n");
        printf("2. Login \n");
        printf("3. Salir\n");
        printf("Ingrese una opcion: ");
        // cambié scanf por fgets para tener mejor control del buffer de entrada
        fgets(input, sizeof(input), stdin);
        // condicion de que lo ingresado por el usuario sea un digito y no una letra o simbolo para no
        // generar errores luego.
        if(sscanf(input,"%d", &option)!=1){
            printf("\nNo es un numero lo que se ha ingresado, introduzca por favor un numero entero.\n");
            // el continue regresa al comienzo para
            // mostrar de nuevo el menu y asi poder
            // ingresar una opcion otra vez
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
            printf("\nSaliendo...\n");
            break;
        default:
            printf("\nOpcion no valida, elija una de las opciones mencionadas.\n");
            menu_principal();
            break;
        }
}
// este es el menu al que se accede tras iniciar sesion
// con una cuenta de administrador
void menu_administrador(){
    int option;
    char input[3];
        printf("\nBienvenido al menu de administrador.\n");
        printf("1. Buscar cuenta por ID\n");
        printf("2. Salir \n");
        printf("Ingresa una opcion: ");
        // cambié scanf por fgets para tener mejor control del buffer de entrada
        fgets(input, sizeof(input), stdin);
        // condicion de que lo ingresado por el usuario sea un digito y no una letra o simbolo para no
        // generar errores luego.
        if(sscanf(input,"%d", &option)!=1){
            printf("\nNo es un numero lo que se ha ingresado, introduzca por favor un numero entero.\n");
            // el continue regresa al comienzo par

            // mostrar de nuevo el menu y asi poder
            // ingresar una opcion otra vez
        }
        switch (option)
        {
        case 1:
            buscar_cuentas_por_id_promp();
            break;
        case 2:
            printf("\nSaliendo...\n");
            break;
        default:
            printf("\nOpcion no valida, elija una de las opciones mencionadas.\n");
            menu_administrador();
            break;
        }
}

void menu_usuario(User *user){
    printf("\nBienvenido al menu de usuario, %s .\n", user->username);
    int option;
    char input[3];
    do{
        printf("1. Mostrar mi informacion\n");
        printf("2. Salir \n");
        printf("Ingresa una opcion: ");
        // cambié scanf por fgets para tener mejor control del buffer de entrada
        fgets(input, sizeof(input), stdin);
        // condicion de que lo ingresado por el usuario sea un digito y no una letra o simbolo para no
        // generar errores luego.
        if(sscanf(input,"%d", &option)!=1){
            printf("\nNo es un numero lo que se ha ingresado, introduzca por favor un numero entero.\n");
        }
        switch (option)
        {
        case 1:
            printf("\nMostrando mi informacion...\n");
            mostrar_informacion_usuario(FILE, user->username);
            break;
        case 2:
            printf("\nSaliendo...\n");
            break;
        default:
            printf("\nOpcion no valida, elija una de las opciones mencionadas.\n");
            break;
        }
        }while(option != 2);

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


    if(validar_nombre_usuario(user->username) != 0){
        printf("\nDebe ingresar un nombre de usuario y solo debe contener letras sin tildes.\n\n");
        free(user);
        menu_principal();
        return;
    }

    printf("Ingrese la clave : ");
    fgets(user->password, sizeof(user->password), stdin);
    user->password[strcspn(user->password, "\n")] = '\0';
        // limito la clave para que sea de 10 caracteres exactamente

        if (validar_password(user->password) != 0) {
        printf("\nLa clave debe ser de 10 caracteres.\n\n");
        free(user);
        menu_principal();
        return;
    }
    printf("Ingrese el numero de celular: ");
    fgets(user->telefono, sizeof(user->telefono), stdin);
    user->telefono[strcspn(user->telefono, "\n")] = '\0';

    if (validar_telefono(user->telefono) != 0) {
        printf("\nEl numero de telefono que se ingrese debe tener 10 digitos y solamente deben ser numeros enteros\n\n");
        free(user);
        menu_principal();
        return;
    }

    int result = register_user(FILE, user);

    if(result == 0) {
        printf("\nEl usuario ha sido creado con exito\n");
    } else {
        printf("\nHubo un error al crear el usuario\n");
    }

    free(user);
    menu_principal();
}


// el usuario ingresa el nombre de usuario y la clave
// si hay una cuenta con datos coincidentes se inicia sesion
void login_promp() {
    User *user = (User *)malloc(sizeof(User));
    if(user == NULL) {
        printf("\nError al crear el usuario\n");
        return;
    }
    printf("\nIngrese el usuario : ");
    fgets(user->username, sizeof(user->username), stdin);
    user->username[strcspn(user->username, "\n")] = '\0';
    printf("\nIngrese la clave : ");
    fgets(user->password, sizeof(user->password), stdin);
    user->password[strcspn(user->password, "\n")] = '\0';
    // una validacion para que lo ingresado no este vacio
    if (strlen(user->username) == 0 || strlen(user->password) == 0) {
        printf("\nUsuario o clave vacios\n\n");
        free(user);
        menu_principal();
        return;
    }
    // si es exitoso el login o no, se libera la memoria
    int result = login_user(FILE, user);
    if (result == 1){
        printf("\nBienvenido, administrador.\n");
        menu_administrador();
    }
    else if(result == 0) {

        printf("\nBienvenido, usuario %s .\n\n", user->username);
         // Copiar el nombre de usuario
        menu_usuario(user);
        // aqui va al menu administrador o usuario acorde al valor retornado
    } else {
        printf("\nUsuario o clave incorrectos\n\n");
        menu_principal();
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
    int result = buscar_cuentas_por_id(FILE, user);
    if (result == 0) {
        printf("Se encontro el ID\n");
    } else {
        printf("No se encontraron usuarios con este ID : %d\n", user->id);
    }
    free(user);
    menu_administrador();
}


