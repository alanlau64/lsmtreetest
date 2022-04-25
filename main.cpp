#include "db.hpp"
#include "Value.hpp"
using namespace std;

#include <chrono>
#include "BloomFilter.h"

using namespace BF;

void queryTest( BloomFilter *bf,  string key ){
    bool result = bf->query( key );
    string result_str = (result)? "positive" : "negative";
    cout << "Bloom Filter query result of " << key  << " is " << result_str << endl;
}


void print(std::vector<int> const &input)
{
    for (int i : input) {
        cout << i << ' ';
    }
    cout << endl;
}

void deleteTableTest(){
    templatedb::DB db;
    //Test Basic DeleteTable
    cout << "Start Basic DeleteTable Test" << endl;
    DeleteTable deleteTable;
//    deleteTable.del(-10,100);
    cout << deleteTable.getTimeInt(2) << endl;
    cout << deleteTable.getTimeInt(99) << endl;

    db.put(-1,Value({1,2}));
    cout << "Put time " << db.get(-1).timestamp << endl;

    //Test save and load
    cout << "End Basic DeleteTable Test" << endl;
}

void bftest(){
    //BF Test

    BloomFilter bf( 1024, 10 ); // number of keys, bits per element

    // Enpty filter is not match, at this level
    cout << "Start Basic BF Test" << endl;
    queryTest(&bf, "hello");
    queryTest(&bf, "world");

    // insert two string
    bf.program("hello");
    bf.program("world");

    queryTest(&bf, "hello");
    queryTest(&bf, "world");
    queryTest(&bf, "x");
    queryTest(&bf, "foo");
    cout << "End Basic BF Test" << endl;
}


int main (int argc, char *argv[])
{
//    templatedb::DB db;
//    Value v1 = Value({1,2,3});
//    Value v2 = Value({4,5,6});
//    db.put(1, v1);
//    db.put(2, v1);
//    db.put(3, v1);
//    db.put(4, v1);
//    db.del(4);
//    db.put(8, v1);
//    db.put(7, v1);
//    db.put(6, v1);
//    db.put(5, v1);
//    db.put(9, v1);
//
//    auto vals = db.scan(4, 9);
//    for (auto v : vals) {
//        if (v.visible) {
//            cout << v.items.size() << endl;
//        }
//        else {
//            cout << "Not visible" << endl;
//        }
//    }

//
    map<int,Value> map1;    Value v1 = Value({1,2,3}); Value v2 = Value({100,3});
//    map1[10] = v1;
//    map1[2] = v2;
//
//    //Test SSTable & SSTableId
//    cout << "Start SSTable & SSTableId Test" << endl;
//        //Test init & Write
//    SSTableId ssid("testfile",10);
//    SSTable ssTable = SSTable(map1,ssid);
//        //Test Read
//    map<int, Value>::iterator iter;
//    map<int,Value> loadmap = ssTable.load();
//    iter = loadmap.begin();
//    while(iter != loadmap.end()) {
//        cout << iter->first << " : ";
//        print(iter->second.items);
//        iter++;
//    }
//    cout << "End SSTable & SSTableId Test" << endl;
//    //Test remove
//    //ssTable.remove();
//
//
//    //Test Basic DB put/get
//    cout << "Start Basic DB put/get Test" << endl;
//
//    templatedb::DB db;
//    for(int i=1; i<=6; i++) {
//        db.put(100 - i, Value({1,2,i + 100}));
//        cout << "DB PUT key --- " << i << endl;
//
//    }
//
//    for(int i=1; i<=3; i++) {
//        cout << "DB GET ---" << i;
//        Value v = db.get(100 - i);
//        print(v.items);
//    }
//
//    cout << "End Basic DB put/get Test" << endl;

deleteTableTest();

    return 0;
}