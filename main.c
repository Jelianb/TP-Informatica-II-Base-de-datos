/*  DATOS DEL ALUMNO                                               */
/*  Nombre y apellido: Benedine Julian                             */
/*  Carrera: Tecnicatura universitaria en programacion informatica */
/*  Fecha de entrega: 09/11/2022                                   */
/*  ARCHIVOS: TP_BENEDINE.C , libreriapropia2.h , corredores_v1.csv */

//NOTAS
// 1- CUANDO CANCELO LA BAJA LOGICA ME OBLIGA A SELECCIONAR LA OPCION DE CANCELAR 2 VECES
//FUNCIONES NO LOGRADAS: 9 Y 10

//incluyo librerias
//#include "sqlite3.h"
#include "libreriapropia2.h"


int Menu();
void migrarDatos(FILE *parchivotxt, FILE *parchivobin, competidores competidor, fecha date);



int main ()
{

    struct competidores competidor;
    struct fecha date;
    FILE *parchivotxt;
    FILE *parchivobin;
    char confirma;

    int opcion,leer;
    //===MENU===
    do
    {
       opcion=Menu();
       switch (opcion)
       {
           case 1:
               printf("%s\n",ARCHIVO_TXT);
               leerTXT(parchivotxt,ARCHIVO_TXT);
               break;//IMPRIMO DATOS DE corredores_v1.csv
           case 2:
               crearbin(parchivobin,ARCHIVO_BIN);
               printf("\n");
               break;//creo archivo binario competidores.dat
           case 3:
               printf("Usted va a sobreescribir los datos almacenados en el archivo competidores.dat, presione s/n para confirmar\n");
               scanf("%c",&confirma);
               fflush(stdin);
               if(confirma=='s' || confirma=='S')
               {
                 migrarDatos(parchivotxt, parchivobin, competidor, date);
               }
               printf("\n");
                break;
           case 4:
               printf("===MENU===\n");
               printf("Que desea emitir?\n");
               printf("1: Todos los datos\n");
               printf("2: Competidores activos\n");
               printf("3: Buscar por pais\n");
               printf("4: Buscar por rango de tiempo\n");
               printf("Respuesta: ");
               scanf("%d", &leer);
               fflush(stdin);
               while(leer >4 || leer<1)
               {
                   printf("Ingrese un valor entre el 1 y el 4\n");
                   scanf("%d", &leer);
                   fflush(stdin);
               }
               emitobinario(parchivobin,ARCHIVO_BIN,competidor,leer);
               printf("\n");
               break;
           case 5:
               alta(parchivobin,ARCHIVO_BIN);
               printf("\n");
               break;
           case 6:
               buscar(parchivobin,ARCHIVO_BIN);
               printf("\n");
               break;
           case 7:
               modificar(parchivobin,ARCHIVO_BIN);
               printf("\n");
               break;
           case 8:
               bajaLogica(parchivobin,ARCHIVO_BIN);
               printf("\n");
               break;
           case 9:
               crearbin(parchivobin,BINARIO2);
               bajafisica(parchivobin,ARCHIVO_BIN);
               printf("\n");
               break;
           /*case 10:
               listarxyz(pArchivo);
               printf("\n");
               break;*/
       }
    } while (opcion != 0 || opcion>10);

    return EXIT_SUCCESS;
}//FIN MAIN

int Menu()
{
    int opcion,exit;

    printf("====Elige una opcion====\n");
    printf("1- Listar TXT (emitir archivo de texto)\n");//IMPRIMO DATOS DE corredores_v1.csv
    printf("2- Creo un archivo binario\n");//creo archivo binario competidores.dat
    printf("3- Migrar datos al archivo binario\n");//migro datos del TXT al BIN
    printf("4- Emitir datos del archivo binario\n");//emito archivo binario + opciones para modificar datos
    printf("5- Alta de competidores\n");//ingreso nuevos competidores, en orden
    printf("6- Buscar (N de orden - N de corredor)\n");//busco por orden o por ID del corredor
    printf("7- Modificar dato solicitado\n");//modifico la edad o el tiempo del corredor buscando en punto anterior
    printf("8- Baja logica\n");//busco competidor, presenta datos, pide confirmaci�n y da de baja
    printf("9- Baja fisica\n");//elimina componentes inactivos - crear nuevo archivo binario
    printf("10- Listar xyz.\n");//listar el archivo construido con competidores de baja
    printf("Presione 0 para salir\n");
    scanf("%d",&opcion);
    fflush(stdin);
    return opcion;
}
// AQUI LISTAMOS, IMPRIMIMOS Y SELECIONAMOS LAS OPCIONES


void migrarDatos(FILE *parchivotxt, FILE *parchivobin, competidores competidor, fecha date)
{
    // Se abren los 2 archivos
    parchivotxt = fopen(ARCHIVO_TXT, "r");
    parchivobin = fopen(ARCHIVO_BIN, "wb");
    // Se inicia un bool para llevar control del primer registro y un char que se completa con cada linea del archivo
    bool pRegistro = true;
    char c[sizeof(competidores)];
    if (parchivotxt == NULL && parchivobin == NULL)
    {
        printf("ERROR\n");
    }
    else
    { // Se recorre linea a linea el archivo de texto
        while (fgets(c, sizeof(competidores), parchivotxt) != NULL)
        {
            // Pongo el puntero al principio del archivo para que guarde todos los registros
            if (pRegistro)
            {
                rewind(parchivotxt);
                pRegistro = false;
            }
            // Esta variable la uso para la comparaci�n antes y despues del fscanf
            int id = competidor.id;
            fscanf(parchivotxt, "%d;%d;%d;%3s;%d;%d;%3s;%f", &competidor.index, &competidor.id, &competidor.date.dia, competidor.date.mes, &competidor.date.ano, &competidor.edad, competidor.pais, &competidor.tiempo);
            // Reviso que no se repitan datos
            if (id != competidor.id)
            {
                // Agrego el campo activo
                competidor.activo = 1;
                fwrite(&competidor, sizeof(competidores), 1, parchivobin);
            }
        }
        fclose(parchivobin);
        fclose(parchivotxt);
    }

    system("cls");
    printf("Los archivos se migraron con exito\n\n");

    return;
}
