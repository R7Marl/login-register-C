#include "user.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int register_user(const char *file, User *user) { // Función para registrar un usuario
    //static int id_contador=1;
    if(user == NULL) {
        printf("Error al crear el usuario\n");
        return -1;
    }
    FILE *fp = fopen(file, "w");// Abre el archivo users.txt
      printf("Generando un archivo nuevo...");
      user->id = generar_id("contador_id.txt");
     // encriptar_password(user->password);
      fprintf(fp, "%s %s %d \n", user->username, user->password, user->id);
      fclose(fp);
      return 0;
}

int login_user(const char *file, User *user) // Función para iniciar sesión
{
    if(user == NULL) {
        printf("Error al crear el usuario\n");
        return -1;
    }
    FILE *fp = fopen(file, "r"); // Abre el archivo users.txt
    if(fp == NULL) {
        printf("Error al abrir el archivo\n"); // Si el archivo no existe va a arrojar este error
        return -1;
    }
    char username[50], password[50]; // Variables para el usuario y la contraseña
    while (fscanf(fp, "%s %s", username, password) != EOF) // Lee el archivo
    {
        // desencripta la contraseña para leerla, sin guardarla desencriptada
        //encriptar_password(password);
        if(strcmp(username, user->username) == 0 && strcmp(password, user->password) == 0) { // Compara el usuario y la contraseña
            fclose(fp);
            return 0; // Devuelve 0 si el usuario y la contraseña coinciden
        }
    }
    fclose(fp);
    printf("Usuario o contraseña incorrectos\n");
    return -1; // Si no coinciden devuelve -1

}

int buscar_cuentas_por_id(const char *file, User *user) {
if (user == NULL) {
        printf("Error al crear el usuario\n");
        return -1;
    }
    FILE *fp = fopen(file, "r");
    if (fp == NULL) {
        printf("Error al abrir el archivo\n");
        return -1;
    }
    int id;
    while (fscanf(fp, "%49s %49s %d", user->username, user->password, &id) != EOF) {
        if (id == user->id) {
            printf("Usuario encontrado:\n");
            printf("Username: %s\n", user->username);
            printf("Password: %s\n", user->password);
            printf("ID: %d\n", user->id);
            fclose(fp);
            // si hay coincidencias con el id, devuelve 0
            return 0;
        }
    }

    fclose(fp);
    // si no hay coincidencias con el id, devuelve -1
    return -1;
}

// Función para encriptar si no esta encriptada/desencriptar si esta encriptada la contraseña usando XOR
// lo que hace es recorrer el string del password ingresado y aplicar la operacion
// XOR caracter a caracter con la clave_XOR
void encriptar_password(char *password) {
    char clave_XOR = 'A';
    int len = strlen(password);
    for (int i = 0; i < len; i++) {
        password[i] = password[i] ^ clave_XOR;
    }
}
// Antes de ejecutar esta funcion se guarda en un archivo contador_id.txt un numero entero que se usa para asignar
// el id a las cuentas que se registran. Cada vez que se usa la funcion de register_user, se llama a esta funcion
// para leer el valor actual del contador desde el archivo y luego se incrementa en 1 el valor ID,
//  se guarda ese valor en el archivo  y se le asigna a la cuenta que se registra ese ID nuevo, volviendo cada uno
// de los ID un ID unico.
int generar_id(const char *file){
    static int contador_id = 1;
    FILE *fp = fopen(file, "r+");
    if (fp == NULL) {
        printf("Error al abrir el archivo\n");
        return -1;
    }
    fscanf(fp, "%d", &contador_id);
    int id_nuevo;
    do {
        id_nuevo = contador_id++;
        rewind(fp);
        fprintf(fp, "%d", contador_id);
    } while (id_nuevo <= 0);
    fclose(fp);
    return id_nuevo;
}
