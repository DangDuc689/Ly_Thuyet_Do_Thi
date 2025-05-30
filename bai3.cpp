#include <stdio.h>
#define MAX 10
#define inputfile "test.txt"

int luuVet[MAX];
int chuaXet[MAX];

typedef struct GRAPH {
    int n;
    int a[MAX][MAX];
} DOTHI;

int DocMaTranKe(const char TenFile[], DOTHI &g) {
    FILE *f = fopen(TenFile, "rt");
    if (f == NULL) {
        printf("khong mo duoc file\n");
        return 0;
    }
    fscanf(f, "%d", &g.n);
    for (int i = 0; i < g.n; i++) {
        for (int j = 0; j < g.n; j++)
            fscanf(f, "%d", &g.a[i][j]);
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


// Duyệt đồ thị theo chiều sâu DFS 
void DFS(int v, GRAPH &g){
    chuaXet[v] = 1;
    for (int u = 0; u < g.n; u++) {
        if (g.a[v][u] != 0 && chuaXet[u] == 0) {
            luuVet[u] = v; 
            DFS(u, g);
        }
    }
}

void duyetTheoDFS(int s, int f, GRAPH g){
    for (int i = 0; i < g.n; i++) {
        luuVet[i] = -1;
        chuaXet[i] = 0; 
    }
    DFS(s, g);
    if (chuaXet[f] == 1){
        printf ("Duong di tu dinh [%d] den dinh [%d] la: \n\t", s, f);
        printf ("%d ", f);
        int i = luuVet[f];
        while (i != -1) {
            printf("<- %d ", i);
            i = luuVet[i];
        }
        printf("\n");
    }
    else {
        printf("Khong co duong di tu dinh [%d] den dinh [%d]\n", s, f);
    }
}


// Xây dựng Queue và duyệt đồ thị theo chiều rộng BFS
struct QUEUE{
    int n;
    int a[MAX];
};

void khoiTaoQueue(QUEUE &q) {
    q.n = 0;
}

int dayGiaTriVaoQueue(QUEUE &q, int value) {
    if (q.n < MAX) {
        q.a[q.n++] = value;
        return 1;
    }
    return 0;
}

int layGiaTriRaKhoiQueue(QUEUE &q, int &value){
    if (q.n <= 0) return 0;
    value = q.a[0];
    for (int i = 0; i < q.n - 1; i++) {
        q.a[i] = q.a[i + 1];
    }
    q.n--;
    return 1;
}

int kiemtraRongQueue(QUEUE &q) {
    return (q.n <= 0);
}

void BFS(int v, GRAPH g){
    QUEUE q;
    khoiTaoQueue(q);
    dayGiaTriVaoQueue(q, v);
    while (!kiemtraRongQueue(q)) {
        layGiaTriRaKhoiQueue(q, v);
        chuaXet[v] = 1;
        for (int u = 0; u < g.n; u++) {
            if (g.a[v][u] != 0 && chuaXet[u] == 0) {
                dayGiaTriVaoQueue(q, u);
                if (luuVet[u] == -1) 
                    luuVet[u] = v; 
            }
        }
    }
}

void duyetTheoBFS(int s, int f, GRAPH g){
    for (int i = 0; i < g.n; i++) {
        luuVet[i] = -1;
        chuaXet[i] = 0;
    }
    BFS(s, g);
    if (chuaXet[f] == 1) {
        printf("Duong di tu dinh [%d] den dinh [%d] la: \n\t", s, f);
        printf("%d ", f);
        int i = luuVet[f];
        while (i != -1) {
            printf("<- %d ", i);
            i = luuVet[i];
        }
        printf("\n");
    }
    else {
        printf("Khong co duong di tu dinh [%d] den dinh [%d]\n", s, f);
    }
}

int nhapDinh(DOTHI &g, const char *tb){
    int value;
    int done = 0;
    while (!done){
        fflush(stdin);
        printf("%s [0..%d] (-1 dung): ", tb, g.n-1);
        scanf("%d", &value);
        if (value == -1) return -1;
        done = (value >= 0 && value <= g.n - 1);
    }
    return value;
}

int main(){
    DOTHI g;
    char inputFile[256];
    if (DocMaTranKe(inputfile, g) == 1) {
        XuatMaTranKe(g);
        int s, f;
        s = nhapDinh(g, "Nhap dinh bat dau");
        if (s != -1)
            f = nhapDinh(g, "Nhap dinh ket thuc");
        if (s != -1 && f != -1) {
            // duyetTheoDFS(s, f, g);
            duyetTheoBFS(s, f, g);
        }
    }
    return 0;
}


