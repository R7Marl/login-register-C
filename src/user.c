#include "../include/user.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // esto es para usar la funcion isprint

#define ADMIN_USER "admin23"
#define ADMIN_PASS "passadmin"

// funcion para registrar un usuario
int register_user(const char *file, User *user) {
    if(user == NULL) {
        printf("\nError al crear el usuario\n");
        return -1;
    }
    // aqui se abre el archivo users.txt
    FILE *fp = fopen(file, "a");
    if (fp == NULL) {
        printf("\nError al abrir el archivo\n");
        return -1;
    }
    // se llama a la funcion generar_id
    // para asignarle un ID a la cuenta registrada
    user->id = generar_id("../data/contador_id.txt");
    // se encripta la contraseña mediante encriptacion XOR antes de guardarse en el archivo
    encriptar_password(user->password);
    // escribe el usuario, password e ID en el archivo
    fprintf(fp, "%d %s %s %s\n", user->id, user->username, user->telefono, user->password);
    fclose(fp);
    return 0;
}


// para revisar lo que se compara
int login_user(const char *file, User *user) {
    if (user == NULL) {
        printf("\nError al crear el usuario\n");
        return -1;
    }
    FILE *fp = fopen(file, "r");
    if (fp == NULL) {
        printf("\nError al abrir el archivo\n");
        return -1;
    }

        if (strcmp(user->username, ADMIN_USER) == 0 && strcmp(user->password, ADMIN_PASS) == 0) {
        return 1; // Es administrador
    }
    // aqui se llama a la funcion de encriptacion para
    // desencriptar el password y asi poder compararlo
    // con la clave ingresada para el login
    encriptar_password(user->password);
    char username[50], password[12], telefono[20];
    while (fscanf(fp, "%d %50s %20s %12s", &(user->id), username, telefono, password) != EOF) {

        // a modo de muestra, se pueden ver por pantalla las distintas
        // cuentas creadas
        //printf("\nEsta es una prueba para ver los strings que se comparan: id='%d' username='%s' password='%s' telefono='%s' \n", user->id, username, password, telefono);

        if (strcmp(username, user->username) == 0 && strcmp(password, user->password) == 0) {
            // si es usuario o si es administrador devuelve un valor u otro
            strcpy(user->telefono, telefono);
            fclose(fp);
            return 0;
        }
    }
    fclose(fp);
    // si no hay coincidencias con usuario y clave retorna -1
    return -1;
}

// esta funcion compara un numero entero que representa
// un ID unico, con los ID encontrados en el archivo
// al haber coincidencia, muestra por pantalla
// la cuenta registrada con ese ID
int buscar_cuentas_por_id(const char *file, User *user) {
if (user == NULL) {
        printf("\nError al crear el usuario\n");
        return -1;
    }
    FILE *fp = fopen(file, "r");
    if (fp == NULL) {
        printf("\nError al abrir el archivo\n");
        return -1;
    }
    int id;
    // muestra los datos del usuario buscado, incluyendo la clave encriptada
    while (fscanf(fp, "%d %49s %20s %12s ", &id, user->username, user->telefono, user->password) != EOF) {
        if (id == user->id) {
            // a modo de muestra del password se puede desencriptar aqui
            //encriptar_password(user->password);
            printf("Usuario encontrado:\n\n");
            printf("ID: %d\n", user->id);
            printf("Nombre de usuario: %s\n", user->username);
            printf("Telefono: %s\n", user->telefono);
            printf("Clave: %s\n\n", user->password);
            fclose(fp);
            // si hay coincidencias con el id, devuelve 0
            return 0;
        }
    }

    fclose(fp);
    // si no hay coincidencias con el id, devuelve -1
    return -1;
}

// Función para encriptar si no esta encriptada o desencriptar si esta encriptada la contraseña usando XOR
// lo que hace es recorrer el string del password ingresado y aplicar la operacion
// con la clave_XOR

void encriptar_password(char *password) {
    // string de 10 caracteres para aplicar
    // con el cifrado XOR con la clave
    // ingresada por el usuario
    char clave_XOR[]= "abecedario";
    int len = strlen(password);
    int len_clave = strlen(clave_XOR);
    // se recorre la longitud de la cadena password
    // y se aplica la operacion xor con la clave_XOR
    for (int i = 0; i < len; i++) {
        password[i] = password[i] ^ clave_XOR[i % len_clave];
        // isprint es una funcion de <ctype.h> que
        // asegura que los caracteres sean imprimibles
        // en esta condicion, si los caracteres de la
        // clave no son imprimibles, se realiza la operacion
        // resto con 95 y luego se le suma 32, para asegurarse
        // de que se encuentra entre los valores imprimibles de
        // la tabla ASCII, que van desde el espacio hasta la virguilla.
        if (!isprint(password[i])) {
            password[i] = (password[i] % 95) + 32;
        }
    }
}

// Antes de ejecutar esta funcion se guarda en un archivo contador_id.txt un numero entero que se usa para asignar
// el id a las cuentas que se registran. Cada vez que se usa la funcion de register_user, se llama a esta funcion
// para leer el valor actual del contador desde el archivo y luego se incrementa en 1 el valor ID,
//  se guarda ese valor en el archivo  y se le asigna a la cuenta que se registra ese ID nuevo, volviendo cada uno
// de los ID un ID unico.
int generar_id(const char *file){
    int contador_id = 1;
    FILE *fp = fopen("../data/contador_id.txt", "r+");
    if (fp == NULL) {
        printf("Error al abrir el archivo\n");
        return -1;
    }
    fscanf(fp, "%d", &contador_id);
    int id_nuevo;
        id_nuevo = contador_id++;
        rewind(fp);
        fprintf(fp, "%d", contador_id);
    fclose(fp);
    return id_nuevo;
}


void mostrar_informacion_usuario(const char *file, const char *username) {
    FILE *fp = fopen(file, "r");
    if (fp == NULL) {
        printf("\nError al abrir el archivo\n");
        return;
    }
    char archivo_usuario[50];
    char archivo_clave[12];
    char archivo_telefono[20];
    int id;
    // esto lee el contenido del archivo para cada campo ingresado por el usuario, entonces
    // imprime por pantalla el contenido de cada uno
    while (fscanf(fp, "%d %49s %19s %10s", &id, archivo_usuario, archivo_telefono, archivo_clave) != EOF) {
        if (strcmp(archivo_usuario, username) == 0) {
            encriptar_password(archivo_clave);
            printf("\nInformacion del usuario:\n");
           // printf("ID : %d\n\n", id);
            printf("Nombre de usuario: %s\n\n", archivo_usuario);
            printf("Numero de celular: %s\n\n", archivo_telefono);
            printf("Clave: %s\n\n", archivo_clave);
            fclose(fp);
            return;
        }
    }

    fclose(fp);
    printf("\nNo se encontro informacion para el usuario: %s\n", username);
}

int validar_telefono(const char *telefono) {
    int longitud = strlen(telefono);
    int i;
    if (longitud != 10) {
        return -1;
    }
    for (i = 0; i < longitud; i++) {
        if (telefono[i] < '0' || telefono[i] > '9') {
            return -1;
        }
    }
    return 0;
}

int validar_nombre_usuario(const char *username) {
    int longitud = strlen(username);
    int i;
    if (longitud == 0) {
        return -1;
    }

    for (i = 0; i < longitud; i++){
        if ((username[i] <= 'A' && username[i] >= 'Z') || (username[i] <= 'a' && username[i] >= 'z')) {
            return -1;
        }
    }
    return 0;
}

int validar_password(const char *password){
    int longitud = strlen(password);
    if (longitud ==0){
        return -1;
    }
    return 0;
}
