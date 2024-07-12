// COPYRIGHT DASSAULT SYSTEMES 2000

//=============================================================================
//  Abstract of CAAIBiogNovel Implementation:
//  -----------------------------------------
//
//  This class is an implementation of the CAAIBiogNovel interface for the
//  "CAAOsmBiographicalNovel" extension late-type. It essentially retrieves and
//  valuates the values of the attributes of this extension.This implementation
//  is included in Use Case CAAFmExtExtensionDefinition.m. 
//  
//=============================================================================
//  Main Methods:
//  ------------
//
//  GetEpoch:  Returns the value of the "Epoch" attribute.
//  SetEpoch:  Valuates the "Epoch" attribute.
//  GetDomain: Returns the value of the "Domain" attribute.
//  SetDomain: Valuates the "Domain" attribute.
//  GetBaseFeature: Retrieve the Base Feature from the CAAOsmBigraphicalNovel feature extension
//==============================================================================================

#ifndef CAAEFmExtBiogNovel_h
#define CAAEFmExtBiogNovel_h

// System
#include "CATBaseUnknown.h"
class CATUnicodeString;

// FeatureModelerExt
#include "CATFmCredentials.h"

// CAAFeatureModelerExt.edu
#include "CAAIFmExtNovel.h"

class CAAEFmExtBiogNovel :  public CATBaseUnknown
{
  CATDeclareClass;

  public:
    HRESULT GetEpoch (CATUnicodeString *opEpoch);
    HRESULT SetEpoch (const CATUnicodeString & iEpoch);
	HRESULT GetDomain (CATUnicodeString *opDomain);
	HRESULT SetDomain (const CATUnicodeString &iDomain);
	
	HRESULT GetBaseFeature (void** oPtr, const IID &IID = IID_CAAIFmExtNovel);

  private:
	// Standard constructors and destructors for an implementation class
	CAAEFmExtBiogNovel ();
	virtual ~CAAEFmExtBiogNovel ();

	CATFmCredentials _MyCredential;

};

#endif

