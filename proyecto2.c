//Proyecto 2

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define N 50000
#define CZ 48

//nuevo

int str2num(char *str)
{
	int num, j;
	num = 0;
	j = str[0]==45? 1 : 0;
	while (str[j] != '\0')
	{
		num *= 10;
		num += (int)(str[j] - CZ);
		j++;
	}
	num = str[0] == 45 ? -num : num;
	return num;
}
float ordenar(float P[], int n){
    int i, j, aux;
    for (i = 1; i < n; i++){   //Ordenar el vector
		j = i-1;
		while (P[j]>P[i]){
            aux = P[j];
			P[j] = P[i];
			j--;
            P[i] = aux;
			if (j == -1)
				break;
		}
	}
    return 0;
}
float mediaA(float P[], int n) {
    int i;
    float med;
    for (i = 0, med = 0; i < n; med+=P[i++]);
    return med/n;
}
float mediaG(float P[]) {
    int i=0, n;
    float r;
    for (i=0;i<n;i++){
        r *= P[i];
    }
    r = sqrtf(r);
    return r;
}
float moda(){
    return 0;
}
// Falta completar varianza
float varianza(float P[], int n,float media) {
    int i=0;
    float r;
    for(i=0;i<n;i++){
        //r += ((P[i] - media)(P[i] - media)) / ((float)(n));
        r += P[i];
    }
    return r;
}
float desviacionE(float varianza) {
    return sqrt(varianza);
}
float coeficienteV(float desviacion, float media) {
    return (desviacion/media*100);
}
float cuartiles(float *P,int n,float *Q)    //Pegar en main despuÈs: cuartiles(P,n,Cuart);
{
    int pos, i;
    for(i=0;i<3;i++)
    {
        pos=ceil((i+1)*n/4);
        Q[i]=n%2!=0?P[pos]:(P[pos]+P[pos+1])/2;
    }
    return 0;
}
float deciles(float *P,int n,float *D)  //Pegar en main despuÈs: deciles(P,n,Deci);
{
    int pos, i;
    for(i=0;i<9;i++)
    {
        pos=ceil((i+1)*n/10);
        D[i]=n%2!=0?P[pos]:(P[pos]+P[pos+1])/2;
    }
    return 0;
}
float percentiles(float *P,int n,float *Pc) //Pegar en main despuÈs: percentiles(P,n,Percen);
{
    int pos, i;
    for(i=0;i<99;i++)
    {
        pos=ceil((i+1)*n/100);
        Pc[i]=n%2!=0?P[pos]:(P[pos]+P[pos+1])/2;
    }
    return 0;
}



int main(int argc, char *argv[]) {
    //*P
    float max, min, *P, aux, AnEs[9], Cuart[3], Deci[9], Percen[99];
    int opc, n, i, j;
    FILE *fp;
    fp = fopen("Analisis_estadistico.txt", "w");
    srand(time(NULL));
    switch (argc) {
        case 1:
            printf("1: Entrada de datos manual\n2: Datos aleatorios\n");
            scanf("%i",&opc);
            // Manuales
            if (opc == 1) {
            do {
                printf("Ingrese el numero de elementos: ");
                scanf("%i", &n);
                }while(n<1 || n>N);
            P = (float*)malloc(n*sizeof(float));
            for(i = 0;i < n;i++) {
                printf("P[%i] :",i+1);
                scanf("%f",&P[i]);
            }
            // Aleatorios
            }else{
            do {
                printf("Ingrese el numero de elementos: ");
                scanf("%i", &n);
                }while(n<1 || n>N);
            printf("Ingrese el valor minimo: ");
            scanf("%f", &min);
            printf("Ingrese el valor maximo: ");
            scanf("%f", &max);
            }
            break;
        case 2:
            n = str2num(argv[1]);
            printf("Ingrese el valor minimo: ");
            scanf("%f", &min);
            printf("Ingrese el valor maximo: ");
            scanf("%f", &max);
            break;
        case 3:
            n = str2num(argv[1]);
            min = str2num(argv[2]);
            printf("Ingrese el valor maximo: ");
            scanf("%f", &max);
            break;
        default:
            n = str2num(argv[1]);
            min = str2num(argv[2]);
            max = str2num(argv[3]);
    }
    /*while (n < 1)
	{
		printf("Ingrese el numero de elementos: ");
		scanf("%d", &n);
	}
    */
	if (min > max)
    {
		min = min + max;
		max = min - max;
		min = min - max;
	}
    P = (float*)malloc(n*sizeof(float));

    if (opc != 1){
        for (i = 0; i < n; i++)
        P[i] = (max - min)*rand() / RAND_MAX + min;
    }
	
    printf("Ordenados:\n");
    ordenar(P,n);
    for(i=0;i<n;i++)
        printf("P[%i]: %.3f\n", i+1, P[i]);
    //(Registrar resultados en el texto)

    for(i=0;i<9;i++)     
        fprintf(fp,"Analisis %d: %f\n",i+1,AnEs[i]);

    fprintf(fp,"Cuartiles:\n");
    for(i=0;i<3;i++)
        fprintf(fp,"\t%f",Cuart[i]);

    fprintf(fp,"Deciles:\n");
    for(i=0;i<9;i++)
        fprintf(fp,"\t%f",Deci[i]);

    fprintf(fp,"Percentiles:\n");
    for(i=0;i<99;i++)
        fprintf(fp,"\t%f",Percen[i]);
    
    fclose(fp);
    free(P);
return 0;
}
