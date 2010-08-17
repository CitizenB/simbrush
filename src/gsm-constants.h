/******************************************************************************
 *
 * NAME:          gsm-constants.h
 *
 * AUTHORS:       Fabio Casadei
 *                fabio.casadei@mercurio-ws.com
 *
 *                Antonio Savoldi
 *                antonio.savoldi@ing.unibs.it
 *
 * FILE TYPE:     Header file
 *
 * DESCRIPTION:   this file contains the definition of constants defined in
 *                GSM standards 
 *
 *****************************************************************************/

// INSTRUCTION CLASS CODES DEFINITION

#define GSM_CLASS 0xA0


// INSTRUCTION CODES DEFINITION

#define SELECT            0xA4
#define STATUS            0xF2
#define READ_BINARY       0xB0
#define UPDATE_BINARY     0xD6
#define READ_RECORD       0xB2
#define UPDATE_RECORD     0xDC
#define SEEK              0xA2
#define INCREASE          0x32
#define VERIFY_CHV        0x20
#define CHANGE_CHV        0x24
#define DISABLE_CHV       0x26
#define ENABLE_CHV        0x28
#define UNBLOCK_CHV       0x2C
#define INVALIDATE        0x04
#define REHABILITATE      0x44
#define RUN_GSM_ALGORITHM 0x88
#define SLEEP             0xFA
#define GET_RESPONSE      0xC0
#define TERMINAL_PROFILE  0x10
#define ENVELOPE          0xC2
#define FETCH             0x12
#define TERMINAL_RESPONSE 0x14


// STATUS WORD 1 (SW1) CODES DEFINITION

#define SW1_CORRECT                         0x90 // commands correctly executed
#define SW1_CORRECT_WITH_PROACTIVE_COMMAND  0x91
#define SW1_CORRECT_SIM_DATA_DOWNLOAD_ERROR 0x9E
#define SW1_CORRECT_WITH_RESPONSE           0x9F

#define SW1_SAT_BUSY 0x93 // commands postponed

#define SW1_MEMORY_NOTE 0x92 // answer regarding memory

#define SW1_REFERENCES 0x94 // answer regarding references

#define SW1_SECURITY 0x98 // answer regarding security management

#define SW1_ERROR_P3                0x67 // application independent errors
                                         // signalling
#define SW1_ERROR_P1_P2             0x6B
#define SW1_ERROR_INSTRUCTION_CODE  0x6D
#define SW1_ERROR_INSTRUCTION_CLASS 0x6E
#define SW1_ERROR_TECHNICAL         0x6F


// STATUS WORD 2 (SW2) CODES DEFINITIONS
// Security related:
#define SW2_CHV_NOT_INITIALIZED            0x02
#define SW2_BAD_ACCCOND_VERIFY_MORE_TRIES  0x04
#define SW2_CONTRADICTION_CHV              0x08
#define SW2_CONTRADICTION_INVALIDATION     0x10
#define SW1_VERIFY_NO_TRIES_CHV_BLOCKED    0x40
#define SW1_INCREASE_NOT_ALLOWED           0x50


// MF, DF AND EF IDENTIFIERS DEFINITION        <--- DA TOGLIERE ?

#define MF          0x3FFF // Master File

#define DFgsm       0x7F20 // Dedicated Files (Directory)
#define DFtelecom   0x7F10

#define EFiccid     0x2FE2 // Elementary Files under MF

#define EFimsi      0x6F07 // Elementary Files under DFgsm

#define EFadn       0x6F3A // Elementary Files under DFtelecom


// EF ACCESS CONDITION CODES DEFINITION (DF and MF does not have such
// permissions in the present version of the GSM)

#define ACC_ALW  0x00 // always
#define ACC_CHV1 0x01 // after CHV1 verification
#define ACC_CHV2 0x02 // after CHV2 verification
#define ACC_RFU  0x03
#define ACC_ADM4 0x04 // administrative codes (ALW, CHV1, CHV2 and NEV can be
                      // used as administrative codes too): they have meaning
                      // to the administrative authority only
#define ACC_ADM5 0x05
#define ACC_ADM6 0x06
#define ACC_ADM7 0x07
#define ACC_ADM8 0x08
#define ACC_ADM9 0x09
#define ACC_ADMA 0x0A
#define ACC_ADMB 0x0B
#define ACC_ADMC 0x0C
#define ACC_ADMD 0x0D
#define ACC_ADME 0x0E
#define ACC_NEV  0x0F // never


// FILE TYPE CODES DEFINITION

#define FTYP_RFU 0x00
#define FTYP_MF  0x01
#define FTYP_DF  0x02
#define FTYP_EF  0x04


// FILE STRUCTURE CODES DEFINITION

#define FSTR_TRANSP 0x00
#define FSTR_LINFIX 0x01
#define FSTR_CYCLIC 0x03


// FILE STATUS CHECKING DEFINITIONS

#define FSTATE_MASK   0x05 // This mask anded with byte 12 of GET RESPONSE
                           // result gives:
#define FSTATE_DEATH  0x00 // --> invalidated and not readable nor updatable
#define FSTATE_ASLEEP 0x04 // --> invalidated but readable and updatable
#define FSTATE_ALIVE  0x01 // --> valid but not readable nor updatable if
                           //     invalidated
#define FSTATE_AWAKEN 0x05 // --> valid and readable and updatable when
                           //     invalidated

// GSM RELATED MESSAGES AND WARNINGS

#define WRN_NO_CHV_INITIALIZED "No CHV has been initialized."
#define WRN_ACCCOND_NOT_FULLFILLED "Access condition non fullfilled."
#define WRN_BAD_CHV_VERIFY_MORE_TRIES "Unsuccessful CHV verification, at least one attempt left."
#define WRN_BAD_UNBLOCK_VERIFY_MORE_TRIES "Unsuccessful UNBLOCK CHV verification, at least one attempt left."
#define WRN_AUTH_FAILED "Authentication failed."
#define WRN_BROKEN_CHV_CONSTRAINT "In contradiction with CHV status."
#define WRN_BROKEN_INVALIDATION_CONSTRAINT "In contradiction with invalidation status."
#define WRN_BAD_CHV_VERIFY_NO_TRIES "Unsuccessful CHV verification, no attempt left."
#define WRN_BAD_UNBLOCK_VERIFY_NO_TRIES "Unsuccessful UNBLOCK CHV verification, no attempt left."
#define WRN_CHV_BLOCKED "CHV blocked."
#define WRN_UNBLOCK_CHV_BLOCKED "UNBLOCK CHV blocked."
#define WRN_INCREASE_NOT_ALLOWED "Increase cannot be performed, Max value reached."

extern long int EF_list[];
extern int EF_list_size;
