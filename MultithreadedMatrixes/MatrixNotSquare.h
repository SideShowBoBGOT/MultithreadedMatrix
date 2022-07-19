#pragma once
#include<xstring>
class MatrixNotSquare {
private:
    std::string m_error;
public:
    MatrixNotSquare(std::string error);
    const char* getError();
};


