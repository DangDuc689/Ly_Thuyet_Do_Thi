#include <stdio.h>
#define max 10
#define inputFile "test.txt"

typedef struct{
    int n;
    int a[max][max];
} DOTHI;

int DocMaTranKe (const char tenFile[], DOTHI &g){
    FILE *f = fopen(tenFile, "rt");
    if (f == NULL){
        printf ("Khong mo duoc file");
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

void xuatMaTranKe (DOTHI g){
    printf ("So dinh cua do thi la %d: \n", g.n);
    printf ("Ma tran ke cua do thi la: \n");
    for (int i = 0; i < g.n; i++){
        printf ("\t");
        for (int j = 0; j < g.n; j++){
            printf ("%4d ", g.a[i][j]);
        }
        printf ("\n");
    }
}


struct STACK{
    int a[100];
    int size;
};

void khoiTaoStack (STACK &stack){
    stack.size = 0;
}

void DayGiaTriVaoStack (STACK &stack, int value){
    if (stack.size < 100){
        stack.a[stack.size] = value;
        stack.size++;
    }
}

void TimDuongDi (int i, DOTHI &g, STACK &stack){
    for (int j = 0; j < g.n; j++){
        if (g.a[i][j] != 0){
            g.a[i][j] = g.a[j][i] = 0;
            TimDuongDi(j, g, stack);
        }
    }
    DayGiaTriVaoStack(stack, i);
}

int bacDinh (DOTHI &g, int v){
    int bac = 0;
    for (int j = 0; j < g.n; j++){
        if (g.a[v][j] != 0)
            bac++;
    }
    return bac;
}

int timChuTrinhEuler (DOTHI &g){
    int i, j;
    int x = 0;
    for (i = 0; i < g.n; i++){
        if (bacDinh(g, i) % 2 != 0){
            return 0;
        }
    }

    DOTHI temp = g;
    STACK stack;
    khoiTaoStack(stack);
    TimDuongDi(x, temp, stack);
    for (int i = 0; i < temp.n; i++){
        for (int j = 0; j < temp.n; j++){
            if (temp.a[i][j] != 0 || temp.a[j][i] != 0){
                return 0;
            }
        }
    }
    if (stack.a[0] != stack.a[stack.size - 1]){
        return 0;
    }
    printf ("\n Chu trinh Euler: ");

    while (stack.size != 0){
        printf ("%d ", stack.a[--stack.size]);
    }
    return 1;
}

int timDuongDiEuler (DOTHI &g){
    int i, j;
    int x = 0;
    int dem = 0;
    int timThay = 0;
    for (i = 0; i < g.n; i++){
        if (bacDinh(g, i) % 2 != 0){
            x = i;
            dem++;
            if (timThay == 0){
                timThay = 1;
            }
        }
    }

    if (!timThay || dem != 2) return 0;

    DOTHI temp = g;
    STACK stack;
    khoiTaoStack(stack);
    TimDuongDi(x, temp, stack);
    for (int i = 0; i < temp.n; i++){
        for (int j = 0; j < temp.n; j++){
            if (temp.a[i][j] != 0 || temp.a[j][i] != 0){
                return 0;
            }
        }
    }
    if (stack.a[0] == stack.a[stack.size - 1]){
        return 0;
    }
    printf ("\n Duong di Euler: ");
    while (stack.size != 0){
        printf ("%d ", stack.a[--stack.size]);
    }
    return 1;
}

int main(){
    DOTHI g;

    // char inputFile[256];
    // printf ("Nhap tap tin du lieu do thi: ");
    // scanf ("%s", inputFile);

    if (DocMaTranKe(inputFile, g) == 1){
        printf ("Da lay duoc thong tin tu file thanh cong. \n\n");
        xuatMaTranKe(g);
        if (!timChuTrinhEuler(g))
            printf ("\n Khong co chu trinh Euler trong do thi\n");
        if (!timDuongDiEuler(g))
            printf ("\n Khong co duong di Euler trong do thi\n");
    }

    return 0;
}