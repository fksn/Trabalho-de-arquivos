#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
typedef struct {
	char code[2];
	double real;
	double img;
} Complex;

Complex get_double(char op[2], char str[32]);

int main(int argc, char * argv[])
{
    FILE * arq = NULL;
    Complex Num;
    if (argc != 4)
    {
        printf("Modelo de uso: ./cpbuild [OPTION] <complex_number_string> <file_name>\n");
        return 0;
    }
    if (strcmp(argv[1],"-a") != 0 && strcmp(argv[1],"-p") != 0 && strcmp(argv[1],"-v") != 0)
    {
        printf("[OPTION] deve ser -a, -p ou -v\n");
        return 0;
    }

    arq = fopen(argv[3], "wb");
    if (arq == NULL)
    {
        printf("Erro ao abrir arquivo\n");
        return 0;
    }
    Num = get_double(argv[1], argv[2]);
    fwrite(Num.code, sizeof(char), 2, arq);
    fwrite(&Num.real, sizeof(double), 1, arq);
    fwrite(&Num.img, sizeof(double), 1, arq);
    fclose(arq);
    return 0;
}

Complex get_double(char op[2], char str[32])
{
    Complex N;
    double x, y;
    char * pch;
    char aux[32];
    int i = 0, n, bool;
    strcpy(N.code, "CP");
    if (strcmp( op, "-a") == 0)
    {
        while (1)
        {
            i++;
            if (str[i] == '+')
            {
               bool = 0;
               n = i;
               break;
            }
            else
            {
                if (str[i] == '-')
                {
                    bool = 1;
                    n = i;
                    break;
                }
            }
        }
        N.real = atof(str);
        str[n] = '+';
        pch = strtok (str,"+");
        pch = strtok (NULL, "+");
        N.img = atof(pch);
        if (bool == 1)
        {
            N.img *= -1;
        }
        return N;
    }
    else
    {
        if (strcmp( op, "-p") == 0)
        {
            x = atof(str);
            pch = strtok (str,":");
            pch = strtok (NULL, ":");
            y = atof(pch);
            N.real = cos((y*M_PI)/180) * x;
            N.img = sin((y*M_PI)/180) * x;
            return N;
        }
        else
        {
            if (strcmp( op, "-v") == 0)
            {
                pch = strtok (str,"[");
                strcpy(aux, pch);
                N.real = atof(aux);
                pch = strtok (str,",");
                pch = strtok (NULL, ",");
                N.img = atof(pch);
                return N;
            }
        }
    }
    return N;
}