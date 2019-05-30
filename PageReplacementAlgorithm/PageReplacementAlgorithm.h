//
//  PageReplacementAlgorithm.h
//  PageReplacementAlgorithm
//
//  Created by LTXX on 2019/5/30.
//  Copyright © 2019 LTXX. All rights reserved.
//

#ifndef PageReplacementAlgorithm_h
#define PageReplacementAlgorithm_h
#include "Pages.h"
#include <iostream>
using namespace std;

// MARK: - 最佳置换算法
void Optimal() {
    numberOfLackPages = pages.length();
    // 遍历整个页面序列
    for (int i = 0; i < pages.length(); i++) {
        // 用以标记当前页面是否已在内存中
        bool existed = false;
        // 遍历blocks数组, 判断当前页面是否已在内存中
        for (int j = 0; j < blocks.length(); j++) {
            // 如果当前页面已在内存中
            if (pages.elem[i] == blocks.elem[j]) {
                // 缺页数-1
                numberOfLackPages -= 1;
                // 更新标记
                existed = true;
                break;
            }
        }
        // 如果当前页面已在内存中, 则执行下一次循环检查下一个页面
        if (existed) {
            // 输出空位表示此处未产生缺页
            for (int j = 0; j < blocks.length(); j++) {
                cout << "*" << " ";
            }
            cout << endl;
            continue;
        } else {
            // 当前页面不在内存中
            // 如果物理块未满, 则将当前页面加入物理块中
            if (blocks.length() < numberOfPhysicalBlock) {
                blocks.append(pages.elem[i]);
                // 输出当前 blocks 数组中的元素
                for (int j = 0; j < blocks.length(); j++) {
                    cout << blocks.elem[j] << " ";
                }
                // 空位用 "*" 代替
                for (int j = 0; j < numberOfPhysicalBlock - blocks.length(); j++) {
                    cout << "*" << " ";
                }
                cout << endl;
            } else {
                // 否则找出物理块中之后永不使用或在很长时间内不再使用的页面
                // 将剩余元素复制为一个新数组
                Array<int> leftover(i, pages.length(), pages.elem);
                // 用于标记被淘汰页面的下标
                int obsolete = 0;
                // 暂时存储最长时间内不再访问的页面
                int farthestPage = leftover.sequentialSearch(blocks.elem[0]);
                // 在剩余页面中依次查找物理块中已有页面的相同页面在剩余页面中出现的位置, 将最靠后的页面(或不存在的元素)在物理块中的位置赋值给 obsolete
                for (int j = 0; j < numberOfPhysicalBlock; j++) {
                    // 如果查找失败, 则当前页面以后永不使用, 立即结束循环
                    if (leftover.sequentialSearch(blocks.elem[j]) == -1) {
                        obsolete = j;
                        break;
                    }
                    if (leftover.sequentialSearch(blocks.elem[j]) > farthestPage) {
                        farthestPage = leftover.sequentialSearch(blocks.elem[j]);
                        obsolete = j;
                    }
                }
                // 此时 blocks 下标等于 obsolete 的物理块中页面被淘汰, 替换为当前页面
                blocks.elem[obsolete] = pages.elem[i];
                // 输出当前 blocks 数组中的元素
                for (int j = 0; j < blocks.length(); j++) {
                    cout << blocks.elem[j] << " ";
                }
                cout << endl;
            }
        }
    }
}

// MARK: - 先进先出页面置换算法
void FIFO() {
    
}

// MARK: - 最近最久页面置换算法
void LRU() {
    
}



#endif /* PageReplacementAlgorithm_h */
