#include "user.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int register_user(const char *file, User *user) { // Función para registrar un usuario
    if(user == NULL) {
        printf("Error al crear el usuario\n");
        return -1;
    }
    FILE *fp = fopen(file, "a"); // Abre el archivo users.txt
    if (fp == NULL) {
        printf("Error al abrir el archivo\n"); // Si el archivo no existe va a arrojar este error
        return -1;
    }
    fprintf(fp, "%s %s\n", user->username, user->password); // Escribe el usuario en el archivo
    fclose(fp); // Cierra el archivo
    return 0; // Devuelve 0
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
        if(strcmp(username, user->username) == 0 && strcmp(password, user->password) == 0) { // Compara el usuario y la contraseña
            fclose(fp);
            return 0; // Devuelve 0 si el usuario y la contraseña coinciden
        }
    }
    fclose(fp);
    return -1; // Si no coinciden devuelve -1
    
}