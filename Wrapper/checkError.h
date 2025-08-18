#pragma once

//É}ÉNÉçíËã`
#ifdef DEBUG
#define glCheckError(func) func;checkError();
#else
#define glCheckError(func) func;
#endif

void checkError();