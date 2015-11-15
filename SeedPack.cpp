//
// Created by evshiron on 11/15/15.
//

#include "SeedPack.h"

#include <iostream>

//#define _DEBUG
#define _INFO

#define FATAL(x) { cerr << x << endl; exit(1); }

void SeedPack::Handle(string no) {

    readBox(no);
    readProduct(no);

    mOutput = new ofstream("./output/ans" + no + ".txt");

#ifdef _INFO
    cout << "EXPECT: " << getProductSize() / getBoxSize() << endl;
#endif

    //writeAnswer('A', 1, 'X', 1, 0, 0, 0, 3, 4, 5);
    place();

#ifdef _INFO
    cout << "RESULT: " << (double) mProductSize / (double) mBoxSize << endl;
#endif

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

    Boxes.sort([&](const SeedBox* a, const SeedBox* b) -> bool {

        if(a->Length > b->Length) return true;
        else return false;

    });

}

void SeedPack::readProduct(string no) {

    FILE* productFile = fopen(string("./input/pro" + no + ".txt").c_str(), "r");

    if(productFile == 0) FATAL("ERROR_PRODUCT_FILE_NOT_FOUND");

    while(!feof(productFile)) {

        SeedProduct* product = new SeedProduct();

        fscanf(productFile, "%c %d %d %d %d\n", &product->Type, &product->Length, &product->Width, &product->Height, &product->Count);

        cout << product->Type << " " << product->Length << " " << product->Width << " " << product->Height << " " << product->Count << endl;

        Products.push_back(product);

    }

    fclose(productFile);

    Products.sort([&](const SeedProduct* a, const SeedProduct* b) -> bool {

        if(a->Length > b->Length) return true;
        else return false;

    });

}

SeedBox* SeedPack::getLargestBox() {

    for(auto it = Boxes.begin(); it != Boxes.end(); it++) {

        if((*it)->Count > 0) {

            return *it;

        }

    }

    return 0;

}

SeedProduct* SeedPack::getSuitableProduct(SeedBox* box, int xBase, int yBase, int zBase, int& xSize, int& ySize, int& zSize) {

    for(auto it = Products.begin(); it != Products.end(); it++) {

        if((*it)->Count > 0) {

            if(box->Length - xBase >= (*it)->Length && box->Width - yBase >= (*it)->Width && box->Height - zBase >= (*it)->Height) {

                xSize = (*it)->Length;
                ySize = (*it)->Width;
                zSize = (*it)->Height;
                return *it;

            }
            else if(box->Length - xBase >= (*it)->Width && box->Width - yBase >= (*it)->Height && box->Height - zBase >= (*it)->Length) {

                xSize = (*it)->Width;
                ySize = (*it)->Height;
                zSize = (*it)->Length;
                return *it;

            }
            else if(box->Length - xBase >= (*it)->Height && box->Width - yBase >= (*it)->Length && box->Height - zBase >= (*it)->Width) {

                xSize = (*it)->Height;
                ySize = (*it)->Length;
                zSize = (*it)->Width;
                return *it;

            }
            else continue;

        }

    }

    return 0;

}

double SeedPack::getBoxSize() {

    double size = 0;

    for(auto it = Boxes.begin(); it != Boxes.end(); it++) {

        size += (*it)->Length * (*it)->Width * (*it)->Height * (*it)->Count;

    }

    return size;

}

double SeedPack::getProductSize() {

    double size = 0;

    for(auto it = Products.begin(); it != Products.end(); it++) {

        size += (*it)->Length * (*it)->Width * (*it)->Height * (*it)->Count;

    }

    return size;

}

int SeedPack::getBoxCount() {

    int count = 0;

    for(auto it = Boxes.begin(); it != Boxes.end(); it++) {

        count += (*it)->Count;

    }

    return count;

}

int SeedPack::getProductCount() {

    int count = 0;

    for(auto it = Products.begin(); it != Products.end(); it++) {

        count += (*it)->Count;

    }

    return count;

}

void SeedPack::place() {

    int xBase, yBase, zBase;
    int xBaseNext, yBaseNext, zBaseNext;
    int xSize, ySize, zSize;

    int blocking = 0;

    SeedBox* box;

    while((box = getLargestBox()) != 0) {

#ifdef _DEBUG
        cout << "DEBUG_BOX_LENGTH: " << box->Length << endl;
#endif

        xBase = xBaseNext = 0;
        yBase = yBaseNext = 0;
        zBase = zBaseNext = 0;

        while(true) {

            SeedProduct* product = getSuitableProduct(box, xBase, yBase, zBase, xSize, ySize, zSize);
            if(product == 0) {

#ifdef _DEBUG
                cout << "DEBUG_NO_SUITABLE_PRODUCT" << endl;
#endif
                blocking++;

                switch(blocking) {
                    case 1:
                        // Move Y.
                        yBase = yBaseNext;
                        xBase = 0;
                        goto END_PRODUCT;
                    case 2:
                        // Move Z.
                        zBase = zBaseNext;
                        xBase = 0;
                        yBase = 0;
                        goto END_PRODUCT;
                    case 3:
                    default:
                        // Next box.
                        goto END_PLACE;
                }

                break;

            }
            else blocking = 0;

            writeAnswer(product->Type, product->Count, box->Type, box->Count, xBase, yBase, zBase, xSize, ySize, zSize);

            product->Count--;
#ifdef _INFO
            mProductSize += product->Length * product->Width * product->Height;
#endif

            // TODO: Base.

            xBase += xSize;
            yBaseNext = yBase + ySize > yBaseNext ? yBase + ySize : yBaseNext;
            zBaseNext = zBase + zSize > zBaseNext ? zBase + zSize : zBaseNext;

            END_PRODUCT: cout;

        }

        END_PLACE:

        box->Count--;
#ifdef _INFO
        mBoxSize += box->Length * box->Width * box->Height;
#endif

        if(getProductCount() == 0) break;

    }

    if(box == 0) cerr << "WARNING_NO_BOX" << endl;

    cout << "INFO_BOX_REMAINING: " << getBoxCount() << endl;

    cout << "Done." << endl;

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
