// ----------------------------------------------------------------------------
//  FILE: CIDGraphDev_Shared.hpp
//  DATE: Fri, Feb 14 18:42:56 2020 -0500
//
//  This file was generated by the Charmed Quark CIDIDL compiler. Do not make
//  changes by hand, because they will be lost if the file is regenerated.
// ----------------------------------------------------------------------------
#pragma once

#pragma CIDLIB_PACK(CIDLIBPACK)

// ----------------------------------------------------------------------------
// Types namespace
// ----------------------------------------------------------------------------
namespace tCIDGraphDev
{
    
    // ------------------------------------------------------------------------
    //  The available background mixing modes
    //                  
    // ------------------------------------------------------------------------
    enum class EBackMixModes
    {
        Opaque
        , Transparent
        , Count
        , Min = Opaque
        , Max = Transparent
    };
    CIDGRDEVEXP EBackMixModes eXlatEBackMixModes(const TString& strToXlat, const tCIDLib::TBoolean bThrowIfNot = kCIDLib::False);
    CIDGRDEVEXP const TString& strXlatEBackMixModes(const EBackMixModes eToXlat, const tCIDLib::TBoolean bThrowIfNot = kCIDLib::True);
    CIDGRDEVEXP tCIDLib::TVoid FormatEBackMixModes
        (
                         TString&            strTarget
              , const    TString&            strPrefix
              , const    tCIDLib::TCh        chSepChar
              , const    TEnumMap::ETextVals eVal = TEnumMap::ETextVals::BaseName
        );
    CIDGRDEVEXP tCIDLib::TBoolean bIsValidEnum(const EBackMixModes eVal);

    
    // ------------------------------------------------------------------------
    //  The facility class' eCalcPlacement uses this. It returns the type
    //  of blit that will be needed to do the calculated placement.
    //                  
    // ------------------------------------------------------------------------
    enum class EBltTypes
    {
        None
        , Clip
        , Stretch
        , Both
        , Tile
        , Count
        , Min = None
        , Max = Tile
    };
    CIDGRDEVEXP EBltTypes eXlatEBltTypes(const TString& strToXlat, const tCIDLib::TBoolean bThrowIfNot = kCIDLib::False);
    CIDGRDEVEXP const TString& strXlatEBltTypes(const EBltTypes eToXlat, const tCIDLib::TBoolean bThrowIfNot = kCIDLib::True);
    CIDGRDEVEXP tCIDLib::TVoid FormatEBltTypes
        (
                         TString&            strTarget
              , const    TString&            strPrefix
              , const    tCIDLib::TCh        chSepChar
              , const    TEnumMap::ETextVals eVal = TEnumMap::ETextVals::BaseName
        );
    CIDGRDEVEXP tCIDLib::TBoolean bIsValidEnum(const EBltTypes eVal);

    
    // ------------------------------------------------------------------------
    //  The available bitmap raster modes
    //                  
    // ------------------------------------------------------------------------
    enum class EBmpModes
    {
        Blackness
        , CaptureBlt
        , DstInvert
        , MergeCopy
        , MergePaint
        , NoMirrorBitmap
        , NotSrcCopy
        , NotSrcErase
        , PatCopy
        , PatInvert
        , PatPaint
        , SrcAnd
        , SrcCopy
        , SrcErase
        , SrcInvert
        , SrcPaint
        , Whiteness
        , Count
        , Min = Blackness
        , Max = Whiteness
    };
    CIDGRDEVEXP EBmpModes eXlatEBmpModes(const TString& strToXlat, const tCIDLib::TBoolean bThrowIfNot = kCIDLib::False);
    CIDGRDEVEXP const TString& strXlatEBmpModes(const EBmpModes eToXlat, const tCIDLib::TBoolean bThrowIfNot = kCIDLib::True);
    CIDGRDEVEXP tCIDLib::TBoolean bIsValidEnum(const EBmpModes eVal);

    
    // ------------------------------------------------------------------------
    //  The text drawing directions we allow, which are basically 0, 90.
    //  180, and 270 degrees.
    //                  
    // ------------------------------------------------------------------------
    enum class EFontDirs
    {
        D0
        , D90
        , D180
        , D270
        , Count
        , Min = D0
        , Max = D270
    };
    CIDGRDEVEXP EFontDirs eXlatEFontDirs(const TString& strToXlat, const tCIDLib::TBoolean bThrowIfNot = kCIDLib::False);
    CIDGRDEVEXP const TString& strXlatEFontDirs(const EFontDirs eToXlat, const tCIDLib::TBoolean bThrowIfNot = kCIDLib::True);
    CIDGRDEVEXP tCIDLib::TVoid FormatEFontDirs
        (
                         TString&            strTarget
              , const    TString&            strPrefix
              , const    tCIDLib::TCh        chSepChar
              , const    TEnumMap::ETextVals eVal = TEnumMap::ETextVals::AltText
        );
    CIDGRDEVEXP tCIDLib::TBoolean bIsValidEnum(const EFontDirs eVal);

    
    // ------------------------------------------------------------------------
    //  The available font weights
    //                  
    // ------------------------------------------------------------------------
    enum class EFontWeights
    {
        DontCare
        , Thin
        , ExtraLight
        , Light
        , Normal
        , Medium
        , SemiBold
        , Bold
        , ExtraBold
        , Heavy
        , Count
        , Min = DontCare
        , Max = Heavy
    };
    CIDGRDEVEXP EFontWeights eXlatEFontWeights(const TString& strToXlat, const tCIDLib::TBoolean bThrowIfNot = kCIDLib::False);
    CIDGRDEVEXP const TString& strXlatEFontWeights(const EFontWeights eToXlat, const tCIDLib::TBoolean bThrowIfNot = kCIDLib::True);
    CIDGRDEVEXP const TString& strAltXlatEFontWeights(const EFontWeights eToXlat, const tCIDLib::TBoolean bThrowIfNot = kCIDLib::True);
    CIDGRDEVEXP EFontWeights eAltXlatEFontWeights(const TString& strToXlat, const tCIDLib::TBoolean bThrowIfNot = kCIDLib::False);
    CIDGRDEVEXP tCIDLib::TVoid FormatEFontWeights
        (
                         TString&            strTarget
              , const    TString&            strPrefix
              , const    tCIDLib::TCh        chSepChar
              , const    TEnumMap::ETextVals eVal = TEnumMap::ETextVals::Text
        );
    CIDGRDEVEXP tCIDLib::TBoolean bIsValidEnum(const EFontWeights eVal);

    
    // ------------------------------------------------------------------------
    //  The available gradient fill directions
    //                  
    // ------------------------------------------------------------------------
    enum class EGradDirs
    {
        Horizontal
        , Vertical
        , UpDiagonal
        , DownDiagonal
        , Count
        , Min = Horizontal
        , Max = DownDiagonal
    };
    CIDGRDEVEXP EGradDirs eXlatEGradDirs(const TString& strToXlat, const tCIDLib::TBoolean bThrowIfNot = kCIDLib::False);
    CIDGRDEVEXP const TString& strXlatEGradDirs(const EGradDirs eToXlat, const tCIDLib::TBoolean bThrowIfNot = kCIDLib::True);
    CIDGRDEVEXP tCIDLib::TVoid FormatEGradDirs
        (
                         TString&            strTarget
              , const    TString&            strPrefix
              , const    tCIDLib::TCh        chSepChar
              , const    TEnumMap::ETextVals eVal = TEnumMap::ETextVals::BaseName
        );
    CIDGRDEVEXP tCIDLib::TBoolean bIsValidEnum(const EGradDirs eVal);

    
    // ------------------------------------------------------------------------
    //  The available line end types. Controls how geometric lines that end
    //  at the same end point in a polygon will form a corner.
    //                  
    // ------------------------------------------------------------------------
    enum class ELineEnds
    {
        Flat
        , Square
        , Round
        , Count
        , Min = Flat
        , Max = Round
    };
    CIDGRDEVEXP ELineEnds eXlatELineEnds(const TString& strToXlat, const tCIDLib::TBoolean bThrowIfNot = kCIDLib::False);
    CIDGRDEVEXP const TString& strXlatELineEnds(const ELineEnds eToXlat, const tCIDLib::TBoolean bThrowIfNot = kCIDLib::True);
    CIDGRDEVEXP tCIDLib::TVoid FormatELineEnds
        (
                         TString&            strTarget
              , const    TString&            strPrefix
              , const    tCIDLib::TCh        chSepChar
              , const    TEnumMap::ETextVals eVal = TEnumMap::ETextVals::BaseName
        );
    CIDGRDEVEXP tCIDLib::TBoolean bIsValidEnum(const ELineEnds eVal);

    
    // ------------------------------------------------------------------------
    //  The available ine join styles.
    //                  
    // ------------------------------------------------------------------------
    enum class ELineJoins
    {
        Bevel
        , Round
        , Mitre
        , Count
        , Min = Bevel
        , Max = Mitre
    };
    CIDGRDEVEXP ELineJoins eXlatELineJoins(const TString& strToXlat, const tCIDLib::TBoolean bThrowIfNot = kCIDLib::False);
    CIDGRDEVEXP const TString& strXlatELineJoins(const ELineJoins eToXlat, const tCIDLib::TBoolean bThrowIfNot = kCIDLib::True);
    CIDGRDEVEXP tCIDLib::TVoid FormatELineJoins
        (
                         TString&            strTarget
              , const    TString&            strPrefix
              , const    tCIDLib::TCh        chSepChar
              , const    TEnumMap::ETextVals eVal = TEnumMap::ETextVals::BaseName
        );
    CIDGRDEVEXP tCIDLib::TBoolean bIsValidEnum(const ELineJoins eVal);

    
    // ------------------------------------------------------------------------
    //  The available line drawing styles, Controls whether the line is
    //  solid or uses one of a set of periodic patterns.
    //                  
    // ------------------------------------------------------------------------
    enum class ELineStyles
    {
        Solid
        , Dot
        , Dash
        , DashDot
        , DashDoubleDot
        , Invisible
        , Alternate
        , Count
        , Min = Solid
        , Max = Alternate
    };
    CIDGRDEVEXP ELineStyles eXlatELineStyles(const TString& strToXlat, const tCIDLib::TBoolean bThrowIfNot = kCIDLib::False);
    CIDGRDEVEXP const TString& strXlatELineStyles(const ELineStyles eToXlat, const tCIDLib::TBoolean bThrowIfNot = kCIDLib::True);
    CIDGRDEVEXP tCIDLib::TVoid FormatELineStyles
        (
                         TString&            strTarget
              , const    TString&            strPrefix
              , const    tCIDLib::TCh        chSepChar
              , const    TEnumMap::ETextVals eVal = TEnumMap::ETextVals::BaseName
        );
    CIDGRDEVEXP tCIDLib::TBoolean bIsValidEnum(const ELineStyles eVal);

    
    // ------------------------------------------------------------------------
    //  The foreground mix modes
    //                  
    // ------------------------------------------------------------------------
    enum class EMixModes
    {
        Black
        , CopyPen
        , MaskNotPen
        , MaskPen
        , MaskPenNot
        , MergeNotPen
        , MergePen
        , MergePenNot
        , NOP
        , Not
        , NotCopyPen
        , NotMaskPen
        , NotMergePen
        , NotXorPen
        , White
        , XorPen
        , Count
        , Min = Black
        , Max = XorPen
    };
    CIDGRDEVEXP EMixModes eXlatEMixModes(const TString& strToXlat, const tCIDLib::TBoolean bThrowIfNot = kCIDLib::False);
    CIDGRDEVEXP const TString& strXlatEMixModes(const EMixModes eToXlat, const tCIDLib::TBoolean bThrowIfNot = kCIDLib::True);
    CIDGRDEVEXP tCIDLib::TVoid FormatEMixModes
        (
                         TString&            strTarget
              , const    TString&            strPrefix
              , const    tCIDLib::TCh        chSepChar
              , const    TEnumMap::ETextVals eVal = TEnumMap::ETextVals::BaseName
        );
    CIDGRDEVEXP tCIDLib::TBoolean bIsValidEnum(const EMixModes eVal);

    
    // ------------------------------------------------------------------------
    //  The available built in brush fill patterns. Others can be created
    //  using bitmaps, but these are always available.
    //                  
    // ------------------------------------------------------------------------
    enum class EPatterns
    {
        Solid
        , BackDiagonal
        , Cross
        , DiagonalCross
        , ForwardDiagonal
        , Horizontal
        , Vertical
        , Count
        , Min = Solid
        , Max = Vertical
    };
    CIDGRDEVEXP EPatterns eXlatEPatterns(const TString& strToXlat, const tCIDLib::TBoolean bThrowIfNot = kCIDLib::False);
    CIDGRDEVEXP const TString& strXlatEPatterns(const EPatterns eToXlat, const tCIDLib::TBoolean bThrowIfNot = kCIDLib::True);
    CIDGRDEVEXP tCIDLib::TVoid FormatEPatterns
        (
                         TString&            strTarget
              , const    TString&            strPrefix
              , const    tCIDLib::TCh        chSepChar
              , const    TEnumMap::ETextVals eVal = TEnumMap::ETextVals::BaseName
        );
    CIDGRDEVEXP tCIDLib::TBoolean bIsValidEnum(const EPatterns eVal);

    
    // ------------------------------------------------------------------------
    //  The placement options of images within their target display area.
    //                  
    // ------------------------------------------------------------------------
    enum class EPlacement
    {
        Center
        , SizeToFit
        , Tile
        , UpperLeft
        , SizeIfTooBig
        , KeepAR
        , FitAR
        , Count
        , Min = Center
        , Max = FitAR
    };
    CIDGRDEVEXP EPlacement eXlatEPlacement(const TString& strToXlat, const tCIDLib::TBoolean bThrowIfNot = kCIDLib::False);
    CIDGRDEVEXP const TString& strXlatEPlacement(const EPlacement eToXlat, const tCIDLib::TBoolean bThrowIfNot = kCIDLib::True);
    CIDGRDEVEXP tCIDLib::TVoid FormatEPlacement
        (
                         TString&            strTarget
              , const    TString&            strPrefix
              , const    tCIDLib::TCh        chSepChar
              , const    TEnumMap::ETextVals eVal = TEnumMap::ETextVals::BaseName
        );
    CIDGRDEVEXP tCIDLib::TBoolean bIsValidEnum(const EPlacement eVal);

    
    // ------------------------------------------------------------------------
    //  The system bitmaps
    //  
    //  This enum must remain zero based and contiguous. If you change it, adjust the
    //  mapping array in CIDGraphDev_Bitmap.cpp!
    //                  
    // ------------------------------------------------------------------------
    enum class ESysBmps
    {
        None
        , Close
        , UpArrow
        , DownArrow
        , RightArrow
        , LeftArrow
        , Reduce
        , Zoom
        , Restore
        , Reduced
        , Zoomed
        , Restored
        , UpArrowD
        , DownArrowD
        , RightArrowD
        , LeftArrowD
        , MnArrow
        , Combo
        , UpArrowI
        , DownArrowI
        , RightArrowI
        , LeftArrowI
        , Size
        , BtSize
        , Check
        , Halftone1
        , Halftone2
        , Halftone3
        , Halftone4
        , Halftone5
        , Halftone6
        , Halftone7
        , Halftone8
        , Halftone9
        , Count
        , Min = None
        , Max = Halftone9
        , FirstSys = Close
        , LastSys = Check
    };
    CIDGRDEVEXP const TString& strAltXlatESysBmps(const ESysBmps eToXlat, const tCIDLib::TBoolean bThrowIfNot = kCIDLib::True);
    CIDGRDEVEXP ESysBmps eAltXlatESysBmps(const TString& strToXlat, const tCIDLib::TBoolean bThrowIfNot = kCIDLib::False);
    CIDGRDEVEXP tCIDLib::TBoolean bIsValidEnum(const ESysBmps eVal);

    
    // ------------------------------------------------------------------------
    //  The available system pointers
    //                  
    // ------------------------------------------------------------------------
    enum class ESysPtrs
    {
        AppStarting
        , Arrow
        , Cross
        , Hand
        , Help
        , IBeam
        , No
        , SizeAll
        , SizeNESW
        , SizeNS
        , SizeNWSE
        , SizeWE
        , UpArrow
        , Wait
        , Count
        , Min = AppStarting
        , Max = Wait
    };
    CIDGRDEVEXP ESysPtrs eXlatESysPtrs(const TString& strToXlat, const tCIDLib::TBoolean bThrowIfNot = kCIDLib::False);
    CIDGRDEVEXP const TString& strXlatESysPtrs(const ESysPtrs eToXlat, const tCIDLib::TBoolean bThrowIfNot = kCIDLib::True);
    CIDGRDEVEXP tCIDLib::TBoolean bIsValidEnum(const ESysPtrs eVal);

    
    // ------------------------------------------------------------------------
    //  This enum is used by the caption interface and most widgets that use this
    //  interface. It indicates what special text effect to use when drawing the
    //  text.
    //  
    //  NOTE:   Add new ones at the END, because this enum is streamed out
    //          to disk in various places.
    //                  
    // ------------------------------------------------------------------------
    enum class ETextFX
    {
        None
        , Gradient
        , GradientRefl
        , Reflected
        , GaussianBlur
        , DropShadow
        , Count
        , Min = None
        , Max = DropShadow
    };
    CIDGRDEVEXP ETextFX eXlatETextFX(const TString& strToXlat, const tCIDLib::TBoolean bThrowIfNot = kCIDLib::False);
    CIDGRDEVEXP const TString& strXlatETextFX(const ETextFX eToXlat, const tCIDLib::TBoolean bThrowIfNot = kCIDLib::True);
    CIDGRDEVEXP const TString& strAltXlatETextFX(const ETextFX eToXlat, const tCIDLib::TBoolean bThrowIfNot = kCIDLib::True);
    CIDGRDEVEXP ETextFX eAltXlatETextFX(const TString& strToXlat, const tCIDLib::TBoolean bThrowIfNot = kCIDLib::False);
    CIDGRDEVEXP tCIDLib::TVoid FormatETextFX
        (
                         TString&            strTarget
              , const    TString&            strPrefix
              , const    tCIDLib::TCh        chSepChar
              , const    TEnumMap::ETextVals eVal = TEnumMap::ETextVals::Text
        );
    CIDGRDEVEXP tCIDLib::TBoolean bIsValidEnum(const ETextFX eVal);

}

#pragma CIDLIB_POPPACK

CIDGRDEVEXP tCIDGraphDev::EBackMixModes operator++(tCIDGraphDev::EBackMixModes& eVal, int);
CIDGRDEVEXP TTextOutStream& operator<<(TTextOutStream& strmTar, const tCIDGraphDev::EBackMixModes eToStream);

CIDGRDEVEXP TBinOutStream& operator<<(TBinOutStream& strmTar, const tCIDGraphDev::EBltTypes eToStream);
CIDGRDEVEXP TBinInStream& operator>>(TBinInStream& strmSrc, tCIDGraphDev::EBltTypes& eToFill);
CIDGRDEVEXP tCIDLib::TVoid TBinInStream_ReadArray(TBinInStream& strmSrc, tCIDGraphDev::EBltTypes* const aeList, const tCIDLib::TCard4 c4Count);
CIDGRDEVEXP tCIDLib::TVoid TBinOutStream_WriteArray(TBinOutStream& strmTar, const tCIDGraphDev::EBltTypes* const aeList, const tCIDLib::TCard4 c4Count);
CIDGRDEVEXP tCIDGraphDev::EBltTypes operator++(tCIDGraphDev::EBltTypes& eVal, int);

CIDGRDEVEXP TBinOutStream& operator<<(TBinOutStream& strmTar, const tCIDGraphDev::EBmpModes eToStream);
CIDGRDEVEXP TBinInStream& operator>>(TBinInStream& strmSrc, tCIDGraphDev::EBmpModes& eToFill);
CIDGRDEVEXP tCIDLib::TVoid TBinInStream_ReadArray(TBinInStream& strmSrc, tCIDGraphDev::EBmpModes* const aeList, const tCIDLib::TCard4 c4Count);
CIDGRDEVEXP tCIDLib::TVoid TBinOutStream_WriteArray(TBinOutStream& strmTar, const tCIDGraphDev::EBmpModes* const aeList, const tCIDLib::TCard4 c4Count);

CIDGRDEVEXP TBinOutStream& operator<<(TBinOutStream& strmTar, const tCIDGraphDev::EFontDirs eToStream);
CIDGRDEVEXP TBinInStream& operator>>(TBinInStream& strmSrc, tCIDGraphDev::EFontDirs& eToFill);
CIDGRDEVEXP tCIDLib::TVoid TBinInStream_ReadArray(TBinInStream& strmSrc, tCIDGraphDev::EFontDirs* const aeList, const tCIDLib::TCard4 c4Count);
CIDGRDEVEXP tCIDLib::TVoid TBinOutStream_WriteArray(TBinOutStream& strmTar, const tCIDGraphDev::EFontDirs* const aeList, const tCIDLib::TCard4 c4Count);
CIDGRDEVEXP tCIDGraphDev::EFontDirs operator++(tCIDGraphDev::EFontDirs& eVal, int);
CIDGRDEVEXP TTextOutStream& operator<<(TTextOutStream& strmTar, const tCIDGraphDev::EFontDirs eToStream);

CIDGRDEVEXP TBinOutStream& operator<<(TBinOutStream& strmTar, const tCIDGraphDev::EFontWeights eToStream);
CIDGRDEVEXP TBinInStream& operator>>(TBinInStream& strmSrc, tCIDGraphDev::EFontWeights& eToFill);
CIDGRDEVEXP tCIDLib::TVoid TBinInStream_ReadArray(TBinInStream& strmSrc, tCIDGraphDev::EFontWeights* const aeList, const tCIDLib::TCard4 c4Count);
CIDGRDEVEXP tCIDLib::TVoid TBinOutStream_WriteArray(TBinOutStream& strmTar, const tCIDGraphDev::EFontWeights* const aeList, const tCIDLib::TCard4 c4Count);
CIDGRDEVEXP tCIDGraphDev::EFontWeights operator++(tCIDGraphDev::EFontWeights& eVal, int);
CIDGRDEVEXP TTextOutStream& operator<<(TTextOutStream& strmTar, const tCIDGraphDev::EFontWeights eToStream);

CIDGRDEVEXP TBinOutStream& operator<<(TBinOutStream& strmTar, const tCIDGraphDev::EGradDirs eToStream);
CIDGRDEVEXP TBinInStream& operator>>(TBinInStream& strmSrc, tCIDGraphDev::EGradDirs& eToFill);
CIDGRDEVEXP tCIDLib::TVoid TBinInStream_ReadArray(TBinInStream& strmSrc, tCIDGraphDev::EGradDirs* const aeList, const tCIDLib::TCard4 c4Count);
CIDGRDEVEXP tCIDLib::TVoid TBinOutStream_WriteArray(TBinOutStream& strmTar, const tCIDGraphDev::EGradDirs* const aeList, const tCIDLib::TCard4 c4Count);
CIDGRDEVEXP tCIDGraphDev::EGradDirs operator++(tCIDGraphDev::EGradDirs& eVal, int);
CIDGRDEVEXP TTextOutStream& operator<<(TTextOutStream& strmTar, const tCIDGraphDev::EGradDirs eToStream);

CIDGRDEVEXP TBinOutStream& operator<<(TBinOutStream& strmTar, const tCIDGraphDev::ELineEnds eToStream);
CIDGRDEVEXP TBinInStream& operator>>(TBinInStream& strmSrc, tCIDGraphDev::ELineEnds& eToFill);
CIDGRDEVEXP tCIDLib::TVoid TBinInStream_ReadArray(TBinInStream& strmSrc, tCIDGraphDev::ELineEnds* const aeList, const tCIDLib::TCard4 c4Count);
CIDGRDEVEXP tCIDLib::TVoid TBinOutStream_WriteArray(TBinOutStream& strmTar, const tCIDGraphDev::ELineEnds* const aeList, const tCIDLib::TCard4 c4Count);
CIDGRDEVEXP tCIDGraphDev::ELineEnds operator++(tCIDGraphDev::ELineEnds& eVal, int);
CIDGRDEVEXP TTextOutStream& operator<<(TTextOutStream& strmTar, const tCIDGraphDev::ELineEnds eToStream);

CIDGRDEVEXP TBinOutStream& operator<<(TBinOutStream& strmTar, const tCIDGraphDev::ELineJoins eToStream);
CIDGRDEVEXP TBinInStream& operator>>(TBinInStream& strmSrc, tCIDGraphDev::ELineJoins& eToFill);
CIDGRDEVEXP tCIDLib::TVoid TBinInStream_ReadArray(TBinInStream& strmSrc, tCIDGraphDev::ELineJoins* const aeList, const tCIDLib::TCard4 c4Count);
CIDGRDEVEXP tCIDLib::TVoid TBinOutStream_WriteArray(TBinOutStream& strmTar, const tCIDGraphDev::ELineJoins* const aeList, const tCIDLib::TCard4 c4Count);
CIDGRDEVEXP tCIDGraphDev::ELineJoins operator++(tCIDGraphDev::ELineJoins& eVal, int);
CIDGRDEVEXP TTextOutStream& operator<<(TTextOutStream& strmTar, const tCIDGraphDev::ELineJoins eToStream);

CIDGRDEVEXP TBinOutStream& operator<<(TBinOutStream& strmTar, const tCIDGraphDev::ELineStyles eToStream);
CIDGRDEVEXP TBinInStream& operator>>(TBinInStream& strmSrc, tCIDGraphDev::ELineStyles& eToFill);
CIDGRDEVEXP tCIDLib::TVoid TBinInStream_ReadArray(TBinInStream& strmSrc, tCIDGraphDev::ELineStyles* const aeList, const tCIDLib::TCard4 c4Count);
CIDGRDEVEXP tCIDLib::TVoid TBinOutStream_WriteArray(TBinOutStream& strmTar, const tCIDGraphDev::ELineStyles* const aeList, const tCIDLib::TCard4 c4Count);
CIDGRDEVEXP tCIDGraphDev::ELineStyles operator++(tCIDGraphDev::ELineStyles& eVal, int);
CIDGRDEVEXP TTextOutStream& operator<<(TTextOutStream& strmTar, const tCIDGraphDev::ELineStyles eToStream);

CIDGRDEVEXP tCIDGraphDev::EMixModes operator++(tCIDGraphDev::EMixModes& eVal, int);
CIDGRDEVEXP TTextOutStream& operator<<(TTextOutStream& strmTar, const tCIDGraphDev::EMixModes eToStream);

CIDGRDEVEXP TBinOutStream& operator<<(TBinOutStream& strmTar, const tCIDGraphDev::EPatterns eToStream);
CIDGRDEVEXP TBinInStream& operator>>(TBinInStream& strmSrc, tCIDGraphDev::EPatterns& eToFill);
CIDGRDEVEXP tCIDLib::TVoid TBinInStream_ReadArray(TBinInStream& strmSrc, tCIDGraphDev::EPatterns* const aeList, const tCIDLib::TCard4 c4Count);
CIDGRDEVEXP tCIDLib::TVoid TBinOutStream_WriteArray(TBinOutStream& strmTar, const tCIDGraphDev::EPatterns* const aeList, const tCIDLib::TCard4 c4Count);
CIDGRDEVEXP tCIDGraphDev::EPatterns operator++(tCIDGraphDev::EPatterns& eVal, int);
CIDGRDEVEXP TTextOutStream& operator<<(TTextOutStream& strmTar, const tCIDGraphDev::EPatterns eToStream);

CIDGRDEVEXP TBinOutStream& operator<<(TBinOutStream& strmTar, const tCIDGraphDev::EPlacement eToStream);
CIDGRDEVEXP TBinInStream& operator>>(TBinInStream& strmSrc, tCIDGraphDev::EPlacement& eToFill);
CIDGRDEVEXP tCIDLib::TVoid TBinInStream_ReadArray(TBinInStream& strmSrc, tCIDGraphDev::EPlacement* const aeList, const tCIDLib::TCard4 c4Count);
CIDGRDEVEXP tCIDLib::TVoid TBinOutStream_WriteArray(TBinOutStream& strmTar, const tCIDGraphDev::EPlacement* const aeList, const tCIDLib::TCard4 c4Count);
CIDGRDEVEXP tCIDGraphDev::EPlacement operator++(tCIDGraphDev::EPlacement& eVal, int);
CIDGRDEVEXP TTextOutStream& operator<<(TTextOutStream& strmTar, const tCIDGraphDev::EPlacement eToStream);

CIDGRDEVEXP TBinOutStream& operator<<(TBinOutStream& strmTar, const tCIDGraphDev::ESysBmps eToStream);
CIDGRDEVEXP TBinInStream& operator>>(TBinInStream& strmSrc, tCIDGraphDev::ESysBmps& eToFill);
CIDGRDEVEXP tCIDLib::TVoid TBinInStream_ReadArray(TBinInStream& strmSrc, tCIDGraphDev::ESysBmps* const aeList, const tCIDLib::TCard4 c4Count);
CIDGRDEVEXP tCIDLib::TVoid TBinOutStream_WriteArray(TBinOutStream& strmTar, const tCIDGraphDev::ESysBmps* const aeList, const tCIDLib::TCard4 c4Count);
CIDGRDEVEXP tCIDGraphDev::ESysBmps operator++(tCIDGraphDev::ESysBmps& eVal, int);

CIDGRDEVEXP TBinOutStream& operator<<(TBinOutStream& strmTar, const tCIDGraphDev::ESysPtrs eToStream);
CIDGRDEVEXP TBinInStream& operator>>(TBinInStream& strmSrc, tCIDGraphDev::ESysPtrs& eToFill);
CIDGRDEVEXP tCIDLib::TVoid TBinInStream_ReadArray(TBinInStream& strmSrc, tCIDGraphDev::ESysPtrs* const aeList, const tCIDLib::TCard4 c4Count);
CIDGRDEVEXP tCIDLib::TVoid TBinOutStream_WriteArray(TBinOutStream& strmTar, const tCIDGraphDev::ESysPtrs* const aeList, const tCIDLib::TCard4 c4Count);
CIDGRDEVEXP TTextOutStream& operator<<(TTextOutStream& strmTar, const tCIDGraphDev::ESysPtrs eToStream);

CIDGRDEVEXP TBinOutStream& operator<<(TBinOutStream& strmTar, const tCIDGraphDev::ETextFX eToStream);
CIDGRDEVEXP TBinInStream& operator>>(TBinInStream& strmSrc, tCIDGraphDev::ETextFX& eToFill);
CIDGRDEVEXP tCIDLib::TVoid TBinInStream_ReadArray(TBinInStream& strmSrc, tCIDGraphDev::ETextFX* const aeList, const tCIDLib::TCard4 c4Count);
CIDGRDEVEXP tCIDLib::TVoid TBinOutStream_WriteArray(TBinOutStream& strmTar, const tCIDGraphDev::ETextFX* const aeList, const tCIDLib::TCard4 c4Count);
CIDGRDEVEXP tCIDGraphDev::ETextFX operator++(tCIDGraphDev::ETextFX& eVal, int);
CIDGRDEVEXP TTextOutStream& operator<<(TTextOutStream& strmTar, const tCIDGraphDev::ETextFX eToStream);

