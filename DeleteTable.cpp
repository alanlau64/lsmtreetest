//
// Created by Junchen Liu on 4/24/2022.
//

#include "DeleteTable.h"

DeleteTable::DeleteTable() {
    //Find if there exist dt file, if so load

}

void DeleteTable::del(int min_key, int max_key){
    vec.emplace_back(min_key,max_key);
}

unsigned long int DeleteTable::getTimeInt(int key) {
    for (auto it = vec.rbegin(); it != vec.rend(); ++it)
    {
        if(key < it->maxKey && key > it->minKey){
            return it->t;
        }
    }
    return 0;
}
