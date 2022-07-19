#include "MatrixInvalidIndex.h"
#include "MatrixNotSquare.h"
MatrixInvalidIndex::MatrixInvalidIndex(std::string error) :m_error(error) {};
const char* MatrixInvalidIndex::getError() { return m_error.c_str(); }