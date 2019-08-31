//
// FILE NAME: CIDBuild_KCCDriver.Cpp
//
// AUTHOR: Will Mason
//
// CREATED: 02/24/99
//
// COPYRIGHT: Charmed Quark Systems, Ltd @ 2019
//
//  This software is copyrighted by 'Charmed Quark Systems, Ltd' and
//  the author (Dean Roddey.) It is licensed under the MIT Open Source
//  license:
//
//  https://opensource.org/licenses/MIT
//
// DESCRIPTION:
//
//  This file implements the TGCCDriver class.
//
// CAVEATS/GOTCHAS:
//
//  1)  Each driver includes its own header directly, so that it does not
//      show up to other code. Only the TToolsDriver.Cpp file includes all
//      of the concrete driver instantiation headers, and uses conditional
//      compilation to include only the one that is required.
//
// LOG:
//
//  $_CIDLib_Log_$
//



// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include    "CIDBuild.hpp"
#include    "CIDBuild_GCCDriver.hpp"
#include    <stdio.h>
#include    <unistd.h>



// ---------------------------------------------------------------------------
//   CLASS: TGCCDriver
//  PREFIX: tdrv
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
//  TGCCDriver: Constructors and Destructor
// ---------------------------------------------------------------------------
TGCCDriver::TGCCDriver() :

    m_bDebug(false)
{
    //
    //  Get a short cut indicator for whether we are doing a debug or prod
    //  build, since we use it a lot below.
    //
    m_bDebug = (facCIDBuild.eBldMode() == tCIDBuild::EBldModes::Develop);
}

TGCCDriver::~TGCCDriver()
{
}


// ---------------------------------------------------------------------------
//  TGCCDriver: Protected, inherited methods
// ---------------------------------------------------------------------------
tCIDLib::TBoolean TGCCDriver::bBuild(const TProjectInfo& projiTarget)
{
    // Store away the target project for internal use while we are here
    m_pprojiTarget = &projiTarget;

    //
    // Build up the target file name. We take the already computed one
    // (minus the path) to avoid duplicating the procedure.
    //
    tCIDLib::TCard4 c4Name;
    tCIDLib::TCard4 c4Ext;
    TUtils::FindPathParts(m_pprojiTarget->strOutBin(), c4Name, c4Ext);
    m_strTargetFile.CopyAt(m_pprojiTarget->strOutBin(), c4Name);

    //
    //  Lets do our Cpp compilations. We just run through each of the Cpp
    //  files, which our parent class has has already set up, and ask if
    //  each one needs to be compiled. If so, we build it.
    //
    bool bObjBuilt = bCompileCpps();

    //
    //  NOTE: We change to the main output directory before we link, so all
    //  of the file names are relative to that. This makes the link line
    //  a LOT smaller.
    //
    if (!TUtils::bChangeDir(facCIDBuild.strOutDir()))
    {
        stdOut << L"Could not change to output directory for link step" << kCIDBuild::EndLn;
        throw tCIDBuild::EErrors::Internal;
    }

    if (bObjBuilt && facCIDBuild.bVerbose())
        stdOut << L"    Linking because an Obj was rebuilt" << kCIDBuild::EndLn;

    //
    //  Now lets see if the target file is out of date with any of its Obj,
    //  Lib, Res, etc... files. If so, then we have to build it. If any
    //  Obj files were built, then don't bother checking since we know that
    //  we have to link.
    //
    //  If the Force option is on, then of course we have to rebuild and
    //  there is no reason to check anything.
    //
    bool bUpdate = (bObjBuilt || facCIDBuild.bForce());
    if (!bUpdate)
    {
        // See if the target exists, if not obviously we have to build
        TFindInfo fndiTarget;
        if (!TFindInfo::bFindAFile(m_strTargetFile, fndiTarget))
        {
            bUpdate = true;

            if (facCIDBuild.bVerbose())
                stdOut << L"    Target file not present: " << m_strTargetFile << kCIDBuild::EndLn;
        }

        //
        //  If nothing to do yet, then see if any of the Lib or Obj files
        //  are newer than the target.
        //
        if (!bUpdate)
        {
            if (bObjsNewer(fndiTarget) || bLibsNewer(fndiTarget))
                bUpdate = true;
        }
    }

    if (bUpdate)
        Link();

    // It went ok, so return success
    return true;
}


//
//  A convenience to invoke the debugger
//
tCIDLib::TBoolean TGCCDriver::bInvokeDebugger(const TProjectInfo& projiTarget)
{

    return kCIDLib::False;
}


tCIDLib::TVoid TGCCDriver::ResetDebugInfo(const TProjectInfo& projiToReset)
{
}


// ---------------------------------------------------------------------------
//  TGCCDriver: Private, non-virtual methods
// ---------------------------------------------------------------------------
tCIDLib::TBoolean TGCCDriver::bCompileCpps()
{
    //
    //  First we want to build up the list of command line parameters that
    //  will be used to compile a Cpp file. For our Visual C++ compiler, the
    //  order of stuff is not important, so we can just build up the stuff
    //  that will stay the same.
    //
    const tCIDBuild::TCh* apszArgs[128];
    tCIDLib::TCard4 c4CurArg = 0;
    apszArgs[c4CurArg++] = L"g++";
    apszArgs[c4CurArg++] = L"-c";

    //
    //  Set up our CIDLib platform define that gets passed to all code
    //  to drive conditional compilation.
    //
    TBldStr strPlatform(L"-D");
    strPlatform.Append(kCIDBuild::pszPlatformDir);
    apszArgs[c4CurArg++] = strPlatform.pszBuffer();


    // Set the flags for the project type
    if (m_pprojiTarget->eType() == tCIDBuild::EProjTypes::SharedLib)
        apszArgs[c4CurArg++] = L"-fPIC";

    //
    //  Set up our standard include directories, for public and private
    //  includes and their respective per-platform subdirectories
    //
    TBldStr strInclude(L"-I");
    strInclude.Append(facCIDBuild.strIncludeDir());
    apszArgs[c4CurArg++] = strInclude.pszBuffer();

    TBldStr strPPInclude(L"-I");
    strPPInclude.Append(facCIDBuild.strPPIncludeDir());
    apszArgs[c4CurArg++] = strPPInclude.pszBuffer();

    TBldStr strPrivInclude(L"-I");
    strPrivInclude.Append(facCIDBuild.strPrivIncludeDir());
    apszArgs[c4CurArg++] = strPrivInclude.pszBuffer();

    TBldStr strPPPrivInclude(L"-I");
    strPPPrivInclude.Append(facCIDBuild.strPPPrivIncludeDir());
    apszArgs[c4CurArg++] = strPPPrivInclude.pszBuffer();

    //
    //  If there are any per-project includes, then add them in as well.
    //
    //  NOTE:
    //  In order to avoid a lot of crap, we just allow these to leak. This
    //  is ok since this program is always just a one shot anyway and this
    //  is not a repetitious operation.
    //
    if (!m_pprojiTarget->listIncludePaths().bEmpty())
    {
        TBldStr strTmp;

        TList<TBldStr>::TCursor cursIncludes(&m_pprojiTarget->listIncludePaths());
        cursIncludes.bResetIter();
        do
        {
            strTmp = L"-I";
            strTmp.Append(cursIncludes.tCurElement());
            apszArgs[c4CurArg++] = strTmp.pszOrphanBuffer();
        }   while (cursIncludes.bNext());
    }

    //
    //  Set up the flags for the runtime library mode.
    apszArgs[c4CurArg++] = L"-D_REENTRANT";

    //
    //  Set up the stuff driven by the 'PUREANSI' setting. This is temporary
    //  until all platform specific stuff is split into per-platform dirs
    //
    if (m_pprojiTarget->bPureCpp())
        apszArgs[c4CurArg++] = L"-ansi";

    //
    //  Every project has a define which is in the form PROJ_XXX, where XXX
    //  is the name of the project uppercased.
    //
    TBldStr strProjDef(L"-DPROJ_");
    strProjDef.Append(m_pprojiTarget->strProjectName());
    strProjDef.UpperCase();
    apszArgs[c4CurArg++] = strProjDef.pszBuffer();

    //
    //  Remember the index at which the file independent parameters stopped
    //  so that we can just add onto the list what we need below.
    //
    const tCIDLib::TCard4 c4FirstPerFileArg = c4CurArg;

    //
    //  And now check each Cpp file and see if we have to build it. If so,
    //  the do it. Keep track of whether we build anything and return that
    //  status.
    //
    TList<TDepInfo>::TCursor cursCpps(&listCpps());
    if (!cursCpps.bResetIter())
        return false;

    tCIDLib::TBoolean bBuiltSomething = false;
    do
    {
        // Get a ref to the current element
        const TDepInfo& depiCur = cursCpps.tCurElement();

        // If this guy does not need to be compiled, check the next one
        if (!bMustCompile(*m_pprojiTarget, depiCur))
            continue;

        // Keep up with the per-file args we add
        tCIDLib::TCard4 c4ExtraArgs = c4FirstPerFileArg;

        // Setup output
        apszArgs[c4ExtraArgs++] = L"-o";
        TBldStr strJustName(depiCur.strObjFileName());
        tCIDLib::TCard4 c4Name, c4Extension;
        TUtils::FindPathParts(strJustName, c4Name, c4Extension);
        strJustName.Cut(c4Name);
        TBldStr strOutput(m_pprojiTarget->strOutDir(), strJustName);
        apszArgs[c4ExtraArgs++] = strOutput.pszBuffer();

        // Add the current file as the source file
        apszArgs[c4ExtraArgs++] = depiCur.strFileName().pszBuffer();

        if (facCIDBuild.bVerbose())
        {
            for (tCIDLib::TUInt uiInd = 0; uiInd < c4ExtraArgs; uiInd++)
                stdOut << apszArgs[uiInd] << L" ";
            stdOut << kCIDBuild::EndLn;
        }

        // Ok, lets do the compilation
        tCIDLib::TCard4 c4ExecFlags = kCIDBuild::c4ExecFlag_None;
        if (facCIDBuild.bLowPrio())
            c4ExecFlags |= kCIDBuild::c4ExecFlag_LowPrio;
        tCIDLib::TCard4 c4Result;

        /*
        if (!TUtils::bExec(apszArgs, c4ExtraArgs, c4Result, c4ExecFlags))
        {
            stdOut << L"Could not execute the compiler" << kCIDBuild::EndLn;
            throw tCIDBuild::EErrors::BuildError;
        }

        if (c4Result)
        {
            stdOut  << L"Failed compilation of file: "
                    << depiCur.strFileName() << L". Error Code: "
                    << c4Result << kCIDBuild::EndLn;
            throw tCIDBuild::EErrors::BuildError;
        }

        */

        // Make sure we have a line after the output if in verbose mode
        if (facCIDBuild.bVerbose())
            stdOut << kCIDBuild::EndLn;

        // Indicate that we built at least one Obj file
        bBuiltSomething = true;
    }   while (cursCpps.bNext());

    return bBuiltSomething;
}


tCIDLib::TBoolean TGCCDriver::bLibsNewer(const TFindInfo& fndiTarget) const
{
    // Get a cursor for the libs list
    TList<TFindInfo>::TCursor cursLibs(&listLibs());

    // If no libs listed, then couldn't be newer
    if (!cursLibs.bResetIter())
        return false;

    do
    {
        //
        //  See if this Lib file is newer than the target. If so, then
        //  return true, since we only have to find one to know that we
        //  have to relink.
        //
        if (cursLibs.tCurElement() > fndiTarget)
        {
            if (facCIDBuild.bVerbose())
            {
                stdOut  << L"    Dependent library is newer: "
                        << cursLibs.tCurElement().strFileName() << kCIDBuild::EndLn;
            }
            return true;
        }

    }   while (cursLibs.bNext());
    return false;
}


tCIDLib::TBoolean TGCCDriver::bMakeRes()
{
    return true;
}


tCIDLib::TBoolean TGCCDriver::bObjsNewer(const TFindInfo& fndiTarget) const
{
    // Get a cursor for the Cpp list
    TList<TDepInfo>::TCursor cursCpps(&listCpps());

    // If no obect files listed, then couldn't be newer
    if (!cursCpps.bResetIter())
        return false;

    TFindInfo fndiTmp;
    do
    {
        // Get a ref to the current element
        const TDepInfo& depiCur = cursCpps.tCurElement();

        // Try to find the current obj
        if (!TFindInfo::bFindAFile(depiCur.strObjFileName(), fndiTmp))
        {
            stdOut  << L"Could not find object file: "
                    << depiCur.strObjFileName() << kCIDBuild::EndLn;
            throw tCIDBuild::EErrors::NotFound;
        }

        //
        //  See if the Obj file is newer than the target. If so, then
        //  return true, since we only have to find one to know that we
        //  have to relink.
        //
        if (fndiTmp > fndiTarget)
        {
            if (facCIDBuild.bVerbose())
            {
                stdOut  << L"    Object file is newer: "
                        << depiCur.strObjFileName() << kCIDBuild::EndLn;
            }
            return true;
        }
    }   while (cursCpps.bNext());
    return false;
}


tCIDLib::TVoid TGCCDriver::Link()
{
    const tCIDBuild::TCh* apszArgs[128];
    tCIDLib::TUInt c4CurArg = 0;

    // Set up the standard stuff
    apszArgs[c4CurArg++] = L"gcc";

    // Set up the output file. It is a versioned file and the name is prebuilt
    apszArgs[c4CurArg++] = L"-o";
    apszArgs[c4CurArg++] = m_strTargetFile.pszBuffer();

    // And the debug vs. production flags
    if (m_bDebug)
        apszArgs[c4CurArg++] = L"-g";
    else
        apszArgs[c4CurArg++] = L"-O3";

    //
    //  And now add in all of the Obj and Lib files. We built them up above
    //  when we needed to check all of the source for staleness of the target.
    //  So we just reference those existing names with our argument list.
    //
    TList<TFindInfo>::TCursor cursLibs(&listLibs());
    if (cursLibs.bResetIter())
    {
        do
        {
            apszArgs[c4CurArg++] = cursLibs.tCurElement().strFileName().pszBuffer();
        }   while (cursLibs.bNext());
    }

    TList<TDepInfo>::TCursor cursCpps(&listCpps());
    if (cursCpps.bResetIter())
    {
        do
        {
            // Get a ref to the current element
            const TDepInfo& depiCur = cursCpps.tCurElement();

            // And add its object file name to the list of args
            apszArgs[c4CurArg++] = depiCur.strObjFileName().pszBuffer();
        }   while (cursCpps.bNext());
    }

    // Multi-threaded support
    apszArgs[c4CurArg++] = L"-lpthread";

    if (m_pprojiTarget->eType() == tCIDBuild::EProjTypes::Executable)
    {
        apszArgs[c4CurArg++] = L"-lncurses";
        apszArgs[c4CurArg++] = L"-ldl";
        apszArgs[c4CurArg++] = L"-lm";
    }
    else if (m_pprojiTarget->strProjectName() == TBldStr(L"CIDKernel"))
    {
        apszArgs[c4CurArg++] = L"-lreadline";
        apszArgs[c4CurArg++] = L"-lhistory";
    }

    if (facCIDBuild.bVerbose())
    {
        for (tCIDLib::TUInt uiInd = 0; uiInd < c4CurArg; uiInd++)
            stdOut << apszArgs[uiInd] << L" ";
        stdOut << kCIDBuild::EndLn;
    }

    // And invoke the link
    tCIDLib::TCard4 c4ExecFlags = kCIDBuild::c4ExecFlag_None;
    if (facCIDBuild.bLowPrio())
        c4ExecFlags |= kCIDBuild::c4ExecFlag_LowPrio;
    tCIDLib::TCard4 c4Result;
    if (!TUtils::bExec(apszArgs, c4CurArg, c4Result, c4ExecFlags))
    {
        stdOut << L"Could not execute the linker" << kCIDBuild::EndLn;
        throw tCIDBuild::EErrors::BuildError;
    }

    if (c4Result)
    {
        stdOut << L"Link step failed. Error Code:" << c4Result << kCIDBuild::EndLn;
        throw tCIDBuild::EErrors::BuildError;
    }

    if (m_pprojiTarget->eType() == tCIDBuild::EProjTypes::SharedLib)
    {
        TBldStr strRealName(m_strTargetFile);
        strRealName.Append(facCIDBuild.strVersionSuffix());

        tCIDBuild::TSCh* pszRealName = TRawStr::pszTranscode(strRealName.pszBuffer());
        TArrayJanitor<tCIDBuild::TSCh> janReal(pszRealName);
        tCIDBuild::TSCh* pszTarget = TRawStr::pszTranscode(m_strTargetFile.pszBuffer());
        TArrayJanitor<tCIDBuild::TSCh> janTarget(pszTarget);

        if (::rename(pszTarget, pszRealName))
        {
            stdOut << L"Unable to rename target file" << kCIDBuild::EndLn;
            throw tCIDBuild::EErrors::BuildError;
        }

        if (::symlink(pszRealName, pszTarget))
        {
            stdOut << L"Unable to create symbolic link" << kCIDBuild::EndLn;
            throw tCIDBuild::EErrors::BuildError;
        }
    }
}
