// ----------------------------------------------------------------------------
//  FILE: CIDUPnP_Shared.hpp
//  DATE: Fri, Feb 14 18:42:56 2020 -0500
//
//  This file was generated by the Charmed Quark CIDIDL compiler. Do not make
//  changes by hand, because they will be lost if the file is regenerated.
// ----------------------------------------------------------------------------
#pragma once

#pragma CIDLIB_PACK(CIDLIBPACK)

// ----------------------------------------------------------------------------
// Constants namespace
// ----------------------------------------------------------------------------
namespace kCIDUPnP
{
    
    // ------------------------------------------------------------------------
    //  Some well known UPnP device type URNs
    //                  
    // ------------------------------------------------------------------------
    CIDUPNPEXP const extern TString strDevType_MediaRenderer;
    CIDUPNPEXP const extern TString strDevType_MediaServer;
    CIDUPNPEXP const extern TString strDevType_RootDev;
    CIDUPNPEXP const extern TString strDevType_ZonePlayer;
    
    // ------------------------------------------------------------------------
    //  Some well known UPnP service type URNs
    //                  
    // ------------------------------------------------------------------------
    CIDUPNPEXP const extern TString strSvcType_AVTransport;
    CIDUPNPEXP const extern TString strSvcType_AlarmClock;
    CIDUPNPEXP const extern TString strSvcType_AudioIn;
    CIDUPNPEXP const extern TString strSvcType_ConnectionMgr;
    CIDUPNPEXP const extern TString strSvcType_ContentDirectory;
    CIDUPNPEXP const extern TString strSvcType_DeviceProperties;
    CIDUPNPEXP const extern TString strSvcType_GroupManagement;
    CIDUPNPEXP const extern TString strSvcType_MusicServices;
    CIDUPNPEXP const extern TString strSvcType_RendControl;
    CIDUPNPEXP const extern TString strSvcType_ZoneGroupTopology;
}

// ----------------------------------------------------------------------------
// Types namespace
// ----------------------------------------------------------------------------
namespace tCIDUPnP
{
    
    // ------------------------------------------------------------------------
    //  The supported UPnP play modes
    //                  
    // ------------------------------------------------------------------------
    enum class EPlayModes
    {
        UNKNOWN
        , NORMAL
        , SHUFFLE
        , REPEAT
        , REPEATONE
        , RANDOM
        , DIRECT
        , INTRO
        , Count
        , Min = UNKNOWN
        , Max = INTRO
    };
    CIDUPNPEXP EPlayModes eXlatEPlayModes(const TString& strToXlat, const tCIDLib::TBoolean bThrowIfNot = kCIDLib::False);
    CIDUPNPEXP const TString& strXlatEPlayModes(const EPlayModes eToXlat, const tCIDLib::TBoolean bThrowIfNot = kCIDLib::True);
    CIDUPNPEXP const TString& strAltXlatEPlayModes(const EPlayModes eToXlat, const tCIDLib::TBoolean bThrowIfNot = kCIDLib::True);
    CIDUPNPEXP EPlayModes eAltXlatEPlayModes(const TString& strToXlat, const tCIDLib::TBoolean bThrowIfNot = kCIDLib::False);
    CIDUPNPEXP tCIDLib::TVoid FormatEPlayModes
        (
                         TString&            strTarget
              , const    TString&            strPrefix
              , const    tCIDLib::TCh        chSepChar
              , const    TEnumMap::ETextVals eVal = TEnumMap::ETextVals::Text
        );
    CIDUPNPEXP tCIDLib::TBoolean bIsValidEnum(const EPlayModes eVal);

    
    // ------------------------------------------------------------------------
    //  The supported UPnP transport modes
    //                  
    // ------------------------------------------------------------------------
    enum class ETransStates
    {
        UNKNOWN
        , STOPPED
        , PAUSED_PLAYBACK
        , PAUSED_RECORDING
        , PLAYING
        , RECORDING
        , TRANSITIONING
        , NO_MEDIA_PRESENT
        , Count
        , Min = UNKNOWN
        , Max = NO_MEDIA_PRESENT
    };
    CIDUPNPEXP ETransStates eXlatETransStates(const TString& strToXlat, const tCIDLib::TBoolean bThrowIfNot = kCIDLib::False);
    CIDUPNPEXP const TString& strXlatETransStates(const ETransStates eToXlat, const tCIDLib::TBoolean bThrowIfNot = kCIDLib::True);
    CIDUPNPEXP const TString& strAltXlatETransStates(const ETransStates eToXlat, const tCIDLib::TBoolean bThrowIfNot = kCIDLib::True);
    CIDUPNPEXP ETransStates eAltXlatETransStates(const TString& strToXlat, const tCIDLib::TBoolean bThrowIfNot = kCIDLib::False);
    CIDUPNPEXP tCIDLib::TVoid FormatETransStates
        (
                         TString&            strTarget
              , const    TString&            strPrefix
              , const    tCIDLib::TCh        chSepChar
              , const    TEnumMap::ETextVals eVal = TEnumMap::ETextVals::Text
        );
    CIDUPNPEXP tCIDLib::TBoolean bIsValidEnum(const ETransStates eVal);

}

#pragma CIDLIB_POPPACK

CIDUPNPEXP TBinOutStream& operator<<(TBinOutStream& strmTar, const tCIDUPnP::EPlayModes eToStream);
CIDUPNPEXP TBinInStream& operator>>(TBinInStream& strmSrc, tCIDUPnP::EPlayModes& eToFill);
CIDUPNPEXP tCIDLib::TVoid TBinInStream_ReadArray(TBinInStream& strmSrc, tCIDUPnP::EPlayModes* const aeList, const tCIDLib::TCard4 c4Count);
CIDUPNPEXP tCIDLib::TVoid TBinOutStream_WriteArray(TBinOutStream& strmTar, const tCIDUPnP::EPlayModes* const aeList, const tCIDLib::TCard4 c4Count);
CIDUPNPEXP TTextOutStream& operator<<(TTextOutStream& strmTar, const tCIDUPnP::EPlayModes eToStream);

CIDUPNPEXP TBinOutStream& operator<<(TBinOutStream& strmTar, const tCIDUPnP::ETransStates eToStream);
CIDUPNPEXP TBinInStream& operator>>(TBinInStream& strmSrc, tCIDUPnP::ETransStates& eToFill);
CIDUPNPEXP tCIDLib::TVoid TBinInStream_ReadArray(TBinInStream& strmSrc, tCIDUPnP::ETransStates* const aeList, const tCIDLib::TCard4 c4Count);
CIDUPNPEXP tCIDLib::TVoid TBinOutStream_WriteArray(TBinOutStream& strmTar, const tCIDUPnP::ETransStates* const aeList, const tCIDLib::TCard4 c4Count);
CIDUPNPEXP TTextOutStream& operator<<(TTextOutStream& strmTar, const tCIDUPnP::ETransStates eToStream);

