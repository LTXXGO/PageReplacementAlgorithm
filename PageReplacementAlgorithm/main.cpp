//
//  main.cpp
//  PageReplacementAlgorithm
//
//  Created by LTXX on 2019/5/30.
//  Copyright © 2019 LTXX. All rights reserved.
//

#include <iostream>
#include "Pages.h"
#include "PageReplacementAlgorithm.h"
#include <vector>
using namespace std;

int main() {
    //pages.input();
    pages.append(7);
    pages.append(0);
    pages.append(1);
    pages.append(2);
    pages.append(0);
    pages.append(3);
    pages.append(0);
    pages.append(4);
    pages.append(2);
    pages.append(3);
    pages.append(0);
    pages.append(3);
    pages.append(2);
    pages.append(1);
    pages.append(2);
    pages.append(0);
    pages.append(1);
    pages.append(7);
    pages.append(0);
    pages.append(1);
    cout << "Optimal: " << endl;
    Optimal();
    cout << "FIFO: " << endl;
    FIFO();
    cout << "LRU: " << endl;
    LRU();
    return 0;
}
