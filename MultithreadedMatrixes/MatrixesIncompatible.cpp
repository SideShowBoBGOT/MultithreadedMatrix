#include "MatrixesIncompatible.h"
MatrixesIncopatible::MatrixesIncopatible(std::string error) :m_error(error) {};
const char* MatrixesIncopatible::getError() { return m_error.c_str(); }
