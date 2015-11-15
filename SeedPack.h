//
// Created by evshiron on 11/15/15.
//

#ifndef SEEDPACK_SEEDPACK_H
#define SEEDPACK_SEEDPACK_H

#include <list>
#include <string>
#include <fstream>

#include "SeedBox.h"
#include "SeedProduct.h"

using namespace std;

class SeedPack {

public:

    list<SeedBox*> Boxes;
    list<SeedProduct*> Products;

    SeedPack() {};

    void Handle(string no);

    ~SeedPack();

private:

    long mBoxSize = 0;
    long mProductSize = 0;

    ofstream* mOutput = 0;

    void readBox(string no);
    void readProduct(string no);
    SeedBox* getLargestBox();
    SeedProduct* getSuitableProduct(SeedBox* box, int xBase, int yBase, int zBase, int& xSize, int& ySize, int& zSize);
    double getBoxSize();
    double getProductSize();
    int getBoxCount();
    int getProductCount();
    void place();
    void writeAnswer(char productType, int productId, char boxType, int boxId, int x, int y, int z, int xSize, int ySize, int zSize);

};


#endif //SEEDPACK_SEEDPACK_H
