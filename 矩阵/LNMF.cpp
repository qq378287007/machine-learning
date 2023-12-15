#include <stdlib.h>
#include "LNMF.h"

// 随机小数(0.0f~1.0f)
static inline float RandFloat()
{
    return rand() / (RAND_MAX + 1.0f);
}
static inline void RandNMFMatrix(INOUT LNMFMatrix &m)
{
    for (unsigned int i = 0; i < m.getRowLen(); i++)
        for (unsigned int j = 0; j < m.getColumnLen(); j++)
            m[i][j] = RandFloat();
}

bool Factoring(IN const LNMFMatrix &V, IN const unsigned int R, IN const unsigned int IterCount, OUT LNMFMatrix *pW, OUT LNMFMatrix *pH)
{
    if (nullptr == pW || nullptr == pH || 0 == R || 0 == IterCount || 0 == V.getRowLen() || 0 == V.getColumnLen())
        return false;

    for (unsigned int row = 0; row < V.getRowLen(); row++)
        for (unsigned int col = 0; col < V.getColumnLen(); col++)
            if (V[row][col] < 0.0f)
                return false;

    // 生成基矩阵
    LNMFMatrix W; // 基矩阵
    W.Reset(V.getRowLen(), R);
    RandNMFMatrix(W);

    // 生成特征矩阵
    LNMFMatrix H; // 系数矩阵
    H.Reset(R, V.getColumnLen());
    RandNMFMatrix(H);

    LNMFMatrix TF;
    LNMFMatrix TW;
    LNMFMatrix TWW;

    LNMFMatrix HN;
    LNMFMatrix HD;
    LNMFMatrix HHN;

    LNMFMatrix WN;
    LNMFMatrix WD;
    LNMFMatrix WH;
    LNMFMatrix WWN;

    for (unsigned int i = 0; i < IterCount; i++) // 迭代求解
    {
        LNMFMatrix::T(W, TW);
        LNMFMatrix::MUL(TW, V, HN);
        LNMFMatrix::MUL(TW, W, TWW);
        LNMFMatrix::MUL(TWW, H, HD);

        LNMFMatrix::DOTMUL(H, HN, HHN);
        LNMFMatrix::DOTDIV(HHN, HD, H);

        LNMFMatrix::T(H, TF);
        LNMFMatrix::MUL(V, TF, WN);
        LNMFMatrix::MUL(W, H, WH);
        LNMFMatrix::MUL(WH, TF, WD);

        LNMFMatrix::DOTMUL(W, WN, WWN);
        LNMFMatrix::DOTDIV(WWN, WD, W);
    }

    *pW = W;
    *pH = H;

    return true;
}