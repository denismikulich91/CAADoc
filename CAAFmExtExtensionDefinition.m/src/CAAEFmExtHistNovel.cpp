// COPYRIGHT DASSAULT SYSTEMES 2010
//
// Implementation of CAAIFmExtHistNovel for the "CAAFmExtHistoricalNovel" extension late type

// FeatureModelerExt Framework
#include "CATFmFeatureFacade.h"
#include "CATFmAttributeName.h"
#include "CATFmAttributeValue.h"
#include "CATUnicodeString.h"
#include "CATFmFeatureModelerID.h"

// Other
#include "CAAEFmExtHistNovel.h"               
#include "iostream.h"

#include "TIE_CAAIFmExtHistNovel.h"
TIE_CAAIFmExtHistNovel(CAAEFmExtHistNovel);

CATImplementClass(CAAEFmExtHistNovel, 
				  DataExtension,
                  CATBaseUnknown,
				  CAAFmExtHistNovel);

//-------------------------------------------------------------------------------------
// CAAFmExtHistNovel : constructor
//-------------------------------------------------------------------------------------
CAAEFmExtHistNovel::CAAEFmExtHistNovel():CATBaseUnknown()
{
	// Add Credentials to authorize Client access to "CAAFmExtExtnCatalogForCredential"
   _MyCredential.RegisterAsApplicationBasedOn(CATFmFeatureModelerID,"CAAFmExtFeatureModeler");
   _MyCredential.RegisterAsCatalogOwner("CAAFmExtExtnCatalogForCredential","CAAFmExtCatalogForCredential");
}

//-------------------------------------------------------------------------------------
// CAAFmExtHistNovel : destructor
//-------------------------------------------------------------------------------------
CAAEFmExtHistNovel::~CAAEFmExtHistNovel()
{
}


HRESULT CAAEFmExtHistNovel::GetEpoch (CATUnicodeString *pEpoch)  
{
    cout << "   Starting GetEpoch" << endl << flush;

	HRESULT rc = E_FAIL;
    if ( NULL == pEpoch ) return rc;
	(*pEpoch)= "" ;

	// Create a Feat Facade over "this"
	CATFmFeatureFacade FeatFacadeOnThis(_MyCredential,this);

	// Retrieve the attribute keys
	CATFmAttributeName AttrKey("Epoch");
	CATFmAttributeValue oValue;
    rc = FeatFacadeOnThis.GetValue(AttrKey,oValue);

	if (SUCCEEDED(rc))
		rc =  oValue.GetString(*pEpoch);

	return rc;
}


HRESULT CAAEFmExtHistNovel::SetEpoch (const CATUnicodeString & epoch) 
{
    cout << "   Starting SetEpoch" << endl << flush;

	HRESULT rc = E_FAIL;

	// Create a Feat Facade over "this"
	CATFmFeatureFacade FeatFacadeOnThis(_MyCredential,this);

	// Retrieve the attribute keys
	CATFmAttributeName AttrKey("Epoch");
	CATFmAttributeValue oValue;
	oValue.SetString(epoch);

    rc = FeatFacadeOnThis.SetValue(AttrKey,oValue);

	return rc;
}



