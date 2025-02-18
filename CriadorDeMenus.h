//Requerimentos: [CONIO2.H] [STDLIB.H] [STDIO.H] [CTYPE.H] [STRING.H]
#include <sys/stat.h> //Utilizado para criação do diretório "ArquivosDoMenu"

//Constantes referentes a distancia da borda esquerda da tela
#define DISTANCIA_BORDA_LINHA 2
#define DISTANCIA_BORDA_COLUNA 3

#define QUANTIDADE_MAXIMA_CARACTER_OPCAO 15
#define DISTANCIA_ENTRE_OPCOES 4
#define DISTANCIA_OPCAO_BORDA_MENU_LINHA 2

void Moldura(int ColunaInicial, int LinhaInicial, int ColunaFinal, int LinhaFinal,int CorLinha,int CorFundo){
	
	textcolor(CorLinha);
	textbackground(CorFundo);
	gotoxy(ColunaInicial, LinhaInicial); printf("%c", 201);
	gotoxy(ColunaFinal, LinhaInicial); printf("%c", 187);
	gotoxy(ColunaInicial, LinhaFinal); printf("%c", 200);
	gotoxy(ColunaFinal, LinhaFinal); printf("%c", 188);
	
	for(int i = ColunaInicial+1; i < ColunaFinal; i++){
		gotoxy(i,LinhaInicial); printf("%c", 205);
		gotoxy(i,LinhaFinal); printf("%c", 205);
	}
	for(int i = LinhaInicial+1; i < LinhaFinal; i++){
		gotoxy(ColunaInicial,i); printf("%c", 186);
		gotoxy(ColunaFinal,i); printf("%c", 186);
	}
	textcolor(7);
	textbackground(0);
	
}

int VerificaArquivosMenu(void) {
	FILE *PtrArquivo = fopen("ArquivosDoMenu/Opcoes.dat", "r");
	
	if(PtrArquivo == NULL) {
		char Opcao;
		
		fclose(PtrArquivo);
		system("cls");
		textcolor(RED);	printf("--ARQUIVOS DO MENU NAO ENCONTRADOS--\n\n"); textcolor(WHITE);
		printf("Deseja cria-los? [S] [N]: ");
		Opcao = toupper(getche());
		
		if(Opcao == 'S')
			return 1;
		
		while(Opcao != 'N') {
			
			system("cls");
			textcolor(RED);	printf("--OPCAO INVALIDA--\n\n"); textcolor(WHITE);
			printf("Deseja cria-los? [S] [N]: ");
			Opcao = toupper(getche());
			
			if(Opcao == 'S')
				return 1;
		}
	}
	
	return 0;
}

void CriaArquivosMenu(int NumeroDeOpcoes) {
	
	char Opcao[QUANTIDADE_MAXIMA_CARACTER_OPCAO];
		
		clrscr();
		if(mkdir("ArquivosDoMenu") == -1) {
			
			textcolor(RED); 
			printf("--ERRO AO CRIAR O DIRETORIO--");
			textcolor(WHITE);
			
		}
		
		else {
			FILE *PtrArquivo = fopen("ArquivosDoMenu/Opcoes.dat", "w");
			
			mkdir("ArquivosDoMenu");
			printf("--NOMEAMENTO DE OPCOES--\n");
			for(int i = 1; i <= NumeroDeOpcoes; i++) {
				
				printf("\nInforme a %d Opcao: ", i);
				fflush(stdin);
				gets(Opcao);
				fputs(Opcao, PtrArquivo);
				fputc('\0', PtrArquivo);
				 
			}
			textcolor(GREEN); printf("\n\n--NOMES REGISTRADOS--\n"); textcolor(WHITE);
			fclose(PtrArquivo);
			
		}
		
		
		getche();
		
		system("cls");
}

void Menu(int TamanhoHorizontal, int TamanhoVertical, int NumeroDeOpcoes, int CorLinha, int CorFundo) {
	
	if(VerificaArquivosMenu()) 
		CriaArquivosMenu(NumeroDeOpcoes);
	
	Moldura(DISTANCIA_BORDA_COLUNA, DISTANCIA_BORDA_LINHA, TamanhoVertical, TamanhoHorizontal, CorLinha, CorFundo);
	char CaracterDaOpcao;
	FILE *PtrOp = fopen("ArquivosDoMenu/Opcoes.dat", "r");
	
	for(int i = 1; i <= NumeroDeOpcoes + 1; i++) {
		Moldura(TamanhoVertical / 2 - (QUANTIDADE_MAXIMA_CARACTER_OPCAO / 2), DISTANCIA_OPCAO_BORDA_MENU_LINHA + (DISTANCIA_ENTRE_OPCOES * i), (TamanhoVertical / 2 - (QUANTIDADE_MAXIMA_CARACTER_OPCAO / 2)) + QUANTIDADE_MAXIMA_CARACTER_OPCAO, DISTANCIA_OPCAO_BORDA_MENU_LINHA + (DISTANCIA_ENTRE_OPCOES * i) + 2, CorLinha, CorFundo);
		gotoxy(TamanhoVertical / 2 - (QUANTIDADE_MAXIMA_CARACTER_OPCAO / 2) + 2,DISTANCIA_OPCAO_BORDA_MENU_LINHA + (DISTANCIA_ENTRE_OPCOES * i) + 1);
		
		CaracterDaOpcao = fgetc(PtrOp);
		while(CaracterDaOpcao != '\0' && !feof(PtrOp)) {
			printf("%c", CaracterDaOpcao);
			CaracterDaOpcao = fgetc(PtrOp);
		}
		
	}
	fclose(PtrOp);
	
	printf("ENCERRAR");
	printf("\n\n");
}	

int Navegacao(int TamanhoVertical, int NumeroDeOpcoes) {
	NumeroDeOpcoes++;
	int PosicaoAtual = DISTANCIA_OPCAO_BORDA_MENU_LINHA + DISTANCIA_ENTRE_OPCOES + 1;
	char Tecla;
	
	gotoxy(TamanhoVertical / 2 - (QUANTIDADE_MAXIMA_CARACTER_OPCAO / 2) + 1, PosicaoAtual);
		
	do {
		
		textcolor(0);
		Tecla = toupper(getche());
		
		if(Tecla == 'W') {
			if(PosicaoAtual == DISTANCIA_OPCAO_BORDA_MENU_LINHA + DISTANCIA_ENTRE_OPCOES + 1)
				PosicaoAtual = DISTANCIA_OPCAO_BORDA_MENU_LINHA + (DISTANCIA_ENTRE_OPCOES * NumeroDeOpcoes) + 1 ;
			else
				PosicaoAtual -= DISTANCIA_ENTRE_OPCOES;
		}
		
		else if(Tecla == 'S') {
			if(PosicaoAtual == DISTANCIA_OPCAO_BORDA_MENU_LINHA + (DISTANCIA_ENTRE_OPCOES * NumeroDeOpcoes) + 1)
				PosicaoAtual = DISTANCIA_OPCAO_BORDA_MENU_LINHA + DISTANCIA_ENTRE_OPCOES + 1;
			else
				PosicaoAtual += DISTANCIA_ENTRE_OPCOES;
		}
		
		gotoxy(TamanhoVertical / 2 - (QUANTIDADE_MAXIMA_CARACTER_OPCAO / 2) + 1, PosicaoAtual);
		
	}while(Tecla != 13);
	
	textcolor(WHITE);
	PosicaoAtual = PosicaoAtual - (DISTANCIA_BORDA_COLUNA + DISTANCIA_ENTRE_OPCOES);
	return PosicaoAtual;
	
}

