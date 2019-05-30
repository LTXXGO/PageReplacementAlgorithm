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
    
    // 取消下列注释以从键盘输入数据
    /*
     pages.input();
     cout << "输入系统分配的物理块数: ";
     cin >> numberOfBlocks;
     */
    
    cout << "Optimal / 最佳置换算法: " << endl;
    Optimal();
    cout << "FIFO / 先进先出页面置换算法: " << endl;
    FIFO();
    cout << "LRU / 最近最久未使用置换算法: " << endl;
    LRU();
    return 0;
}
