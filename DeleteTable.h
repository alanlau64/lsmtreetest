//
// Created by Junchen Liu on 4/24/2022.
//

#ifndef TEST_DELETETABLE_H
#define TEST_DELETETABLE_H
#include <ctime>
#include <vector>
#include <string>

using namespace std;

class MinMaxPair
{
public:
    int minKey ;
    int maxKey;
    unsigned long int t;



    MinMaxPair(int _min, int _max) {
        minKey = _min;
        maxKey = _max;
        t = time(nullptr);
    }

    MinMaxPair(int _min, int _max, unsigned long int _t) {
        minKey = _min;
        maxKey = _max;
        t = _t;
    }

};


class DeleteTable {
public:
    DeleteTable();
    ~DeleteTable() {close();};

    unsigned long int getTimeInt(int key); //If get 0, then not in dt.
    void del(int min_key, int max_key);
    void close();

private:
    vector<MinMaxPair> vec;
    string fileName = "dtFile";

    void load();
    void save();
};


#endif //TEST_DELETETABLE_H
