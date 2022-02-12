#include <iostream>
#include <vector>

int main()
{
    int n;
    int num;
    int a, b;
    int jolly;
    int dif;
    std::vector<int> list;
    while(std::cin >> n){
        std::vector<int> nums(n, 0);
        for (int i=0; i<n; i++){
            std::cin >> num;
            list.push_back(num);
        }        

        for (int i=0; i<n-1; i++){
            if (list[i] < list[i+1]){
                a = list[i+1];
                b = list[i];
            }else{
                a = list[i];
                b = list[i+1];
            }
            dif = a-b;
            if (dif > 0 && dif < n){
                nums[dif] = 1;
            }
            
        }

        jolly = 1;
        for (int i=1; i<n; i++){
            if (nums[i] != 1){
                jolly = 0;
                break;
            }
        }

        list.clear();

        if (jolly){
            std::cout << "Jolly\n";
        }else{
            std::cout << "Not jolly\n";
        }
    }

    return 0;
}