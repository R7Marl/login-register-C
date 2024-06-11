#include "../include/user.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // esto es para usar la funcion isprint

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
    fprintf(fp, "%s %s %d \n", user->username, user->password, user->id);
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
    // aqui se llama a la funcion de encriptacion para
    // desencriptar el password y asi poder compararlo
    // con la clave ingresada para el login
    encriptar_password(user->password);
    char username[50], password[12];
    while (fscanf(fp, "%50s %12s %d", username, password, &(user->id)) != EOF) {


//        username[strcspn(username, "\n")] = '\0';
//        password[strcspn(password, "\n")] = '\0';
        // a modo de muestra, se pueden ver por pantalla las distintas
        // cuentas creadas
        printf("\nEsta es una prueba para ver los strings que se comparan: username='%s' password='%s' id='%d'\n", username, password, user->id);

        if (strcmp(username, user->username) == 0 && strcmp(password, user->password) == 0) {
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
    // a modo de muestra, se muestra tambien el password, que en una version
    // usable para un negocio no se deberia mostrar
    while (fscanf(fp, "%49s %12s %d", user->username, user->password, &id) != EOF) {
        if (id == user->id) {
            // a modo de muestra del password se puede desencriptar aqui
            //encriptar_password(user->password);
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
        // la tabla ASCII.
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
