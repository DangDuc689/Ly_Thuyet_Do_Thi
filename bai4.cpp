#include <stdio.h>
#define MAX 10
#define inputfile "test.txt"

typedef struct GRAPH {
    int n;
    int a[MAX][MAX];
} DOTHI;

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

void timDinhLienThong(DOTHI &g, int nhan[MAX], int i){
    for (int j = 0; j < g.n; j++){
        if (g.a[i][j] != 0 && nhan[i] != nhan[j]){
            nhan[j] = nhan[i];
            timDinhLienThong(g, nhan, j);
        }
    }
}

int soTPLienThong(DOTHI &g){
    int soTPLT = 0;
    int nhan[MAX];
    for (int i = 0; i < g.n; i++){
        nhan[i] = 0;
    }
    for (int i = 0; i < g.n; i++){
        if (nhan[i] == 0){
            soTPLT++;
            nhan[i] = soTPLT;
            timDinhLienThong(g, nhan, i);
        }
    }
    return soTPLT;
} 

typedef struct EDGE{
    int u, v, value;
} CANH;


// thuat toan Prim
void Prim(DOTHI g){
    CANH T[MAX];
    if (soTPLienThong(g) != 1){
        printf("Do thi khong lien thong, dung thuat toan Prim\n");
        return;
    }
    int nT = 0;
    int chuaXet[MAX];
    for (int i = 0; i < g.n; i++){
        chuaXet[i] = 0;
    }
    chuaXet[0] = 1; 
    while (nT < g.n - 1){
        CANH canhNhoNhat;
        int GiaTriNhoNhat = 10000;
        for (int i = 0; i < g.n; i++){
            if (chuaXet[i] == 1){
                for (int j = 0; j < g.n; j++){
                    if (chuaXet[j] == 0 && g.a[i][j] != 0 && GiaTriNhoNhat > g.a[i][j]){
                        canhNhoNhat.u = i;
                        canhNhoNhat.v = j;
                        canhNhoNhat.value = g.a[i][j];
                        GiaTriNhoNhat = g.a[i][j];
                    }
                }
            }
        }
        T[nT++] = canhNhoNhat;
        chuaXet[canhNhoNhat.v] = 1; 
    }
    int trongSoCuaCayKhung = 0;
    printf("Cay khung nho nhat cua do thi la: \n");
    for (int i = 0; i < nT-1; i++){
        printf ("(%d, %d), ", T[i].u, T[i].v);
        trongSoCuaCayKhung += T[i].value;
    }
    printf ("(%d, %d)\n", T[nT-1].u, T[nT-1].v);
    trongSoCuaCayKhung += T[nT-1].value;
    printf("Trong so cua cay khung la: %d\n", trongSoCuaCayKhung);
}


//thuat toan Kruskal
void SapXepCanh(CANH E[100], int tongSoCanh){
    for (int i = 0; i < tongSoCanh - 1; i++){
        for (int j = i + 1; j < tongSoCanh; j++){
            if (E[i].value > E[j].value){
                CANH temp = E[i];
                E[i] = E[j];
                E[j] = temp;
            }
        }
    }
}

void kruskal (DOTHI g){
    CANH listEdge[MAX];
    CANH T[MAX];
    int tongSoCanh = 0;
    for (int i = 0; i < g.n; i++){
        for (int j = i + 1; j < g.n; j++){
            if (g.a[i][j] > 0){
                listEdge[tongSoCanh].u = i;
                listEdge[tongSoCanh].v = j;
                listEdge[tongSoCanh].value = g.a[i][j];
                tongSoCanh++;
            }
        }
    }
    SapXepCanh(listEdge, tongSoCanh);
    int nT = 0;
    int nhan[MAX];
    for (int i = 0; i < g.n; i++){
        nhan[i] = i; 
    }
    int canhDangXet = 0;
    while (nT < g.n && canhDangXet < tongSoCanh){
        CANH edge = listEdge[canhDangXet];
        int u = nhan[edge.u];
        int v = nhan[edge.v];
        if (u != v) {
            T[nT++] = edge;
            for (int i = 0; i < g.n; i++) {
                if (nhan[i] == v) {
                    nhan[i] = u; 
                }
            }
        }
        canhDangXet++;
    }
    if (nT != g.n - 1)
        printf ("\nDo thi khong lien thong\n");
    else {
        int trongSoCayKhung = 0;
        printf("Cay khung nho nhat cua do thi la: \n");
        for (int i = 0; i < nT; i++) {
            printf("(%d, %d), ", T[i].u, T[i].v);
            trongSoCayKhung += T[i].value;
        }
        printf("\nTong trong so cua cay khung la: %d\n", trongSoCayKhung);
    }
}

int main() {
    DOTHI g;
    if (!DocMaTranKe(inputfile, g)) {
        return 1;
    }
    printf("So dinh cua do thi: %d\n", g.n);
    printf("Ma tran ke:\n");
    for (int i = 0; i < g.n; i++) {
        for (int j = 0; j < g.n; j++)
            printf("%4d ", g.a[i][j]);
        printf("\n");
    }

    printf("\n=== Thuat toan Prim ===\n");
    Prim(g);

    printf("\n=== Thuat toan Kruskal ===\n");
    kruskal(g);

    return 0;
}