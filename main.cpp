#include <iostream>
#include <string>

#include <stdio.h>
#include "SeedPack.h"

#define FATAL(x) { cerr << x << endl; exit(1); }

using namespace std;

int main() {

    cout << "Hello, World!" << endl;

    string no;

    while(true) {

        cin >> no;

        cout << "Handling " << no << "." << endl;

        SeedPack pack;
        pack.Handle(no);

    }

    return 0;

}