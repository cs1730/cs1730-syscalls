
#include <iostream>
#include <climits>
#include <cstdlib>

using std::cout;
using std::endl;

int main() {
  cout.setf(std::ios_base::unitbuf);
  cout << "See http://en.cppreference.com/w/cpp/header/climits for descriptions..." << endl;
  cout << "  CHAR_BIT = " <<   CHAR_BIT << endl;
  cout << " SCHAR_MIN = " <<  SCHAR_MIN << endl;
  cout << " SCHAR_MAX = " <<  SCHAR_MAX << endl;
  cout << " UCHAR_MAX = " <<  UCHAR_MAX << endl;
  cout << "  CHAR_MIN = " <<   CHAR_MIN << endl;
  cout << "  CHAR_MAX = " <<   CHAR_MAX << endl;
  cout << "MB_LEN_MAX = " << MB_LEN_MAX << endl;
  cout << "  SHRT_MIN = " <<   SHRT_MIN << endl;
  cout << "  SHRT_MAX = " <<   SHRT_MAX << endl;
  cout << " USHRT_MAX = " <<  USHRT_MAX << endl;
  cout << "   INT_MIN = " <<    INT_MIN << endl;
  cout << "   INT_MAX = " <<    INT_MAX << endl;
  cout << "  UINT_MAX = " <<   UINT_MAX << endl;
  cout << "  LONG_MIN = " <<   LONG_MIN << endl;
  cout << "  LONG_MAX = " <<   LONG_MAX << endl;
  cout << " ULONG_MAX = " <<  ULONG_MAX << endl;
  cout << " LLONG_MIN = " <<  LLONG_MIN << endl;
  cout << " LLONG_MAX = " <<  LLONG_MAX << endl;
  cout << "ULLONG_MAX = " << ULLONG_MAX << endl;
  return EXIT_SUCCESS;
} // main

