/*
// Crypto++
 #include "cryptlib.h"
 
 // std
 #include <iostream>
 
 void DumpMessage(CryptoPP::BufferedTransformation& bt)
 {
     using namespace std;
     
     static char const* szHexDigits = "0123456789abcdef";
     byte b;
     while (bt.AnyRetrievable())
     {
         if (!bt.Get(b))
             throw "Error: AnyRetrievable() returned true, "
                   "so this shouldn't happen.";

         // It is much easier to implement this using HexEncoder;
         // however, let's not get into that just yet. The below code
         // could do some special kind of processing that is not
         // supported by an off-the-shelf Filter class.

         cout << szHexDigits[(b >> 4) & 0x0f]
              << szHexDigits[b & 0x0f]
              << ' ';
     }
 }
 
 // Crypto++
 #include "filters.h"
 
 int main()
 {
     using namespace CryptoPP;
 
     char const* szMessage = "How do you do?";
     DumpMessage(StringSource(szMessage, true));
         // If we constructed StringSource with 'false' instead of 'true',
         // StringSource wouldn't call its PumpAll() method on construction,
         // and no data would be extractable from the StringSource object
         // until someone called the object's Pump() or PumpAll() method.
 
     return 0;
 }
 */