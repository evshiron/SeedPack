//
// Created by evshiron on 11/15/15.
//

#include "SeedPack.h"

#include <iostream>

#define FATAL(x) { cerr << x << endl; exit(1); }

void SeedPack::Handle(string no) {

    FILE* boxFile = fopen(string("./input/box" + no + ".txt").c_str(), "r");

    if(boxFile == 0) FATAL("ERROR_BOX_FILE_NOT_FOUND");

    while(!feof(boxFile)) {

        SeedBox* box = new SeedBox();

        fscanf(boxFile, "%c %d %d %d %d %d\n", &box->Type, &box->X, &box->Y, &box->Z, &box->Capacity, &box->Count);

        cout << box->Type << " " << box->X << " " << box->Y << " " << box->Z << " " << box->Capacity << " " << box->Count << endl;

        Boxes.push_back(box);

    }

    fclose(boxFile);

    FILE* productFile = fopen(string("./input/pro" + no + ".txt").c_str(), "r");

    if(productFile == 0) FATAL("ERROR_PRODUCT_FILE_NOT_FOUND");

    while(!feof(productFile)) {

        SeedProduct* product = new SeedProduct();

        fscanf(productFile, "%c %d %d %d %d\n", &product->Type, &product->X, &product->Y, &product->Z, &product->Count);

        cout << product->Type << " " << product->X << " " << product->Y << " " << product->Z << " " << product->Count << endl;

    }

    fclose(productFile);


}
