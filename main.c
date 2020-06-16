#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

void bilgiAl();
void bellektenYer();
void degerAta();
void bubbleSort();
void transpozeAl();
void dosyayaYaz();
void kaprekarBul();
bool kaprekar(int sayi);

struct matbil{
    int **matris;
    int satir;
    int sutun;
    int **transpoze;
} matbilgi;

int main()
{

	srand(time(NULL));

    // Boyut Alma
	bilgiAl();

    // Bellekten Yer Tahsis Etme

    bellektenYer();


    // Deðer Atama

    degerAta();


    // Bubble Sort

    bubbleSort();

    // Transpoze Alma

    transpozeAl();

    // Transpoze Ve Normal Hali Yazdırma

    dosyayaYaz();


    // Kaprekar Bulma

    kaprekarBul();

    return 0;
}



void bilgiAl(){
    printf( "Satir sayisi giriniz : " );
	scanf( "%d", &matbilgi.satir );
	printf( "Sutun sayisi giriniz : " );
	scanf( "%d", &matbilgi.sutun);
};

void bellektenYer(){
    int i;
    // Matris İçin
    matbilgi.matris = (int **) malloc( matbilgi.satir * sizeof(int) );
	if( matbilgi.matris == NULL )
		printf( "Yetersiz bellek!" );


	for( i = 0; i < matbilgi.satir; i++ ) {
		matbilgi.matris[i] = malloc( matbilgi.sutun * sizeof(int) );
		if( matbilgi.matris[i] == NULL )
			printf( "Yetersiz bellek!" );
	};

	// Transpozesi İçin

	matbilgi.transpoze = (int **) malloc( matbilgi.sutun * sizeof(int) );
	if( matbilgi.transpoze == NULL )
		printf( "Yetersiz bellek!" );


	for( i = 0; i < matbilgi.sutun; i++ ) {
		matbilgi.transpoze[i] = malloc( matbilgi.satir * sizeof(int) );
		if( matbilgi.transpoze[i] == NULL )
			printf( "Yetersiz bellek!" );
	};
};

void degerAta(){

    int s, k;
    for(s = 0; s < matbilgi.satir; s++)
        for(k = 0; k < matbilgi.sutun; k++) {
            matbilgi.matris[s][k] = 5+rand()%39995;
        };
};


void bubbleSort(){
    int i, j;
    int sayac = 0;
    int sayac2 = 0;
    int temp;
    int boyut = matbilgi.satir * matbilgi.sutun;
    int sirala[boyut];

    while(sayac < boyut){
        for(i=0;i<matbilgi.satir;i++){
            for(j=0; j<matbilgi.sutun; j++){
                sirala[sayac] = matbilgi.matris[i][j];
                sayac++;
            };
        };

    };

    for (i=1; i<boyut; i++){
         for (j=0; j<boyut-i; j++){
             if(sirala[j] > sirala[j+1]){
                temp = sirala[j];
                sirala[j] = sirala[j+1];
                sirala[j+1] = temp;
             };
         };
     };

    while(sayac2 < boyut){
        for(i=0; i<matbilgi.satir; i++){
            for(j=0; j<matbilgi.sutun; j++){

                matbilgi.matris[i][j] = sirala[sayac2];
                sayac2++;

            };
        };
    };

};

void transpozeAl(){
    int i, j;

    for(i=0; i<matbilgi.satir; i++){
        for(j=0; j<matbilgi.sutun; j++){
            matbilgi.transpoze[j][i] = matbilgi.matris[i][j];
        };
    };
};

void dosyayaYaz(){
    int s, k;
    FILE *pDosya;
    pDosya = fopen("transpoze.txt", "w+");

    if(pDosya == NULL){
        printf("transpoze.txt dosyasi acilamadi !\n");
        exit(1);
    };

    fprintf(pDosya, "Matrisin Ilk Hali : \n");

    for(s = 0; s < matbilgi.satir; s++) {
        for(k = 0; k < matbilgi.sutun; k++){
            fprintf(pDosya, "%6d\t", matbilgi.matris[s][k]);
        };
        fprintf(pDosya, "\n");
    };

    fprintf(pDosya, "Matrisin Transpozeli Hali : \n");

    for(s = 0; s < matbilgi.sutun; s++) {
        for(k = 0; k < matbilgi.satir; k++){
            fprintf(pDosya, "%6d\t", matbilgi.transpoze[s][k]);
        };
        fprintf(pDosya, "\n");
    };


    fclose(pDosya);

    printf("\nYazdirma Islemi Tamam !\n");
};

void kaprekarBul(){
    int boyut = matbilgi.satir * matbilgi.sutun;
    int kaprekarsayilari[boyut];
    int sayac3 = 0;
    int kapdegil = 0;
    FILE *ptrKapDosya;
    int i, s, k;

    for(s = 0; s < matbilgi.sutun; s++) {
        for(k = 0; k < matbilgi.satir; k++){
            if(kaprekar(matbilgi.transpoze[s][k])){
                kaprekarsayilari[sayac3] = matbilgi.transpoze[s][k];
                sayac3++;
            }
            else{
                kapdegil++;
            };
        };
    };

    if(kapdegil == boyut){
        printf("\nKaprekar Yok !\n");
    }
    else{
        ptrKapDosya = fopen("kaprekar.txt", "w+");

        for(i=0; i<sayac3; i++){
            fprintf(ptrKapDosya, "%6d\n", kaprekarsayilari[i]);
        };

    };


};

bool kaprekar(int sayi)
{
    if(sayi == 1){
        return true;
    };

    int sayikaresi = sayi * sayi;

    int bassayac = 0;
    while (sayikaresi){
        bassayac++;
        sayikaresi /= 10;
    };
    sayikaresi = sayi*sayi;
    for (int basparca=1; basparca<bassayac; basparca++){
         int esparca = pow(10, basparca);

         if(esparca == sayi){
            continue;
         };
         int toplam = sayikaresi/esparca + sayikaresi % esparca;
         if (toplam == sayi){
           return true;
         };
    };
    return false;
}
