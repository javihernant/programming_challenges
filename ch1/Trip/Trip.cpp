#include <iostream>
#include <vector>

std::string get_cents(int);

int main()
{
    int num_students;
    int total; /* total cents spent */
    int avg_floor, avg_ceil; /* average in cents */
    int remainings; /* remainings after dividing all cents into all the students */
    int money; /* all cents spent by current student */
    int dollars, cents; /*dollars and cents of current student */
    int diff_a, diff_b; 
    int res;
    std::vector<int> v;

    while(scanf("%d", &num_students) != EOF){
        
        if(num_students==0){
            break;
        }
        v.clear();
        

        total = 0;
        for(int i=0; i<num_students; i++){
            scanf("%d.%d", &dollars, &cents);
            money = dollars*100 + cents;
            v.push_back(money);
            total += money;
        }

        remainings = total % num_students;
        avg_floor = (total/num_students) + ((remainings)/num_students);
        avg_ceil = (total/num_students) + ((remainings + (num_students-1))/num_students);

        diff_a = 0;
        diff_b = 0;

        for(int i=0; i<num_students; i++){
            if(v[i] <= avg_floor){
                diff_a += avg_floor - v[i];
            }else{
                diff_b += v[i] - avg_ceil;
            }    
        }
        
        
        res = diff_a > diff_b ? diff_a : diff_b;
        std::cout << "$" << res/100 <<"." << get_cents(res%100) << "\n";
   
    }

    return 0;
}

/* to convert two or one digits into a string. 
If it is a one digit number, append a '0' in the beginning.  (i.e 1 = "01", 32 = "32") */

std::string get_cents(int num){
    int i = 1;
    std::string str {"00"};
    while(i >= 0 && num){
        str[i] = '0' + num%10;
        num /= 10;
        i--;
    }
    return str;
}