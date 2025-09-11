# SDeMMC Health Reader
This simple program can read "vendor proprietary" health reports.
Requires native mmc interface (eg : /dev/mmcblkx ; NOT /dev/sdx)
Compilation : gcc smart.c -o smart

# Supported & Tested eMMC Devices :
# Samsung old MoviNAND Report:
| ID | eMMC Version | IC Model | Nand Type |
| - | - | - | - |
| M4G1GM | 4.3 | KLM4G1EEHM | 32nm MLC |
| M8G4DE | 4.3 | KLM8G4DEHE | 32nm MLC |
| M8G2FB | 4.41 | KLM8G2FE3B | 21nm MLC |
| M8GYE4 | 4.41 | KLM8G2YE4C | 21nm TLC |
| SJS00A | 4.41 | KMSJS000KA | 21nm MLC |
| VTU00M | 4.5 | KMVTU000LM | 21nm MLC |
| Q313MB | 5.0 | KMQ310013M | 16nm MLC |
| -      | 5.0 | KMR21000AM | 16nm MLC | 
| -      | 5.0 | KMR21000BM | 16nm MLC | 
| V2W00M | 5.0 | KMV2W000LM | 19nm MLC | 

| Samsung Evo+ 32G | SD | MB-MC32D | 16nm TLC |

# Samsung new SMART Report:
| ID | eMMC Version | IC Model | Nand Type | Report |
| - | - | - | - | - |
| QE63MB | 5.1 | KMQE60013M | ? MLC | VSM + OSV |

# Hynix old (V0) Report:
| ID | eMMC Version | IC Model |
| - | - | - |

# Hynix new (V1) Report:
| ID | eMMC Version | IC Model | Nand Type |
| - | - | - | - |
| hB8aP> | 5.1 | H26M62002JPR | 1znm MLC |

# Toshiba Report:
| ID | eMMC Version | IC Model | Nand Type | Report |
| - | - | - | - | - |
| 008G4B | 4.41 | THGBM4G6D2HBAIR | 24nm MLC | Health Only |
| 008G92 | 4.5  | THGBM5G6A2JBAIR | 19nm MLC | Health + Erase |
| 016G92 | 4.5  | THGBMAG7A2JBAIR | 19nm MLC | Health + Erase |
| 008GE0 | 5.0  | THGBMBG6D1KBAIL | 19nm MLC | Health + Erase |
| 032G32 | 5.1  | THGBMHG8C2LBAIL | ? MLC | Health + Erase |
| 032G34 | 5.1  | THGBMHG8C4LBAIL | 19nm MLC | Health + Erase |
# WD/Sandisk Report:
| ID | eMMC Version | IC Model |
| - | - | - |
| iNAND® 7232 | 5.1 | SDINADF4-XXG |
| iNAND® EM111 | 5.1 | SDINADF4-XXG |

# SMI SD Cards :

| Vendor | Model | SD Controller | CMD56 ARG |
| - | - | - | - |
| ADATA | AUSDX128GUICL10A1-RA1  | SM2705 / SM2707? | 0x110005F1 |
| PNY   | PNY ELITE U1           | SM2705 / SM2707? | 0x110005F1 |

# Not Working Devices : 

| Vendor | Family | eMMC Version | IC Model |
| - | - | - | - |
| SAMSUNG* | MoviNAND® 4.5 | 4.5 | KLMAG2GEAC-B001 |
| SAMSUNG* | MoviNAND® 5.0 | 5.0 | KLMAG2GEAC-B031** |
| SAMSUNG* | MoviNAND® 5.0 | 5.0 | Most Of TLC 5.0 eMMC's |

1* : Do Not Run Code If OS Runs From SAMSUNG eMMC . Sometimes eMMC can't exit from report mode. System will hang.  
2* : Same model eMMC but 5.0 Version. Supports EXT_CSD Life report but still no MoviNAND S.M.A.R.T Report
