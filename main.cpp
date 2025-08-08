#include <iostream>
#include "move_semantics.hpp"
#include <vector>
#include <memory>
using namespace std;
int main() {
    {
        // test shared_ptr.
        auto deleter =[](int *p) {
            cout << "call deleter" << endl;
            delete p;
        };
        std::shared_ptr<int> share_ptr(new int {100},[](int *p) {
            cout << "call deleter: " << *p << endl;
            delete p;
        });
        share_ptr.reset(new int {29});
        std::shared_ptr<int>ptr(new int (10));
        auto ptr_1(ptr);
        cout << ptr.use_count() << ' ' <<ptr_1.use_count() << '\n';
        ptr.reset();
        cout << ptr.use_count() << ' ' <<ptr_1.use_count() << '\n' ;
    }
    // vector<MemoryBlock> v;
    // v.push_back(MemoryBlock(23));
    // v.push_back(MemoryBlock(21));
    // return 0;
}