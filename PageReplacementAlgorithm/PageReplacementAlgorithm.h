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
    // 把前n个互不相同的页面装入内存(当物理块数组未满时)
    for (int i = 0; blocks.length() < numberOfPhysicalBlock; i++) {
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
        // 如果当前页面已在内存中则执行下一次循环检查下一个页面
        if (existed) {
            continue;
        } else {
            // 当前页面不在内存中且物理块未满, 则将当前页面加入物理块中
            blocks.append(pages.elem[i]);
        }
    }
    
    // 遍历之后的页面序列数 = 缺页数 - 物理块中的页数
    for (int i = numberOfLackPages - numberOfPhysicalBlock; i < pages.length(); i++) {
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
        // 如果当前页面已在内存中则执行下一次循环检查下一个页面
        if (existed) {
            continue;
        } else {
            // 如果当前页面不在内存中, 找出物理块中之后永不使用或在很长时间内不再使用的页面
            // 将剩余元素复制为一个新数组
            Array<int> leftover(i, pages.length(), pages.elem);
            // 用于标记被淘汰页面的下标
            int obsolete = 0;
            // 在剩余页面中依次查找物理块中已有页面的相同页面在剩余页面中出现的位置, 将最靠后的页面(或不存在的元素)在物理块中的位置赋值给 obsolete
            for (int j = 0; j < numberOfPhysicalBlock; j++) {
                // 如果查找失败, 则当前页面以后永不使用, 立即结束循环
                if (leftover.sequentialSearch(blocks.elem[j]) == -1) {
                    obsolete = j;
                    break;
                }
                if (leftover.sequentialSearch(blocks.elem[j]) < leftover.sequentialSearch(blocks.elem[j + 1])) {
                    obsolete = j + 1;
                }
            }
            // 此时 blocks 下标等于 obsolete 的物理块中页面被淘汰, 替换为当前页面
            blocks.elem[obsolete] = pages.elem[i];
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
