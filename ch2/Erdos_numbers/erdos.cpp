#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <limits>

void read_entry(std::vector<std::string>& names);
void ignore_line();
void init_lvls(std::unordered_map<std::string, int>& lvls, std::vector<std::vector<std::string>>& entries );

int main()
{
    int scenarios;
    int num_entries;
    int num_names;
    std::string name;
    int best_lv;
    std::cin >> scenarios;

    for (int s{0}; s<scenarios; s++){
        std::cout << "Scenario " << s+1 << "\n";
        std::cin >> num_entries;
        std::cin >> num_names;
        std::unordered_map<std::string, int> lvls = 
        {
            {"Erdos, P.", 0},
        };

        std::vector<std::vector<std::string>> entries;
        for (int i{0}; i<num_entries; i++){
            std::cin >> std::ws;
            entries.push_back(std::vector<std::string>());
            read_entry(entries[i]);
        }

        init_lvls(lvls, entries);

        for (int i{0}; i<num_names; i++){
            std::getline(std::cin, name);
            std::cout << name << " ";
            if (lvls.count(name)){
                std::cout << lvls[name] << "\n";
            }else{
                std::cout << "infinity\n";
            }
        }
    }

    return 0;
}

void init_lvls(std::unordered_map<std::string, int>& lvls, std::vector<std::vector<std::string>>& entries )
{
    int lv_not_found = 0;
    int lv = 0;
    std::string name;
    std::vector<int> look_at;
    for (int i{0}; i<entries.size(); i++){
        look_at.push_back(i);
    }
    int entries_left = look_at.size();
    while (entries_left > 0){
        std::vector<int> tmp_look_at;
        for (const int idx:look_at){
            int skip = -1;
            //search for name with level = lv
            for (int i{0}; i<entries[idx].size(); i++){
                name = entries[idx][i];
                if (lvls.count(name)){
                    if (lvls[name] == lv){
                        skip = i;
                        break;
                    }
                }
            }

            if (skip != -1){
                for (int i{0}; i<entries[idx].size(); i++){
                    name = entries[idx][i];
                    if (i != skip && lvls.count(name)==0){
                        lvls[name] = lv+1;
                    }
                }

            }else{
                tmp_look_at.push_back(idx);
            }
        }
        //break if there's no conexion to a particular lv
        if (tmp_look_at.size() == entries_left){
            break;
        }else{
            look_at.clear();
            for (int idx: tmp_look_at){
                look_at.push_back(idx);
            }
            entries_left = look_at.size();
        }
        ++lv;
    }
}

void read_entry(std::vector<std::string>& names)
{
    std::string nm;
    char c;
    int count = 0;  
    while (true){
        if (count == 2){
            names.push_back(nm);
            nm.clear();
            std::cin >> std::ws;
            count = 0;
            if (c == ':'){
                ignore_line(); //ignores rest of the line
                break;
            }
        }

        c = std::cin.get();
        if (c == ',' || c == ':'){
            ++count;
        }
        if (count < 2){
            if (c!=':'){
                nm.push_back(c);
            }else{
                ignore_line();
                break;
            }
        }
    }
} 

void ignore_line(){
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

