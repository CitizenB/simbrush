
// moved here from gsm-constants.h

// GSM STANDARD FILE
long int EF_list[] = {
                        
  //Standard Dedicated Fle (DF)
                        
  0x7F20, // GSM                  :: MF -> DF_GSM                 
  0x7F10, // TELECOM              :: MF -> DF_TELECOM                     
  0x7F22, // IS-41                :: MF -> DF_IS-41
  0x7F23, // FP-CTS               :: MF -> DF_FP-CTS
                        
  0x5F50, // GRAPHICS             :: MF -> DF_TELECOM -> DF_GRAPHICS
                        
  0x5F30, // IRIDIUM
  0x5F31, // GLOBST
  0x5F32, // ICO
  0x5F33, // ACeS                 :: MF -> DF_GSM 
                        
  0x5F40, // EIA/TIA-553
  0x5F60, // CTS
  0x5F70, // SoLSA                :: MF -> DF_GSM
                        
  0x5F3C, // MExE                 :: MF -> DF_GSM -> EF_MExE
                        
                        
  //Standard Elementary File (EF)
                        
  // MF(0x3F00) -> EF_MF
  0x2FE2, // ICCID
  0x2F05, // ELP
                        
  // MF -> DF_TELECOM(0x7F10) -> EF_TELECOM
  0x6F3A, // ADN
  0x6F3B, // FDN
  0x6F3C, // SMS
  0x6F3D, // CCP
  0x6F40, // MSISDN
                        
  0x6F42, // SMSP
  0x6F43, // SMSS
  0x6F44, // LND
  0x6F47, // SMSR
  0x6F49, // SDN
                        
  0x6F4A, // EXT1
  0x6F4B, // EXT2
  0x6F4C, // EXT3
  0x6F4D, // BDN
  0x6F4E, // EXT4
                        
  // MF(0x3F00) -> DF_TELECOM(0x7F10) -> DF_GRAPHICS(0x5F50) -> EF_IMG
  0x4F20,
                        
  // MF -> DF_GSM(0x7F20) -> DF_SoSLA(0x5F70) -> EF_SoSLA
  0x4F30, // SAI
  0x4F31, // SLL
                        
  // MF -> DF_GSM(0x7F20) -> DF_MExE(0x5F3C) -> EF_MExE
  0x4F40, // MExE-ST
  0x4F41, // ORPK
  0x4F42, // ARPK
  0x4F43, // TPRPK
                        
  // MF -> DF_GSM(0x7F20) -> EF_GSM
  0x6F05, // LP
  0x6F07, // IMSI
  0x6F20, // Kc
  0x6F30, // PLMNsel
  0x6F31, // HPPLMN
  0x6F37, // ACMmax

  0x6F38, // SST
  0x6F39, // ACM
  0x6F3E, // GID1
  0x6F3F, // GID2
  0x6F41, // PUCT
  0x6F45, // CBMI

  0x6F46, // SPN
  0x6F48, // CBMID
  0x6F74, // BCCH
  0x6F78, // ACC
  0x6F7B, // FPLMN
  0x6F7E, // LOCI

  0x6FAD, // AD
  0x6FAE, // PHASE
  0x6FB1, // VGCS
  0x6FB2, // VGCSS
  0x6FB3, // VBS
  0x6FB4, // VBSS

  0x6FB5, // eMLPP
  0x6FB6, // AAeM
  0x6FB7, // ECC
  0x6F50, // CBMIR
  0x6F51, // NIA
  0x6F52, // KcGPRS

  0x6F53, // LOCIGPRS
  0x6F54, // SUME
  0x6F60, // PLMNwAcT
  0x6F61, // OPLMNwAcT
  0x6F62, // HPLMNAcT
  0x6F63, // CPBCCH

  0x6F64 // INVSCAN
                                                
};                   

int EF_list_size = sizeof(EF_list)/sizeof(EF_list[0]);
