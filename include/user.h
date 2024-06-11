#ifndef USER_H
#define USER_H

typedef struct
{
    char username[50];
    char password[12];
    int id;
} User;

// prototipos de funciones
int register_user(const char *file, User *user);
int login_user(const char *file, User *user);
int buscar_cuentas_por_id(const char *file, User *user);
void encriptar_password(char *password);
int generar_id(const char *file);

#endif
