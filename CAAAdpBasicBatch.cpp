// COPYRIGHT DASSAULT SYSTEMES 2006
//=============================================================================
// PLM basic use case
// Abstract: This use case connects to a repository (or provider) and lists available environments
//
// Steps :
//    1. Check the input arguments
//    2. Set up the connection parameters
//    3. Create the PLM session
//    4. List available environments
//    5. Close the PLM session
//=============================================================================
// To execute:
//
//   mkrun -c "CAAAdpBasicBatch <Repository> <Server> <LoginTicket>"
//   
//	 where    Repository	: The name of the repository 
//			  Server		: The host , port, and RootURI of the server as host:port_number/rootURI
//			  LoginTicket	: A string representing the Login Ticket
//								 
//   or
//   mkrun -c "CAAAdpBasicBatch <Repository> <ServerHost> <ServerPort> <ServerRootURI> <LoginTicket>"
//   
//	 where    Repository	: The name of the repository 
//			  ServerHost    : The host of the server 
//			  ServerPort    : The port of the server 
//			  ServerRootURI : The rootURI of the server  
//			  LoginTicket  : The Login Ticket 
//
// Return code :
//    0 successful completion
//    1 execution failed
// 
//=============================================================================

// CATPLMComponentInterfaces Framework
#include "CATPLMSessionServices.h"

// CATPlMIntegrationAccess Framework
#include "CATAdpDictionaryServices.h"

// System Framework
#include "CATString.h"
#include "CATUnicodeString.h"
#include "CATListOfCATString.h"
#include "CATListOfCATUnicodeString.h"

// C++ Library
#include <iostream.h>
//=============================================================================

int main(int iargc, char *iargv[])
{
	HRESULT hr=E_FAIL;

	cout << "CAAAdpBasicBatch started" << endl << endl;

	// 1. Check the input arguments
	//
	if ( (4 != iargc) && (6 != iargc) ) {
		cout << "Usage 1: " << iargv[0] << " <Repository> <ServerHost:ServerPort/ServerRootURI> <LoginTicket>"<< endl;
		cout << "Usage 2: " << iargv[0] << " <Repository> <ServerHost> <ServerPort> <ServerRootURI> <LoginTicket>"<< endl;
		return 1;
	}

	const char* repository = iargv[1];
	const char* server     = iargv[2];
	const char* server_host = NULL ;
	const char* server_port = NULL ;
	const char* server_rootURI = NULL ;

	int argshift = 0 ;
	if ( 6 == iargc )
	{
       argshift = +2 ;
       server_host = iargv[2];
	   server_port = iargv[3];
	   server_rootURI =  iargv[4];
	}
	const char* iLoginTicket = iargv[3+argshift];
	
	//
	// 2. Set the connection parameters
	//
   hr = CATPLMSessionServices::SetPLMSessionParameter("Repository", repository);
   if (FAILED(hr)) { return 1;}
	

   if ( 4 == iargc )
	{
	   hr = CATPLMSessionServices::SetPLMSessionParameter("Server", server);
	   if (FAILED(hr)) return 1;
	}else
	{
	   // On Customer installation https is
	   const char* server_protocol = "https" ;
	   hr = CATPLMSessionServices::SetPLMSessionParameter("ServerProtocol",server_protocol);
	   if (FAILED(hr)) return 1;
       hr = CATPLMSessionServices::SetPLMSessionParameter("ServerName", server_host);
	   if (FAILED(hr)) return 1;
	   hr = CATPLMSessionServices::SetPLMSessionParameter("ServerPort", server_port);
	   if (FAILED(hr)) return 1;
	   hr = CATPLMSessionServices::SetPLMSessionParameter("ServerRootURI", server_rootURI);
	   if (FAILED(hr)) return 1;
	}	

	hr = CATPLMSessionServices::SetPLMSessionParameter("LoginTicket", iLoginTicket);
	if (FAILED(hr)) return 1; 		
	cout << "  Connection parameters set" << endl; 

	//
	// 3. Create a PLM session
	//
	if ( 4 == iargc )
	{
	cout << "  Initializing session with:" << endl
         << "    Repository = "  << repository << endl
	     << "    Server     = "  << server << endl
	     << "    Login Ticket = "  << iLoginTicket << endl;
	}
	else
	{
		cout << "  Initializing session with:" << endl
         << "    Repository = "  << repository << endl
	     << "    Server Host     = "  << server_host << endl
		 << "    Server Port     = "  << server_port << endl
		 << "    Server RootURI  = "  << server_rootURI << endl
		 << "    Login Ticket = "  << iLoginTicket << endl;
	} 

  	hr = CATPLMSessionServices::InitPLMSession();
	if (FAILED(hr))
	{
		cout << "   ERROR initializing PLM Session" <<endl;
		return 1;   
	}
	cout << "  PLM Session initialized" << endl;

	//
	// 4. List available environments
	//
	CATListValCATString envIDList;
	CATListValCATUnicodeString envAliasList;
	hr = CATAdpDictionaryServices::ListEnvironments(repository,
							envIDList,
							envAliasList);
	if (FAILED(hr)) return 1;
		
	cout << "  Available environments:" << endl;
	for (int i = 1; i <= envIDList.Size(); i++) {
		cout << "    " << envIDList[i]
		     << ", alias: " << envAliasList[i].ConvertToChar()
		     << endl;
	}

	//
	// 5. Close the PLM session
	//
	hr = CATPLMSessionServices::ClosePLMSession();
	if (FAILED(hr))	{
		return 1;   
	}
	cout << "  PLM session closed" << endl;

	cout << "CAAAdpBasicBatch ended" << endl << endl;
	return 0;
}
