#include <unordered_map>
#include <iostream>

using namespace std;

int main(){
    unordered_map<string, int> ar;

    ar.insert(pair<string, int>("one", 1));
    ar.emplace("four", 4);

    for (auto &item : ar){
        cout << item.first << " " << item.second << endl;
    }

    auto res = ar.erase("four");
    cout << res << endl;

    auto val = ar["one"];
    cout << val << endl;

    auto vol = ar.find("four");
   // Условие проверки наличия значения
   if (vol != ar.end()) {
       cout << vol->first << " " << vol->second << endl; // Доступ к значениям через ->
   } else {
       cout << "Element not found" << endl;
   }

    return 0;
}
