#include "MatrixNotSquare.h"
MatrixNotSquare::MatrixNotSquare(std::string error) :m_error(error) {};
const char* MatrixNotSquare::getError() { return m_error.c_str(); }