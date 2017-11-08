#ifndef CONVERTOR_H
#define CONVERTOR_H

#include "opcodestream.h"

char* binaryOfOpcode(OpcodeStream *OS);
char* convertOPCodes(OpcodeStream *OS, int debug);

#endif
