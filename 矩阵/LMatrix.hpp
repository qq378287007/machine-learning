#pragma once

#define IN
#define INOUT
#define OUT

template <typename Type>
class LMatrix
{
public:
    static bool ADD(IN const LMatrix<Type> &A, IN const LMatrix<Type> &B, OUT LMatrix<Type> &C);
    static bool SUB(IN const LMatrix<Type> &A, IN const LMatrix<Type> &B, OUT LMatrix<Type> &C);
    static bool MUL(IN const LMatrix<Type> &A, IN const LMatrix<Type> &B, OUT LMatrix<Type> &C);
    static bool SCALARMUL(IN const LMatrix<Type> &A, IN const Type &B, OUT LMatrix<Type> &C);
    static bool DOTMUL(IN const LMatrix<Type> &A, IN const LMatrix<Type> &B, OUT LMatrix<Type> &C);
    static bool SCALARDIV(IN const LMatrix<Type> &A, IN const Type &B, OUT LMatrix<Type> &C);
    static bool DOTDIV(IN const LMatrix<Type> &A, IN const LMatrix<Type> &B, OUT LMatrix<Type> &C);
    static bool T(IN const LMatrix<Type> &A, OUT LMatrix<Type> &B);
    static bool SUBMATRIX(IN const LMatrix<Type> &S,
                          IN unsigned int rowStart,
                          IN unsigned int rowLen,
                          IN unsigned int colStart,
                          IN unsigned int colLen,
                          OUT LMatrix<Type> &D);

public:
    ~LMatrix();
    LMatrix(IN unsigned int row = 0, IN unsigned int col = 0);
    LMatrix(IN unsigned int row, IN unsigned int col, IN const Type &initValue);
    LMatrix(IN unsigned int row, IN unsigned int col, IN const Type *pDataList);
    LMatrix(IN const LMatrix<Type> &rhs);

    LMatrix<Type> &operator=(IN const LMatrix<Type> &rhs);
    LMatrix<Type> operator+(IN const LMatrix<Type> &B) const;
    LMatrix<Type> &operator+=(IN const LMatrix<Type> &B);
    LMatrix<Type> operator-(IN const LMatrix<Type> &B) const;
    LMatrix<Type> &operator-=(IN const LMatrix<Type> &B);
    LMatrix<Type> operator*(IN const LMatrix<Type> &B) const;
    LMatrix<Type> &operator*=(IN const LMatrix<Type> &B);
    LMatrix<Type> ScalarMul(IN const Type &B) const;
    LMatrix<Type> ScalarDiv(IN const Type &B) const;

    Type *&operator[](IN unsigned int row) { return m_DataTable[row]; }
    const Type *operator[](IN unsigned int row) const { return m_DataTable[row]; }

    bool Empty() const { return m_ColumnLen == 0 || m_RowLen == 0; }
    bool Square() const { return m_ColumnLen == m_RowLen && m_ColumnLen != 0; }

    LMatrix<Type> T() const;

    void SplitRow(IN unsigned int rowIdx, OUT LMatrix<Type> &up, OUT LMatrix<Type> &down) const;       // 索引行被包含在下矩阵中
    void SplitCloumn(IN unsigned int colIdx, OUT LMatrix<Type> &left, OUT LMatrix<Type> &right) const; // 索引列被包含在右矩阵中

    LMatrix<Type> SubMatrix(IN unsigned int rowStart, IN unsigned int rowLen, IN unsigned int colStart, IN unsigned int colLen) const;
    void SubMatrix(IN unsigned int rowStart, IN unsigned int rowLen, IN unsigned int colStart, IN unsigned int colLen, OUT LMatrix<Type> &D) const;

    LMatrix<Type> GetRow(IN unsigned int row) const;
    void GetRow(IN unsigned int row, OUT LMatrix<Type> &rowVector) const;
    LMatrix<Type> GetColumn(IN unsigned int col) const;
    void GetColumn(IN unsigned int col, OUT LMatrix<Type> &colVector) const;

    void Reset(IN unsigned int row, IN unsigned int col);
    void Reset(IN unsigned int row, IN unsigned int col, IN const Type &initValue);

public:
    unsigned int getRowLen() const { return m_RowLen; };
    unsigned int getColumnLen() const { return m_ColumnLen; };

private:
    Type **m_DataTable{nullptr}; ///< 二维数据表
    Type *m_DataList{nullptr};   ///< 实际存储的数据列表
    unsigned int m_RowLen{0};    ///< 矩阵行长度
    unsigned int m_ColumnLen{0}; ///< 矩阵列长度
};

template <typename Type>
LMatrix<Type>::~LMatrix()
{
    if (m_DataTable)
    {
        delete[] m_DataTable;
        m_DataTable = nullptr;
    }

    if (m_DataList)
    {
        delete[] m_DataList;
        m_DataList = nullptr;
    }
}

template <typename Type>
LMatrix<Type>::LMatrix(IN unsigned int row, IN unsigned int col) { Reset(row, col); }

template <typename Type>
LMatrix<Type>::LMatrix(IN unsigned int row, IN unsigned int col, IN const Type &initValue)
{
    Reset(row, col);
    unsigned int size = row * col;
    for (unsigned int i = 0; i < size; i++)
        m_DataList[i] = initValue;
}

template <typename Type>
LMatrix<Type>::LMatrix(IN unsigned int row, IN unsigned int col, IN const Type *pDataList)
{
    Reset(row, col);
    unsigned int size = row * col;
    for (unsigned int i = 0; i < size; i++)
        m_DataList[i] = pDataList[i];
}

template <typename Type>
LMatrix<Type>::LMatrix(IN const LMatrix<Type> &rhs)
{
    unsigned int row = rhs.getRowLen();
    unsigned int col = rhs.getColumnLen();

    Reset(row, col);
    unsigned int size = row * col;
    for (unsigned int i = 0; i < size; i++)
        m_DataList[i] = rhs.m_DataList[i];
}

template <typename Type>
LMatrix<Type> &LMatrix<Type>::operator=(IN const LMatrix<Type> &rhs)
{
    unsigned int row = rhs.getRowLen();
    unsigned int col = rhs.getColumnLen();

    Reset(row, col);
    unsigned int size = row * col;
    for (unsigned int i = 0; i < size; i++)
        m_DataList[i] = rhs.m_DataList[i];
    return *this;
}

template <typename Type>
LMatrix<Type> LMatrix<Type>::operator+(IN const LMatrix<Type> &B) const
{
    LMatrix<Type> C;
    ADD(*this, B, C);
    return C;
}

template <typename Type>
LMatrix<Type> &LMatrix<Type>::operator+=(IN const LMatrix<Type> &B)
{
    ADD(*this, B, *this);
    return *this;
}

template <typename Type>
LMatrix<Type> LMatrix<Type>::operator-(IN const LMatrix<Type> &B) const
{
    LMatrix<Type> C;
    SUB(*this, B, C);
    return C;
}

template <typename Type>
LMatrix<Type> &LMatrix<Type>::operator-=(IN const LMatrix<Type> &B)
{
    SUB(*this, B, *this);
    return *this;
}

template <typename Type>
LMatrix<Type> LMatrix<Type>::operator*(IN const LMatrix<Type> &B) const
{
    LMatrix<Type> C;
    MUL(*this, B, C);
    return C;
}

template <typename Type>
LMatrix<Type> &LMatrix<Type>::operator*=(IN const LMatrix<Type> &B)
{
    LMatrix<Type> C;
    MUL(*this, B, C);
    *this = C;
    return *this;
}

template <typename Type>
LMatrix<Type> LMatrix<Type>::ScalarMul(IN const Type &B) const
{
    LMatrix<Type> C;
    SCALARMUL(*this, B, C);
    return C;
}

template <typename Type>
LMatrix<Type> LMatrix<Type>::ScalarDiv(IN const Type &B) const
{
    LMatrix<Type> C;
    SCALARDIV(*this, B, C);
    return C;
}

template <typename Type>
LMatrix<Type> LMatrix<Type>::T() const
{
    LMatrix<Type> B;
    T(*this, B);
    return B;
}

template <typename Type>
void LMatrix<Type>::SplitRow(IN unsigned int rowIdx, OUT LMatrix<Type> &up, OUT LMatrix<Type> &down) const
{
    up.Reset(0, 0);
    down.Reset(0, 0);
    SUBMATRIX(*this, 0, rowIdx, 0, m_ColumnLen, up);
    SUBMATRIX(*this, rowIdx, m_RowLen - rowIdx, 0, m_ColumnLen, down);
}

template <typename Type>
void LMatrix<Type>::SplitCloumn(IN unsigned int colIdx, OUT LMatrix<Type> &left, OUT LMatrix<Type> &right) const
{
    left.Reset(0, 0);
    right.Reset(0, 0);
    SUBMATRIX(*this, 0, m_RowLen, 0, colIdx, left);
    SUBMATRIX(*this, 0, m_RowLen, colIdx, m_ColumnLen - colIdx, right);
}

template <typename Type>
LMatrix<Type> LMatrix<Type>::SubMatrix(IN unsigned int rowStart, IN unsigned int rowLen, IN unsigned int colStart, IN unsigned int colLen) const
{
    LMatrix<Type> D;
    SUBMATRIX(*this, rowStart, rowLen, colStart, colLen, D);
    return D;
}

template <typename Type>
void LMatrix<Type>::SubMatrix(IN unsigned int rowStart, IN unsigned int rowLen, IN unsigned int colStart, IN unsigned int colLen, OUT LMatrix<Type> &D) const
{
    SUBMATRIX(*this, rowStart, rowLen, colStart, colLen, D);
}

template <typename Type>
LMatrix<Type> LMatrix<Type>::GetRow(IN unsigned int row) const
{
    LMatrix<Type> rowVector(1, m_ColumnLen);
    GetRow(row, rowVector);
    return rowVector;
}

template <typename Type>
void LMatrix<Type>::GetRow(IN unsigned int row, OUT LMatrix<Type> &rowVector) const
{
    rowVector.Reset(1, m_ColumnLen);
    for (unsigned int i = 0; i < m_ColumnLen; i++)
        rowVector.m_DataTable[0][i] = m_DataTable[row][i];
}

template <typename Type>
LMatrix<Type> LMatrix<Type>::GetColumn(IN unsigned int col) const
{
    LMatrix<Type> columnVector(m_RowLen, 1);
    GetColumn(col, columnVector);
    return columnVector;
}

template <typename Type>
void LMatrix<Type>::GetColumn(IN unsigned int col, OUT LMatrix<Type> &colVector) const
{
    colVector.Reset(m_RowLen, 1);
    for (unsigned int i = 0; i < m_RowLen; i++)
        colVector.m_DataTable[i][0] = m_DataTable[i][col];
}

template <typename Type>
void LMatrix<Type>::Reset(IN unsigned int row, IN unsigned int col)
{
    if (m_RowLen != row || m_ColumnLen != col)
    {
        if (m_DataTable)
        {
            delete[] m_DataTable;
            m_DataTable = nullptr;
        }

        if (m_DataList)
        {
            delete[] m_DataList;
            m_DataList = nullptr;
        }

        if (row * col > 0)
        {
            m_RowLen = row;
            m_ColumnLen = col;

            m_DataTable = new Type *[m_RowLen];
            m_DataList = new Type[m_RowLen * m_ColumnLen];
            for (unsigned int i = 0; i < m_RowLen; i++)
                m_DataTable[i] = &m_DataList[m_ColumnLen * i];
        }
        else
        {
            m_RowLen = 0;
            m_ColumnLen = 0;
        }
    }
}

template <typename Type>
void LMatrix<Type>::Reset(IN unsigned int row, IN unsigned int col, IN const Type &initValue)
{
    Reset(row, col);
    unsigned int size = row * col;
    for (unsigned int i = 0; i < size; i++)
        m_DataList[i] = initValue;
}

template <typename Type>
bool LMatrix<Type>::ADD(IN const LMatrix<Type> &A, IN const LMatrix<Type> &B, OUT LMatrix<Type> &C)
{
    if (A.getRowLen() != B.getRowLen() || A.getColumnLen() != B.getColumnLen())
        return false;

    C.Reset(A.getRowLen(), A.getColumnLen());
    for (unsigned int i = 0; i < C.getRowLen(); i++)
        for (unsigned int j = 0; j < C.getColumnLen(); j++)
            C.m_DataTable[i][j] = A.m_DataTable[i][j] + B.m_DataTable[i][j];
    return true;
}

template <typename Type>
bool LMatrix<Type>::SUB(IN const LMatrix<Type> &A, IN const LMatrix<Type> &B, OUT LMatrix<Type> &C)
{
    if (A.getRowLen() != B.getRowLen() || A.getColumnLen() != B.getColumnLen())
        return false;

    C.Reset(A.getRowLen(), A.getColumnLen());
    for (unsigned int i = 0; i < C.getRowLen(); i++)
        for (unsigned int j = 0; j < C.getColumnLen(); j++)
            C.m_DataTable[i][j] = A.m_DataTable[i][j] - B.m_DataTable[i][j];
    return true;
}

template <typename Type>
bool LMatrix<Type>::MUL(IN const LMatrix<Type> &A, IN const LMatrix<Type> &B, OUT LMatrix<Type> &C)
{
    if (A.getColumnLen() != B.getRowLen())
        return false;

    C.Reset(A.getRowLen(), B.getColumnLen());
    for (unsigned int i = 0; i < C.getRowLen(); i++)
        for (unsigned int j = 0; j < C.getColumnLen(); j++)
        {
            C.m_DataTable[i][j] = A.m_DataTable[i][0] * B.m_DataTable[0][j];
            for (unsigned int k = 1; k < A.getColumnLen(); k++)
                C.m_DataTable[i][j] += A.m_DataTable[i][k] * B.m_DataTable[k][j];
        }
    return true;
}

template <typename Type>
bool LMatrix<Type>::SCALARMUL(IN const LMatrix<Type> &A, IN const Type &B, OUT LMatrix<Type> &C)
{
    C.Reset(A.getRowLen(), A.getColumnLen());
    for (unsigned int row = 0; row < A.getRowLen(); row++)
        for (unsigned int col = 0; col < A.getColumnLen(); col++)
            C.m_DataTable[row][col] = A.m_DataTable[row][col] * B;
    return true;
}

template <typename Type>
bool LMatrix<Type>::DOTMUL(IN const LMatrix<Type> &A, IN const LMatrix<Type> &B, OUT LMatrix<Type> &C)
{
    if (A.getRowLen() != B.getRowLen() || A.getColumnLen() != B.getColumnLen())
        return false;

    C.Reset(A.getRowLen(), A.getColumnLen());
    for (unsigned int i = 0; i < C.getRowLen(); i++)
        for (unsigned int j = 0; j < C.getColumnLen(); j++)
            C.m_DataTable[i][j] = A.m_DataTable[i][j] * B.m_DataTable[i][j];
    return true;
}

template <typename Type>
bool LMatrix<Type>::SCALARDIV(IN const LMatrix<Type> &A, IN const Type &B, OUT LMatrix<Type> &C)
{
    C.Reset(A.getRowLen(), A.getColumnLen());
    for (unsigned int row = 0; row < A.getRowLen(); row++)
        for (unsigned int col = 0; col < A.getColumnLen(); col++)
            C.m_DataTable[row][col] = A.m_DataTable[row][col] / B;
    return true;
}

template <typename Type>
bool LMatrix<Type>::DOTDIV(IN const LMatrix<Type> &A, IN const LMatrix<Type> &B, OUT LMatrix<Type> &C)
{
    if (A.getRowLen() != B.getRowLen() || A.getColumnLen() != B.getColumnLen())
        return false;

    C.Reset(A.getRowLen(), A.getColumnLen());
    for (unsigned int i = 0; i < C.getRowLen(); i++)
        for (unsigned int j = 0; j < C.getColumnLen(); j++)
            C.m_DataTable[i][j] = A.m_DataTable[i][j] / B.m_DataTable[i][j];
    return true;
}

template <typename Type>
bool LMatrix<Type>::T(IN const LMatrix<Type> &A, OUT LMatrix<Type> &B)
{
    B.Reset(A.getColumnLen(), A.getRowLen());
    for (unsigned int i = 0; i < A.getRowLen(); i++)
        for (unsigned int j = 0; j < A.getColumnLen(); j++)
            B.m_DataTable[j][i] = A.m_DataTable[i][j];
    return true;
}

template <typename Type>
bool LMatrix<Type>::SUBMATRIX(IN const LMatrix<Type> &S,
                              IN unsigned int rowStart,
                              IN unsigned int rowLen,
                              IN unsigned int colStart,
                              IN unsigned int colLen,
                              OUT LMatrix<Type> &D)
{
    if (rowStart + rowLen > S.getRowLen() || colStart + colLen > S.getColumnLen() || rowLen < 1 || colLen < 1)
        return false;

    D.Reset(rowLen, colLen);
    for (unsigned int row = 0; row < D.getRowLen(); row++)
        for (unsigned int col = 0; col < D.getColumnLen(); col++)
            D[row][col] = S[rowStart + row][colStart + col];
    return true;
}
