//
// FILE NAME: CIDLib_Collection.hpp
//
// AUTHOR: Dean Roddey
//
// CREATED: 12/24/1995
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
//  This header implements the base class for all template collections. All
//  of the collections derive from TCollectionBase and must implement its
//  virtual interface. This interface allows for basic things like checking
//  the number of elements, checking for empty, checking for full. I.e. things
//  that do not depend upon any particular ordering or storage style or
//  knowledge of the storage mechanism or element type.
//
//  By value collections also implement the MDuplicable interface, which allows
//  a collection to be duplicated polymorphically (with all its contents.) This is
//  a powerful concept. It means that all element classes must support copy
//  construction and assignment, but that was already a requirement anyway for a
//  'by value' collection of elements (in order to get elements in and out of the
//  collection.)
//
//  There are two derivatives of TCollectionBase, which represent the two main types
//  of by value collections, element based and map based. Element based collections
//  have self contained elements. Map based collections have a key and a value,
//  whether the key is conceptually part of the element or a separate thing. Either
//  way, they require another instantiation parameter, that of the key field. Hash
//  key based ones have self contained elements, but must provide a key extractor
//  so that the key can be known to the collection.
//
//  TRefCollection is the derivative of TCollectionBase that serves as the base for
//  all 'by reference' collections. The main difference is that the by value
//  derivatives use an objAdd(const TElem&)) method and the by ref one use an
//  Add(TElem* const) method, representing the two ways that they accept their elements.
//  The former of course copies the added element.
//
//  And finally we introduce two commonly used node classes, which are based on the
//  fundamental doubly linked list node. Many collections are based on this doubly
//  linked list, and so can use this common node literally or as the basis for their
//  nodes. We have one for by value and one for by reference nodes.
//
//  We also provide a base class for fundamental collections, which are a different
//  set of collections from the object based ones. They just hold fundamental types
//  and are much simpler. The base class is just to help get common code out of the
//  templatized stuff in order to make the generated code smaller, mostly error
//  checking/throwing stuff.
//
//
// CAVEATS/GOTCHAS:
//
// LOG:
//
//  $_CIDLib_Log_$
//
#pragma once


#pragma CIDLIB_PACK(CIDLIBPACK)

class TThreadWaitList;
class TColBlockModeJan;


// ---------------------------------------------------------------------------
//   CLASS: TColPubSubInfo
//  PREFIX: colpsi
// ---------------------------------------------------------------------------
class CIDLIBEXP TColPubSubInfo : public TObject
{
    public  :
        // -------------------------------------------------------------------
        //  Public types
        // -------------------------------------------------------------------
        enum class EEvents
        {
            BlockAdded
            , BlockChanged
            , BlockRemoved
            , Cleared
            , ElemAdded
            , ElemChanged
            , ElemMoved
            , ElemRemoved
            , Reordered
            , Swapped

            , Count
        };


        // -------------------------------------------------------------------
        //  Constructors and destructor
        // -------------------------------------------------------------------
        TColPubSubInfo();

        TColPubSubInfo
        (
            const   EEvents                 eEvent
            , const tCIDLib::TCard4         c4Index = 0
        );

        TColPubSubInfo
        (
            const   EEvents                 eEvent
            , const tCIDLib::TCard4         c4Index1
            , const tCIDLib::TCard4         c4Index2
        );

        TColPubSubInfo(const TColPubSubInfo&) = default;
        TColPubSubInfo(TColPubSubInfo&&) = default;

        ~TColPubSubInfo() = default;


        // -------------------------------------------------------------------
        //  Public operators
        // -------------------------------------------------------------------
        TColPubSubInfo& operator=(const TColPubSubInfo&) = default;
        TColPubSubInfo& operator=(TColPubSubInfo&&) = default;


        // -------------------------------------------------------------------
        //  Public, non-virtual methods
        // -------------------------------------------------------------------
        tCIDLib::TCard4 c4Index1() const
        {
            return m_c4Index1;
        }

        tCIDLib::TCard4 c4Index2() const
        {
            return m_c4Index2;
        }

        EEvents eEvent() const
        {
            return m_eEvent;
        }

    private :
        // -------------------------------------------------------------------
        //  Private data members
        //
        //  m_c4Index1
        //  m_c4Index2
        //      Some indices that mean different things based on the event. See the
        //      class comments above.
        //
        //  m_eEvent
        //      The event being reported
        // -------------------------------------------------------------------
        tCIDLib::TCard4 m_c4Index1;
        tCIDLib::TCard4 m_c4Index2;
        EEvents         m_eEvent;


        // -------------------------------------------------------------------
        //  Magic macros
        // -------------------------------------------------------------------
        RTTIDefs(TColPubSubInfo,TObject)
};




// ---------------------------------------------------------------------------
//   CLASS: TCollectionBase
//  PREFIX: col
// ---------------------------------------------------------------------------
class CIDLIBEXP TCollectionBase : public TObject, public MLockable
{
    public  :
        // -------------------------------------------------------------------
        //  Public, static methods
        // -------------------------------------------------------------------
        static tCIDLib::TVoid BadStoredCount
        (
            const   TClass&                 clsCol
        );


        // -------------------------------------------------------------------
        //  Constructors and Destructor
        // -------------------------------------------------------------------
        ~TCollectionBase();


        // -------------------------------------------------------------------
        //  Public, inherited methods
        //
        //  At this level, we just always say the lock worked, because there is
        //  no lock. Derived classes that provide locking will override these.
        //  This lets all collections (internally and externally) be locked via
        //  the standard MLockable interface and TLocker lock janitor.
        // -------------------------------------------------------------------
        tCIDLib::TBoolean bTryLock(const tCIDLib::TCard4) const override
        {
            return kCIDLib::True;
        }

        tCIDLib::TVoid Lock(const tCIDLib::TCard4 c4WaitMSs) const override
        {
        }

        tCIDLib::TVoid Unlock() const override
        {
        }


        // -------------------------------------------------------------------
        //  Public, virtual methods
        // -------------------------------------------------------------------
        virtual tCIDLib::TBoolean bIsEmpty() const = 0;

        virtual tCIDLib::TCard4 c4ElemCount() const = 0;

        virtual tCIDLib::EMTStates eMTSafe() const
        {
            return tCIDLib::EMTStates::Unsafe;
        }

        virtual tCIDLib::TVoid RemoveAll() = 0;


        // -------------------------------------------------------------------
        //  Public, non-virtual methods
        // -------------------------------------------------------------------
        tCIDLib::TBoolean bIsFull(const tCIDLib::TCard4 c4Limit) const
        {
            return (c4ElemCount() >= c4Limit);
        }

        tCIDLib::TBoolean bIsMTSafe() const
        {
            return (eMTSafe() == tCIDLib::EMTStates::Safe);
        }

        tCIDLib::TBoolean bPublishEnabled() const
        {
            return (m_ppstopReport != nullptr);
        }

        tCIDLib::TCard4 c4SerialNum() const;

        tCIDLib::TVoid CheckIsFull
        (
            const   tCIDLib::TCard4         c4Limit
            , const tCIDLib::TCh* const     pszDescr
        );

        tCIDLib::TVoid PublishBlockChanged
        (
            const   tCIDLib::TCard4         c4At
            , const tCIDLib::TCard4         c4Count
        );

        tCIDLib::TVoid PublishElemChanged
        (
            const   tCIDLib::TCard4         c4At
        );

        tCIDLib::TVoid PublishReload();

        const TString& strTopicPath() const
        {
            if (!m_ppstopReport)
                return TString::strEmpty();
            return m_ppstopReport->strPath();
        }


    protected   :
        // -------------------------------------------------------------------
        //  Declare our friends
        // -------------------------------------------------------------------
        friend class TColBlockModeJan;


        // -------------------------------------------------------------------
        //  Protected, static methods
        // -------------------------------------------------------------------
        static tCIDLib::TBoolean bWaitForData
        (
                    TLocker&                lockrQueue
            , const TCollectionBase&        colSrc
            , const tCIDLib::TCard4         c4WaitMSs
            ,       TThreadWaitList&        twlWaitList
            , const tCIDLib::TBoolean       bThrowIfNot
        );


        // -------------------------------------------------------------------
        //  Hidden constructors and operators
        // -------------------------------------------------------------------
        TCollectionBase();

        TCollectionBase
        (
            const   TCollectionBase&        colSrc
        );

        TCollectionBase& operator=
        (
            const   TCollectionBase&        colSrc
        );

        // No move support, it's too complicated
        TCollectionBase(TCollectionBase&&) = delete;
        TCollectionBase& operator=(TCollectionBase&&) = delete;


        // -------------------------------------------------------------------
        //  Protected, non-virtual methods
        // -------------------------------------------------------------------
        tCIDLib::TBoolean bCheckNewSize
        (
            const   tCIDLib::TCard4         c4New
            , const tCIDLib::TCard4         c4Current
            , const tCIDLib::TCh* const     pszFile
            , const tCIDLib::TCard4         c4Line
        )   const;

        tCIDLib::TVoid BlockModeEnd
        (
            const   tCIDLib::TBoolean       bAddMode
            , const tCIDLib::TCard4         c4Index
            , const tCIDLib::TCard4         c4Count
        );

        tCIDLib::TVoid BlockModeStart();

        tCIDLib::TCard4 c4IncSerialNum();

        tCIDLib::TVoid CheckAllocAndCount
        (
            const   tCIDLib::TCard4         c4Count
            , const tCIDLib::TCard4         c4Alloc
            , const tCIDLib::TCh* const     pszFile
            , const tCIDLib::TCard4         c4Line
        );

        tCIDLib::TVoid CheckCursorValid
        (
            const   TCursorBase&            cursToCheck
            , const tCIDLib::TCh* const     pszFile
            , const tCIDLib::TCard4         c4Line
        )   const;

        tCIDLib::TVoid CheckIndex
        (
            const   tCIDLib::TCard4         c4ToCheck
            , const tCIDLib::TCard4         c4CurCount
            , const tCIDLib::TCh* const     pszFile
            , const tCIDLib::TCard4         c4Line
        )   const;

        tCIDLib::TVoid CheckOneNonAdopting
        (
            const   tCIDLib::EAdoptOpts     eAdoptSrc
            , const tCIDLib::EAdoptOpts     eAdoptTar
            , const tCIDLib::TCh* const     pszFile
            , const tCIDLib::TCard4         c4Line
        )   const;

        tCIDLib::TVoid CheckReallocParms
        (
            const   tCIDLib::TCard4         c4NewSize
            , const tCIDLib::TCard4         c4CurCount
            , const tCIDLib::TBoolean       bKeepOld
            , const tCIDLib::TCh* const     pszFile
            , const tCIDLib::TCard4         c4Line
        )   const;

        tCIDLib::TVoid ColIsEmpty
        (
            const   tCIDLib::TCh* const     pszFile
            , const tCIDLib::TCard4         c4Line
        )   const;

        tCIDLib::TVoid ColIsFull
        (
            const   tCIDLib::TCh* const     pszFile
            , const tCIDLib::TCard4         c4Line
            , const tCIDLib::TCard4         c4Max
        )   const;

        tCIDLib::TVoid DuplicateElem
        (
            const   tCIDLib::TCh* const     pszFile
            , const tCIDLib::TCard4         c4Line
        )   const;

        tCIDLib::TVoid DuplicateKey
        (
            const   TObject&                objKey
            , const tCIDLib::TCh* const     pszFile
            , const tCIDLib::TCard4         c4Line
        )   const;

        tCIDLib::TVoid EnablePublish
        (
            const   TString&                strDesiredPath
            ,       TString&                strActualPath
        );

        tCIDLib::TVoid EnablePublish
        (
            const   TString&                strTopicPath
        );

        tCIDLib::TVoid HashChanged
        (
            const   tCIDLib::TCh* const     pszFile
            , const tCIDLib::TCard4         c4Line
        )   const;

        tCIDLib::TVoid KeyNotFound
        (
             const  tCIDLib::TCh* const     pszFile
            , const tCIDLib::TCard4         c4Line
        )   const;

        tCIDLib::TVoid MustClearFirst
        (
            const   tCIDLib::TCh* const     pszFile
            , const tCIDLib::TCard4         c4Line
        )   const;

        tCIDLib::TVoid NodeNotFound
        (
            const   tCIDLib::TCh* const     pszFile
            , const tCIDLib::TCard4         c4Line
        )   const;

        tCIDLib::TVoid NotMemberNode
        (
            const   tCIDLib::TCh* const     pszFile
            , const tCIDLib::TCard4         c4Line
        ) const;

        tCIDLib::TVoid NotMyCursor
        (
            const   TClass&                 clsCursor
            , const TClass&                 clsCol
            , const tCIDLib::TCh* const     pszFile
            , const tCIDLib::TCard4         c4Line
        )   const;

        tCIDLib::TVoid NullNodeAdded
        (
            const   tCIDLib::TCh* const     pszFile
            , const tCIDLib::TCard4         c4Line
        )   const;

        tCIDLib::TVoid PublishAdd
        (
            const   tCIDLib::TCard4         c4At
        );

        tCIDLib::TVoid PublishBlockAdded
        (
            const   tCIDLib::TCard4         c4At
            , const tCIDLib::TCard4         c4Count
        );

        tCIDLib::TVoid PublishBlockRemoved
        (
            const   tCIDLib::TCard4         c4At
            , const tCIDLib::TCard4         c4Count
        );

        tCIDLib::TVoid PublishClear();

        tCIDLib::TVoid PublishMoved
        (
            const   tCIDLib::TCard4         c4From
            , const tCIDLib::TCard4         c4To
        );

        tCIDLib::TVoid PublishRemove
        (
            const   tCIDLib::TCard4         c4At
        );

        tCIDLib::TVoid PublishReorder();

        tCIDLib::TVoid PublishSwap
        (
            const   tCIDLib::TCard4         c4At1
            , const tCIDLib::TCard4         c4At2
        );

        tCIDLib::TVoid SrcTooBig
        (
            const   tCIDLib::TCh* const     pszFile
            , const tCIDLib::TCard4         c4Line
            , const tCIDLib::TCard4         c4SrcElems
            , const tCIDLib::TCard4         c4TarMax
        )   const;

        tCIDLib::TVoid Unsupported
        (
            const   tCIDLib::TCh* const     pszFile
            , const tCIDLib::TCard4         c4Line
            , const tCIDLib::TCh* const     pszOpName
        )   const;

        tCIDLib::TVoid ZeroSize
        (
            const   tCIDLib::TCh* const     pszFile
            , const tCIDLib::TCard4         c4Line
        )   const;


    private :
        // -------------------------------------------------------------------
        //  Private data members
        //
        //  m_bInBlockMode
        //      This indicates we are in a block mode and we will not send individual
        //      add/remove reports if pub/sub is enabled.
        //
        //  m_c4SerialNum
        //      This is a serial number from the collection. It is bumped up every time
        //      changes are made to the element content. Cursors watch it to know if they
        //      are out of date.
        //
        //      We start the serial number at 1! This makes it easier for code that
        //      needs to watch for changes. They can set their last serial number to
        //      zero, and it will always trigger an initial inequality.
        //
        //  m_ppstopReport
        //      A topic to report changes to subscribers. See the header comments above
        //      for details. Only created if the derived class sets it up.
        // -------------------------------------------------------------------
        tCIDLib::TBoolean   m_bInBlockMode;
        tCIDLib::TCard4     m_c4SerialNum;
        TPubSubTopic*       m_ppstopReport;


        // -------------------------------------------------------------------
        //  Magic macros
        // -------------------------------------------------------------------
        RTTIDefs(TCollectionBase,TObject)
};



// ---------------------------------------------------------------------------
//   CLASS: TFundColBase
//  PREFIX: col
// ---------------------------------------------------------------------------
class CIDLIBEXP TFundColBase : public TCollectionBase
{
    public  :
        // -------------------------------------------------------------------
        //  Constructors and Destructor
        // -------------------------------------------------------------------
        ~TFundColBase();


    protected   :
        // -------------------------------------------------------------------
        //  Hidden constructors and operators
        // -------------------------------------------------------------------
        TFundColBase();

        TFundColBase(const TFundColBase&)  = default;
        TFundColBase& operator=(const TFundColBase&) = default;

        // No move support, it's too complicated
        TFundColBase(TFundColBase&&)  = delete;
        TFundColBase& operator=(TFundColBase&&) = delete;


    private :
        // -------------------------------------------------------------------
        //  Magic macros
        // -------------------------------------------------------------------
        RTTIDefs(TFundColBase, TCollectionBase)
};




// ---------------------------------------------------------------------------
//   CLASS: TCollection
//  PREFIX: col
// ---------------------------------------------------------------------------
template <typename TElem>
class TCollection : public TCollectionBase, public MDuplicable
{
    public  :
        // -------------------------------------------------------------------
        //  Constructors and Destructor
        // -------------------------------------------------------------------
        ~TCollection() = default;


        // -------------------------------------------------------------------
        //  Public, pure virtual methods
        // -------------------------------------------------------------------
        virtual TElem& objAdd
        (
            const   TElem&                  objNew
        ) = 0;

        [[nodiscard]] virtual TColCursor<TElem>* pcursNew() const = 0;


        // -------------------------------------------------------------------
        //  Public, non-virtual methods
        // -------------------------------------------------------------------
        tCIDLib::TVoid AddXCopies(  const   TElem&          objNew
                                    , const tCIDLib::TCard4 c4Count)
        {
            for (tCIDLib::TCard4 c4Index = 0; c4Index < c4Count; c4Index++)
                objAdd(objNew);
        }


        //
        //  Call back each element, breaking out on false return. Can be a function
        //  pointer or lambda. We use a cursor so it will work for any of our
        //  collection derivatives. We can only provide the const version here
        //  since we don't understand the derived class' non-const cursors, and
        //  it may not even provide one. It has to implement the non-const version.
        //
        template <typename IterCB> tCIDLib::TBoolean bForEach(IterCB iterCB) const
        {
            TLocker lockrThis(this);
            TColCursor<TElem>* pcursEach = pcursNew();
            TJanitor<TColCursor<TElem>> janCursor(pcursEach);
            while (pcursEach->bIsValid())
            {
                if (!iterCB(pcursEach->objRCur()))
                    return kCIDLib::False;
                pcursEach->bNext();
            }
            return kCIDLib::True;
        }


    protected   :
        // -------------------------------------------------------------------
        //  Hidden constructors and operators
        // -------------------------------------------------------------------
        TCollection() :

            TCollectionBase()
        {
        }

        TCollection(const TCollection<TElem>&) = default;
        TCollection<TElem>& operator=(const TCollection<TElem>&) = default;

        TCollection(TCollection<TElem>&&) = delete;
        TCollection<TElem>& operator=(TCollection<TElem>&&) = delete;


    private :
        // -------------------------------------------------------------------
        //  Do any needed magic macros
        // -------------------------------------------------------------------
        TemplateRTTIDefs(TCollection<TElem>,TCollectionBase)
};



// ---------------------------------------------------------------------------
//   CLASS: TMapCollection
//  PREFIX: col
// ---------------------------------------------------------------------------
template <typename TElem, class TKey> class TMapCollection

    : public TCollection<TKeyObjPair<TKey, TElem>>
{
    public  :
        // -------------------------------------------------------------------
        //  Public class types
        // -------------------------------------------------------------------
        using TMyType = TMapCollection<TElem, TKey>;
        using TParent = TCollection<TKeyObjPair<TKey, TElem>>;


        // -------------------------------------------------------------------
        //  Constructors and Destructor
        // -------------------------------------------------------------------
        ~TMapCollection()
        {
        }


        // -------------------------------------------------------------------
        //  Public, inherited methods
        // -------------------------------------------------------------------
        tCIDLib::TBoolean bIsDescendantOf(const TClass& clsTarget) const override
        {
            if (clsTarget == this->clsThis())
                return kCIDLib::True;
            return TParent::bIsDescendantOf(clsTarget);
        }

        const TClass& clsParent() const override
        {
            return TMyType::clsThis();
        }


    protected   :
        // -------------------------------------------------------------------
        //  Hidden constructors and operators
        // -------------------------------------------------------------------
        TMapCollection() : TParent()
        {
        }

        TMapCollection(const TMyType&) = default;
        TMapCollection& operator=(const TMyType&) = default;

        TMapCollection(TMyType&&) = delete;
        TMapCollection& operator=(TMyType&&) = delete;
};



// ---------------------------------------------------------------------------
//   CLASS: TBasicColNode
//  PREFIX: node
// ---------------------------------------------------------------------------
template <typename TElem> class TBasicColNode : public TDLstNode
{
    public  :
        // -------------------------------------------------------------------
        //  Constructors and Destructor
        // -------------------------------------------------------------------
        TBasicColNode() = delete;

        TBasicColNode(const TElem& objData) :

            m_objData(objData)
        {
        }

        TBasicColNode(TElem&& objData) :

            m_objData(tCIDLib::ForceMove(objData))
        {
        }

        // A special one for in place elements.
        template <typename... TArgs> TBasicColNode(TArgs&&... Args) :

            m_objData(tCIDLib::Forward<TArgs>(Args)...)
        {
        }

        TBasicColNode(const TBasicColNode<TElem>&) = delete;
        TBasicColNode(TBasicColNode<TElem>&&) = delete;

        ~TBasicColNode() {}


        // -------------------------------------------------------------------
        //  Public operators
        // -------------------------------------------------------------------
        TBasicColNode<TElem>& operator=(const TBasicColNode<TElem>&) = delete;
        TBasicColNode<TElem>& operator=(TBasicColNode<TElem>&&) = delete;


        // -------------------------------------------------------------------
        //  Public, non-virtual methods
        // -------------------------------------------------------------------
        const TElem& objData() const
        {
            return m_objData;
        }

        TElem& objData()
        {
            return m_objData;
        }


    private :
        // -------------------------------------------------------------------
        //  Private data members
        //
        //  m_objData
        //      The user data object.
        // -------------------------------------------------------------------
        TElem   m_objData;


        // -------------------------------------------------------------------
        //  Do any needed magic macros
        // -------------------------------------------------------------------
        TemplateRTTIDefs(TBasicColNode<TElem>,TDLstNode)
};



// ---------------------------------------------------------------------------
//   CLASS: TRefCollection
//  PREFIX: curs
// ---------------------------------------------------------------------------
template <typename TElem> class TRefCollection : public TCollectionBase
{
    public  :
        // -------------------------------------------------------------------
        //  Constructors and Destructor
        // -------------------------------------------------------------------
        ~TRefCollection()
        {
        }

        // -------------------------------------------------------------------
        //  Public, pure virtual methods
        // -------------------------------------------------------------------
        virtual tCIDLib::TVoid Add
        (
                    TElem* const            pobjToAdd
        ) = 0;

        virtual tCIDLib::EAdoptOpts eAdopt() const = 0;

        virtual tCIDLib::TVoid GiveAllTo
        (
                    TRefCollection<TElem>&  colTarget
        ) = 0;

        virtual tCIDLib::TVoid OrphanElem
        (
                    TElem* const            pobjToRemove
        ) = 0;

        [[nodiscard]] virtual TColCursor<TElem>* pcursNew() const = 0;

        virtual tCIDLib::TVoid RemoveElem
        (
                    TElem* const            pobjToRemove
        ) = 0;


        //
        //  Call back each element, breaking out on false return. Can be a function
        //  pointer or lambda. We use a cursor so it will work for any of our
        //  collection derivatives. We can only provide a constant version. We don't
        //  understand constant cursors here, and the derived class may not even
        //  provide one. They have to provide any non-const version of this.
        //
        template <typename IterCB> tCIDLib::TBoolean bForEach(IterCB iterCB) const
        {
            TLocker lockrThis(this);
            TColCursor<TElem>* pcursEach = pcursNew();
            TJanitor<TColCursor<TElem>> janCursor(pcursEach);
            while (pcursEach->bIsValid())
            {
                if (!iterCB(pcursEach->objRCur()))
                    return kCIDLib::False;
                pcursEach->bNext();
            }
            return kCIDLib::True;
        }


    protected   :
        // -------------------------------------------------------------------
        //  Hidden constructors and operators
        // -------------------------------------------------------------------
        TRefCollection() : TCollectionBase()
        {
        }


        TRefCollection(TRefCollection&&) = delete;
        TRefCollection(const TRefCollection&) = delete;
        TRefCollection<TElem>& operator=(TRefCollection&&) = delete;
        TRefCollection<TElem>& operator=(const TRefCollection&) = delete;


    private :
        // -------------------------------------------------------------------
        //  Do any needed magic macros
        // -------------------------------------------------------------------
        TemplateRTTIDefs(TRefCollection<TElem>,TCollectionBase)
};



// ---------------------------------------------------------------------------
//   CLASS: TBasicRefColNode
//  PREFIX: node
// ---------------------------------------------------------------------------
template <typename TElem> class TBasicColRefNode : public TDLstNode
{
    public  :
        // -------------------------------------------------------------------
        //  Constructors and Destructor
        // -------------------------------------------------------------------
        TBasicColRefNode() = delete;
        TBasicColRefNode(       TElem* const        pobjData
                        , const tCIDLib::EAdoptOpts eAdopt) :

            m_bOwns(eAdopt == tCIDLib::EAdoptOpts::Adopt)
            , m_pobjData(pobjData)
        {
        }

        TBasicColRefNode(const TBasicColRefNode<TElem>&) = delete;
        TBasicColRefNode( TBasicColRefNode<TElem>&&) = delete;

        ~TBasicColRefNode()
        {
            // Delete the data if we own it
            if (m_bOwns && m_pobjData)
                delete m_pobjData;
        }


        // -------------------------------------------------------------------
        //  Public operators
        // -------------------------------------------------------------------
        TBasicColRefNode<TElem>& operator=(const TBasicColRefNode<TElem>&) = delete;
        TBasicColRefNode<TElem>& operator=(TBasicColRefNode<TElem>&&) = delete;


        // -------------------------------------------------------------------
        //  Public, non-virtual methods
        // -------------------------------------------------------------------
        tCIDLib::TVoid OrphanData()
        {
            m_pobjData = nullptr;
        }

        [[nodiscard]] TElem* pobjOrphanData()
        {
            TElem* pobjRet = m_pobjData;
            m_pobjData = nullptr;
            return pobjRet;
        }

        const TElem* pobjData() const
        {
            return m_pobjData;
        }

        TElem* pobjData()
        {
            return m_pobjData;
        }


    private :
        // -------------------------------------------------------------------
        //  Private data members
        //
        //  m_bOwns
        //      A flag that indicates whether we own our data or not.
        //
        //  m_pobjData
        //      The pointer to the user data object.
        // -------------------------------------------------------------------
        tCIDLib::TCard1 m_bOwns;
        TElem*          m_pobjData;


        // -------------------------------------------------------------------
        //  Do any needed magic macros
        // -------------------------------------------------------------------
        TemplateRTTIDefs(TBasicColRefNode<TElem>,TDLstNode)
};


// ---------------------------------------------------------------------------
//   CLASS: TColBlockModeJan
//  PREFIX: jan
//
//  Our ctor sets the m_bBlockMode flag on the collection. Our dtor calls the
//  BlockAddDone() method on it.
// ---------------------------------------------------------------------------
class CIDLIBEXP TColBlockModeJan
{
    public :
        // -------------------------------------------------------------------
        //  Constructors and destructor
        // -------------------------------------------------------------------
        TColBlockModeJan() = delete;

        TColBlockModeJan
        (
                    TCollectionBase* const  pcolTar
            , const tCIDLib::TBoolean       bLoad
            , const tCIDLib::TCard4         c4Start = kCIDLib::c4MaxCard
        );

        TColBlockModeJan(const TColBlockModeJan&) = delete;
        TColBlockModeJan(TColBlockModeJan&&) = delete;

        ~TColBlockModeJan();


        // -------------------------------------------------------------------
        //  Public operators
        // -------------------------------------------------------------------
        TColBlockModeJan& operator=(const TColBlockModeJan&) = delete;
        TColBlockModeJan& operator=(TColBlockModeJan&&) = delete;


        // -------------------------------------------------------------------
        //  Public, non-virtual methods
        // -------------------------------------------------------------------
        tCIDLib::TVoid IncCount();


    private :
        // -------------------------------------------------------------------
        //  Private data members
        //
        //  m_bLoad
        //      Remembers if this is a block add or block remove
        //
        //  m_c4Count
        //      The count of elements added at start. Initially zero and bumped by
        //      the IncCount() method.
        //
        //  m_c4Start
        //      The starting index of the block load. If max card, then this is a
        //      non-contiguous (maybe sorted) load.
        //
        //  m_pcolTar
        //      A pointer to the collection we are handling.
        // -------------------------------------------------------------------
        tCIDLib::TBoolean   m_bLoad;
        tCIDLib::TCard4     m_c4Count;
        tCIDLib::TCard4     m_c4Start;
        TCollectionBase*    m_pcolTar;
};


//
//  Global equality comparisons that will work for all by value and by ref
//  collections if the elements have an equality operator.
//
template <typename TElem>
tCIDLib::TBoolean operator==(const TCollection<TElem>& col1, const TCollection<TElem>& col2)
{
    if (&col1 == &col2)
        return kCIDLib::True;

    // Lock both of the collections while we do this
    TLocker lockrThis(&col1);
    TLocker lockrSrc(&col2);

    if (col1.c4ElemCount() != col2.c4ElemCount())
        return kCIDLib::False;

    TColCursor<TElem>* pcurs1 = col1.pcursNew();
    TColCursor<TElem>* pcurs2 = col2.pcursNew();
    TJanitor<TColCursor<TElem>> janCurs1(pcurs1);
    TJanitor<TColCursor<TElem>> janCurs2(pcurs2);

    while (pcurs1->bIsValid())
    {
        if (!(pcurs1->objRCur() == pcurs2->objRCur()))
            return kCIDLib::False;
        pcurs1->bNext();
        pcurs2->bNext();
    }
    return kCIDLib::True;
}

template <typename TElem>
tCIDLib::TBoolean operator!=(const TCollection<TElem>& col1, const TCollection<TElem>& col2)
{
    return !operator==(col1, col2);
}


template <typename TElem> tCIDLib::TBoolean
operator==(const TRefCollection<TElem>& col1, const TRefCollection<TElem>& col2)
{
    if (&col1 == &col2)
        return kCIDLib::True;

    // Lock both of the collections while we do this
    TLocker lockrThis(&col1);
    TLocker lockrSrc(&col2);

    if (col1.c4ElemCount() != col2.c4ElemCount())
        return kCIDLib::False;

    TColCursor<TElem>* pcurs1 = col1.pcursNew();
    TColCursor<TElem>* pcurs2 = col2.pcursNew();
    TJanitor<TColCursor<TElem>> janCurs1(pcurs1);
    TJanitor<TColCursor<TElem>> janCurs2(pcurs2);

    while (pcurs1->bIsValid())
    {
        if (!(pcurs1->objRCur() == pcurs2->objRCur()))
            return kCIDLib::False;
        pcurs1->bNext();
        pcurs2->bNext();
    }
    return kCIDLib::True;
}

template <typename TElem> tCIDLib::TBoolean
operator!=(const TRefCollection<TElem>& col1, const TRefCollection<TElem>& col2)
{
    return !operator==(col1, col2);
}


//
//  And here are some methods that also compare two collections, but they
//  allow for a custom comparator.
//
namespace tCIDLib
{
    template <typename TElem, typename TCompFunc = tCIDLib::TDefEqComp<TElem>>
    tCIDLib::TBoolean
    bCompareElems(  const   TCollection<TElem>& col1
                    , const TCollection<TElem>& col2
                    ,       TCompFunc           pfnComp = tCIDLib::TDefEqComp<TElem>())
    {
        if (&col1 == &col2)
            return kCIDLib::True;

        // Lock both of the collections while we do this
        TLocker lockrThis(&col1);
        TLocker lockrSrc(&col2);

        if (col1.c4ElemCount() != col2.c4ElemCount())
            return kCIDLib::False;

        TColCursor<TElem>* pcurs1 = col1.pcursNew();
        TColCursor<TElem>* pcurs2 = col2.pcursNew();
        TJanitor<TColCursor<TElem>> janCurs1(pcurs1);
        TJanitor<TColCursor<TElem>> janCurs2(pcurs2);

        while (pcurs1->bIsValid())
        {
            if (!pfnComp(pcurs1->objRCur(), pcurs2->objRCur()))
                return kCIDLib::False;

            pcurs1->bNext();
            pcurs2->bNext();
        }
        return kCIDLib::True;
    }


    template <typename TElem, typename TCompFunc>
    tCIDLib::TBoolean
    bCompareElems(  const   TRefCollection<TElem>&  col1
                    , const TRefCollection<TElem>&  col2
                    ,       TCompFunc               pfnComp)
    {
        if (&col1 == &col2)
            return kCIDLib::True;

        // Lock both of the collections while we do this
        TLocker lockrThis(&col1);
        TLocker lockrSrc(&col2);

        if (col1.c4ElemCount() != col2.c4ElemCount())
            return kCIDLib::False;

        TColCursor<TElem>* pcurs1 = col1.pcursNew();
        TColCursor<TElem>* pcurs2 = col2.pcursNew();
        TJanitor<TColCursor<TElem>> janCurs1(pcurs1);
        TJanitor<TColCursor<TElem>> janCurs2(pcurs2);

        while (pcurs1->bIsValid())
        {
            if (!pfnComp(pcurs1->objRCur(), pcurs2->objRCur()))
                return kCIDLib::False;

            pcurs1->bNext();
            pcurs2->bNext();
        }
        return kCIDLib::True;
    }
}

#pragma CIDLIB_POPPACK
