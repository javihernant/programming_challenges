#include <iostream>
#include <vector>

void init_regs(std::vector<int>& regs);
void init_ram(std::vector<std::string>& ram);
int execute_ins(std::vector<std::string>& ram, std::vector<int>& regs);

int main()
{
    int res; /*number of instructions executed*/
    std::vector<std::string> ram;
    std::vector<int> regs;

    int num_tests;
    std::cin >> num_tests;

    for(int i{0}; i<num_tests; i++){
        init_regs(regs);
        init_ram(ram);
        res = execute_ins(ram, regs);
        std::cout << res << '\n'; 
        if (i<num_tests-1){
            std::cout << '\n';
        }
    }
    
    return 0;
}

void init_regs(std::vector<int>& regs)
{
    regs.clear();
    for (int i{0}; i<10; i++){
        regs.push_back(0);
    }
}

void init_ram(std::vector<std::string>& ram)
{
    int c;
    std::string val;
    ram.clear();
    int i{0};
    
    std::cin>>std::ws;
    while ((c=std::cin.peek()) != EOF && c != '\n'){
        std::cin >> val;
        std::cin.ignore(); /* ignore the \n after the number */
        ram.push_back(val);
        i++;
    }
    
    for (; i<1000; i++){
        ram.push_back("000");
    }
}

void store_num(std::string& str,int num);

int execute_ins(std::vector<std::string>& ram, std::vector<int>& regs)
{
    int count = 0;
    int i = 0;
    int new_i;
    int a,b,c;
    for ( ;i<ram.size(); count++){
        a = ram[i][0] - '0';
        b = ram[i][1] - '0';
        c = ram[i][2] - '0';

        switch (a)
        {
        case 1:
            if (b == 0 && c == 0){
                return count+1;
            }
            break;
        case 2:
            regs[b] = c;
            break;
        case 3:
            regs[b] = (regs[b] + c) % 1000;
            break;
        case 4:
            regs[b] = (regs[b] * c) % 1000;
            break;
        case 5:
            regs[b] = regs[c];
            break;
        case 6:
            regs[b] = (regs[c]+regs[b])%1000;
            break;
        case 7:
            regs[b] = (regs[c]*regs[b])%1000;
            break;
        case 8:
            regs[b] = std::stoi(ram[regs[c]]);
            break;
        case 9:
            store_num(ram[regs[c]],regs[b]);
            break;
        case 0:
            new_i = regs[b];
            if (regs[c] != 0){
                i = new_i;
                continue;
            }
            break;
        }
        i++;
    }

    return count;
}

void store_num(std::string& str,int num)
{
    int i = 2;
    while(num && i>=0){
        str[i] = '0' + num%10;
        num/=10;
        i--;
    }
}