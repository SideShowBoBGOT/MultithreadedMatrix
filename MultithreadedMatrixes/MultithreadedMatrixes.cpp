#include <iostream>
#include "Object.h"
#include "TMatrix.h"


TMatrix<int> generateMatrix(ThreadPool*tp, int rows, int cols) {
    TMatrix<int> m(tp, rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
        {
            m.SetItem(i, j, rand() % 100);
        }
    }
    return m;
}
TMatrix<Object<int>> genMatrix(ThreadPool* tp, int rows, int cols) {
    TMatrix<Object<int>> m(tp, rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
        {
            m.SetItem(i, j, std::move(Object<int>(2 + rand()%10)));
        }
    }
    return m;
}
int main()
{
    srand(time(NULL));
    ThreadPool tp;
    int rows = 6;
    int cols = 10;
    TMatrix<int> m1(&tp, rows, cols);
    TMatrix<int> m2(&tp, cols, rows);
    m1 = generateMatrix(&tp, rows, cols);
    m2 = generateMatrix(&tp, cols, rows);
    std::cout << m1 << '\n';
    std::cout << m2 << '\n';
    std::cout << m1*m2 << '\n';
}
