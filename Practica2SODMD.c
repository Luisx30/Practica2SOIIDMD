#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

void CrearDirectorio(char *Nombredirectorio, char *Nombrearchivo);
void CrearArchivo(char *Nombredirectorio, char *Nombrearchivo);
void CrearEnlaceSimbolico(char *Nombrearchivo);
void CrearEnlaceFisico(char *Nombrearchivo);
void ListaAtributosArchivo(char *Nombrearchivo);
void ListaAtributosEntradaDirectorio(char *Nombredirectorio);
void ExisteDirectorio(char *Nombredirectorio, char *Nombrearchivo);

///A Validar el número de argumentos del main
int main(int argc, char **argv){
    if (argc > 2){
        ExisteDirectorio(argv[1], argv[2]);
        CrearDirectorio(argv[1], argv[2]);
    }
    else printf("\n**Necesita ingresar el nombre del archivo y del folder**\n");
    return 0;
}
///B Crear directorio
void CrearDirectorio(char *Nombredirectorio, char *Nombrearchivo){
    char *Directorioactual = Nombredirectorio;
    if (!mkdir(Nombredirectorio, 0777)){
        CrearArchivo(Nombredirectorio, Nombrearchivo);
        CrearEnlaceSimbolico(Nombrearchivo);
        CrearEnlaceFisico(Nombrearchivo);
        ListaAtributosArchivo(Nombrearchivo);
        ListaAtributosEntradaDirectorio(Nombredirectorio);
    }
    else printf("\n**ERROR**: No se ha podido crear el directorio\n");
}
///C Crear archivo y D Escribir en el archivo los nombres de los integrantes
void CrearArchivo(char *Nombredirectorio, char *Nombrearchivo){
    char *Nombres = {"\nArce Medina Valeria\nAzamar Avilés Santiago\nCardoso Martinez Luis Fernando\nCarreón Alonso Sebastián\nCastillo Corona Enrique\nIzaguirre Camacho Jorge\n"};
    FILE* Equipo = fopen(Nombrearchivo, "w+");
    if(Equipo){
        if (fwrite(Nombres,strlen(Nombres),1,Equipo)) printf("\nEl archivo se ha creado correctamente\n");
        else printf("\n**ERROR**: No se ha podido escribir en el archivo\n");
        fclose(Equipo);
    }
}
///E Crear enlaces (simbolicos y fisico) del archivo
///ENLACE SIMBOLICO
void CrearEnlaceSimbolico(char *Nombrearchivo){
    char *simbolico = {"*Enlace Simbolico*"};
    if (!symlink(Nombrearchivo, simbolico)) printf("\nEl enlace simbolico se ha creado correctamente\n");
    else printf("\n**ERROR*: No se ha podido crear el enlace simbolico\n");
}
///ENLACE FISICO
void CrearEnlaceFisico(char *Nombrearchivo){
    char *fisico = {"*Enlace Fisico*"};
    if (!link(Nombrearchivo, fisico)) printf("\nEl enlace fisco se ha creado correctamnete\n");
    else printf("\n**ERROR*: No se ha podido crear el enlace fisico\n");
}
///F enlistar los atributos del archivo
void ListaAtributosArchivo(char *Nombrearchivo){
    struct stat archInfo;
    if (!stat(Nombrearchivo, &archInfo)){
        printf("\n**Lista atributos del archivo: %s\n", Nombrearchivo);
        printf("Numero de inodo: %ld\n", archInfo.st_ino);
        printf("Tamaño: %ld bytes\n", archInfo.st_size);
        printf("Numero de enlaces: %ld\n", archInfo.st_nlink);
    }
}
///G Enlistar los atributos de las entradasdel directorio actual
void ListaAtributosEntradaDirectorio(char *Nombredirectorio){
    struct dirent* dirInfo;
    DIR* dir = opendir("./");
    if (dir){
        printf("\n**Lista Atributos del directorio:\n");
        while (dirInfo = readdir(dir)){
            printf("Numero del inodo: %ld\n", dirInfo->d_ino);
            printf("Nombre del archivo: %s\n",dirInfo->d_name);
            printf("-------------------------------------\n");
        }
        free(dirInfo);
        free(dir);
    }
}
///H PUNTO EXTRA Si ya existe el directorio o el archivo a crear,
///pedir otro nombre para el directorio o archivo y continuar con la ejecución
void ExisteDirectorio(char *Nombredirectorio, char *Nombrearchivo){
    DIR *dir = opendir(Nombredirectorio);
    FILE *file = fopen(Nombrearchivo, "r");
    if (dir){
        printf("\n*Ingrese el nuevo nombre del directorio: ");
        scanf("%s", Nombredirectorio);
        closedir(dir);
    }
    if (file){
        printf("\n*Ingrese el nuevo nombre del archivo: ");
        scanf("%s", Nombrearchivo);
        fclose(file);
    }
}
