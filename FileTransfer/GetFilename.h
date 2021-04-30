#ifndef _GETFILENAME_H_
#define _GETFILENAME_H_

#ifndef _INC_STRING
#include <string.h>
#endif
#ifndef _INC_STDLIB 
#include <stdlib.h>
#endif

char* GetFilename(const char* path) {
	char* filename;
	int length = 0;
    for (int i = strlen(path) - 1; i >= 0; --i) {
        if (path[i] == '/' || path[i] == '\\') {
			if ((filename = (char*)malloc(length + 1)) == NULL) {
				return 0;
			}
			memset(filename, 0, length);
			strncpy_s(filename, length + 1, path + i + 1, length);
			return filename;
        }
		++length;
    }
	if ((filename = (char*)malloc(length + 1)) == NULL) {
		return 0;
	}
	memcpy(filename, path, length + 1);
	return filename;
}

#endif