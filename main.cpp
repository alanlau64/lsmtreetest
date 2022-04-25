#include "db.hpp"
#include "Value.hpp"
using namespace std;
void print(std::vector<int> const &input)
{
    for (int i : input) {
        cout << i << ' ';
    }
    cout << endl;
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

    map<int,Value> map1;    Value v1 = Value({1,2,3}); Value v2 = Value({100,3});
    map1[10] = v1;
    map1[2] = v2;

    //Test SSTable & SSTableId
    cout << "Start SSTable & SSTableId Test" << endl;
        //Test init & Write
    SSTableId ssid("testfile",10);
    SSTable ssTable = SSTable(map1,ssid);
        //Test Read
    map<int, Value>::iterator iter;
    map<int,Value> loadmap = ssTable.load();
    iter = loadmap.begin();
    while(iter != loadmap.end()) {
        cout << iter->first << " : ";
        print(iter->second.items);
        iter++;
    }
    cout << "End SSTable & SSTableId Test" << endl;
    //Test remove
    //ssTable.remove();


    //Test Basic DB put/get
    cout << "Start Basic DB put/get Test" << endl;

    templatedb::DB db;
    for(int i=1; i<=6; i++) {
        db.put(100 - i, Value({1,2,i + 100}));
        cout << "DB PUT key --- " << i << endl;

    }

    for(int i=1; i<=3; i++) {
        cout << "DB GET ---" << i;
        Value v = db.get(100 - i);
        print(v.items);
    }

    cout << "End Basic DB put/get Test" << endl;

    //Test Basic DeleteTable
    cout << "Start Basic DeleteTable Test" << endl;
    DeleteTable deleteTable;
    deleteTable.del(1,10);
    cout << deleteTable.getTimeInt(2) << endl;
    cout << deleteTable.getTimeInt(100) << endl;

    db.put(-1,Value({1,2}));
    cout << "Put time " << db.get(-1).timestamp << endl;

    db.del(-10,10);


    cout << "End Basic DeleteTable Test" << endl;

}