#include<cstdio>
#include<cstring>
using namespace std;

const int N = 15 , M2 = 8192 , M3 = 1594323 , inf = (int)1e9;

#define fo(i , st , en) for (int i = st; i <= en; i++)
#define fd(i , st , en) for (int i = st; i >= en; i--)
#define mymin(x , y) ((x) < (y) ? (x) : (y))
#define Me(x , y) memset(x , y , sizeof(x))
#define lowbite(x) ((x) & -(x))

int n , k , m , need , full;
int da[N][N] , db[N][N];
int t3[N] , sum3[M2] , f[M3] , num[N] , opt[M2];

void Init(){
    scanf("%d%d" , &n , &k); int x , y , z;
    Me(da , 127); Me(db , 127); need = 0; Me(num , 0);
    fo (i , 1 , k){
        scanf("%d%d%d" , &x , &y , &z);
        da[x][y] = da[y][x] = z; num[x]++; num[y]++;
        db[x][y] = db[y][x] = mymin(db[y][x] , z);
        need |= 1 << x - 1; need |= 1 << y - 1;
    }
    scanf("%d" , &m);
    fo (i , 1 , m){
        scanf("%d%d%d" , &x , &y , &z);
        db[x][y] = db[y][x] = mymin(db[y][x] , z);
    }
    t3[0] = 1; sum3[0] = 0; full = (1 << n) - 1;
    fo (i , 1 , n - 1) t3[i] = t3[i - 1] * 3;
    fo (i , 0 , n - 1) sum3[1 << i] = t3[i];
    fo (i , 1 , full) sum3[i] = sum3[i & (i - 1)] + sum3[lowbite(i)];
}

void Calc(int s1 , int s2){
    int cur = f[sum3[s1] + sum3[s2]];
    if (cur > inf) return;
    if ((s1 & need) == need) opt[s2] = mymin(opt[s2] , cur);
    fo (i , 2 , n)
        if ((1 << i - 1 & s1) == 0){
            bool flag = 0; int value = 0;
            fo (j , 1 , n)
                if ((1 << j - 1 & s1) && da[i][j] < inf){
                    flag = 1; value += da[i][j];
                }
            if (flag){
                int temp = sum3[s1] + sum3[s2] + t3[i - 1] * ((num[i] & 1) + 1);
                f[temp] = mymin(f[temp] , cur + value);
            }
            else{
                fo (j , 1 , n)
                    if ((1 << j - 1 & s1) && db[i][j] < inf){
                        int temp = sum3[s2 ^ 1 << j - 1] + sum3[s1 ^ 1 << i - 1];
                        if ((num[i] & 1) == 0) temp += t3[i - 1];
                        f[temp] = mymin(f[temp] , cur + db[i][j]);
                    }
            }
        }
}

void Work(){
    Me(f , 127); f[1 + (num[1] & 1)] = 0; Me(opt , 127);
    fo (s1 , 0 , full){
        for (int s2 = s1; s2; s2 = s1 & (s2 - 1))
            Calc(s1 , s2);
        Calc(s1 , 0);
    }
    fo (l , 1 , n)
        fo (i , 1 , n)
            if (l != i)
                fo (j , i + 1 , n)
                    if (j != l && db[i][l] < inf && db[l][j] < inf){
                        db[i][j] = db[j][i] = mymin(db[j][i] , db[i][l] + db[l][j]);
                    }
    fd (i , full , 1)
        if (opt[i] < inf){
            fo (i1 , 1 , n)
                fo (i2 , 1 , n)
                    if (i1 != i2 && (1 << i1 - 1 & i) && (1 << i2 - 1 & i) && db[i1][i2] < inf){
                        int temp = i ^ 1 << i1 - 1 ^ 1 << i2 - 1;
                        opt[temp] = mymin(opt[temp] , opt[i] + db[i1][i2]);
                    }
        }
    printf("%d\n" , opt[0]);
}

int main(){
    Init();
    Work();
    return 0;
}
