//Proyecto 2

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define N 50000
#define CZ 48


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
    int i, j;
    float aux;
    for (i = 1; i < n; i++){   //Ordenar el vector
		j = i-1;
		aux = P[i];
		while (aux<P[j]){
			P[j+1] = P[j];
			j--;
			if (j == -1)
				break;
		}
		P[j+1] = aux;
	}
    return 0;
}
float mediaA(float P[], int n) {
    int i;
    float med;
    for (i = 0, med = 0; i < n; med+=P[i++]);
    return med/n;
}
float mediaG(float P[], int n) {
    int i=0;
    float r=1;
    for (i=0;i<n;i++){
        if(P[i]<0)
        P[i] = P[i]*-1.0;
        r *= P[i];
    }
    return powf(r, (1.0/(float)n));
}
float mediana(float P[], int n){
	int num;
	ordenar(P,n);
	num = ceil(n/2);
	return P[num];
}
float moda(){
	
    return 0;
}
// Falta completar varianza
float varianza(float P[], int n) {
    int i=0;
    float r;
    for(i=0;i<n;i++){
        r += ((P[i] - mediaA(P,n))*(P[i] - mediaA(P,n))) / (n);
        //r += P[i];
    }
    return r;
}
float desviacionE(float P[], int n) {
    int i=0;
    float r;
    for(i=0;i<n;i++){
        r += ((P[i] - mediaA(P,n))*(P[i] - mediaA(P,n))) / (n);
        //r += P[i];
    }
    return sqrt(r);
}
float coeficienteV(float P[],int n) {
    return (desviacionE(P,n) / (mediaA(P,n)*100));
}
float cuartiles(float *P,int n,float *Q)    //Pegar en main despuÃˆs: cuartiles(P,n,Cuart);
{
    int pos, i;
    for(i=0;i<3;i++)
    {
        pos=ceil((i+1)*n/4);
        Q[i]=n%2!=0?P[pos]:(P[pos]+P[pos+1])/2;
    }
    return 0;
}
float deciles(float *P,int n,float *D)  //Pegar en main despuÃˆs: deciles(P,n,Deci);
{
    int pos, i;
    for(i=0;i<9;i++)
    {
        pos=ceil((i+1)*n/10);
        D[i]=n%2!=0?P[pos]:(P[pos]+P[pos+1])/2;
    }
    return 0;
}
float percentiles(float *P,int n,float *Pc) //Pegar en main despuÃˆs: percentiles(P,n,Percen);
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
    float max, min, *P, Cuart[3], Deci[9], Percen[99];
    int opc, n, i;
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
    if (opc != 1){
		P = (float*)malloc(n*sizeof(float));
        for (i = 0; i < n; i++)
        P[i] = (max - min)*rand() / RAND_MAX + min;
    }
	for(i=0;i<n;i++)
        printf("P[%i]: %.3f\n", i+1, P[i]);
    printf("Ordenados:\n");
    ordenar(P,n);
    for(i=0;i<n;i++)
        printf("P[%i]: %.3f\n", i+1, P[i]);

    //(Registrar resultados en el texto)
    printf("Sus resultados se han guardado en el texto \"Analisis_estadistico.txt\".");
    fprintf(fp,"Resultados:\n");

    fprintf(fp,"Maximo: %f\n:", P[0]);

    fprintf(fp,"Minimo: %f\n:", P[n]);

    fprintf(fp,"Media: %f\n", mediaA(P,n));

    fprintf(fp,"Media geometrica: %f\n", mediaG(P, n));

    fprintf(fp,"Mediana: %f\n", mediana(P,n));

    fprintf(fp,"Varianza: %f\n", varianza(P, n));

    fprintf(fp,"Desviacion Estandar: %f\n", desviacionE(P, n));

    fprintf(fp,"Coeficiente de Variacion: %f\n",coeficienteV(P,n));

    fprintf(fp,"Cuartiles:\n");
    for(i=0;i<3;i++)
    {
        cuartiles(P,n,Cuart);
        fprintf(fp,"\t%f",Cuart[i]);
    }

    fprintf(fp,"\nDeciles:\n");
    for(i=0;i<9;i++)
    {
        deciles(P,n,Deci);
        fprintf(fp,"\t%f",Deci[i]);
    }

    fprintf(fp,"\nPercentiles:\n");
    for(i=0;i<99;i++)
    {
        percentiles(P,n,Percen);
        fprintf(fp,"\t%f",Percen[i]);
    }

    fclose(fp);
    free(P);
return 0;
}