#include <stdio.h>
#include <stdlib.h>
#include <winscard.h>
#include <list>

#define FALSE 0
#define TRUE 1

using namespace std;

class SCard {
 protected:

  SCARDCONTEXT hContext;
  SCARDHANDLE hCard;
  DWORD dwActiveProtocol;
  SCARD_IO_REQUEST pioSendPci;
 
 public:
  SCard ();      // create the SC context.
  ~SCard ();     // delete the SC context.
  
  list<char*>* availableReaders ();                                                  // list of the SC readers (used for setReader argument)
  int setReader (char* name);                                                        // reader selection
  int sendCommand (BYTE* cmd, int lenCmd, BYTE* resp, long unsigned int* lenResp);   // send command and receives response
  
};
