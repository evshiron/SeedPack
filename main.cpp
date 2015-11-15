#include <iostream>
#include <string>

#include <stdio.h>
#include "SeedPack.h"

#define FATAL(x) { cerr << x << endl; exit(1); }

using namespace std;

int main(int argc, char** argv) {

    //cout << "Hello, World!" << endl;

    if(argc > 1) {

        for(int i = 1; i < argc; i++) {

            cout << "Handling " << argv[i] << "." << endl;

            SeedPack pack;
            pack.Handle(string(argv[i]));

        }

    }
    else {

        string no;

        while(true) {

            cin >> no;

            cout << "Handling " << no << "." << endl;

            SeedPack pack;
            pack.Handle(no);

        }

    }

    return 0;

}