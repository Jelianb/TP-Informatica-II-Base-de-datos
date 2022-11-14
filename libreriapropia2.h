#include <ctype.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//-----DEFINES-----//
#define ARCHIVO_BIN "competidores.dat"
#define ARCHIVO_TXT "corredores_v1.csv"
#define BINARIO2 "competidores_bajas_.xyz"
//-----STRUCTS-----//
typedef struct fecha
{
    int dia, ano;
    char mes[3];
}fecha;

typedef struct competidores
{
    int index, id, edad, activo;
    struct fecha date;
    char pais[3];
    float tiempo;
}competidores;
//==FIN STRUCT==//



//== 1- FUNCION PARA EMITIR LOS DATOS DEL ARCHIVO DE TEXTO==//
void leerTXT(FILE *archivo, char *nombre)
{
    archivo = fopen(nombre, "r");
    char c = ' ';
    if (archivo != NULL)
    {
        while (!feof(archivo))
        {
            c = fgetc(archivo);
            printf("%c", c);
        }
        fclose(archivo);
    }
    else
    {
        printf("Error,el archivo no pudo abrirse\n");
    }
    return;
}//== 1- FIN FUNCION PARA LEER ARCHIVO DE TEXTO//


//==FUNCION PARA BORRAR CONTENIDO DEL TXT==// OPCIONAL
void borrarTXT(FILE *archivo, char *nombre)
{
    archivo = fopen(nombre, "w");
    if (archivo != NULL)
    {
        fputs("", archivo);
        fclose(archivo);
    }
    else
    {
        printf("Error,el archivo no pudo abrirse\n");
    }

    return;
}
//FIN BORRAR TXT

// 2- FUNCION PARA CREAR EL ARCHIVO BINARIO
void crearbin(FILE *archivo, char *nombre)
{
    archivo = fopen(nombre, "wb");
    if (archivo == NULL)
    {
        printf("Error, el archivo no pudo crearse\n");
    }
    else
    {
        printf("\nArchivo creado correctamente!\n\n");
        fclose(archivo);
    }
    return;
}
//FIN FUNCION 2 - CREAR ARCHIVO BINARIO

//FUNCION AUXILIAR PARA IMPRIMIR DATOS SOLICITADOS DEL COMPETIDOR
void imprimirCompetidor(competidores competidor)
{
    printf("===========================\n");
    printf("Numero de orden  : %d\n", competidor.index);
    printf("ID del competidor: %d\n", competidor.id);
    printf("Fecha            : %d/%s/%d\n", competidor.date.dia, competidor.date.mes, competidor.date.ano);
    printf("Edad             : %d\n", competidor.edad);
    printf("Pais             : %s\n", competidor.pais);
    printf("Tiempo           : %.6f\n", competidor.tiempo);
    printf("Activo           : %d\n", competidor.activo);
    printf("===========================\n\n");
    return;
}
//FIN FUNCION AUXILIAR PARA IMPRIMIR DATOS DEL COMPETIDOR

//FUNCION PARA CONVERTIR CARCACTERES EN MAYUSCULA
void mayus(char *c)
{
    for (int i = 0; i < strlen(c); i++)
    {
        c[i] = toupper(c[i]);
    }

    return;
}
//FIN CONVERTIR A MAYUSCULA

//4- FUNCION PARA EMITIR LOS DATOS DEL BINARIO
void emitobinario(FILE *archivo, char *nombre, competidores competidor, int leer)
{
    // CHEQUEO DE ARCHIVO
    archivo = fopen(nombre, "rb");
    if (archivo == NULL)
    {
        printf("Error, el archivo no pudo abrirse\n");
    }
    else
    {
        // Variables
        char vpais[3];
        int compara;
        float tiempoMin, tiempoMax;
        // ADQUIRIMOS LA CANTIDAD DE REGISTROS
        fseek(archivo, 0, SEEK_END);
        int nReg = ftell(archivo) / sizeof(competidores);
        rewind(archivo);
        // FUNCION SWITCH PARA EMITIR DATOS
        switch (leer)
        {
        case 1: // IMPRIME TODO
            for (int i = 0; i < nReg; i++)
            {
                fread(&competidor, sizeof(competidores), 1, archivo);
                imprimirCompetidor(competidor);
            }
            break;
        case 2: // SOLO COMPETIDORES ACTIVOS
            for (int i = 0; i < nReg; i++)
            {
                fread(&competidor, sizeof(competidores), 1, archivo);
                // CONFIRMACION DE ESTADO ACTIVO
                if (competidor.activo == 1)
                {
                    imprimirCompetidor(competidor);
                }
            }
            break;
        case 3:
            // INGRESO EL PAIS
            printf("Ingrese el pais:\n");
            gets(vpais);
            fflush(stdin);
            // TRASPASO LAS LETRAS A MAYUSCULA
            mayus(vpais);

            for (int i = 0; i < nReg; i++)
            {
                fread(&competidor, sizeof(competidores), 1, archivo);
                // COMPARO EL PAIS
            }
            if (strstr(vpais,competidor.pais)!=NULL)
                {
                    imprimirCompetidor(competidor);
                }
            break;
        case 4:
            // POR RANGO  DE TIEMPO
            // INGRESO LOS VALORES
            printf("Ingrese el valor minimo:\n");
            scanf("%f", &tiempoMin);
            fflush(stdin);
            printf("Ingrese el valor maximo:\n");
            scanf("%f", &tiempoMax);
            fflush(stdin);
            // RECORRO ARCHIVO
            for (int i = 0; i < nReg; i++)
            {
                // RECORRO ARCHIVO
                fread(&competidor, sizeof(competidores), 1, archivo);
                // COMPARO TIEMPOS E IMPRIMO LOS QUE CUMPLEN EL RANGO INGRESADO
                if (competidor.tiempo >= tiempoMin && competidor.tiempo <= tiempoMax)
                {
                    //IMPRIMO COMPETIDORES QUE CUMPLEN
                    imprimirCompetidor(competidor);
                }
            }
            break;
            default:
            printf("Error, no se ingreso una opcion valida\n");
            break;
        }
        fclose(archivo);
    }

    return;
}
// 4- FIN FUNCION PARA EMITIR LOS DATOS DEL BINARIO


//FUNCION PARA SABER SI EXISTE UN COMPETIDOR EN LA POSICION SELECCIONADA
int existeComp(FILE *archivo, char *nombre, int index)
{
    competidores competidor;
    fecha date;
    archivo = fopen(nombre, "rb");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo\n");
    }
    else
    {
        fseek(archivo, 0, SEEK_END);
        int nReg = ftell(archivo) / sizeof(competidores);
        rewind(archivo);
        for (int i = 0; i < nReg; i++)
        {
            fread(&competidor, sizeof(competidores), 1, archivo);
            if (index == competidor.index)
            {
                return 1;
            }
        }
    }
    return 0;
}
//FUNCION PARA CONFIRMAR SI EXISTE UN COMPETIDOR EN LA POSICION INDICADA POR EL USUARIO

//FUNCION CONVERTIR MES EN CHAR
void mesToChar(char *mes)
{
    //CONVIERTO LOS MESES INGRESADOS COMO INT EN VALORES CHAR
    if (strcmp(mes, "1") == 0)
    {
        strcpy(mes, "ene");
    }
    else if (strcmp(mes, "2") == 0)
    {
        strcpy(mes, "feb");
    }
    else if (strcmp(mes, "3") == 0)
    {
        strcpy(mes, "mar");
    }
    else if (strcmp(mes, "4") == 0)
    {
        strcpy(mes, "abr");
    }
    else if (strcmp(mes, "5") == 0)
    {
        strcpy(mes, "may");
    }
    else if (strcmp(mes, "6") == 0)
    {
        strcpy(mes, "jun");
    }
    else if (strcmp(mes, "7") == 0)
    {
        strcpy(mes, "jul");
    }
    else if (strcmp(mes, "8") == 0)
    {
        strcpy(mes, "ago");
    }
    else if (strcmp(mes, "9") == 0)
    {
        strcpy(mes, "sep");
    }
    else if (strcmp(mes, "10") == 0)
    {
        strcpy(mes, "oct");
    }
    else if (strcmp(mes, "11") == 0)
    {
        strcpy(mes, "nov");
    }
    else if (strcmp(mes, "12") == 0)
    {
        strcpy(mes, "dic");
    }

    return;
}
//CONVIERTO MES INGRESADO COMO INT EN CHAR

//FUNCION PARA CONVERTIR STRING EN MINUSCULA
void minuscula(char *c)
{
    for (int i = 0; i < strlen(c); i++)
    {
        c[i] = tolower(c[i]);
    }

    return;
}
//CONVIERTO LOS CARACTERES EN MINUSCULAS

//FUNCION PARA VALIDAR FECHAS
int validarFecha(int dia, char mes[3], int ano)
{
    // VALIDO QUE DIAS COINCIDA CON LOS MESES
    if (ano <= 0)
    {
        return 1;
    }
    if ((strcmp(mes, "ene") == 0 || strcmp(mes, "mar") == 0 || strcmp(mes, "may") == 0 || strcmp(mes, "jul") == 0 || strcmp(mes, "ago") == 0 || strcmp(mes, "oct") == 0 || strcmp(mes, "dic") == 0 && (dia <= 31 && dia > 0)))
    {
        return 0;
    }
    if ((strcmp(mes, "abr") == 0 || strcmp(mes, "jun") == 0 || strcmp(mes, "sep") == 0 || strcmp(mes, "nov") == 0) && (dia <= 30 && dia > 0))
    {
        return 0;
    }
    // COMPRUEBO ANIOS BICIESTOS
    if ((strcmp(mes, "feb") == 0 && (dia <= 28 && dia > 0) && (ano % 4 != 0)) || (strcmp(mes, "feb") == 0 && (dia <= 29 && dia > 0) && (ano % 4 == 0)))
    {
        return 0;
    }

    return 1;
}
//VALIDO QUE LAS FECHAS INGRESADAS SEAN CORRECTAS (CONTROL DE DIAS EN UN MES, RANGO DE MESES Y ANIO BICIESTO)

int checkNumString(char *c)
{
    // PARA VALIDAR SI HAY UN NUMERO DENTRO DE UN STRING
    for (int i = 0; i < sizeof(c); i++)
    {
        if (c[i] >= '0' && c[i] <= '9')
        {
            return 1;
        }
    }
    return 0;
}
//VERIFICAR SI UNA STRING CONTIENE NUMEROS

//==5- ACTIVAR UN COMPETIDOR==//
void alta(FILE *archivo, char *nombre)
{
    // Variables
    char activo;
    competidores competidor;
    archivo = fopen(nombre, "r+b");
    if (archivo == NULL)
    {
        printf("Error, el archivo no pudo abrirse\n");
    }
    else
    {
        // SE SOLICITA EL DATO POSICION DEL COMPETIDOR
        printf("Ingrese la posicion en la que ingresara al competidor: ");
        int isdigit = scanf("%d", &competidor.index); // isdigit se utiliza para confirmar que el valor elegido sea un int
        fflush(stdin);
        // Se revisa que no exista el competidor, que la posicion sea mayor a 0 y que sea un numero
        while (((existeComp(archivo, ARCHIVO_BIN, competidor.index) == 1) || (competidor.index <= 0)) || (isdigit == 0))
        {
            // Dependiendo el error se hace un output diferente
            if (competidor.index <= 0)
            {
                printf("ERROR, ingrese una posicion mayor a 0: ");
            }
            else if (existeComp(archivo, ARCHIVO_BIN, competidor.index) == 1)
            {
                printf("ERROR, la posicion ya existe, ingresela nuevamente: ");
            }
            else if(isdigit ==0)
            {
                printf("Error, ingrese un numero\n");
            }
            isdigit = scanf("%d", &competidor.index);
            fflush(stdin);
            //SE VUELVE A PEDIR EL DATO PARA CUALQUIERA DE LOS 3 ERRORES
        }

        // SE PIDE EL ID DEL COMPETIDOR
        printf("Ingrese el ID del competidor: ");
        isdigit = scanf("%d", &competidor.id);
        fflush(stdin);
        // Se valida que el ID sea mayor a 0 y que sea un numero
        while (competidor.id <= 0 || isdigit == 0)
        {
            if (competidor.id <= 0)
            {
                printf("Error, ingrese un ID mayor a 0: ");
            }
            else if (isdigit == 0)
            {
                printf("Error, ingrese un numero\n");
            }
            isdigit = scanf("%d", &competidor.id);
            fflush(stdin);
            //SE VUELVE A PEDIR EL DATO PARA CUALQUIERA DE LOS 2 ERRORES

        }
        // INGRESO FECHAS
        //DIA
        printf("Ingrese el dia: ");
        isdigit = scanf("%d", &competidor.date.dia);
        fflush(stdin);
        // VALIDO NUMERO
        while (isdigit == 0)
        {
            printf("Error, ingrese un numero\n");
            isdigit = scanf("%d", &competidor.date.dia);
            fflush(stdin);
        }
        //MES
        printf("Ingrese el mes: ");
        scanf("%3s", competidor.date.mes);
        fflush(stdin);
        // SE HACE EL CAMBIO DE TIPO DE DATO, EN CASO DE QUE EL USUARIO HAYA INGRESADO EL MES DE MANERA ESCRITA
        mesToChar(competidor.date.mes);
        minuscula(competidor.date.mes);
        //ANIO
        printf("Ingrese el anio: ");
        isdigit = scanf("%d", &competidor.date.ano);
        fflush(stdin);
        // VALIDO NUMERO
        while (isdigit ==0)
        {
            printf("Error, ingrese un numero\n");
            isdigit = scanf("%d", &competidor.date.dia);
            fflush(stdin);
        }
        while (validarFecha(competidor.date.dia, competidor.date.mes, competidor.date.ano) == 1)//VALIDO EL RANGO DE FECHAS INGRESADAS
        {
            printf("Las fechas no son correctas, intente nuevamente\n");
            printf("Ingrese el dia: ");
            isdigit = scanf("%d", &competidor.date.dia);
            fflush(stdin);
            while (isdigit == 0)
            {
                printf("Error, ingrese un numero\n");
                scanf("%d", &competidor.date.dia);
                fflush(stdin);
            }
            printf("Ingrese el mes: ");
            scanf("%3s", competidor.date.mes);
            fflush(stdin);
            // Se cambia el input del usuario a char en caso de que ingrese un int
            mesToChar(competidor.date.mes);
            minuscula(competidor.date.mes);
            printf("Ingrese el anio: ");
            isdigit = scanf("%d", &competidor.date.ano);
            fflush(stdin);
            // Se valida que el a�o sea un numero
            while (isdigit == 0)
            {
                printf("Error, ingrese un numero\n");
                isdigit = scanf("%d", &competidor.date.dia);
                fflush(stdin);
            }
        }
        //FIN VALIDAR EL RANGO DE FECHAS INGRESADAS

        // EDAD
        printf("Ingrese la edad: ");
        isdigit = scanf("%d", &competidor.edad);
        fflush(stdin);
        while (competidor.edad <= 0 || isdigit == 0)
        {
            printf("Edad invalida, ingrese nuevamente: ");
            isdigit = scanf("%d", &competidor.edad);
            fflush(stdin);
        }
        // PAIS
        printf("Ingrese el pais: ");
        scanf("%3s", competidor.pais);
        fflush(stdin);
        mayus(competidor.pais);
        while (checkNumString(competidor.pais))
        {
            printf("Ingrese un texto valido: ");
            scanf("%3s", competidor.pais);
            fflush(stdin);
            mayus(competidor.pais);
        }
        // TIEMPO
        printf("Ingrese el tiempo: ");
        isdigit = scanf("%f", &competidor.tiempo);
        fflush(stdin);
        while (competidor.tiempo < 0 || isdigit == 0)
        {
            printf("El tiempo ingresado es incorrecto, ingreselo nuevamente: ");
            isdigit = scanf("%f", &competidor.tiempo);
            fflush(stdin);
        }
        // ACTIVA EL COMPETIDOR
        competidor.activo = 1;
        // UBICO EL PUNTERO AL INICIO DEL ARCHIVO
        rewind(archivo);
        // UBICO EL PUNTERO PARA GUARDAR LOS DATOS EN EL ORDEN INDICADO POR EL USUARIO
        fseek(archivo, (competidor.index - 1) * sizeof(competidores), SEEK_CUR);
        fwrite(&competidor, sizeof(competidores), 1, archivo);
        fclose(archivo);
    }
    return;
}
//FIN ALTA DE COMPETIDOR

//6- BUSCAR COMPETIDOR
void buscar(FILE *archivo, char *nombre)
{
    int opc, nroOrden = 0, nroComp = 0, nReg = 0;
    int existe = 1;//VARIABLE "BANDERA" PARA DETERMINAR SI LA OPCION SELECCIONADA POR EL USUARIO YA EXISTE
    archivo = fopen(nombre, "rb");
    competidores competidor;
    if (archivo == NULL)
    {
        printf("Error, el archivo no pudo abrirse\n");
    }
    else
    {
        // SE LE SOLICITA UNA OPCION DE BUSQUEDA AL USUARIO
        printf("========================\n");
        printf("1: Numero de orden\n");
        printf("2: ID del competidor\n");
        printf("========================\n");
        scanf("%d", &opc);
        fflush(stdin);
        // Se compara esa opcion y se hace una busqueda acorde
        switch (opc)
        {
        case 1:
            printf("Ingrese el numero de orden: ");
            int isdigit = scanf("%d", &nroOrden);
            fflush(stdin);
            // Se valida que sea un numero mayor a 0 y un numero
            while (nroOrden <= 0 || isdigit == 0)
            {
                if (nroOrden <= 0)
                {
                    printf("Ingrese un numero mayor a 0: ");
                    isdigit = scanf("%d", &nroOrden);
                    fflush(stdin);
                }
                else if (isdigit == 0)
                {
                    printf("Error, ingrese u numero\n");
                    isdigit = scanf("%d", &nroOrden);
                    fflush(stdin);
                }
            }
            fseek(archivo, 0, SEEK_END);
            nReg = ftell(archivo) / sizeof(competidores);
            rewind(archivo);
            // Se recorre el archivo
            for (int i = 0; i < nReg; i++)
            {
                // Se lee la linea del archivo y se guardan los datos en competidor
                fread(&competidor, sizeof(competidores), 1, archivo);
                // Se compara el nro de orden
                if (nroOrden == competidor.index)
                {
                    imprimirCompetidor(competidor);
                    existe = 0;
                }
            }
            if (existe == 1)
            {
                system("cls");
                printf("El competidor ingresado no existe\n\n");
            }
            break;
        case 2:
            printf("Ingrese el ID del competidor: ");
            scanf("%d", &nroComp);
            fflush(stdin);
            fseek(archivo, 0, SEEK_END);
            nReg = ftell(archivo) / sizeof(competidores);
            rewind(archivo);
            // Se recorre el archivo
            for (int i = 0; i < nReg; i++)
            {
                // Se lee la linea del archivo y se guardan los datos en competidor
                fread(&competidor, sizeof(competidores), 1, archivo);
                // Se compara el ID
                if (nroComp == competidor.id)
                {
                    system("cls");
                    imprimirCompetidor(competidor);
                    existe = 0;
                }
            }
            if (existe == 1)
            {
                system("cls");
                printf("El competidor ingresado no existe\n\n");
            }
            break;
        default:
            system("cls");
            printf("Error\n");
            break;
        }
        fclose(archivo);
    }

    return;
}
//FIN BUSCAR

void modificar(FILE *archivo, char *nombre)
{
    //REUTILIZO LA FUNCION BUSCAR
    int opc, nroOrden = 0, nroComp = 0, nReg = 0;
    int existe = 1;//VARIABLE "BANDERA" PARA DETERMINAR SI LA OPCION SELECCIONADA POR EL USUARIO YA EXISTE
    competidores competidor;
    archivo = fopen(nombre, "r+b");
    if (archivo == NULL)
    {
        printf("Error, el archivo no pudo abrirse\n");
    }
    else
    {
        // SE LE SOLICITA UNA OPCION DE BUSQUEDA AL USUARIO
        printf("========================\n");
        printf("1: Numero de orden\n");
        printf("2: ID de competidor\n");
        printf("========================\n");
        scanf("%d", &opc);
        fflush(stdin);
        // Se compara esa opcion y se hace una busqueda acorde
        switch (opc)
        {
        case 1:
            printf("Ingrese el numero de orden: ");
            int isdigit = scanf("%d", &nroOrden);
            fflush(stdin);
            // VALIDO QUE HAYA INGRESADO UN NUMERO Y MAYOR A 0
            while (nroOrden <= 0 || isdigit == 0)
            {
                if (nroOrden <= 0)
                {
                    printf("Ingrese un numero mayor a 0: ");
                    isdigit = scanf("%d", &nroOrden);
                    fflush(stdin);
                }
                else if (isdigit == 0)
                {
                    printf("Error, ingrese u numero\n");
                    isdigit = scanf("%d", &nroOrden);
                    fflush(stdin);
                }
            }//FIN VALIDAR NUMERO INGRESADO

            //RECORRO EL ARCHIVO
            fseek(archivo, 0, SEEK_END);
            nReg = ftell(archivo) / sizeof(competidores);
            rewind(archivo);
            for (int i = 0; i < nReg; i++)
            {
                // Se lee la linea del archivo y se guardan los datos en competidor
                fread(&competidor, sizeof(competidores), 1, archivo);
                // Se compara el nro de orden
                if (nroOrden == competidor.index)
                {
                    printf("Que valor desea modificar?\n");
                    printf("Edad (oprima 1) - Tiempo (oprima 2)\n");
                    scanf("%d", &opc);
                    fflush(stdin);
                    switch(opc)
                    {
                        case 1:
                            printf("Ingrese la edad a guardar: ");
                            scanf("%d",&competidor.edad);
                            fflush(stdin);
                            rewind(archivo);
                            fseek(archivo, (competidor.index - 1) * sizeof(competidores), SEEK_CUR);
                            fwrite(&competidor,sizeof(competidores),1,archivo);
                            existe = 0;
                            fclose(archivo);
                            break;

                        case 2:
                            printf("Ingrese el tiempo a guardar: ");
                            scanf("%6f",&competidor.tiempo);
                            fflush(stdin);
                            rewind(archivo);
                            fseek(archivo, (competidor.index - 1) * sizeof(competidores), SEEK_CUR);
                            fwrite(&competidor,sizeof(competidores),1,archivo);
                            existe = 0;
                            fclose(archivo);
                            break;

                    }//FIN SWITCH EDAD O TIEMPO
                }
            }
            if (existe == 1)
            {
                system("cls");
                printf("El competidor ingresado no existe\n\n");
            }
            break;
        case 2:
            printf("Ingrese el ID de competidor: ");
            scanf("%d", &nroComp);
            fflush(stdin);
            fseek(archivo, 0, SEEK_END);
            nReg = ftell(archivo) / sizeof(competidores);
            rewind(archivo);
            // Se recorre el archivo
            for (int i = 0; i < nReg; i++)
            {
                // Se lee la linea del archivo y se guardan los datos en competidor
                fread(&competidor, sizeof(competidores), 1, archivo);
                // Se compara el ID
                if (nroComp == competidor.id)
                {
                    //ACA TENGO QUE MODIFICAR LA ACCION CUANDO ENCUENTRE EL CORREDOR
                    printf("Que valor desea modificar?\n");
                    printf("Edad (oprima 1) - Tiempo (oprima 2)\n");
                    scanf("%d", &opc);
                    fflush(stdin);
                    switch(opc)
                    {
                        case 1:
                            printf("Ingrese la edad a guardar: ");
                            scanf("%d",&competidor.edad);
                            fflush(stdin);
                            rewind(archivo);
                            fseek(archivo, (competidor.index - 1) * sizeof(competidores), SEEK_CUR);
                            fwrite(&competidor,sizeof(competidores),1,archivo);
                            existe = 0;
                            fclose(archivo);
                            break;

                        case 2:
                            printf("Ingrese el tiempo a guardar: ");
                            scanf("%6f",&competidor.tiempo);
                            fflush(stdin);
                            rewind(archivo);
                            fseek(archivo, (competidor.index - 1) * sizeof(competidores), SEEK_CUR);
                            fwrite(&competidor,sizeof(competidores),1,archivo);
                            existe = 0;
                            fclose(archivo);
                            break;
                    }//FIN SWITCH EDAD O TIEMPO
                }//FIN IF ENCUENTRO ID
            }//FIN RECORRER ARCHIVO

            if (existe == 1)
            {
                printf("El competidor ingresado no existe\n\n");
            }//FIN VALIDACION SI EXISTE EL COMPETIDOR MENCIONADO

            break;
        default:
            printf("Error, no se ingreso una respuesta valida. Intente con los datos recomendados\n");
            break;
        }//FIN SWITCH PARA BUSCAR SEGUN ID U ORDEN

        fclose(archivo);
    }

    return;
}
//FIN FUNCION 7 - BUSCAR Y MODIFICAR

//FUNCION 8 - BAJA LOGICA
void bajaLogica(FILE *archivo, char *nombre)
{
    //REUTILIZO LA FUNCION BUSCAR
    int opc, nroOrden = 0, nroComp = 0, nReg = 0;
    int existe = 1;//VARIABLE "BANDERA" PARA DETERMINAR SI LA OPCION SELECCIONADA POR EL USUARIO YA EXISTE
    competidores competidor;
    archivo = fopen(nombre, "r+b");
    if (archivo == NULL)
    {
        printf("Error, el archivo no pudo abrirse\n");
    }
    else
    {
        printf("Ingrese el numero de orden: ");
        int isdigit = scanf("%d", &nroOrden);
        fflush(stdin);
        // VALIDO QUE HAYA INGRESADO UN NUMERO Y MAYOR A 0
        while (nroOrden <= 0 || isdigit == 0)
        {
            if (nroOrden <= 0)
            {
                printf("Ingrese un numero mayor a 0: ");
                isdigit = scanf("%d", &nroOrden);
                fflush(stdin);
            }
            else if (isdigit == 0)
            {
                printf("Error, ingrese u numero\n");
                isdigit = scanf("%d", &nroOrden);
                fflush(stdin);
            }
        }//FIN VALIDAR NUMERO INGRESADO

        //RECORRO EL ARCHIVO
        fseek(archivo, 0, SEEK_END);
        nReg = ftell(archivo) / sizeof(competidores);
        rewind(archivo);
        for (int i = 0; i < nReg; i++)
        {
            // Se lee la linea del archivo y se guardan los datos en competidor
            fread(&competidor, sizeof(competidores), 1, archivo);
            // Se compara el nro de orden
            if (nroOrden == competidor.index)
            {
                printf("Usted va a dar de baja un competidor\n");
                printf("Para continuar oprima 1 - Para volver al menu (oprima 2)\n");
                scanf("%d", &opc);
                fflush(stdin);
                switch(opc)
                {
                    case 1:
                        competidor.activo = 0;
                        fflush(stdin);
                        rewind(archivo);
                        fseek(archivo, (competidor.index - 1) * sizeof(competidores), SEEK_CUR);
                        fwrite(&competidor,sizeof(competidores),1,archivo);
                        existe = 0;
                        fclose(archivo);
                        break;

                    case 2:
                        printf("Volviendo al menu...\n");
                        existe = 0;
                        fclose(archivo);
                        break;

                }//FIN SWITCH EDAD O TIEMPO
            }
        }
        if (existe == 1)
        {
            printf("El competidor ingresado no existe\n\n");
        }
        fclose(archivo);
    }
    return;
}
//FIN BAJA LOGICA


// 9- BAJA FISICA
void bajafisica(FILE * archivo, char *nombre)
{
    FILE *temp;
    competidores competidor;
    archivo=fopen(nombre,"r+b");
    temp= fopen("competidores_bajas_.xyz","w+b");

    fseek(archivo,0,SEEK_END);

    while(fread(&competidor,sizeof(competidores),1,archivo)==1){
        if(competidor.activo == 0){
            fwrite(&competidor,sizeof(competidores),1,temp);
        }
    }
    fclose(temp);
    fclose(archivo);
    rename("competidores_bajas_.xyz","competidores_bajas_");
    remove("competidores_bajas_.xyz");
    printf("\n***--Archivo actualizado--***\n");
    return;
}

