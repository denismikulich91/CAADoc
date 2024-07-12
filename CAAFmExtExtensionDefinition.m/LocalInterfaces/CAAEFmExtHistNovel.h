// COPYRIGHT DASSAULT SYSTEMES 2010

//=============================================================================
//  Abstract of CAAIFmExtHistNovel Implementation:
//  -----------------------------------------
//
// This class is an implementation of the CAAIFmExtHistNovel interface for the
// "CAAFmExtHistNovel" extension late-type. It essentially retrieves and
// valuates the values of the attributes of this extension.
// This implementation is included in module CAAFmExtExtensionDefinition.m. 
//  
//=============================================================================
//  Main Methods:
//  ------------
//
//  GetEpoch:  Returns the value of the "Epoch" attribute.
//  SetEpoch:  Valuates the "Epoch" attribute.
//==============================================================================================

#ifndef CAAEFmExtHistNovel_h
#define CAAEFmExtHistNovel_h

// System
#include "CATBaseUnknown.h"
class CATUnicodeString ;

// FeatureModelerExt
#include "CATFmCredentials.h"


class CAAEFmExtHistNovel :  public CATBaseUnknown
{
  CATDeclareClass;

  public:
    HRESULT GetEpoch (CATUnicodeString *opEpoch);
    HRESULT SetEpoch (const CATUnicodeString & iEpoch);

  private:
	// Standard constructors and destructors for an implementation class
	CAAEFmExtHistNovel ();
	virtual ~CAAEFmExtHistNovel ();

	CATFmCredentials _MyCredential;

};

#endif

