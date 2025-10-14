#include <stdio.h>

#include "create_disk.h"
#include "read_sb.h"
#include "create_file.h"
#include "write_file.h"

int main () {
    while (1) {
        printf("\n");
        printf("Elige una opcion:\n\n");
        printf("0. Salir.\n");
        printf("1. Crear disco (reemplaza existente).\n");
        printf("2. Leer Superblock.\n");
        printf("3. Crear archivo.\n");
        printf("4. Escribir archivo.\n\n");
        
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
                create_file();
                break;
            case 4:
                write_file();
            default:
                continue;
                break;
        };
    };

    return 0;
};