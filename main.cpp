#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    char meno[60];
    char pohlavie[60];
    int roknar;
    char spz[9];
    int typ;
    int pokuta;
    int date;
} PRIESTUPOK;

void velkost(int *n){
    char pomocna[60];
    FILE *f;
    f=fopen("../priestupky.txt","r");
    while(feof(f) == 0){
        fgets(pomocna,60,f);
        (*n)++;
    }
    if((*n)%7==(*n)/7) {
        (*n) = (*n) / 7;
    } else {
        (*n)=0;
    }
}

void funkcia_v(PRIESTUPOK *osoba, int n){
    if(osoba != 0){
        for (int i = 0; i < n; i++) {
            printf("%d %d",i,n);
            printf("meno priezvisko: %spohlavie: %srok narodenia: %d\nSPZ: %styp priestupku: %d\nvyska pokuty: %d\ndatum priestupku: %d\n\n",osoba[i].meno, osoba[i].pohlavie, osoba[i].roknar, osoba[i].spz, osoba[i].typ, osoba[i].pokuta, osoba[i].date);
        }
    }
}

void funkcia_x(PRIESTUPOK *osoba,int n){
    if (osoba != 0){
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);

        for (int cyklovy = 0; cyklovy < n; cyklovy++) {
            if(osoba[cyklovy].typ==0 && ((tm.tm_year + 1900) == (osoba[cyklovy].date / 10000))){
                printf("meno priezvisko: %sSPZ: %sdatum priestupku: %d\n\n", osoba[cyklovy].meno, osoba[cyklovy].spz, osoba[cyklovy].date);
            }
        }
    }
}

float funkcia_r(PRIESTUPOK *osoba, int n) {
    if (osoba != 0) {
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        float malepok = 0, velkepok = 0;
        for (int cyklovy = 0; cyklovy < n; cyklovy++) {
            if (((tm.tm_mon + 1) == ((osoba[cyklovy].date % 10000) / 100))) {
                if (osoba[cyklovy].typ == 1) {
                    malepok += 0.052 * (osoba[cyklovy].pokuta);
                } else {
                    velkepok += 0.038 * (osoba[cyklovy].pokuta);
                }
            }
        }
        return (malepok + velkepok);
    }
}

void funkcia_p(PRIESTUPOK *osoba, int n){
    if (osoba != 0) {
        for (int cyklovy = 0; cyklovy < n; cyklovy++) {
            int palindrom=1;
            for(int k=0;k<7;k++){
                if(osoba[cyklovy].spz[k] != osoba[cyklovy].spz[6-k]){
                    palindrom=0;
                    break;

                }
            }
            if(palindrom == 1){
                printf("%s%s",osoba[cyklovy].meno, osoba[cyklovy].spz);
            }
        }
    }
}

void funkcia_a(PRIESTUPOK *osoba,int *n){
    FILE *f;
    f=fopen("../priestupky.txt","r+");
    free(osoba);
    (*n)++;
    if((osoba = (PRIESTUPOK *) malloc((*n) * sizeof(PRIESTUPOK))) != 0){
        char temp[60];
        for(int j = 0;j < (*n)-1; j++){
            fgets(osoba[j].meno, 60, f);
            printf("stare %s",osoba[j].meno);
            fgets(osoba[j].pohlavie, 60, f);
            fgets(temp, 60, f);
            osoba[j].roknar = atoi(temp);
            fgets(osoba[j].spz, 9, f);
            fgets(temp, 60, f);
            osoba[j].typ = atoi(temp);
            fgets(temp, 60, f);
            osoba[j].pokuta = atoi(temp);
            fgets(temp, 60, f);
            osoba[j].date = atoi(temp);
            fgets(temp, 60, f);
            strcpy(temp, "");
        }
        fputs("\n",f);
        scanf(" %[^\t\n]s",osoba[(*n)-1].meno);
        fprintf(f,"%s\n",osoba[(*n)-1].meno);
        scanf("%s",osoba[(*n)-1].pohlavie);
        fprintf(f,"%s\n",osoba[(*n)-1].pohlavie);
        scanf("%d",&osoba[(*n)-1].roknar);
        fprintf(f,"%d\n",osoba[(*n)-1].roknar);
        scanf("%s",osoba[(*n)-1].spz);
        fprintf(f,"%s\n",osoba[(*n)-1].spz);
        scanf("%d",&osoba[(*n)-1].typ);
        fprintf(f,"%d\n",osoba[(*n)-1].typ);
        scanf("%d",&osoba[(*n)-1].pokuta);
        fprintf(f,"%d\n",osoba[(*n)-1].pokuta);
        scanf("%d",&osoba[(*n)-1].date);
        fprintf(f,"%d\n",osoba[(*n)-1].date);
        printf("nult%s posl%s",osoba[(*n)-1].meno,osoba[0].meno);
        int i=(*n)-1;
        printf("meno priezvisko: %spohlavie: %srok narodenia: %d\nSPZ: %styp priestupku: %d\nvyska pokuty: %d\ndatum priestupku: %d\n\n",osoba[i].meno, osoba[i].pohlavie, osoba[i].roknar, osoba[i].spz, osoba[i].typ, osoba[i].pokuta, osoba[i].date);

    }
    fclose(f);
}

int main ()
{
    char vstup;
    int n = 0;
    FILE *f;
    f=fopen("../priestupky.txt", "r");
    if (f == nullptr) {
        printf("subor neexistuje\n");
        return 0;
    }
    velkost(&n);
    PRIESTUPOK *osoba=0;
    do {
        switch (vstup){
            case 'o':
                FILE *f;
                f=fopen("../priestupky.txt", "r");
                if (f == nullptr) {
                    printf("subor neexistuje\n");
                    return 0;
                }
                if(osoba != 0){
                    free(osoba);
                }
                if((osoba = (PRIESTUPOK *) malloc(n * sizeof(PRIESTUPOK))) == 0 || (n * sizeof(PRIESTUPOK)) == 0){
                    printf("Pole nie je naplnené.");
                }
                char temp[60];
                for(int j = 0;j < n; j++){
                    fgets(osoba[j].meno, 60, f);
                    fgets(osoba[j].pohlavie, 60, f);
                    fgets(temp, 60, f);
                    osoba[j].roknar = atoi(temp);
                    fgets(osoba[j].spz, 9, f);
                    fgets(temp, 60, f);
                    osoba[j].typ = atoi(temp);
                    fgets(temp, 60, f);
                    osoba[j].pokuta = atoi(temp);
                    fgets(temp, 60, f);
                    osoba[j].date = atoi(temp);
                    fgets(temp, 60, f);
                    strcpy(temp, "");
                }
                fclose(f);
                break;
            case 'v':
                printf("%d",n);
                funkcia_v(osoba,n);
                break;
            case 'x':
                funkcia_x(osoba,n);
                break;
            case 'r':
                printf("%.2f\n",funkcia_r(osoba,n));//treba upravit aby sa nevypisovalo ked sa nic nezhoduje .. len printf dat do funkcie a nie tu
                break;
            case 'p':
                funkcia_p(osoba,n);
                break;
            case 'a':
                funkcia_a(osoba,&n);
                break;
        }
    } while ((vstup=getchar())!= 'k');
    fclose(f);
    return 0;
}