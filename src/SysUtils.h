/***************************************
SysUtils.h

System utilities

Written by:
Lage Ragnarsson
***************************************/
#ifndef _SYS_UTILS_
#define _SYS_UTILS_

#include <dirent.h>
#include <string>
#include <vector>

std::vector<std::string> listDir(std::string path = ".") {
    DIR*    dir;
    dirent* pdir;
    std::vector<std::string> files;

    dir = opendir(path.c_str());

    while (pdir = readdir(dir)) {
        files.push_back(pdir->d_name);
    }

    return files;
}

#endif // _SYS_UTILS_
