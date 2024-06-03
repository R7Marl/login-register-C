#ifndef USER_H
#define USER_H

typedef struct  
{
    /* data */
    char username[50];
    char password[50];
} User;

int register_user(const char *file, User *user);
int login_user(const char *file, User *user);

#endif
