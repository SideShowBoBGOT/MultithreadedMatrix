#pragma once
#include<xstring>
class MatrixInvalidIndex {
private:
    std::string m_error;
public:
    MatrixInvalidIndex(std::string error);
    const char* getError();
};

