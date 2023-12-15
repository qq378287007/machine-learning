#pragma once

#include "LMatrix.hpp"

// 非负矩阵因式分解
// 将一个非负矩阵分解为两个非负矩阵的乘, V = W * H
// V为原始矩阵, W为基矩阵, H为系数矩阵
// 基矩阵的列数和系数矩阵的行数为R

/*
float dataList[4] =
{
    1.0f, 2.0f,
    3.0f, 4.0f
};
LNMFMatrix V(2, 2, dataList);
const unsigned int R = 2;
const unsigned int IterCount = 50;
LNMFMatrix W;
LNMFMatrix H;
bool flag = Factoring(problem, &W, &H);
*/

// V原始矩阵(不能有负数)
// R基矩阵的列数(系数矩阵的行数)
// IterCount迭代次数

typedef LMatrix<float> LNMFMatrix;
bool Factoring(IN const LNMFMatrix &V, IN const unsigned int R, IN const unsigned int IterCount, OUT LNMFMatrix *pW, OUT LNMFMatrix *pH);
