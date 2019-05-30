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
// 自定义矩阵模板类, 为了便于将结果显示在控制台上
#include "Martix.h"
#include <iostream>
using namespace std;

// 输出特殊格式函数
void output(Martix<int> result) {
    cout << "页面号序列为: " << endl;
    for (int i = 0; i < pages.length(); i++) {
        cout << pages[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < pages.length(); i++) {
        cout << "--";
    }
    cout << endl;
    for (int r = 0; r < result.getRow(); r++) {
        for (int c = 0; c < result.getColumn(); c++) {
            if (result.elem[r][c] == -1) {
                cout << " " << " ";
            } else {
                cout << result.elem[r][c] << " ";
            }
        }
        cout << endl;
    }
    cout << "缺页率为: " << calculatePageFaultRate() << endl;
}

// MARK: - 最佳置换算法
void Optimal() {
    // 定义矩阵用于存储置换过程中每一时刻的状态
    Martix<int> result(numberOfBlocks, pages.length());
    // 重置 blocks 数组
    blocks.clear();
    // 重置缺页数
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
                //cout << "*" << " ";
                result.elem[j][i] = -1;
            }
            //cout << endl;
            continue;
        } else {
            // 当前页面不在内存中
            // 如果物理块未满, 则将当前页面加入物理块中
            if (blocks.length() < numberOfBlocks) {
                blocks.append(pages.elem[i]);
                // 输出当前 blocks 数组中的元素
                for (int j = 0; j < blocks.length(); j++) {
                    //cout << blocks.elem[j] << " ";
                    result.elem[j][i] = blocks.elem[j];
                }
                // 物理块中空位用 "*" 代替
                for (int j = blocks.length(); j < numberOfBlocks; j++) {
                    //cout << "*" << " ";
                    result.elem[j][i] = -1;
                }
                //cout << endl;
            } else {
                // 否则找出物理块中之后永不使用或在很长时间内不再使用的页面
                // 将剩余页面序列复制为一个新数组
                Array<int> leftover(i, pages.length(), pages.elem);
                // 用于标记被淘汰页面的下标
                int obsolete = 0;
                // 暂时存储最长时间内不再访问的页面的下标
                int farthestPageNumber = leftover.sequentialSearch(blocks.elem[0]);
                // 在剩余页面中顺序查找物理块中已有页面的相同页面在剩余页面中出现的位置, 将最靠后的页面(或不存在的元素)在物理块中的位置赋值给 obsolete
                for (int j = 0; j < numberOfBlocks; j++) {
                    // 如果查找失败, 则当前页面以后永不使用, 立即结束循环
                    if (leftover.sequentialSearch(blocks.elem[j]) == -1) {
                        obsolete = j;
                        break;
                    }
                    if (leftover.sequentialSearch(blocks.elem[j]) > farthestPageNumber) {
                        farthestPageNumber = leftover.sequentialSearch(blocks.elem[j]);
                        obsolete = j;
                    }
                }
                // 此时 blocks 下标等于 obsolete 的物理块中页面被替换为当前页面
                blocks.elem[obsolete] = pages.elem[i];
                // 输出当前 blocks 数组中的元素
                for (int j = 0; j < blocks.length(); j++) {
                    //cout << blocks.elem[j] << " ";
                    result.elem[j][i] = blocks.elem[j];
                }
                //cout << endl;
            }
        }
    }
    output(result);
}

// MARK: - 先进先出页面置换算法
void FIFO() {
    // 定义矩阵用于存储置换过程中每一时刻的状态
    Martix<int> result(numberOfBlocks, pages.length());
    // 重置 blocks 数组
    blocks.clear();
    // 重置缺页数
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
                //cout << "*" << " ";
                result.elem[j][i] = -1;
            }
            //cout << endl;
            continue;
        } else {
            // 当前页面不在内存中
            // 如果物理块未满, 则将当前页面加入物理块中
            if (blocks.length() < numberOfBlocks) {
                blocks.append(pages.elem[i]);
                // 输出当前 blocks 数组中的元素
                for (int j = 0; j < blocks.length(); j++) {
                    //cout << blocks.elem[j] << " ";
                    result.elem[j][i] = blocks.elem[j];
                }
                // 物理块中空位用 "*" 代替
                for (int j = blocks.length(); j < numberOfBlocks; j++) {
                    //cout << "*" << " ";
                    result.elem[j][i] = -1;
                }
                //cout << endl;
            } else {
                // 否则找出物理块中最早进入的页面将其替换为当前页面
                blocks.elem[(i - pages.length() + numberOfLackPages) % numberOfBlocks] = pages.elem[i];
                // 输出当前 blocks 数组中的元素
                for (int j = 0; j < blocks.length(); j++) {
                    //cout << blocks.elem[j] << " ";
                    result.elem[j][i] = blocks.elem[j];
                }
                //cout << endl;
            }
        }
    }
    output(result);
}

// MARK: - 最近最久页面置换算法
void LRU() {
    // 定义矩阵用于存储置换过程中每一时刻的状态
    Martix<int> result(numberOfBlocks, pages.length());
    // 重置 blocks 数组
    blocks.clear();
    // 重置缺页数
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
                //cout << "*" << " ";
                result.elem[j][i] = -1;
            }
            //cout << endl;
            continue;
        } else {
            // 当前页面不在内存中
            // 如果物理块未满, 则将当前页面加入物理块中
            if (blocks.length() < numberOfBlocks) {
                blocks.append(pages.elem[i]);
                // 输出当前 blocks 数组中的元素
                for (int j = 0; j < blocks.length(); j++) {
                    //cout << blocks.elem[j] << " ";
                    result.elem[j][i] = blocks.elem[j];
                }
                // 物理块中空位用 "*" 代替
                for (int j = blocks.length(); j < numberOfBlocks; j++) {
                    //cout << "*" << " ";
                    result.elem[j][i] = -1;
                }
                //cout << endl;
            } else {
                // 否则找出物理块中之前最久未使用的页面
                // 将访问过的页面序列复制为一个新数组
                Array<int> leftover(0, i, pages.elem);
                // 用于标记被淘汰页面的下标
                int obsolete = 0;
                // 暂时存储最长时间内未访问的页面的下标
                int farthestPageNumber = leftover.reverseSearch(blocks.elem[0]);
                // 在剩余页面中倒序查找物理块中已有页面的相同页面在已访问页面中出现的位置, 将最靠前的页面在物理块中的位置赋值给 obsolete
                for (int j = 0; j < numberOfBlocks; j++) {
                    if (leftover.reverseSearch(blocks.elem[j]) < farthestPageNumber) {
                        farthestPageNumber = leftover.reverseSearch(blocks.elem[j]);
                        obsolete = j;
                    }
                }
                // 此时 blocks 下标等于 obsolete 的物理块中页面被替换为当前页面
                blocks.elem[obsolete] = pages.elem[i];
                // 输出当前 blocks 数组中的元素
                for (int j = 0; j < blocks.length(); j++) {
                    //cout << blocks.elem[j] << " ";
                    result.elem[j][i] = blocks.elem[j];
                }
                //cout << endl;
            }
        }
    }
    output(result);
}


#endif /* PageReplacementAlgorithm_h */
