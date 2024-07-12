// COPYRIGHT DASSAULT SYSTEMES 2000
//
// Implementation of CAAIFmExtBiogNovel for the "CAAOsmBiographicalNovel"
// extension late type.  

// FeatureModelerExt Framework
#include "CATFmFeatureFacade.h"
#include "CATFmAttributeName.h"
#include "CATFmAttributeValue.h"
#include "CATUnicodeString.h"
#include "CATFmFeatureModelerID.h"

// Other
#include "CAAEFmExtBiogNovel.h"               
#include "iostream.h"

#include "TIE_CAAIFmExtBiogNovel.h"
TIE_CAAIFmExtBiogNovel(CAAEFmExtBiogNovel);

CATImplementClass(CAAEFmExtBiogNovel, 
				  DataExtension,
                  CATBaseUnknown,
				  CAAOsmBiographicalNovel);

//-------------------------------------------------------------------------------------
// CAAEFmExtBiogNovel : constructor
//-------------------------------------------------------------------------------------
CAAEFmExtBiogNovel::CAAEFmExtBiogNovel():CATBaseUnknown()
{
	// Add Credentials to authorize Client access to "CAAOsmExt1Catalog"
   _MyCredential.RegisterAsApplicationBasedOn(CATFmFeatureModelerID,"CAAFmExtFeatureModeler");
   _MyCredential.RegisterAsCatalogOwner("CAAOsmExt1Catalog","CAAOsmClientId1");
}

//-------------------------------------------------------------------------------------
// CAAEFmExtBiogNovel : destructor
//-------------------------------------------------------------------------------------
CAAEFmExtBiogNovel::~CAAEFmExtBiogNovel()
{
}


HRESULT CAAEFmExtBiogNovel::GetEpoch (CATUnicodeString *pEpoch)  
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


HRESULT CAAEFmExtBiogNovel::SetEpoch (const CATUnicodeString & epoch) 
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


HRESULT CAAEFmExtBiogNovel::GetDomain (CATUnicodeString *pDomain)
{
    cout << "   Starting GetDomain" << endl << flush;

	HRESULT rc = E_FAIL;
	if ( NULL == pDomain ) return rc;
	(*pDomain)= "" ;

	// Create a Feat Facade over "this"
	CATFmFeatureFacade FeatFacadeOnThis(_MyCredential,this);

	// Retrieve the attribute keys
	CATFmAttributeName AttrKey("Domain");
	CATFmAttributeValue oValue;
    rc = FeatFacadeOnThis.GetValue(AttrKey,oValue);

	if (SUCCEEDED(rc))
		rc =  oValue.GetString(*pDomain);

	return rc;
}


HRESULT CAAEFmExtBiogNovel::SetDomain (const CATUnicodeString & domain)
{
    cout << "   Starting SetDomain" << endl << flush;

	HRESULT rc = E_FAIL;

	// Create a Feat Facade over "this"
	CATFmFeatureFacade FeatFacadeOnThis(_MyCredential,this);

	// Retrieve the attribute keys
	CATFmAttributeName AttrKey("Domain");
	CATFmAttributeValue oValue;
	oValue.SetString(domain);
    rc = FeatFacadeOnThis.SetValue(AttrKey,oValue);

	return rc;
}


HRESULT CAAEFmExtBiogNovel::GetBaseFeature (void** oPtr, const IID &IID)
{
	cout << "   CAAEFmExtBiogNovel::GetBaseFeature " << endl;

	HRESULT rc = E_FAIL;

	// Create a Feat Facade over "this"
	CATFmFeatureFacade FeatFacadeOnThis(_MyCredential,this);
	
	CATFmAttributeValue oFmAttrValueOnBaseFeat;
	rc = FeatFacadeOnThis.GetBaseFeature(oFmAttrValueOnBaseFeat);

	CATFmFeatureFacade FeatFacadeOnBaseFeat ;
	FeatFacadeOnBaseFeat = oFmAttrValueOnBaseFeat;

	rc =  FeatFacadeOnBaseFeat.QueryInterfaceOnFeature(IID,oPtr);

	return rc;
}






