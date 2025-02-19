#include <stdio.h>
//#include <conio2.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "meuconio.h"
#include "CriadorDeMenus.h"

int main (void) {
	
	Menu(25, 55, 3, 15, 0);
	printf("%d", Navegacao(55, 3));
	
	return 0;
}
