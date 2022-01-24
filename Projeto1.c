#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int thresholding(FILE *in, char *arr);
int negative(FILE *in, char *arr);
int histogram(FILE *in, char *arr);
void openpgm(FILE *in, char *arr);
void closepgm(FILE *in);
int main()
{
    FILE *in;
    char *arr;
    arr = malloc(1024 * sizeof(char));
    printf("Digite o nome do arquivo(Insira a imagem na pasta que contem o programa): ");
    scanf("%s", arr);
    arr = strcat(arr, ".pgm");
    in = fopen(arr, "rb");
    if (in == NULL)
    {
        printf("Failed to open the file");
        return 1;
    }
    thresholding(in, arr);
    negative(in, arr);
    histogram(in, arr);
    closepgm(in);
    return 0;
}
void openpgm(FILE *in, char *arr)
{
    in = fopen(arr, "rb");
    if (in == NULL)
    {
        printf("Failed to open the file");
        return;
    }
    return;
}
void closepgm(FILE *in)
{
    fclose(in);
}

int thresholding(FILE *in, char *arr)
{
    int i, j, line, column, max_intense, pixel;
    FILE *out;
    out = fopen("thresholding_example.pgm", "wb");
    if (out == NULL)
    {
        printf("Failed to open the file");
        return 1;
    }
    char linePrincipal[3];
    fscanf(in, "%[^\n]", &linePrincipal);
    fprintf(out, "%s\n", linePrincipal);

    fscanf(in, "%d %d", &column, &line);
    fprintf(out, "%d %d\n", column, line);

    fscanf(in, "%d", &max_intense);
    fprintf(out, "%d\n", max_intense);
    for (i = 0; i < line; i++)
    {
        for (j = 0; j < column; j++)
        {
            pixel = 0;
            fscanf(in, "%d", &pixel);
            if (pixel < 150)
            {
                pixel = 0;
                fprintf(out, "%d ", pixel);
            }

            else
            {
                pixel = 255;
                fprintf(out, "%d ", pixel);
            }
        }
    }
    closepgm(in);
    fclose(out);
    return 0;
}

int negative(FILE *in, char *arr)
{
    openpgm(in, arr);
    int i, j, line, column, max_intense, aux;
    FILE *out;
    out = fopen("negative_example.pgm", "wb");
    if (out == NULL)
    {
        printf("Failed to open the file");
        return 1;
    }
    char linePrincipal[3];
    fscanf(in, "%[^\n]", &linePrincipal);
    fprintf(out, "%s\n", linePrincipal);

    fscanf(in, "%d %d", &column, &line);
    fprintf(out, "%d %d\n", column, line);

    fscanf(in, "%d", &max_intense);
    fprintf(out, "%d\n", max_intense);
    int pixel;
    for (i = 0; i < line; i++)
    {
        for (j = 0; j < column; j++)
        {
            fscanf(in, "%d", &pixel);
            aux = max_intense - pixel;
            fprintf(out, "%d ", aux);
        }
    }
    closepgm(in);
    fclose(out);
    return 0;
}

int histogram(FILE *in, char *arr)
{
    openpgm(in, arr);
    int aux, line, column, i, j, pixel;
    FILE *out;
    out = fopen("histogram.txt", "wb");
    if (out == NULL)
    {
        printf("Failed to open the file");
        return 1;
    }
    char linePrincipal[3];
    fscanf(in, "%[^\n]", &linePrincipal);
    fscanf(in, "%d %d", &column, &line);
    fscanf(in, "%d", &aux);
    int *counter;
    counter = (int *)malloc(aux * sizeof(int));
    for (i = 0; i < aux; i++)
    {
        counter[i] = 0;
    }
    for (i = 0; i < line; i++)
    {
        for (j = 0; j < column; j++)
        {

            fscanf(in, "%d", &pixel);
            counter[pixel]++;
        }
    }
    for (i = 0; i <= aux; i++)
    {
        fprintf(out, "Quantity of pixels of %d is: %d\n", i, counter[i]);
    }
    closepgm(in);
    fclose(out);
    return 0;
}
