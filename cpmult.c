#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
typedef struct {
	char code[2];
	double real;
	double img;
} Complex;

int main(int argc, char * argv[])
{
    FILE * arq1 = NULL;
    FILE * arq2 = NULL;
    FILE * arq3 = NULL;
    Complex Num[3];
    int real, img;
    double aux;
    if (argc != 4)
    {
        printf("Modelo de uso: ./cpsub <file_name_1> <file_name_2> <file_name_out>\n");
        return 0;
    }
    
    arq1 = fopen(argv[1], "rb");
    if (arq1 == NULL)
    {
        printf("Erro ao abrir primeiro arquivo\n");
        return 0;
    }
    arq2 = fopen(argv[2], "rb");
    if (arq2 == NULL)
    {
        printf("Erro ao abrir o segundo arquivo\n");
        return 0;
    }
    arq3 = fopen(argv[3], "wb");
    if (arq3 == NULL)
    {
        printf("Erro ao abrir o terceiro arquivo arquivo\n");
        return 0;
    }
    
    fread(Num[0].code, sizeof(char), 2, arq1);
    if (Num[0].code[0] != 'C' || Num[0].code[1] != 'P')
    {
        printf("Arquivo invalido\n");
        fclose(arq1);
        return 0;
    }
    fread(&(Num[0].real), sizeof(double), 1, arq1);
    fread(&(Num[0].img), sizeof(double), 1, arq1);


    fread(Num[1].code, sizeof(char), 2, arq2);
    if (Num[1].code[0] != 'C' || Num[1].code[1] != 'P')
    {
        printf("Arquivo invalido\n");
        fclose(arq2);
        return 0;
    }
    fread(&(Num[1].real), sizeof(double), 1, arq2);
    fread(&(Num[1].img), sizeof(double), 1, arq2);
    
    strcpy(Num[2].code, "CP");
    Num[2].real = Num[0].real * Num[1].real - Num[0].img * Num[1].img;
    Num[2].img = Num[0].real *  Num[1].img + Num[0].img * Num[1].real;
    fwrite(Num[2].code, sizeof(char), 2, arq3);
    fwrite(&Num[2].real, sizeof(double), 1, arq3);
    fwrite(&Num[2].img, sizeof(double), 1, arq3);

    fclose(arq1);
    fclose(arq2);
    fclose(arq3);
    return 0;
}