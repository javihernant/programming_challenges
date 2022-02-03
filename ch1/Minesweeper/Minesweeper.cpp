#include <iostream>
#include <vector>

void load_input(std::vector<std::vector<int>>& mx, int n, int m);
void process_mx(std::vector<std::vector<int>>& mx);
void print_mx(std::vector<std::vector<int>>& mx, int field);

int main()
{
    int field = 0; /* current field being processed */
    int n, m; /* n rows, m cols */

    while(scanf("%d %d", &n, &m) != EOF){
        if(n==0 && m==0){
            break;
        }

        std::vector<std::vector<int>> mx;
        load_input(mx, n, m);
        process_mx(mx);
        print_mx(mx, ++field);
   
    }

    return 0;
}

void load_input(std::vector<std::vector<int>>& mx, int n, int m)
{
    char ch;

    for(int i=0; i<n; i++){
        mx.push_back(std::vector<int>(m, 0));
        for(int j=0; j<m; j++){
            std::cin >> ch;
            if (ch == '*'){
                mx[i][j] = -1;
            }
        }
    }
}

void process_mx(std::vector<std::vector<int>>& mx)
{
    int n = mx.size();
    int m = mx[0].size();
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(mx[i][j]==-1){
                int ni, nj; /* indices to look the cells surounding element mx[i][j] */
                for(int k=-1; k<=1; k++){
                    for(int l=-1; l<=1; l++){
                        ni = i+k;
                        nj = j+l;
                        if(ni < n && ni >= 0 && nj < m && nj >= 0 && mx[ni][nj]!= -1){
                            mx[ni][nj]++;
                        }
                    }
                }
            }
        }   
    }
}

void print_mx(std::vector<std::vector<int>>& mx, int field)
{
    int n = mx.size();
    int m = mx[0].size();
    int num; /* holds numbers of the processed matrix */
    if(field>1){
        std::cout << "\n";
    }
    std::cout << "Field #" << field << ":\n";
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if((num = mx[i][j]) == -1){
                std::cout << '*';
            }else{
                std::cout << num;
            }
            
        }
        std::cout << "\n";
    }
}


