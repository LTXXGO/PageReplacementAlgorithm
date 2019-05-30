//
//  Pages.h
//  PageReplacementAlgorithm
//
//  Created by LTXX on 2019/5/30.
//  Copyright © 2019 LTXX. All rights reserved.
//

#ifndef Pages_h
#define Pages_h
#include <iostream>
// 自定义数组模板类
#include "Array.h"
using namespace std;

// 物理块数
int numberOfPhysicalBlock = 3;
// 页面序列
Array<int> pages;
// 内存物理块
Array<int> blocks;
// 缺页数初始化为全部, 未产生缺页中断时 -1
int numberOfLackPages = pages.length();

// 计算缺页率
float calculatePageFaultRate() {
    return float(numberOfLackPages) / float(pages.length());
}
#endif /* Pages_h */
