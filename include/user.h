#ifndef USER_H
#define USER_H

typedef struct
{
    /* data */
    char username[50];
    char password[50];
    int id;
} User;

int register_user(const char *file, User *user);
int login_user(const char *file, User *user);
int buscar_cuentas_por_id(const char *file, User *user);
void encriptar_password(char *password); // Función para encriptar la contraseña
int generar_id(const char *file);
#endif
