//
// Created by evshiron on 11/15/15.
//

#ifndef SEEDPACK_SEEDPACK_H
#define SEEDPACK_SEEDPACK_H

#include <list>
#include <string>

#include "SeedBox.h"
#include "SeedProduct.h"

using namespace std;

class SeedPack {

public:

    list<SeedBox*> Boxes;
    list<SeedProduct*> Products;

    SeedPack() {};
    void Handle(string no);

};


#endif //SEEDPACK_SEEDPACK_H
