// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
// Abstract of Use Case "CAAFmExtSimpleAttr":
// ---------------------------------------
//
// This sample illustrates fundamentally to retrieve a StartUp from an existing catalog,
// Instantiate it , valuate some attributes and retrieve the new values.
//
//
// The current UC refers to the following list of the StartUps defined in the catalog 
// CAAOsmCatalogSU.CATfct, which thus is its prerequisite
// This catalog is provided in the CAAFeatureModelerExt.edu/CNext/resources/graphic folder,
// which on mkrtv is copied to the Workspace run time view
// Alternatively, user can execute the CAAOsmCatalogSU Use Case, to generate this CATfct
//
// Only these two StartUps will be referenced in this use case:
//
//		StartUp									Attribute
//		-------									---------
//
//		CAAOsmBook								Title
//												BookPublisher
//
//		CAAOsmNovel (a kind of CAAOsmBook)		Title
//												BookPublisher
//												Author
//												(list of) NovelChapter
//													
//
//
//=============================================================================
//  Steps
//
//  1- Checks the arguments
//  2- Initializes the PLM session 
//  3- Creates a Credential Object
//  4- Creates a Product Representation Reference as Techno Rep in which to store the new features
//  6- Creates "Title" & "Author" Attributes  
//  7- Instantiates "CAAOsmNovel" , the instance is named Novel
//  8- Retrieves its "Author" attribute  ((own attribute)
//  9- Retrieves its "Author" attribute value  
// 10- Valuates its "Title" attribute (inherited attribute)
// 11- Retrieves its "Title" attribute value  
//
// 12- Saves the session
// 13- Closes the session
//
//=============================================================================
// How to execute :
//
//   mkrun -c "CAAFmExtSimpleAttr <Repository> <Server> <LoginTicket> <Environment>"  
//
//	 where    Repository	      : The name of the repository (or provider) 
//			  Server		      : The name and port of the server as name:port_number
//	          LoginTicket	      : A string representing the Login Ticket
//			  Environment	      : A PLM Environment containing a PRODUCT modeler customization
//
//
// Return code :
//   0 successful execution
//   1 execution failed
// 
//=============================================================================

//local Framework
#include "CAAFmExtCreateRepRef.h"     // to create the Rep ref

//System Framework
#include "CATUnicodeString.h"
#include "CATString.h"
#include "CATBaseUnknown.h"

// ObjectModelerBase
#include "CATOmbLifeCycleRootsBag.h"

//CAT3DPhysicalRepInterfaces Framework
#include "CATIPsiRepresentationReference.h"  // interface on rep ref

// CATPLMIntegrationUse
#include "CATAdpSaver.h"

// CAAPLMClientAdapter.edu Framework
#include "CAAAdpCreateCloseSession.h"

// FeatureModelerExt 
#include "CATFmFeatureFacade.h"
#include "CATFmContainerFacade.h"
#include "CATFmStartUpFacade.h"
#include "CATFmCredentials.h"
#include "CATFmAttributeName.h"
#include "CATFmAttributeValue.h"
#include "CATFmFeatureModelerID.h"

// PLMSessionInterfaces Framework
#include "CATIAdpEnvironment.h"
// CATPLMIntegrationAccess  Framework
#include "CATAdpDictionaryServices.h"

#include <iostream.h> 
 
//=======================================================================================

int main (int iArgc, char * iArgv[])
{ 
//---------------------
// 1- Checks arguments
//---------------------
  
	if ( 5 != iArgc )
	{
		cout << endl;
		cout << "Usage: CAAFmExtSimpleAttr <Repository> <Server> <LoginTicket> <Environment> " ;
		cout <<endl;
		return 1;
	}

	cout << "The CAAFmExtSimpleAttr main program begins ...."<< endl << endl;
  
//------------------------------------------------------------------
//2 - Initializes the PLM session 
//------------------------------------------------------------------
  	HRESULT rc = ::CAAAdpCreateSession(iArgv[1], iArgv[2], iArgv[3]);
	if (FAILED(rc))	 return 1;   
		
	cout << "   PLM session initialized with the following connection parameters" << endl;
	cout << "      Repository=" << iArgv[1] << endl;
	cout << "      Server="     << iArgv[2] << endl;
	
	// Correction for IR-234807V6R2014 - Environemnt need to be keep as CreateTechnologicalRepReference is KO with NULL env
	CATString Repository = iArgv[1];
	CATString EnvToUse = iArgv[4];
	CATIAdpEnvironment * pIAdpEnvironment = NULL ;
    rc = CATAdpDictionaryServices::GetEnvironment(Repository.ConvertToChar(),EnvToUse,&pIAdpEnvironment);
	
//--------------------------------------------------------------------
// 3- Creates a Credential Object
// -------------------------------------------------------------------
	CATFmCredentials MyCredential;
	rc = MyCredential.RegisterAsApplicationBasedOn(CATFmFeatureModelerID,"CAAFmExtFeatureModeler");
	if (FAILED(rc)) return 1;
    rc = MyCredential.RegisterAsCatalogOwner("CAAOsmCatalogSU","CAAOsmClientId");
	if (FAILED(rc)) return 1;
	cout << "   Success in creating the credentials" << endl;

//------------------------------------------------------------------
// 4- Creates a Product Representation Reference
//------------------------------------------------------------------
	CATUnicodeString NameAndTypeofContainer = "CAAFmExtAppliCont" ;
	CATIPsiRepresentationReference * pPsiCreatedRepRef= NULL;
	CATBaseUnknown * pContainer = NULL ;
	
	rc = ::CAAFmExtCreateRepRef(MyCredential, pIAdpEnvironment,NameAndTypeofContainer,NameAndTypeofContainer,
		                        IID_CATIPsiRepresentationReference,(void**) &pPsiCreatedRepRef, &pContainer);
	
	if (FAILED(rc) || (NULL==pPsiCreatedRepRef) || (NULL==pContainer) ) return 1;
	cout <<"   The Product Representation Reference is created" << endl;

	// Insert component that is loaded in session, in BAG
	CATOmbLifeCycleRootsBag Bag;
	Bag.InsertRoot(pPsiCreatedRepRef);

	//Create container facade to work with
	CATFmContainerFacade MyContainerFacade(MyCredential,pContainer);

    pPsiCreatedRepRef->Release();
	pPsiCreatedRepRef = NULL;

	if(NULL!=pIAdpEnvironment)
	{
		pIAdpEnvironment->Release();
		pIAdpEnvironment = NULL;
	}

//--------------------------------------------------------------------------------
// 6- Creates Attribute Names
//--------------------------------------------------------------------------------
	CATFmAttributeName TitleAttrName("Title");
	cout << "   Retrieved the Name to the attribute Title" << endl;

	CATFmAttributeName AuthorAttrName("Author");
	cout << "   Retrieved the Name to the attribute Author" << endl;
//------------------------------------------------------------------
// 7- Instantiates "CAAOsmNovel" , the instance is named Novel
//------------------------------------------------------------------
	CATUnicodeString MyStartUpType("`CAAOsmNovel`@`CAAOsmCatalogSU.CATfct`");
	CATFmStartUpFacade NovelStartUpFacade(MyCredential, MyStartUpType);
	cout << "CAAOsmNovel StartUp Facade retrieved OK" << endl << flush;

	CATFmFeatureFacade oFeatFacadeOnNovel(MyCredential);
	rc = NovelStartUpFacade.InstantiateIn(MyContainerFacade,oFeatFacadeOnNovel);
	if (FAILED(rc)) return 1;
		
	cout << "   The Novel feature is created" << endl;

//------------------------------------------------------------------
// 9- Valuates the "Author" attribute of the Novel feature
//------------------------------------------------------------------
	CATUnicodeString AuthorOfBook = "Dumas";
	CATFmAttributeValue AuthorAsFmValue(AuthorOfBook);
	rc =  oFeatFacadeOnNovel.SetValue(AuthorAttrName,AuthorAsFmValue);
	if (FAILED(rc)) return 1;
		
	cout << "   Valuated the Author attribute of the Novel" << endl;

//-------------------------------------------------------------------------------------
// 10- Retrieves "Author" attribute value of the Novel feature
//-------------------------------------------------------------------------------------
    CATFmAttributeValue RetrievedValueAsFmValue;
	rc = oFeatFacadeOnNovel.GetValue(AuthorAttrName,RetrievedValueAsFmValue); 
	if (SUCCEEDED(rc))
	{
		CATUnicodeString oStrAuthor ;
		AuthorAsFmValue.GetString(oStrAuthor);

		if ( RetrievedValueAsFmValue==AuthorAsFmValue )
		{
			cout << "   Confirmation on the Valuation is OK" << endl;
		} else rc = E_FAIL ; 
				
	}
    if (FAILED(rc)) return 1;

//------------------------------------------------------------------
// 11- Valuates the "Title" attribute of the Novel feature
//------------------------------------------------------------------
	CATUnicodeString TheThreeMusketeers = "The Three Musketeers";
	CATFmAttributeValue TitleAsFmValue(TheThreeMusketeers);
	rc =  oFeatFacadeOnNovel.SetValue(TitleAttrName,TitleAsFmValue);
	if (FAILED(rc)) return 1;
		
	cout << "   Valuated the Title attribute of the Novel" << endl;

//-------------------------------------------------------------------------------------
// 12- Retrieves "Title" attribute value of the Novel feature
//-------------------------------------------------------------------------------------
	rc = oFeatFacadeOnNovel.GetValue(TitleAttrName,RetrievedValueAsFmValue); 
	if (SUCCEEDED(rc))
	{
		CATUnicodeString oStrTitle ;
		TitleAsFmValue.GetString(oStrTitle);

		if ( RetrievedValueAsFmValue==TitleAsFmValue )
		{
			cout << "   Confirmation on the Valuation is OK" << endl;
		} else rc = E_FAIL ; 
				
	}
    if (FAILED(rc)) return 1;



//-------------------------------------------------------------------------------------
// 12- Saves the session
//-------------------------------------------------------------------------------------
	CATAdpSaver saver;
    rc = saver.Save();
	if ( FAILED(rc)  ) return 1;
    cout <<"   Save is successful " << endl;

	// Unload components from session
	Bag.RemoveAll();

	pContainer->Release();
	pContainer = NULL ;
//--------------------------------------------------------------------------------------
//13- Closes the session
//--------------------------------------------------------------------------------------
	rc = ::CAAAdpCloseSession();
	if (FAILED(rc) ) return 1;
		
	cout <<"   PLM session closed" << endl;
	cout << endl << "The CAAFmExtSimpleAttr main program ends ...."<< endl << endl;

	return 0;
}
