// header.h : include file for standard system include files,
// or project specific include files
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <commdlg.h> 
#include <fstream> 
#include <vector> 
#include <string> 
#include <Shlwapi.h>
#include <intrin.h>

#pragma comment(lib, "Shlwapi.lib")

int size(wchar_t* str) {
    int size = 0;
    while (str[size]) {
        size++;
    }
    return size;
}
