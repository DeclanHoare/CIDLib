//
// FILE NAME: CIDKernel_SystemInfo_Linux.Cpp
//
// AUTHOR: Will Mason
//
// CREATED: 12/21/1998
//
// COPYRIGHT: Charmed Quark Systems, Ltd - 2019
//
//  This software is copyrighted by 'Charmed Quark Systems, Ltd' and 
//  the author (Dean Roddey.) It is licensed under the MIT Open Source 
//  license:
//
//  https://opensource.org/licenses/MIT
//
// DESCRIPTION:
//
//  This file implements the TKrnlSysInfo class for the Win32 platform. This
//  is a simple namespace that encapsulates the retrieval of general system
//  information.  It will precache info that cannot change for the run of
//  the host process, for faster return. Otherwise, it just gets when asked.
//
// CAVEATS/GOTCHAS:
//
// LOG:
//
//  $_CIDLib_Log_$
//


// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include    "CIDKernel_.hpp"

// ---------------------------------------------------------------------------
//  Global variables
// ---------------------------------------------------------------------------

namespace CIDKernel_SystemInfo_Linux
{
    //
    // These are used to pick off argc and argv as they go by. That way I don't have
    // to try to reproduce the array provided by the startup code. The proc file
    // system only provides the full command line, and using these global variables
    // saves me a lot of possible errors involving parsing inconsistencies between
    // me and Linux.
    //
    int argc = -1;
    char** argv = 0;


    // ---------------------------------------------------------------------------
    //  Local types
    //
    //  This structure is used to hold the system info data that we cache during
    //  init and keep around.
    //
    //  apszArgList
    //      This is storage for the command line parameters.
    //
    //  c4ArgCnt
    //      This is the number of command line arguments that show to to the
    //      outside world (we strip out the standard ones.)
    //
    //  c4CPUCount
    //      The number of CPUs in the system, from the OS's perspective. If the
    //      hardware allows some to be taken off line, then I would assume you
    //      would only see the active ones here.
    //
    //  c4OSBuildNum
    //  c4OSMajVersion
    //  c4OSMinVersion
    //      These are all about the version of the OS that we find ourselves
    //      running on.
    //
    //  c8TotalPhysicalMem
    //      The amount of memory installed in the machine.
    //
    //  szNodeName
    //      The name assigned to this machine in the system setup. This size
    //      should be grotesquely overkill for any node name.
    //
    //  szProcessName
    //      The name of the process that this DLL is running in the context of.
    // ---------------------------------------------------------------------------
    struct TCachedInfo
    {
        tCIDLib::TCh*           apszArgList[kCIDLib::c4MaxCmdLineParms];
        tCIDLib::TCard4         c4ArgCnt;
        tCIDLib::TCard4         c4CPUCount;
        tCIDLib::TCard4         c4OSBuildNum;
        tCIDLib::TCard4         c4OSMajVersion;
        tCIDLib::TCard4         c4OSMinVersion;
        tCIDLib::TCard4         c4OSRev;
        tCIDLib::TCard8         c8TotalPhysicalMem;
        tCIDLib::TZStr64        szNodeName;
        tCIDLib::TZStr128       szProcessName;
    };


    // ---------------------------------------------------------------------------
    //  Local data
    //
    //  CIDKernel_SystemInfo_Linux::CachedInfo
    //      The cached system info that we cache up init and hang onto.
    // ---------------------------------------------------------------------------
    TCachedInfo      CachedInfo;


    // ---------------------------------------------------------------------------
    //  Intra-facility methods
    // ---------------------------------------------------------------------------
    tCIDLib::TBoolean bQueryVersionInfo(const struct utsname& UtsName)
    {
        tCIDLib::TSCh* pszBegin = const_cast<tCIDLib::TSCh*>(UtsName.release);
        tCIDLib::TSCh* pszEnd;
        tCIDLib::TCard4 c4Tmp = ::strtoul(pszBegin, &pszEnd, 10);
        if (pszEnd == pszBegin || *pszEnd == '\000')
        {
            TKrnlError::SetLastKrnlError(kKrnlErrs::errcData_InvalidFormat);
            return kCIDLib::False;
        }
        CachedInfo.c4OSMajVersion = c4Tmp;

        pszBegin = ++pszEnd;
        c4Tmp = ::strtoul(pszBegin, &pszEnd, 10);
        if (pszEnd == pszBegin || *pszEnd == '\000')
        {
            TKrnlError::SetLastKrnlError(kKrnlErrs::errcData_InvalidFormat);
            return kCIDLib::False;
        }
        CachedInfo.c4OSMinVersion = c4Tmp;

        pszBegin = ++pszEnd;
        c4Tmp = ::strtoul(pszBegin, &pszEnd, 10);
        if (pszEnd == pszBegin)
        {
            TKrnlError::SetLastKrnlError(kKrnlErrs::errcData_InvalidFormat);
            return kCIDLib::False;
        }
        CachedInfo.c4OSRev = c4Tmp;

        tCIDLib::TSCh szVerCopy[SYS_NMLN];
        ::strcpy(szVerCopy, &UtsName.version[1]);

        c4Tmp = ::strtoul(szVerCopy, &pszEnd, 10);
        if (pszEnd == szVerCopy)
        {
            TKrnlError::SetLastKrnlError(kKrnlErrs::errcData_InvalidFormat);
            return kCIDLib::False;
        }
        CachedInfo.c4OSBuildNum = c4Tmp;

        return kCIDLib::True;
    }

    tCIDLib::TBoolean bQueryCPUInfo(const struct utsname& UtsName)
    {
        FILE* CPUFile = ::fopen("/proc/cpuinfo", "r");
        if (!CPUFile)
        {
            TKrnlError::SetLastHostError(errno);
            return kCIDLib::False;
        }

        tCIDLib::TCard4 c4ProcessorCount = 0;
        tCIDLib::TSCh szLine[128];

        const tCIDLib::TSCh szProcLine[] = "processor";
        const tCIDLib::TCard4 c4ProcLineLen = sizeof(szProcLine) - 1;

        while (::fgets(szLine, sizeof(szLine), CPUFile))
        {
            if (!::strncmp(szLine, szProcLine, c4ProcLineLen))
                c4ProcessorCount++;
        }

        ::fclose(CPUFile);

        CachedInfo.c4CPUCount = c4ProcessorCount;

        return kCIDLib::True;
    }

    tCIDLib::TBoolean bQueryProcMemInfo()
    {
        FILE* MemFile = ::fopen("/proc/meminfo", "r");
        if (!MemFile)
        {
            TKrnlError::SetLastHostError(errno);
            return kCIDLib::False;
        }

        tCIDLib::TSCh szLine[128];
        if (!::fgets(szLine, sizeof(szLine), MemFile))
        {
            ::fclose(MemFile);
            TKrnlError::SetLastKrnlError(kKrnlErrs::errcData_InvalidFormat);
            return kCIDLib::False;
        }

        tCIDLib::TCard4 c4Tmp;
        tCIDLib::TSInt iRc = ::fscanf(MemFile, "%*s %lu", &c4Tmp);

        ::fclose(MemFile);

        if (iRc != 1)
        {
            TKrnlError::SetLastKrnlError(kKrnlErrs::errcData_InvalidFormat);
            return kCIDLib::False;
        }

        CachedInfo.c8TotalPhysicalMem = c4Tmp;
        CachedInfo.c8TotalPhysicalMem *= 1024;

        return kCIDLib::True;
    }

    tCIDLib::TBoolean bQueryNameFromPID(pid_t pid)
    {
        tCIDLib::TSCh szProcPid[128];
        ::sprintf(szProcPid, "/proc/%i/stat", pid);

        FILE* StatFile = ::fopen(szProcPid, "r");
        if (!StatFile)
        {
            TKrnlError::SetLastHostError(errno);
            return kCIDLib::False;
        }

        tCIDLib::TSCh szParenName[512];
        tCIDLib::TSInt iRc = ::fscanf(StatFile, "%*d %512s", szParenName);

        ::fclose(StatFile);

        if (iRc != 1)
        {
            TKrnlError::SetLastKrnlError(kKrnlErrs::errcData_InvalidFormat);
            return kCIDLib::False;
        }

        tCIDLib::TCard4 c4Len = ::strlen(szParenName);
        if (c4Len < 2)
        {
            TKrnlError::SetLastKrnlError(kKrnlErrs::errcData_InvalidFormat);
            return kCIDLib::False;
        }

        szParenName[c4Len - 1] = '\000';

        TRawStr::pszConvert(&szParenName[1]
                            , CachedInfo.szProcessName
                            , c4MaxBufChars(CachedInfo.szProcessName));

        return kCIDLib::True;
    }

    tCIDLib::TVoid InitArgArray()
    {
        CachedInfo.c4ArgCnt = CIDKernel_SystemInfo_Linux::argc;
        for (tCIDLib::TCard4 c4Idx = 0; c4Idx < CachedInfo.c4ArgCnt; c4Idx++)
        {
            CachedInfo.apszArgList[c4Idx] =
                TRawStr::pszConvert(CIDKernel_SystemInfo_Linux::argv[c4Idx]);
        }
        CIDKernel_SystemInfo_Linux::argc = -1;
    }
}


tCIDLib::TBoolean
TCIDKrnlModule::bInitTermSysInfo(const tCIDLib::EInitTerm eInitTerm)
{
    // We only have pre-constructor init
    if (eInitTerm == tCIDLib::EInitTerm::Initialize)
    {
        if (!CIDKernel_SystemInfo_Linux::bQueryProcMemInfo())
            return kCIDLib::False;

        tCIDLib::TProcessId pidThis = ::getpid();
        if (!CIDKernel_SystemInfo_Linux::bQueryNameFromPID(pidThis))
            return kCIDLib::False;

        if (::getpagesize() != kCIDLib::c4MemPageSize)
        {
            TKrnlError::SetLastKrnlError(kKrnlErrs::errcMem_HostPageSize);
            return kCIDLib::False;
        }

        // Find the name of the workstation that we are running in.
        struct utsname UtsName;
        if (::uname(&UtsName))
        {
            TKrnlError::SetLastHostError(errno);
            return kCIDLib::False;
        }
        TRawStr::pszConvert(UtsName.nodename
                            , CIDKernel_SystemInfo_Linux::CachedInfo.szNodeName
                            , c4MaxBufChars(CIDKernel_SystemInfo_Linux::CachedInfo.szNodeName));

        if (!CIDKernel_SystemInfo_Linux::bQueryVersionInfo(UtsName))
            return kCIDLib::False;

        if (!CIDKernel_SystemInfo_Linux::bQueryCPUInfo(UtsName))
            return kCIDLib::False;
    }

    return kCIDLib::True;
}



// ---------------------------------------------------------------------------
//  TKrnlSysInfo functions
// ---------------------------------------------------------------------------
tCIDLib::TBoolean
TKrnlSysInfo::bCmdLineArg(  const   tCIDLib::TCard4 c4Index
                            , const tCIDLib::TCh*&  pszToFill)
{
    if (CIDKernel_SystemInfo_Linux::argc != -1)
        CIDKernel_SystemInfo_Linux::InitArgArray();

    if (c4Index >= CIDKernel_SystemInfo_Linux::CachedInfo.c4ArgCnt)
    {
        TKrnlError::SetLastKrnlError(kKrnlErrs::errcGen_IndexError);
        return kCIDLib::False;
    }
    pszToFill = CIDKernel_SystemInfo_Linux::CachedInfo.apszArgList[c4Index];
    return kCIDLib::True;
}



tCIDLib::TBoolean
TKrnlSysInfo::bQueryUserName(       tCIDLib::TCh* const pszBuffer
                            , const tCIDLib::TCard4     c4MaxChars)
{
    struct passwd* pwd = ::getpwuid(::getuid());

    if (!pwd)
    {
        TKrnlError::SetLastHostError(errno);
        return kCIDLib::False;
    }

    if (c4MaxChars < ::strlen(pwd->pw_name))
    {
        TKrnlError::SetLastKrnlError(kKrnlErrs::errcData_InsufficientBuffer);
        return kCIDLib::False;
    }

    TRawStr::pszConvert(pwd->pw_name, pszBuffer, c4MaxChars);

    return kCIDLib::True;
}


tCIDLib::TBoolean
TKrnlSysInfo::bRemoveCmdLineArg(const tCIDLib::TCard4 c4Index)
{
    if (CIDKernel_SystemInfo_Linux::argc != -1)
        CIDKernel_SystemInfo_Linux::InitArgArray();

    if (!c4Index || (c4Index >= CIDKernel_SystemInfo_Linux::CachedInfo.c4ArgCnt))
    {
        TKrnlError::SetLastKrnlError(kKrnlErrs::errcGen_IndexError);
        return kCIDLib::False;
    }

    // Delete the string in this element
    delete [] CIDKernel_SystemInfo_Linux::CachedInfo.apszArgList[c4Index];

    // If this is the only element, then we are done
    if (CIDKernel_SystemInfo_Linux::CachedInfo.c4ArgCnt == 1)
    {
        CIDKernel_SystemInfo_Linux::CachedInfo.c4ArgCnt = 0;
        return kCIDLib::True;
    }

    // If this is the last element, we are done
    if (c4Index == CIDKernel_SystemInfo_Linux::CachedInfo.c4ArgCnt-1)
    {
        CIDKernel_SystemInfo_Linux::CachedInfo.c4ArgCnt--;
        return kCIDLib::True;
    }

    // Move the elements down
    for (tCIDLib::TCard4 c4MoveIndex = c4Index; c4MoveIndex < CIDKernel_SystemInfo_Linux::CachedInfo.c4ArgCnt-1; c4MoveIndex++)
        CIDKernel_SystemInfo_Linux::CachedInfo.apszArgList[c4MoveIndex] = CIDKernel_SystemInfo_Linux::CachedInfo.apszArgList[c4MoveIndex+1];

    CIDKernel_SystemInfo_Linux::CachedInfo.c4ArgCnt--;
    return kCIDLib::True;
}


tCIDLib::TCard4 TKrnlSysInfo::c4CPUCount()
{
    return CIDKernel_SystemInfo_Linux::CachedInfo.c4CPUCount;
}


tCIDLib::TCard4 TKrnlSysInfo::c4CmdLineArgCount()
{
    if (CIDKernel_SystemInfo_Linux::argc != -1)
        CIDKernel_SystemInfo_Linux::InitArgArray();

    return CIDKernel_SystemInfo_Linux::CachedInfo.c4ArgCnt;
}


tCIDLib::TCard8 TKrnlSysInfo::c8TotalPhysicalMem()
{
    return CIDKernel_SystemInfo_Linux::CachedInfo.c8TotalPhysicalMem;
}


const tCIDLib::TCh* TKrnlSysInfo::pszNodeName()
{
    return CIDKernel_SystemInfo_Linux::CachedInfo.szNodeName;
}


const tCIDLib::TCh* TKrnlSysInfo::pszProcessName()
{
    return CIDKernel_SystemInfo_Linux::CachedInfo.szProcessName;
}


tCIDLib::TVoid
TKrnlSysInfo::QueryOSInfo(  tCIDLib::TCard4&    c4OSMajVersion
                            , tCIDLib::TCard4&  c4OSMinVersion
                            , tCIDLib::TCard4&  c4OSRev
                            , tCIDLib::TCard4&  c4OSBuildNum)
{
    c4OSBuildNum    = CIDKernel_SystemInfo_Linux::CachedInfo.c4OSBuildNum;
    c4OSMajVersion  = CIDKernel_SystemInfo_Linux::CachedInfo.c4OSMajVersion;
    c4OSMinVersion  = CIDKernel_SystemInfo_Linux::CachedInfo.c4OSMinVersion;
    c4OSRev         = CIDKernel_SystemInfo_Linux::CachedInfo.c4OSRev;
}
