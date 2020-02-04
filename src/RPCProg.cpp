#include "RPCProg.h"
#include <stdarg.h>
#include <stdio.h>
#include <share.h>

CRPCProg::CRPCProg()
{
    m_bLogOn = true;
}

CRPCProg::~CRPCProg()
{
    if (m_pFile != NULL) {
        fclose(m_pFile);
    }
}

void CRPCProg::SetLogOn(bool bLogOn)
{
    m_bLogOn = bLogOn;
}

void CRPCProg::WriteToFile(const char* pFileName)
{
    m_pFile = _fsopen(pFileName, "a", _SH_DENYNO);
    if (m_pFile == NULL) {
        PrintLog("Could not open the file %s\nError: %i\n", pFileName);
    }
}

int CRPCProg::PrintLog(const char *format, ...)
{
    va_list vargs;
    int nResult;

    nResult = 0;

    if (m_bLogOn) {
        va_start(vargs, format);
        if (m_pFile != NULL) {
            nResult = vfprintf(m_pFile, format, vargs);
        } else {
            nResult = vprintf(format, vargs);
        }
        va_end(vargs);
    }

    return nResult;
}
