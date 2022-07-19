#pragma once

#include <future>
#include <vector>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <sstream>
#include "MatrixesIncompatible.h"
#include "MatrixNotSquare.h"
#include "MatrixInvalidIndex.h"
#include "ThreadPool.h"
/*
    A template class representing matrix. It is threadsafe and operations
    of adding, subtracting and multiplying are multithreaded.

    Author:             Serhii Panchenko
    Telegram:           @choleraplague
    Email:              SideShowBoBGOT@gmail.com
    ================================================================================
    Instance attributes:
        1)  Name:       mat
            Type:       Cell**
            Access:     private 
            Desc:       The matrix istself

        2)  Name:        mtx
            Type:       std::shared_mutex
            Access:     private 
            Desc:       Shared mutex to isolate operations upon the whole matrix
                        between several threads.
    
        3)  Name:       rows
            Type:       int 
            Access:     private
            Desc:       Number of rows in the matrix
    
        4)  Name:       cols
            Type:       int
            Access:     private
            Desc:       Number of columns in the matrix
    ================================================================================
    Class Attributes:
        1)  Name:       tp
            Type:       ThreadPool
            Access:     private
            Desc:       Thread pool that contolls tasks sent by all instances
                        of the class

        2)  Name:       maxThsNum
            Type:       int
            Access:     private
            Desc:       Maximum number of threads available on the current
                        machine
    ================================================================================
    Inner Structures:
        1)  Type:       Cell
            Access:     private
            Desc:       Structure representing single cell.

                Instance attributes:

                    1)  Name:   mtx
                        Type:   std::shared_mutex
                        Access: public
                        Desc:   Shared mutex to isolate operations upon single cell
                                between several threads.
                    
                    2)  Name:   data
                        Type:   T
                        Access: public
                        Desc:   Data that cell holds.
    ================================================================================
    Constructors:
        
        1)  Params:     void
            Access:     public
            Desc:       Default constructor
        
        2)  Params:
                    -   Name:   rows
                        Type:   [in]    int
                        Desc:   Number of rows in the matrix.
                    
                    -   Name:   cols
                        Type:   [in]    int
                        Desc:   Number of columns in the matrix.
            Access:     public

        3)  Params: -   Name:   other
                        Type:   [in]    TMatrix&
                        Desc:   The other one instance of TMatrix
            Access:     public
            Desc:       Copy constructor
        
        4)  Params: -   Name:   other
                        Type:   [in]    TMatrix&&
                        Desc:   The other one instance of TMatrix
            Access:     public
            Desc:       Move constructor
    ================================================================================
    Destructors:
        
        1)  Params:     void
            Access:     public
            Desc:       Destructor that deletes mat attribute which
                        allocates memory from heap
    ================================================================================
    Instance methods:
        
        1)  Name:       GetRows
            Params:     void
            Access:     public
            Return:     int
            Desc:       Method returning number of rows of the matrix
        
        2)  Name:       GetCols
            Params:     void
            Access:     public
            Return:     int
            Desc:       Method returning number of columns of the matrix

        3)  Name:       IsSquare
            Params:     void
            Access:     public
            Return:     bool
            Desc:       Method returning true if martrix has equal number of rows
                        and columns, else false

        4)  Name:       Resize
            Params:     
                    -   Name:   rows
                        Type:   [in]    int
                        Desc:   Number of rows in the matrix.
                    
                    -   Name:   cols
                        Type:   [in]    int
                        Desc:   Number of columns in the matrix.
            Access:     public
            Return:     void
            Desc:       Method resizing matrix

        5)  Name:       Transpose
            Params:     void
            Access:     public
            Return:     void
            Desc:       Method making rows be columns and columns be rows

        6)  Name:       SetItem
            Params:     
                    -   Name:   row
                        Type:   [in]    int
                        Desc:   Certain row in the matrix.
                    
                    -   Name:   col
                        Type:   [in]    int
                        Desc:   Certain column in the matrix.
                    
                    -   Name:   data
                        Type:   [in]    T
                        Desc:   Data to be set in the cell
            Access:     public
            Return:     void
            Desc:       Method setting data to certain cell
        
        7)  Name:       GetItem
            Params:     
                    -   Name:   row
                        Type:   [in]    int
                        Desc:   Certain row in the matrix.
                    
                    -   Name:   col
                        Type:   [in]    int
                        Desc:   Certain column in the matrix.
                    
            Access:     public
            Return:     
            Desc:       Method setting data to certain cell
        
        8)  Name:       operator=
            Params: -   Name:   other
                        Type:   [in]    TMatrix&
                        Desc:   The other one instance of TMatrix
            Access:     public
            Return:     TMatrix&
            Desc:       Copy assign
        
        9)  Name:       operator=
            Params: -   Name:   other
                        Type:   [in]    TMatrix&&
                        Desc:   The other one instance of TMatrix
            Access:     public
            Return:     TMatrix&
            Desc:       Move assign
        
       10)  Name:       operator+
            Params: -   Name:   other
                        Type:   [in]    TMatrix&&
                        Desc:   The other one instance of TMatrix
            Return:     TMatrix
            Access:     public
        
       11)  Name:       operator+
            Params: -   Name:   other
                        Type:   [in]    TMatrix&
                        Desc:   The other one instance of TMatrix
            Return:     TMatrix
            Access:     public
        
       12)  Name:       operator-
            Params: -   Name:   other
                        Type:   [in]    TMatrix&&
                        Desc:   The other one instance of TMatrix
            Return:     TMatrix
            Access:     public

       13)  Name:       operator-
            Params: -   Name:   other
                        Type:   [in]    TMatrix&
                        Desc:   The other one instance of TMatrix
            Return:     TMatrix
            Access:     public
    ================================================================================
    Class methods:
        1)  Name:       Add
            Params: -   Name:   m1
                        Type:   [in]    TMatrix&
                        Desc:   The other one instance of TMatrix

                    -   Name:   m2
                        Type:   [in]    TMatrix&
                        Desc:   The other one instance of TMatrix

                    -   Name:   m3
                        Type:   [out]   TMatrix&
                        Desc:   result matrix
            Return:     void
            Access:     private
            Desc:       Method for adding two matrixes

        2)  Name:       Sub
            Params: -   Name:   m1
                        Type:   [in]    TMatrix&
                        Desc:   The other one instance of TMatrix

                    -   Name:   m2
                        Type:   [in]    TMatrix&
                        Desc:   The other one instance of TMatrix

                    -   Name:   m3
                        Type:   [out]   TMatrix&
                        Desc:   result matrix
            Return:     void
            Access:     private
            Desc:       Method for subtracting two matrixes

        3)  Name:       Add
            Params: -   Name:   m1
                        Type:   [in]    TMatrix&
                        Desc:   The other one instance of TMatrix

                    -   Name:   m2
                        Type:   [in]    TMatrix&
                        Desc:   The other one instance of TMatrix

                    -   Name:   m3
                        Type:   [out]   TMatrix&
                        Desc:   result matrix
            Return:     void
            Access:     private
            Desc:       Method for multiplying two matrixes
    ================================================================================
    Friend functions
        1)  Name:       operator<<
            Params: -   Name:   m
                        Type:   [in]    TMatrix&
                        Desc:   this instance of TMatrix
    
                    -   Name:   out
                        Type:   [out]   std::ostream&
                        Desc:   output stream
            Access:     public
            Desc:       Method for outputting the instance of the matrix
        
        2)  Name:       operator<<
            Params: -   Name:   m
                        Type:   [in]    TMatrix&&
                        Desc:   this instance of TMatrix

                    -   Name:   out
                        Type:   [out]   std::ostream&
                        Desc:   output stream
            Access:     public
            Desc:       Method for outputting the instance of the matrix
 */
template<class T>
class TMatrix {
private:
    struct Cell {
        std::shared_mutex mtx;
        T data;
    };
    Cell**mat;
    std::shared_mutex mtx;
    int rows;
    int cols;
    ThreadPool* tp;
    static const int maxThsNum;
    static void Add(TMatrix& m1, TMatrix& m2, TMatrix& m3, const int row);
    static void Sub(TMatrix& m1, TMatrix& m2, TMatrix& m3, const int row);
    static void Mul(TMatrix& m1, TMatrix& m2, TMatrix& m3, const int row);
    void Delete();
    void Copy(TMatrix& other);
    void Move(TMatrix& other);
    bool IsIndexNegative(int row, int col);
    bool IsIndexOutBounds(int row, int col);
public:
    TMatrix(ThreadPool* tp);
    TMatrix(ThreadPool* tp, int rows, int cols);
    TMatrix(TMatrix& other);
    TMatrix(TMatrix&& other) noexcept;
    ~TMatrix();
    int GetRows();
    int GetCols();
    bool IsSquare();
    void Resize(int rows, int cols);
    void SetItem(int row, int col, T data);
    T* GetItem(int row, int col);
    void Transpose();
    TMatrix& operator =(TMatrix&& other) noexcept;
    TMatrix& operator =(TMatrix& other);
    TMatrix operator+(TMatrix& other);
    TMatrix operator+(TMatrix&& other);
    TMatrix operator-(TMatrix& other);
    TMatrix operator-(TMatrix&& other);
    TMatrix operator*(TMatrix& other);
    TMatrix operator*(TMatrix&& other);
    
    template <class T> friend std::ostream& operator <<(std::ostream& out, TMatrix<T>& m);
    template <class T> friend std::ostream& operator <<(std::ostream& out, TMatrix<T>&& m);
};
template <class T> int const TMatrix<T>::maxThsNum = std::thread::hardware_concurrency();
template <class T> void TMatrix<T>::Add(TMatrix& m1, TMatrix& m2, TMatrix& m3, const int row) {
    for (int j = 0; j < m1.cols; j++)
        m3.SetItem(row, j, std::move(* m1.GetItem(row, j) + *m2.GetItem(row, j)));
}
template <class T> void TMatrix<T>::Sub(TMatrix& m1, TMatrix& m2, TMatrix& m3, const int row) {
     for (int j = 0; j < m1.cols; j++)
        m3.SetItem(row, j, std::move(*m1.GetItem(row, j) - *m2.GetItem(row, j)));
}
template <class T> void TMatrix<T>::Mul(TMatrix& m1, TMatrix& m2, TMatrix& m3, const int row) {
        for (int j = 0; j < m2.cols; j++)
        {
            m3.SetItem(row, j, std::move(* m1.GetItem(row, 0) * *m2.GetItem(0, j)));
        }
        for (int i = 1; i < m2.rows; i++)
        {
            for (int j = 0; j < m2.cols; j++)
            {
                m3.SetItem(row, j, std::move(*m3.GetItem(row, j) + *m1.GetItem(row, i)* *m2.GetItem(i, j)));
            }
        }
}
template <class T> void TMatrix<T>::Delete() {
    std::vector<std::future<void>> rFutures;
    for (int i = 0; i < rows; i++) {
        rFutures.push_back(tp->Submit([i, this]() {
            delete[] this->mat[i];
        }));
    }
    for (auto& f : rFutures)
        f.get();
    delete[] this->mat;
    this->mat = nullptr;
    this->rows = 0;
    this->cols = 0;
}
template <class T> void TMatrix<T>::Copy(TMatrix& other) {
    this->Delete();
    this->rows = other.rows;
    this->cols = other.cols;
    this->mat = new Cell * [other.rows];
    this->tp = other.tp;
    std::vector<std::future<void>> rFutures;
    for (int i = 0; i < rows; i++) {
        rFutures.push_back(tp->Submit([i, this, &other]() {
            this->mat[i] = new Cell[this->cols];
            for (int j = 0; j < this->cols; j++)
            {
                this->mat[i][j].data = other.mat[i][j].data;
            }
        }));
    }
    for (auto& f : rFutures)
        f.get();
}
template <class T> void TMatrix<T>::Move(TMatrix& other) {
    this->Delete();
    this->rows = other.rows;
    this->cols = other.cols;
    this->mat = other.mat;
    other.mat = nullptr;
    other.rows = 0;
    other.cols = 0;
}
template <class T> bool TMatrix<T>::IsIndexNegative(int row, int col) {
    if (row<0||col<0)
        return true;
    return false;
}
template <class T> bool TMatrix<T>::IsIndexOutBounds(int row, int col) {
    if (row > this->rows || col > this->cols)
        return true;
    return false;
}
template <class T> TMatrix<T>::TMatrix(ThreadPool* tp) {
    this->rows = 0;
    this->cols = 0;
    this->mat = nullptr;
    this->tp = tp;
}
template <class T> TMatrix<T>::TMatrix(ThreadPool* tp, int rows, int cols) {
    if (this->IsIndexNegative(rows, cols))
        throw MatrixInvalidIndex("Negative rows or cols");
    this->rows = rows;
    this->cols = cols;
    this->mat = new Cell * [rows];
    this->tp = tp;
    std::vector<std::future<void>> rFutures;
    for (int i = 0; i < rows; i++) {
        rFutures.push_back(tp->Submit([i, cols, this]() {
            this->mat[i] = new Cell[cols];
        }));
    }
    for (auto& f : rFutures)
        f.get();
}
template <class T> TMatrix<T>::TMatrix(TMatrix<T>& other):TMatrix(other.tp) {
    this->mtx.lock();
    other.mtx.lock();
    this->Copy(other);
    other.mtx.unlock();
    this->mtx.unlock();
}
template <class T> TMatrix<T>::TMatrix(TMatrix<T>&& other) noexcept :TMatrix(other.tp) {
    this->mtx.lock();
    other.mtx.lock();
    this->Move(other);
    other.mtx.unlock();
    this->mtx.unlock();
}
template <class T> TMatrix<T>::~TMatrix() {
    this->Delete();
}
template <class T> int TMatrix<T>::GetRows(){
    this->mtx.lock_shared();
    int r = this->rows;
    this->mtx.unlock_shared();
    return r;
}
template <class T> int TMatrix<T>::GetCols(){
    this->mtx.lock_shared();
    int c = this->cols;
    this->mtx.unlock_shared();
    return c;
}
template <class T> bool TMatrix<T>::IsSquare(){
    this->mtx.lock_shared();
    bool res = this->cols == this->rows;
    this->mtx.unlock_shared();
    return res;
}
template <class T> void TMatrix<T>::Resize(int rows, int cols) {
    if (this->IsIndexNegative(rows, cols))
        throw MatrixInvalidIndex("Negative rows or cols");
    this->mtx.lock();
    Cell** mat = new Cell *[rows];
    std::vector<std::future<void>> rFutures;
    for (int i = 0; i < rows; i++) {
        rFutures.push_back(tp->Submit([i, cols, mat]() {
            mat[i] = new Cell[cols];
        }));
    }
    for (auto& f : rFutures)
        f.get();
    rFutures.clear();
    int minRows = (this->rows > rows) ? rows : this->rows;
    int minCols = (this->cols > cols) ? cols : this->cols;
    for (int i = 0; i < minRows; i++)
    {
        rFutures.push_back(tp->Submit([i, minCols, mat, this]() {
            for (int j = 0; j < minCols; j++)
            {
                mat[i][j].data = std::move(this->mat[i][j].data);
            }
        })); 
    }
    for (auto& f : rFutures)
        f.get();
    this->Delete();
    this->mat = mat;
    this->rows = rows;
    this->cols = cols;
    this->mtx.unlock();
}
template <class T> void TMatrix<T>::Transpose() {
    this->mtx.lock();
    Cell** mat = new Cell *[this->cols];
    std::vector<std::future<void>> rFutures;
    for (int i = 0; i < this->cols; i++)
    {
        rFutures.push_back(tp->Submit([i, mat, this]() {
            mat[i] = new Cell[this->rows];
        }));
    }
    for (auto& f : rFutures)
        f.get();
    rFutures.clear();
    for (int i = 0; i < this->rows; i++)
    {
        rFutures.push_back(tp->Submit([i, mat, this]() {
            for (int j = 0; j < this->cols; j++)
            {
                mat[j][i].data = std::move(this->mat[i][j].data);
            }
        }));
    }
    for (auto& f : rFutures)
        f.get();
    int rows = this->rows;
    int cols = this->cols;
    this->Delete();
    this->mat = mat;
    this->rows = cols;
    this->cols = rows;
    this->mtx.unlock();
}
template <class T> void TMatrix<T>::SetItem(int row, int col, T data) {
    if (this->IsIndexNegative(row, col))
        throw MatrixInvalidIndex("Index negative");
    if (this->IsIndexOutBounds(row, col))
        throw MatrixInvalidIndex("Index out of bounds");
    this->mtx.lock_shared();
    this->mat[row][col].mtx.lock();
    this->mat[row][col].data = std::move(data);
    this->mat[row][col].mtx.unlock();
    this->mtx.unlock_shared();
}
template <class T> T* TMatrix<T>::GetItem(int row, int col){
    if (this->IsIndexNegative(row, col))
        throw MatrixInvalidIndex("Index negative");
    if (this->IsIndexOutBounds(row, col))
        throw MatrixInvalidIndex("Index out of bounds");
    this->mtx.lock_shared();
    this->mat[row][col].mtx.lock_shared();
    T* data = &(this->mat[row][col].data);
    this->mat[row][col].mtx.unlock_shared();
    this->mtx.unlock_shared();
    return data;
}
template <class T> TMatrix<T>& TMatrix<T>::operator =(TMatrix<T>&& other) noexcept {
    other.mtx.lock();
    this->mtx.lock();
    if (this == &other) {
        this->mtx.unlock();
        other.mtx.unlock();
        return *this;
    }
    this->Move(other);
    this->mtx.unlock();
    other.mtx.unlock();
    return *this;
}
template <class T> TMatrix<T>& TMatrix<T>::operator =(TMatrix<T>& other) {
    other.mtx.lock();
    this->mtx.lock();
    if (this == &other) {
        this->mtx.unlock();
        other.mtx.unlock();
        return *this;
    }
    this->Copy(other);
    this->mtx.unlock();
    other.mtx.unlock();
    return *this;
}
template <class T> TMatrix<T> TMatrix<T>::operator+(TMatrix& other) {
    this->mtx.lock_shared();
    other.mtx.lock_shared();
    if (this->rows != other.rows || this->cols != other.cols)
        throw MatrixesIncopatible("Number of rows and cols does not match");
    TMatrix m(this->tp, this->rows, this->cols);
    std::vector<std::future<void>> rFutures;
    for (int i = 0; i < rows; i++) {
        rFutures.push_back(tp->Submit([i, this, &other, &m]() {
            TMatrix<T>::Add(std::ref(*this), std::ref(other), std::ref(m), i);
        }));
    }
    for (auto& f : rFutures)
        f.get();
    other.mtx.unlock_shared();
    this->mtx.unlock_shared();
    return m;
}
template <class T> TMatrix<T> TMatrix<T>::operator+(TMatrix&& other) {
    return this->operator+(other);
}
template <class T> TMatrix<T> TMatrix<T>::operator-(TMatrix& other) {
    this->mtx.lock_shared();
    other.mtx.lock_shared();
    if (this->rows != other.rows || this->cols != other.cols)
        throw MatrixesIncopatible("Number of rows and cols does not match");
    TMatrix m(this->tp, this->rows, this->cols);
    std::vector<std::future<void>> rFutures;
    for (int i = 0; i < rows; i++) {
        rFutures.push_back(tp->Submit([i, this, &other, &m]() {
            TMatrix<T>::Sub(std::ref(*this), std::ref(other), std::ref(m), i);
        }));
    }
    for (auto& f : rFutures)
        f.get();
    other.mtx.unlock_shared();
    this->mtx.unlock_shared();
    return m;
}
template <class T> TMatrix<T> TMatrix<T>::operator-(TMatrix&& other) {
    return this->operator-(other);
}
template <class T> TMatrix<T> TMatrix<T>::operator*(TMatrix& other) {
    this->mtx.lock_shared();
    other.mtx.lock_shared();
    if (this->rows != other.cols || this->cols != other.rows)
        throw MatrixesIncopatible("Number of rows and cols does not match");
    TMatrix m(this->tp, this->rows, other.cols);
    std::vector<std::future<void>> rFutures;
    for (int i = 0; i < rows; i++) {
        rFutures.push_back(tp->Submit([i, this, &other, &m]() {
            TMatrix<T>::Mul(std::ref(*this), std::ref(other), std::ref(m), i);
        }));
    }
    for (auto& f:rFutures)
        f.get();
    other.mtx.unlock_shared();
    this->mtx.unlock_shared();
    return m;
}
template <class T> TMatrix<T> TMatrix<T>::operator*(TMatrix&& other) {
    return this->operator*(other);
}
template <class T> std::ostream& operator <<(std::ostream& out, TMatrix<T>& m) {
    auto split = [](std::string s, std::string delimiter) {
        std::vector<std::string> words;
        int pos = 0;
        std::string token;
        while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            words.push_back(token);
            s.erase(0, pos + delimiter.length());
        }
        words.push_back(s);
        return words;
    };
    int maxWidth = 0;
    int maxHeight = 1;
    std::ostringstream oss;
    std::string s;
    m.mtx.lock_shared();
    for (int i = 0; i < m.rows; i++)
    {
        for (int j = 0; j < m.cols; j++)
        {
            
            oss << *m.GetItem(i, j);
            s = oss.str();
            std::vector<std::string> lines = split(s, "\n");
            for (std::string line : lines)
                maxWidth = std::max(maxWidth, (int)line.length());
            int endlCount = 0;
            for (int k = 0; (k = s.find("\n", k)) != std::string::npos; k++) {
                endlCount++;
            }
            maxHeight = std::max(maxHeight, endlCount);
            oss.str(std::string());
        }
    }
    auto drawLine = [&]() {
        for (int j = 0; j < m.cols; j++)
        {
            out << "+=";
            for (int k = 0; k < maxWidth; k++)
            {
                out << "=";
            }
        }
        out << "+" << std::endl;
    };
    for (int i = 0; i < m.rows; i++)
    {
        drawLine();
        std::vector<std::vector<std::string>> cells;
        for (int j = 0; j < m.cols; j++) {
            oss << *m.GetItem(i, j);
            s = oss.str();
            cells.push_back(split(s, "\n"));
            oss.str(std::string());
        }
        for (int j = 0; j < maxHeight; j++)
        {
            for (auto cell : cells) {
                out << "|";
                s = "";
                if (j < cell.size()) {
                    s = cell[j];
                }
                for (int k = s.length(); k <= maxWidth; k++)
                {
                    s += " ";
                }
                out << s;
            }
            out << "|" << std::endl;
        }
    }
    drawLine();
    m.mtx.unlock_shared();
    return out;
}
template <class T> std::ostream& operator <<(std::ostream& out, TMatrix<T>&& m) {
    out << m;
    return out;
}
