#include <stdio.h>
#include <string.h>

int i = 0;
struct data{
    char nama[100], huruf[3];
    int eval1, eval2, eval3, uas, maks, min, nrp;
    float rata_rata;
} mahasiswa[120];

struct maksimal{
    float nilai;
    char nama[100];
};

struct minimal{
    float nilai;
    char nama[100];
};

struct drata_rata{
    float nilai;
    struct minimal min;
    struct maksimal maks;
} rata_rata;

struct deval1{
    struct minimal min;
    struct maksimal maks;
} eval1;

struct deval2{
    struct minimal min;
    struct maksimal maks;
} eval2;

struct deval3{
    struct minimal min;
    struct maksimal maks;
} eval3;

struct duas{
    struct minimal min;
    struct maksimal maks;
} uas;

void menu(){
    int pilihan;
    puts("\nSilahkan pilih menu anda:");
    puts("1. Menambahkan mahasiswa dan nilai");
    puts("2. Menampilkan Data Mahasiswa");
    puts("3. Selesai");
    printf("Pilihan anda: ");
    scanf("%d", &pilihan);

    switch(pilihan)
    {
        case 1:
            menambah();
            break;
        case 2:
            tampil();
            break;
        case 3:
            exit(1);
        default:
            printf("Input salah coba lagi\n\n");
            menu();
            break;
    }
}

void menambah(){
    char jawab;
    do {
        printf("\nData mahasiswa ke-%d\n", i + 1);
        printf("NRP: ");
        scanf("%d", &mahasiswa[i].nrp);
        getchar();
        printf("Nama: ");
        fgets(mahasiswa[i].nama, sizeof(mahasiswa[i].nama), stdin);
        mahasiswa[i].nama[strcspn(mahasiswa[i].nama, "\n")] = 0;
        printf("Masukkan nilai\n");
        printf("Eval1 Eval2 Eval3 UAS: ");
        scanf(" %d %d %d %d", &mahasiswa[i].eval1, &mahasiswa[i].eval2, &mahasiswa[i].eval3, &mahasiswa[i].uas);

        // Mencari maks dan min dari setiap nilai
        int nilai[] = {mahasiswa[i].eval1, mahasiswa[i].eval2, mahasiswa[i].eval3, mahasiswa[i].uas};
        mahasiswa[i].maks = nilai[0];
        mahasiswa[i].min = nilai[0];
        for (int j = 0; j < 4; j++){
            if (mahasiswa[i].maks < nilai[j]) mahasiswa[i].maks = nilai[j];
            if (mahasiswa[i].min > nilai[j]) mahasiswa[i].min = nilai[j];
        }

        // Nilai rata-rata mahasiswa
        mahasiswa[i].rata_rata = (float)(mahasiswa[i].eval1 + mahasiswa[i].eval2 + mahasiswa[i].eval3 + mahasiswa[i].uas) / 4.0;

        // Cek huruf
        cekgrade();
        i++;

        printf("Mau menambah mahasiswa lagi? (y/t): ");
        scanf(" %c", &jawab);
    } while (jawab == 'y' || jawab == 'Y');
}

void tampil(){
    rata_rata.maks.nilai = 0;
    rata_rata.min.nilai = 101;

    eval1.maks.nilai = 0;
    eval1.min.nilai = 101;

    eval2.maks.nilai = 0;
    eval2.min.nilai = 101;

    eval3.maks.nilai = 0;
    eval3.min.nilai = 101;

    uas.maks.nilai = 0;
    uas.min.nilai = 101;

    float jumlah = 0.0;
    puts("==========================================================================================================");
    puts("No.\tNRP\tNama\tEval1\tEval2\tEval3\tUAS\trata-rata\tmaks\tmin\thuruf");
    puts("==========================================================================================================");
    for (int j = 0; j < i; j++){
        jumlah += mahasiswa[j].rata_rata;
        cekdata(j);
        printf("%d\t%d\t%s\t%d\t%d\t%d\t%d\t%.2f\t\t%d\t%d\t%s\n", j+1, mahasiswa[j].nrp, mahasiswa[j].nama, mahasiswa[j].eval1, mahasiswa[j].eval2, mahasiswa[j].eval3, mahasiswa[j].uas, mahasiswa[j].rata_rata, mahasiswa[j].maks, mahasiswa[j].min, mahasiswa[j].huruf);
    }
    puts("");

    rata_rata.nilai = jumlah / (float)i+1;

    printf("Nilai rata-rata seluruh mahasiswa       : %.2f\n", rata_rata.nilai);
    printf("Nilai rata-rata mahasiswa tertinggi     : %s dengan nilai %.2f\n", rata_rata.maks.nama, rata_rata.maks.nilai);
    printf("Nilai rata-rata mahasiswa terendah      : %s dengan nilai %.2f\n", rata_rata.min.nama, rata_rata.min.nilai);
    printf("Nilai mahasiswa dengan eval1 tertinggi  : %s dengan nilai %.f\n", eval1.maks.nama, eval1.maks.nilai);
    printf("Nilai mahasiswa dengan eval1 terendah   : %s dengan nilai %.f\n", eval1.min.nama, eval1.min.nilai);
    printf("Nilai mahasiswa dengan eval2 tertinggi  : %s dengan nilai %.f\n", eval2.maks.nama, eval2.maks.nilai);
    printf("Nilai mahasiswa dengan eval2 terendah   : %s dengan nilai %.f\n", eval2.min.nama, eval2.min.nilai);
    printf("Nilai mahasiswa dengan eval3 tertinggi  : %s dengan nilai %.f\n", eval3.maks.nama, eval3.maks.nilai);
    printf("Nilai mahasiswa dengan eval3 terendah   : %s dengan nilai %.f\n", eval3.min.nama, eval3.min.nilai);
    printf("Nilai mahasiswa dengan uas tertinggi    : %s dengan nilai %.f\n", uas.maks.nama, uas.maks.nilai);
    printf("Nilai mahasiswa dengan uas terendah     : %s dengan nilai %.f\n", uas.min.nama, uas.min.nilai);
}

void cekdata(int j){
    if (rata_rata.maks.nilai < mahasiswa[j].rata_rata){
        rata_rata.maks.nilai = mahasiswa[j].rata_rata;
        strcpy(rata_rata.maks.nama, mahasiswa[j].nama);
    }
    if (rata_rata.min.nilai > mahasiswa[j].rata_rata){
        rata_rata.min.nilai = mahasiswa[j].rata_rata;
        strcpy(rata_rata.min.nama, mahasiswa[j].nama);
    }
    if (eval1.maks.nilai < mahasiswa[j].eval1){
        eval1.maks.nilai = mahasiswa[j].eval1;
        strcpy(eval1.maks.nama, mahasiswa[j].nama);
    }
    if (eval1.min.nilai > mahasiswa[j].eval1){
        eval1.min.nilai = mahasiswa[j].eval1;
        strcpy(eval1.min.nama, mahasiswa[j].nama);
    }
    if (eval2.maks.nilai < mahasiswa[j].eval2){
        eval2.maks.nilai = mahasiswa[j].eval2;
        strcpy(eval2.maks.nama, mahasiswa[j].nama);
    }
    if (eval2.min.nilai > mahasiswa[j].eval2){
        eval2.min.nilai = mahasiswa[j].eval2;
        strcpy(eval2.min.nama, mahasiswa[j].nama);
    }
    if (eval3.maks.nilai < mahasiswa[j].eval3){
        eval3.maks.nilai = mahasiswa[j].eval3;
        strcpy(eval3.maks.nama, mahasiswa[j].nama);
    }
    if (eval3.min.nilai > mahasiswa[j].eval3){
        eval3.min.nilai = mahasiswa[j].eval3;
        strcpy(eval3.min.nama, mahasiswa[j].nama);
    }
    if (uas.maks.nilai < mahasiswa[j].uas){
        uas.maks.nilai = mahasiswa[j].uas;
        strcpy(uas.maks.nama, mahasiswa[j].nama);
    }
    if (uas.min.nilai > mahasiswa[j].uas){
        uas.min.nilai = mahasiswa[j].uas;
        strcpy(uas.min.nama, mahasiswa[j].nama);
    }
};

void cekgrade(){
    if (mahasiswa[i].rata_rata >= 86 && mahasiswa[i].rata_rata <= 100){
        strcpy(mahasiswa[i].huruf, "A");
    } else if (mahasiswa[i].rata_rata >= 81 && mahasiswa[i].rata_rata < 86){
        strcpy(mahasiswa[i].huruf, "A-");
    } else if (mahasiswa[i].rata_rata >= 76 && mahasiswa[i].rata_rata < 81){
        strcpy(mahasiswa[i].huruf, "AB");
    } else if (mahasiswa[i].rata_rata >= 71 && mahasiswa[i].rata_rata < 76){
        strcpy(mahasiswa[i].huruf, "B+");
    } else if (mahasiswa[i].rata_rata >= 66 && mahasiswa[i].rata_rata < 71){
        strcpy(mahasiswa[i].huruf, "B");
    } else if (mahasiswa[i].rata_rata >= 61 && mahasiswa[i].rata_rata < 66){
        strcpy(mahasiswa[i].huruf, "BC");
    } else if (mahasiswa[i].rata_rata >= 56 && mahasiswa[i].rata_rata < 61){
        strcpy(mahasiswa[i].huruf, "C");
    } else if (mahasiswa[i].rata_rata >= 41 && mahasiswa[i].rata_rata < 56){
        strcpy(mahasiswa[i].huruf, "D");
    } else{
        strcpy(mahasiswa[i].huruf, "E");
    }
};

int main (){
    puts("P R O G R A M  N I L A I  M A H A S I S W A");
    puts("  Oleh Fathu Alwi Nabiil NRP 3124600020");
    puts("===========================================");

    while(1){
        menu();
    }

    return 0;
}
