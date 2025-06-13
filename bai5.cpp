#include <stdio.h>

#define VOCUC 1000
#define MAX 10
int LuuVet[MAX];
int ChuaXet[MAX];
int DoDaiDuongDiToi[MAX];

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

void XuatMaTranKe(DOTHI g) {
    printf("So dinh cua do thi la %d\n", g.n);
    printf("Ma tran ke cua do thi la: \n");
    for (int i = 0; i < g.n; i++) {
        printf("\t");
        for (int j = 0; j < g.n; j++)
            printf("%4d ", g.a[i][j]);
        printf("\n");
    }
}

int TimDuongDiNhoNhat(DOTHI g){
    int li = -1;
    float p = VOCUC;
    for (int i = 0; i < g.n; i++){
        if (ChuaXet[i] == 0 && DoDaiDuongDiToi[i] < p){
            p = DoDaiDuongDiToi[i];
            li = i;
        }
    }
    return li;
}

void CapNhatDuongDi(int u, DOTHI g){
    ChuaXet[u] = 1;
    for (int v = 0; v < g.n; v++){
        if (ChuaXet[v] == 0 && g.a[u][v] > 0 && g.a[u][v] < VOCUC){
            if (DoDaiDuongDiToi[v] > DoDaiDuongDiToi[u] + g.a[u][v]) {
                DoDaiDuongDiToi[v] = DoDaiDuongDiToi[u] + g.a[u][v];
                LuuVet[v] = u; 
            }
        }
    }
}

void Dijkstra(DOTHI g, int s, int f) {
    for (int i = 0; i < g.n; i++) {
        ChuaXet[i] = 0;
        DoDaiDuongDiToi[i] = VOCUC;
        LuuVet[i] = -1; 
    }
    DoDaiDuongDiToi[s] = 0;

    while (ChuaXet[f] == 0) {
        int u = TimDuongDiNhoNhat(g);
        if (u == -1) break;
        CapNhatDuongDi(u, g);
    }
    if (ChuaXet[f] == 1){
        printf ("Duong di ngan nhat tu dinh [%d] den dinh [%d] la: \n\t", s, f);
        printf ("%d ", f);
        int i = LuuVet[f];
        while (i != -1) {
            printf("<- %d ", i);
            i = LuuVet[i];
        }
        printf ("\n");
        printf ("Voi do dai la: %d\n", DoDaiDuongDiToi[f]);
    }
    else 
        printf("Khong co duong di tu dinh %d den dinh %d\n", s, f);
}


void Floyd(DOTHI g, int s, int f){
    int SauNut[MAX][MAX];
    int l[MAX][MAX];
    for (int i = 0; i < g.n; i++) {
        for (int j = 0; j < g.n; j++) {
            if (g.a[i][j] > 0){
                SauNut[i][j] = i;
                l[i][j] = g.a[i][j];
            }
            else{
                SauNut[i][j] = -1;
                l[i][j] = VOCUC;
            }
        }
    }
    for (int k = 0; k < g.n; k++){
        for (int i = 0; i < g.n; i++){
            for (int j = 0; j < g.n; j++){
                if (l[i][j] > l[i][k] + l[k][j]) {
                    l[i][j] = l[i][k] + l[k][j];
                    SauNut[i][j] = SauNut[k][j];
                }
            }
        }
    }
    if (SauNut[s][f] == -1)
        printf("Khong co duong di tu dinh %d den dinh %d\n", s, f);
    else {
        printf("Duong di ngan nhat tu dinh %d den dinh %d la: \n\t", s, f);
        int path[MAX], cnt = 0;
        int u = f;
        while (u != s && cnt < g.n) {
            path[cnt++] = u;
            u = SauNut[s][u];
            if (u == -1) break; 
        }
        if (u == -1 || cnt >= g.n) {
            printf("Khong co duong di tu dinh %d den dinh %d\n", s, f);
            return;
        }
        path[cnt++] = s;
        for (int i = cnt - 1; i >= 0; i--) {
            printf("%d", path[i]);
            if (i > 0) printf(" --> ");
        }
        printf ("\n\tVoi tong trong so la: %d\n", l[s][f]);
    }
}


// không thể hoạt động trên đồ thị có trọng số âm
// không thể hoạt động trên đồ thị không liên thông (hoặc chạy không đúng)

int main() {
    DOTHI g;
    if (!DocMaTranKe(inputfile, g)) {
        return 1;
    }
    XuatMaTranKe(g);

    int s, f;
    printf("\nNhap dinh bat dau (tu 0): "); scanf("%d", &s);
    printf("Nhap dinh ket thuc (tu 0): "); scanf("%d", &f);

    printf("\n=== Thuat toan Dijkstra ===\n");
    Dijkstra(g, s, f);

    printf("\n=== Thuat toan Floyd ===\n");
    Floyd(g, s, f);

    return 0;
}
