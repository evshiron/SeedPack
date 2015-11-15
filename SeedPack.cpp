//
// Created by evshiron on 11/15/15.
//

#include "SeedPack.h"

#include <iostream>

#define FATAL(x) { cerr << x << endl; exit(1); }

void SeedPack::Handle(string no) {

    readBox(no);
    readProduct(no);

    mOutput = new ofstream("./output/ans" + no + ".txt");

    //writeAnswer('A', 1, 'X', 1, 0, 0, 0, 3, 4, 5);

}

void SeedPack::readBox(string no) {

    FILE* boxFile = fopen(string("./input/box" + no + ".txt").c_str(), "r");

    if(boxFile == 0) FATAL("ERROR_BOX_FILE_NOT_FOUND");

    while(!feof(boxFile)) {

        SeedBox* box = new SeedBox();

        fscanf(boxFile, "%c %d %d %d %d %d\n", &box->Type, &box->Length, &box->Width, &box->Height, &box->Capacity, &box->Count);

        cout << box->Type << " " << box->Length << " " << box->Width << " " << box->Height << " " << box->Capacity << " " << box->Count << endl;

        Boxes.push_back(box);

    }

    fclose(boxFile);

}

void SeedPack::readProduct(string no) {

    FILE* productFile = fopen(string("./input/pro" + no + ".txt").c_str(), "r");

    if(productFile == 0) FATAL("ERROR_PRODUCT_FILE_NOT_FOUND");

    while(!feof(productFile)) {

        SeedProduct* product = new SeedProduct();

        fscanf(productFile, "%c %d %d %d %d\n", &product->Type, &product->Length, &product->Width, &product->Height, &product->Count);

        cout << product->Type << " " << product->Length << " " << product->Width << " " << product->Height << " " << product->Count << endl;

    }

    fclose(productFile);

}

void SeedPack::writeAnswer(char productType, int productId, char boxType, int boxId, int x, int y, int z,
                           int xSize, int ySize, int zSize) {

    (*mOutput) << productType << productId << " " << boxType << boxId << " " << x << " " << y << " " << z << " " << xSize << " " << ySize << " " << zSize << endl;

}

SeedPack::~SeedPack() {

    mOutput->close();

    for(auto it = Boxes.begin(); it != Boxes.end(); it++) {

        delete *it;

    }

    for(auto it = Products.begin(); it != Products.end(); it++) {

        delete *it;

    }

}
