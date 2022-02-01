#include <iostream>
#include <unordered_map>

int get_cycles(int n, std::unordered_map<int, int>& mp);

int main()
{
    int a,b; /* the two number input */
    int i,j; /* first and last number */
    int x; /* current number whose cycles we are calculating */
    int tmp; /* to store num of cycles of i */
    int max; /* maximum number of cycles */

    std::unordered_map<int, int> m;

    while(scanf("%d %d", &a, &b) != EOF){
        if(a>b){
            i = b;
            j = a;
        }else{
            i = a;
            j = b;
        }

        max = 0;
        for(x=i ; x<=j; x++){
            tmp = get_cycles(x, m);
            if(tmp>max){
                max = tmp;
            }
        } 
        std::cout << a<< " " << b << " " << max << "\n";
    }

    return 0;
}

int get_cycles(int n, std::unordered_map<int, int>& mp)
{
    int res;
    if(n == 1){
        res = 1;
    }else if(mp.count(n) != 0){
        res = mp[n];
    }else if(n%2 == 0){
        res = get_cycles(n/2, mp) + 1;
    }else{
        res = get_cycles(n*3 + 1, mp) + 1;
    }

    mp[n] = res;
    return res;
}

