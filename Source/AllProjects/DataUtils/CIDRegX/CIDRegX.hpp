//
// FILE NAME: CIDRegX.hpp
//
// AUTHOR: Dean Roddey
//
// CREATED: 03/20/1999
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
//  This is the main public header for the facility. It is the single point
//  of contact for the outside world. By including it, they get what we
//  have to offer.
//
//  This facility implements a regular expression engine. It's quite a basic
//  one. I have all the guts to make a really powerful one with the DFA that
//  is used in the XML parser. It needs time to be addressed.
//
// CAVEATS/GOTCHAS:
//
// LOG:
//
//  $_CIDLib_Log_$
//
#pragma once


// ---------------------------------------------------------------------------
//  Set up our import/export attributes
// ---------------------------------------------------------------------------
#if     defined(PROJ_CIDREGX)
#define CIDREGXEXP  CID_DLLEXPORT
#else
#define CIDREGXEXP  CID_DLLIMPORT
#endif


// ---------------------------------------------------------------------------
//  Include our underlying headers
// ---------------------------------------------------------------------------
#include    "CIDLib.hpp"


// ---------------------------------------------------------------------------
//  Now subinclude our other headers, in the needed order.
// ---------------------------------------------------------------------------
#include    "CIDRegX_ErrorIds.hpp"
#include    "CIDRegX_ThisFacility.hpp"
#include    "CIDRegX_RegExNFA.hpp"
#include    "CIDRegX_RegExEngine.hpp"


// ---------------------------------------------------------------------------
//  Export the lazy evalution method for the facility object.
// ---------------------------------------------------------------------------
extern CIDREGXEXP TFacCIDRegX& facCIDRegX();
