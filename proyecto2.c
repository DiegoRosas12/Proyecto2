//Proyecto 2

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
//comment
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

float mediaA(){
    return 0;
}
float mediaG(float P[]) {
    int i=0;
    float r;
    for (i=0;i<n;i++){
        r *= P[i];
    }
    r = sqrtf(r);
    return r;
}
float varianza(float P[], int n,float media) {
    int i=0;
    float r;
    for(i=0;i<n;i++){
        r += ((P[i] - media)(P[i] - media)) / ((float)(n));
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
    int pos;
    for(i=0;i<3;i++)
    {
        pos=ceil((i+1)*n/4);
        Q[i]=n%2!=0?P[pos]:(P[pos]+P[pos+1])/2;
    }
    return 0;
}

float deciles(float *P,int n,float *D)  //Pegar en main despuÈs: deciles(P,n,Deci);
{
    int pos;
    for(i=0;i<9;i++)
    {
        pos=ceil((i+1)*n/10);
        D[i]=n%2!=0?P[pos]:(P[pos]+P[pos+1])/2;
    }
    return 0;
}

float percentiles(float *P,int n,float *Pc) //Pegar en main despuÈs: percentiles(P,n,Percen);
{
    int pos;
    for(i=0;i<3;i++)
    {
        pos=ceil((i+1)*n/100);
        Pc[i]=n%2!=0?P[pos]:(P[pos]+P[pos+1])/2;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    float max, min, *P, aux, AnEs[9], Cuart[3], Deci[9], Percen[99];
    int opc, n, i;
    /*FILE *fp;
    fp = fopen("Analisis_estadistico.txt", "w");*/
    srand(time(NULL));
    switch (argc) {
        case 1:
            printf("1: Entrada de datos manual\n2: Datos aleatorios\n");
            scanf("%i",&opc);
            // Manuales
            if (opc == 1) {
            do {
                printf("Ingrese el n˙mero de elementos: ");
                scanf("%i", &n);
                }while(n<1 || n>N);
            for(i = 0;i < n;i++) {
                printf("P[%i] :",i+1);
                scanf("%f",&P[i]);
            }
            // Aleatorios
            }else{
            do {
                printf("Ingrese el n˙mero de elementos: ");
                scanf("%i", &n);
                }while(n<1 || n>N);
            printf("Ingrese el valor minimo: ");
            scanf("%f", &min);
            printf("Ingrese el valor maximo: ");
            scanf("%f", &max);
            if (max < min) {
            max = max + min;
            min = max - min;
            max = max - min;
            }
            P = (int*)malloc(n*sizeof(int));
	        for (i = 0; i < n; i++)
		    P[i] = (max - min)*rand() / RAND_MAX + min;
            for(i=0;i<n;i++)
            printf("P[%i]: %.3f\n", i, P[i]);}
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
    while (n < 1)
	{
		printf("Ingrese el numero de elementos: ");
		scanf("%d", &n);
	}
	if (min > max)
	{
		min = min + max;
		max = min - max;
		min = min - max;
	}
	for (i = 0; i < n; i++)
        P[i] = (max - min)*rand() / RAND_MAX + min;
    for(i=0;i<n;i++)
        printf("P[%i]: %.3f\n", i, P[i]);
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
	/*Eliminar esto, que debe hacer todos los an·lisis
    opc=\0;
    printf("Que desea calcular?\n1: Maximo\n2: Minimo\n3: Media aritmetica\n4: Media geometrica\n5: Mediana\n6: Moda\n7: Varianza\n8: Desviacion estandar\n9: Coeficiente de variacion\n10: Cuartiles\n11: Deciles\n12: Percentiles\n");
    scanf("%i", &opc);
    switch (opc) {
        case 1:
        printf("Maximo\n");
        break;
        case 7:
        printf("Varianza\n");
        float media;
        media = mediaA();
        printf("Varianza: %f\n", varianza(P,n,media));
        case 8:
        printf("Desviacion estandar\n");
        float media;
        media = mediaA();
        printf("Varianza: %f\n", varianza(P,n,media));
        default:
            break;
    }*/
    /*for(i=0;i<9;i++)     (Registrar resultados en el texto)
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
    fclose(fp);*/
    free(P);
return 0;
}
