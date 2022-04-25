#include "db.hpp"
#include "Value.hpp"
#include "operation.hpp"
using namespace std;

int main (int argc, char *argv[])
{
    templatedb::DB db;
    vector<templatedb::Operation> ops = templatedb::Operation::ops_from_file("op");

    for (auto op : ops) {
        if (op.type == templatedb::op_code::GET) {
            Value v = db.get(op.key);
            if (v.visible) {
                cout << "Key: " << op.key << " Items: ";
                for (int i : v.items)
                    cout << i << " ";
                cout << endl;
            }
            else
                cout << "Key " << op.key << " not found." << endl;
        }
        if (op.type == templatedb::op_code::PUT) {
            db.put(op.key, Value(op.args));
            cout << "Put key " << op.key << " in." << endl;
        }
    }

}