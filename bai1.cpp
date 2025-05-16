#include <stdio.h>
#define MAX 100
#define inputFile "test.txt"

typedef struct GRAPH{
    int n;
    int a[MAX][MAX];
}DOTHI;

int DocMaTranKe(const char TenFile[], DOTHI &g){
    FILE *f = fopen(TenFile, "rt");
    if (f == NULL){
        printf("Khong mo duoc file!");
        return 0;
    }
    fscanf(f, "%d", &g.n);
    for (int i = 0; i < g.n; i++){
        for (int j = 0; j < g.n; j++){
            fscanf(f, "%d", &g.a[i][j]);
        }
    }
    fclose(f);
    return 1;
}

void XuatMaTranKe(DOTHI g){
    printf ("So dinh cua do thi la: %d\n", g.n);
    printf("Ma tran ke cua do thi la: \n");
    for (int i = 0; i < g.n; i++){
        printf ("\t");
        for (int j = 0; j < g.n; j++){
            printf("%4d ", g.a[i][j]);
        }
        printf("\n");
    }
}

int KiemTraMaTranKeHopLe(DOTHI g){
    for (int i = 0; i < g.n; i++){
        if (g.a[i][i] != 0)
            return 0;
    }
    return 1;
}

int KiemTraDoThiVoHuong(DOTHI g){
    for (int i = 0; i < g.n; i++){
        for (int j = 0; j < g.n; j++){
            if (g.a[i][j] != g.a[j][i])
                return 0;
        }
    }
    return 1;
}

void DiTimCacDinhLienThong(DOTHI g, int nhan[MAX], int i){
    for (int j = 0; j < g.n; j++){
        if (g.a[i][j] != 0 && nhan[j] != nhan[i]){
            nhan[j] = nhan[i];
            DiTimCacDinhLienThong(g, nhan, j);
        }
    }
}

void XetLienThong(DOTHI g){
    int nhan[MAX];
    for (int i = 0; i < g.n; i++){
        nhan[i] = 0;
    }
    int dem = 0;
    for (int i = 0; i < g.n; i++){
        if (nhan[i] == 0){
            dem++;
            nhan[i] = dem;
            DiTimCacDinhLienThong(g, nhan, i);
        }
    }
    printf("So thanh phan lien thong la: %d\n", dem);
    for (int i = 1; i <= dem; i++){
        printf("Thanh phan lien thong thu [%d] gom cac dinh: ", i);
        for (int j = 0; j < g.n; j++){
            if (nhan[j] == i){
                printf("%d ", j);
            }
        }
        printf("\n");
    }
}

int main(){
    DOTHI g;
    /*
    if (DocMaTranKe(inputFile, g) == 1){
        printf("Doc thong tin do thi tu file thanh cong.\n\n");
        XuatMaTranKe(g);
        printf("Do thi co ma tran ke: %s\n", KiemTraMaTranKeHopLe(g) == 1 ? "Hop le" : "Khong hop le");
        printf("Do thi thuoc dang: %s\n", KiemTraDoThiVoHuong(g) == 1 ? "vo huong" : "co huong");
    }
    */

    char inputfile[256];
    printf("Nhap ten tap tin du lieu do thi: ");
    scanf("%s", inputfile);
    if (DocMaTranKe(inputfile, g) == 1){
        printf("Doc thanh cong du lieu do thi.\n\n");
        XuatMaTranKe(g);
        // printf("Do thi co ma tran ke: %s\n", KiemTraMaTranKeHopLe(g) == 1 ? "Hop le" : "Khong hop le");
        // printf("Do thi thuoc dang: %s\n", KiemTraDoThiVoHuong(g) == 1 ? "vo huong" : "co huong");
        XetLienThong(g);
    }
    else{
        printf("Khong mo duoc file!\n");
    }
    return 0;
}



