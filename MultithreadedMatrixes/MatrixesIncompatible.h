#pragma once
#include<xstring>
class MatrixesIncopatible {
private:
    std::string m_error;
public:
    MatrixesIncopatible(std::string error);
    const char* getError();
};


