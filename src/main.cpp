//#include "nesCPU.h"
#include <thread>
#include <wx/wx.h>
#include <wx/string.h>


__asm__(".symver realpath,realpath@GLIBC_2.2.5");

int main(int argc, char **argv)
{
  wxPuts(wxT("A wxWidgets console application"));
}
