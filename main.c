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
        printf("3. Crear archivo.\n\n");
        
        int option;

        printf("Ingresa tu eleccion: ");
        scanf("%d", &option);
        printf("\n\n");

        char filename[32];

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
                printf("Nombre del archivo: ");
                scanf("%32s", filename);
                create_file(filename);
                break;
            case 4:
                printf("Nombre del archivo: ");
                scanf("%32s", filename);

                char data[503];
                printf("Escribe el contenido: ");
                scanf("%503s", data);
                
                write_file(filename, data);
            default:
                continue;
                break;
        };
    };

    return 0;
};