#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
using namespace std;
map <int, vector<string>> TID; //存放data
map <string, vector<pair<int, vector<int>>>> combCount; //存放排序過後的組合&哪張發票&位置



// 讀檔
void LoadData() {
    string filename = "C:/Users/Adios/Downloads/HUIdata.txt";
    ifstream file(filename);
    if (file.is_open()) {
        int TID_id;
        string line;
        string item;

        while (getline(file, line)) {
            istringstream rd(line);
            if (rd >> TID_id >> item) {         //依序讀發票和商品名
                TID[TID_id].push_back(item);
            }

        }
        file.close();

    }
    else {
        cout << "開啟檔案錯誤" << endl;
    }
}

// 組合遞迴函數
void comb(int TID_id, const vector<string>* items, string* set, vector<int>* pos, int index) {
    if (!set->empty()) {
        combCount[*set].push_back({ TID_id, *pos });//如果空 map的key存新組合 value存商品在哪張發票和第幾個位置
    }
    for (int i = index; i < items->size(); i++) {
        string newSet = *set + "'" + (*items)[i] + "'" + " ";
        vector<int> newPos = *pos;
        newPos.push_back(i);                    //紀錄位置
        comb(TID_id, items, &newSet, &newPos, i + 1);
    }
}

int main() {
    LoadData();
    int t = 0;
    int x = 0;
    for (const auto& entry : TID) {
        int Tid_id = entry.first;                   //Map TID的key
        const vector<string>& items = entry.second;//TID的value
        comb(Tid_id, &items, new string(""), new vector<int>{}, 0);

    }


    for (const auto& entry : combCount) {
        if (entry.second.size() >= 1) {             //顯示出現n次以上的組合 combCount的value>=n
            cout << "組合:[" << entry.first << "]" << endl << endl;
            t++;
            for (const auto& pos : entry.second) {  //讀combCount的value
                 cout << "出現在發票: " << pos.first << ", 的哪些位置:[ ";
                for (int i = 0; i < pos.second.size(); ++i) {
                    cout << pos.second[i];
                    if (i != pos.second.size() - 1) {
                           cout << ", ";
                    }
                }
                 cout << "]" << endl << endl;

            }
        }
    }
    cout << "共有: " << t << " 種符合條件組合" << endl; //顯示了多少組合



    return 0;
}