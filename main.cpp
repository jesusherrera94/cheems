#include <windows.h>
#include <iostream>
#include <fstream>
#include <wchar.h>
#include <locale.h>
#include "ios.h"
#include "validations.h"
#include "persona.h"
#include "usuarios.h"
#include "producto.h"
#include "utilities.h"
using namespace std;

string ExePath() {
       char buffer[MAX_PATH];
       GetModuleFileName( NULL, buffer, MAX_PATH );
       string::size_type pos = string( buffer ).find_last_of( "\\/" );
       return string( buffer ).substr( 0, pos-9);
}

int main()
{
    setlocale(LC_ALL, "spanish");
  /*Escritura
  ofstream file;
  file.open(ExePath() + "/BD/archivo.txt");
  file << "primera l�nea\n";
  file << "segunda l�nea\n";
  file << "tercera l�nea\n";
  file.close();
 */
/* prueba de usuarios
Validations vt;

cout<<vt.isUserExists(0001);
*/
    return 0;
}



using namespace std;



