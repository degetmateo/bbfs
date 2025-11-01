#include <stdio.h>

#include "create_disk.h"
#include "read_sb.h"
#include "create_file.h"
#include "write_file.h"
#include "read_block.h"
#include "read_file.h"
#include "delete_file.h"

#include "./utils/read_console.h"

int console_create_file () {
    char filename[32];

    printf("Nombre del archivo: ");
    scanf("%32s", filename);

    create_file(filename);
};

int console_write_file () {
    char filename[32];

    printf("Nombre del archivo: ");
    scanf("%32s", filename);

    printf("Escribe el archivo: ");
    Buffer data = read_console();

    write_file(filename, data);
};

int console_read_block () {
    printf("Numero del bloque: ");
    
    int number;
    scanf("%d", &number);

    Block block = read_block(number);
    printf("%s", block.data);
    return 0;
}

int console_read_file () {
    char filename[32];
    printf("Nombre del archivo: ");
    scanf("%32s", filename);

    char* content = read_file(filename);
    printf("%s", content);
    free(content);
    return 0;
}

int console_delete_file () {
    char filename[32];
    printf("Nombre del archivo: ");
    scanf("%32s", filename);

    delete_file(filename);

    return 0;
};

int main () {
    while (1) {
        printf("\n");
        printf("Elige una opcion:\n\n");
        printf("0. Salir.\n");
        printf("1. Crear disco (reemplaza existente).\n");
        printf("2. Leer Superblock.\n");
        printf("3. Crear archivo.\n");
        printf("4. Escribir archivo.\n");
        printf("5. Leer archivo.\n");
        printf("6. Eliminar archivo.\n\n");
        
        int option;

        printf("Ingresa tu eleccion: ");
        scanf("%d", &option);
        printf("\n\n");

        switch (option) {
            case 0:
                return 0;
                break;  
            case 1:
                create_disk();
                break;
            case 2:
                read_sb();
                break;
            case 3:
                console_create_file();
                break;
            case 4:
                console_write_file();
                break;
            case 5:
                console_read_file();
                break;
            case 6:
                console_delete_file();
                break;
            default:
                continue;
                break;
        };
    };

    return 0;
};