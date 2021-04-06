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
    FILE * arq = NULL;
    Complex Num;
    int real, img;
    double aux;
    if (argc != 3)
    {
        printf("Modelo de uso: ./cpview [OPTION] <file_name>\n");
        return 0;
    }
    if (strcmp(argv[1],"-a") != 0 && strcmp(argv[1],"-p") != 0 && strcmp(argv[1],"-v") != 0)
    {
        printf("[OPTION] deve ser -a, -p ou -v\n");
        return 0;
    }
    
    arq = fopen(argv[2], "rb");
    if (arq == NULL)
    {
        printf("Erro ao abrir arquivo\n");
        return 0;
    }

    fread(Num.code, sizeof(char), 2, arq);
    if (Num.code[0] != 'C' || Num.code[1] != 'P')
    {
        printf("Arquivo invalido\n");
        fclose(arq);
        return 0;
    }
    else
    {
        fread(&(Num.real), sizeof(double), 1, arq);
        real = Num.real;
        fread(&(Num.img), sizeof(double), 1, arq);
        img = Num.img;
        if (strcmp(argv[1],"-a") == 0)
        {
            printf("%.2lf%+.2lfi\n",Num.real, Num.img);
        }
        else
        {
            if (strcmp(argv[1],"-v") == 0)
            {
                printf("[%.2lf,%.2lf]\n",Num.real, Num.img);
            }
            else
            {
                aux = sqrt( (Num.real * Num.real) + (Num.img * Num.img) );
                printf("%.2lf;", aux);
                aux = atan(Num.img/Num.real)* 180 / M_PI;
                printf("%.2lf\n", aux);
            }
        }
    }
    fclose(arq);
    return 0;
}