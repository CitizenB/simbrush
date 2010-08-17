/******************************************************************************
 *
 * NAME:          SIMbrush.c
 *
 * AUTHORS:       Fabio Casadei
 *                fabio.casadei@mercurio-ws.com
 *
 *                Antonio Savoldi
 *                antonio.savoldi@ing.unibs.it
 *
 * FILE TYPE:     C source
 *
 * DESCRIPTION:   this is the file where function main resides.
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "winscard.h"
#include "utils.h"
#include "gsm-constants.h"
#include "pcsc-wrappers.h"
#include "dirtree.h"
#include "xml-results.h"

#define active_protocol SCARD_PCI_T0

int  dumping_mode;      // '0' => FULL ACQUISITION OF SIM CARD
                        // '1' => PARTIAL ACQUISITION OF SIM CARD

int print_auth_code_status(SCARDHANDLE hCard, SCARD_IO_REQUEST* dwActiveProtocol);
int chv1_verification_ok(SCARDHANDLE hCard, SCARD_IO_REQUEST* dwActiveProtocol);

int main (int argc, char const* const* argv) {
  int app_var;
  int chv1_verified = 0;
  int dont_verify_chv1 = 0;
  time_t t1, t2;

  //##
  //##   VARIABLES DEFINITION
  //##

  SIM_CARD* seized_card; //It will contain seized SIM card informations

  RESPONSE* atr = malloc(sizeof(RESPONSE)); //It will contain the ATR
                                            //from the card.

  //Connection context
  SCARDCONTEXT hContext;

  //List of available readers
  LPSTR mszReaders;

  //Connection handler
  SCARDHANDLE hCard;

  //File that will store the xml formatted results
  FILE* xml_output_file;


  //##
  //##   1ST SECTION: PARSING OF COMMAND LINE PARAMETER
  //##


  //##
  //##   2ND SECTION: SIM CARD READER(S) SETUP AND CONNECTION(S) SETUP
  //##

  hContext = SIM_Establish_Context(SCARD_SCOPE_SYSTEM);
  mszReaders = Detect_Readers(hContext);

  //This call functions only when there is only one active reader. To
  //activate the scan on every reader attached to the system, it is
  //necessary to parse mszReaders.
  hCard = SIM_Connect(hContext,mszReaders);
  printf("\n\nPress a key to see card status...\n\n");
  getchar();
  atr = SIM_Status(hCard);
  SIM_Begin_Transaction(hCard);



  //##
  //##   3RD SECTION: PART A - AUTHENTICATION
  //##

  printf("\n\nPress a key to enter authentication session...\n\n");
  getchar();

  if(print_auth_code_status(hCard, active_protocol)) {
    while(!chv1_verified && !dont_verify_chv1) {
      printf("\n\n");
      printf("\n############################################################\n");
      printf("CHV1 ON THE CARD IS ENABLED. WHAT DO YOU WANT TO DO ?\n");
      printf("\n\tType 1 to do CHV1 verification\n");
      printf("\n\tType 2 to go ahead without CHV1 verification (only content of files with access condition equal to ALW will be extracted)\n");
      printf("\n\tType 3 to exit");
      printf("\n############################################################\n");
      scanf("%i", &app_var);
      switch(app_var) {
        case 1: {
          chv1_verified = chv1_verification_ok(hCard, active_protocol);
          break;
        }
        case 2: {
          dont_verify_chv1 = 1;
          break;
        }
        case 3: {
          exit(EXIT_SUCCESS);
          break;
        }
        default: printf("\nPlease make a choice beetween 1 and 3.\n");
      } // switch()
    } // while()
  } // if()


  //##
  //##   3RD SECTION: PART B - FILES AND DIRECTORY TREE EXTRACTION
  //##

  printf("\n\nPress a key to extract card directory tree...\n\n");
  getchar();

  printf("\n\n");
  printf("*******************************************************************************\n");
  printf("*                                                                             *\n");
  printf("* EXTRACTION OF FILES AND DIRECTORIES REACHABLE FROM MASTER FILE UNDER WAY... *\n");
  printf("*                                                                             *\n");
  printf("*******************************************************************************\n");
  printf("\n\n");

  printf("\nDEBUG: entering create_directory_tree...\n");

  printf("\n\nSelect Acquisition mode for SIMbrush tool... \n\n");
  printf("'0' for FULL acquisition.\n\n");
  printf("'1' for PARTIAL acquisition.\n\n");
  scanf("%d", &dumping_mode);


  // dumping_mode = 0 ==> FULL ACQUISITION
  // dumping_mode = 1 ==> PARTIAL ACQUISITION


  (void) time(&t1); // Starting time

  seized_card = create_SIM_card(hCard, active_protocol);
  (*seized_card).raw_atr = atr;

  (void) time(&t2); // Ending time

  printf("\nExtraction time is %d minute, that is %d second \n",
         (int)((t2-t1)/60), (int)(t2-t1) );

  //##
  //##   4TH SECTION: XML FORMATTING AND OUTPUT OF THE RESULTS
  //##

  //This has to be improved changing the name of the output file at every run,
  //so that it is unambiguously named and cannot overwrite older files.
  //If a conflict arise, it should be prompted to the user a request about
  //what to do.
  xml_output_file = fopen("./results/xml-results/image.xml","w");

  if(xml_output_file == NULL) {
    printf("DEBUG: cannot open xml results file.");
    exit(1);
  }

  create_xml_results(xml_output_file, seized_card);
  fclose(xml_output_file);

  //##
  //##   5TH SECTION: CARD(S) DISCONNECTION
  //##

  SIM_End_Transaction(hCard);
  SIM_Disconnect(hCard);
  SIM_Release_Context(hContext);

  return 0;
}

//
// FUNCTION NAME: print_auth_codes_status
//
// DESCRIPTION: this function print on the screen the status of the
//              authentication codes of the sim card.
//
// INPUT PARAMETERS:
//   None.
//
// OUTPUT PARAMETERS: int
//   Returns 1 if CHV1 is enabled, 0 otherwise.
//
int print_auth_code_status(SCARDHANDLE hCard,
                           SCARD_IO_REQUEST* dwActiveProtocol) {

  int app;
  RESPONSE* resp;

  //Get card CHV abilitation status
  resp = gsm_select(hCard, dwActiveProtocol,0x3F00);
  if(blist_get_element(resp,-2) == SW1_CORRECT_WITH_RESPONSE) {
    resp = gsm_get_response(hCard, dwActiveProtocol,
                            blist_get_element(resp,-1));
    printf("\n\n");
    printf("*****************************************\n");
    printf("*                                       *\n");
    printf("*   AUTHENTICATION STATUS OF THE CARD   *\n");
    printf("*                                       *\n");
    printf("******************************************\n");
    printf("\n\n");

    printf("NUMBER OF CHVs, UNBLOCK CHVs AND ADMINISTRATIVE CODES\t=\t%i\n",
           blist_get_element(resp,16));

    printf("\nCHV1 STATUS (PIN1)\t\t=\t");
    app = 0x80; //binary value of this mask = 10000000
    if(blist_get_element(resp,18) & app)
      printf("INITIALIZED,\t");
    else printf("DEACTIVATED,\t");
    app = 0x0f; //binary value of this mask = 00001111
    printf("TRIES LEFT = %i\n", blist_get_element(resp,18) & app);

    printf("\nUNBLOCK CHV1 STATUS (PUK1)\t=\t");
    app = 0x80; //binary value of this mask = 10000000
    if(blist_get_element(resp,19) & app)
      printf("INITIALIZED,\t");
    else printf("DEACTIVATED,\t");
    app = 0x0f; //binary value of this mask = 00001111
    printf("TRIES LEFT = %i\n", blist_get_element(resp,19) & app);

    printf("\nCHV2 STATUS (PIN2)\t\t=\t");
    app = 0x80; //binary value of this mask = 10000000
    if(blist_get_element(resp,20) & app)
      printf("INITIALIZED,\t");
    else printf("DEACTIVATED,\t");
    app = 0x0f; //binary value of this mask = 00001111
    printf("TRIES LEFT = %i\n", blist_get_element(resp,20) & app);

    printf("\nUNBLOCK CHV2 STATUS (PUK2)\t=\t");
    app = 0x80; //binary value of this mask = 10000000
    if(blist_get_element(resp,21) & app)
      printf("INITIALIZED,\t");
    else printf("DEACTIVATED,\t");
    app = 0x0f; //binary value of this mask = 00001111
    printf("TRIES LEFT = %i\n", blist_get_element(resp,21) & app);

    printf("\nCHV1 abilitation state is:\t");
    app = 0x80; //binary value of this mask = 10000000
    if(blist_get_element(resp,13) & app) {
      printf("DISABLED\n");
      return(0);
    }
    else {
      printf("ENABLED");
      return(1);
    }
  }
  else {
    perror("IMPOSSIBLE TO SELECT MF: card damaged, not GSM, badly inserted into the reader or not supported.");
    exit(EXIT_FAILURE);
  }
}

//
// FUNCTION NAME: chv1_verification_ok
//
// DESCRIPTION: this function get CHV1 from the user and send it to the card
//              for verification.
//
// INPUT PARAMETERS:
//   None.
//
// OUTPUT PARAMETERS:
//   Returns 1 if verification is successful, 0 otherwise.  Also exits if user does not want to continue with CHV1 verification
//
// NOTES:
//   - This function verifies exclusively CHV1. If CHV2 verification will be
//     needed in the future, then the function could be easily changed.
//
int chv1_verification_ok(SCARDHANDLE hCard, SCARD_IO_REQUEST* dwActiveProtocol) {
  printf("\n\n");
  printf("\n같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같\n");
  printf("INSTRUCTIONS:\n");
  printf("ENTER THE PIN1 CODE (ex. 1234)\n");
  printf("WARNING: DON'T GO AHEAD IF YOU DON'T REALLY KNOW CHV1!\n");
  printf("SENDING RANDOMLY CHOSEN CHVs BLOCKS YOUR CARD IN 3 TRIES!!!");

  //PIN CODING:
  //The coding for the PIN1 is determined by hexadecimal representation of
  //pin's number with '0xff' padding byte; for example the pin
  //'1234' in decimal notation will be converted in '31323334ffffffff'

  BYTE_LIST* chv1 = create_b_list();
  int i;
  for(i=0; i<8; i++) {
    blist_add_element(chv1, 0xFF);
  }

  int const MAX_PIN = 8; // chars
  char pin[MAX_PIN + 1];
  char const* pin_scanf_format_string = "%8s";

  printf("\nEnter CHV1 code (PIN1): ");
  scanf(pin_scanf_format_string, pin);

  for(i=0;i<strlen(pin);i++){
    BYTE app = pin[i]; // PIN is converted into hexadecimal representation (i.e. '0'->'0x30')
    blist_set_element(chv1,i,app); // The first strlen(pin) are changed into hexadecimal value of PIN
  }

  getchar();

  printf("\nThe codified CHV1 is: ");
  for(i=0; i<8; i++) {
    printf("%.2X",blist_get_element(chv1,i));
  }
  printf("\n\n");

  char app_char = 'X';
  while(app_char != 'N' && app_char !='Y') {
    printf("\nAre you sure you want to continue (Y/N)?\n");
    scanf("%c", &app_char);
  }

  if(app_char == 'N') {
    printf("\nExiting program...\n");
    exit(EXIT_FAILURE);
  }
  else { /* app_char == 'Y' */
    RESPONSE* sim_response = gsm_verify_chv(hCard, dwActiveProtocol, chv1);

    if((blist_get_element(sim_response,-2) == 0x90) && (blist_get_element(sim_response,-1) == 0x00)) {
      printf("\nCHV1 SUCCESSFULLY VERIFIED.\n");
      return 1;
    }
    else {
      printf("\nCHV1 VERIFICATION FAILED.\n");
      print_auth_code_status(hCard,dwActiveProtocol);
      return 0;
    }
  }
}

