// HashMap.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "HashMap.h"
#include <iostream>
using namespace std;

int main()
{

    /*
    TO DO:
    search method, delete method
    *decrease distinctKeys in delete in some cases
    maybe: resizing 
    */

    HashMap<string, int> map;
    map.insert("ana", 2);
    map.insert("ana", 4);
    cout << map["ana"] << endl;
    try {
        cout << map["mara"] << endl;
    }
    catch (char const* e) {
        cout << e << endl;
    }
    vector<int>v = map.getValues("ana");
    for (int e : v)cout << e << " ";
    cout << endl;
    cout << map.getDistinctKeys() << endl;
    map.insert("mara", 1);
    cout << map.getDistinctKeys() << endl;
    cout << map << endl;
    HashMap<int,int> test;
    cout << test;
}