//BIBLIOTECAS UTILIZADAS
#include <iostream>				//BIBLIOTECA NATIVA 
#include <time.h>				//NECESSÁRIA PARA O FUNCIONAMENTO DE NÚMEROS RANDÔMICOS - SRAND
#include <windows.h>			//NECESSÁRIA PARA O FUNCIONAMENTO DA FUNÇÃO - GOTOXY
#include <conio.h>				//NECESSÁRIA PARA O FUNCIONAMENTO DAS FUNÇÕES DE TEXTCOLOR E TEXTBACKGROUND
#include <string.h>				//NECESSÁRIA PARA O FUNCIONAMENTO DAS FUNÇÕES DE STRING

//INÍCIO DAS DEFINES - VISUAL
/////////////////////////////////
#define CORMODIFICADA YELLOW	//COR DO TEMA
#define CORPADRAO BLACK			//COR PADRÃO DE FUNDO
#define COLOR_BASE YELLOW	//DEFINE A COR DA FONTE DAS CELULAS QUE PERMITIRÃO ALTERAÇÕES
#define COLOR_ALL WHITE			//DEFINE A COR DA FONTE DO RESTANTE DAS CELULAS

//DEFINES DO JOGO
/////////////////
#define APP_VERSION "1.40"
#define PAUSE_MSG "Pressione qualquer tecla para continuar..."
#define COPY_RIGHT "DESENVOLVEDORES - FACEAR - ALUNOS : EBNER SILVA & LEONARDO GRANDI - 2016"

//DEFINES MATRIZ TRIGU'S SOFTWARE
#define MAX_LEN 9
#define MAX_GRD 3
#define AUTO_PREENCHER 0

//ENUMERAÇÃO QUE DEFINE A ESTRUTURA DO TIPO DE CORES.
enum COLORS {
	BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN,
	LIGHT_GRAY, DARK_GRAY, LIGHT_BLUE, LIGHT_GREEN, LIGHT_CYAN,
	LIGHT_RED, LIGHT_MAGENTA, YELLOW, WHITE 
};

//TIPO DE DADOS PARA CONFIGURAÇÃO DE CORES
typedef enum COLORS color;

//RANKING
struct ranking{
char nome[50];
int pontos;	
};

///////////////////////
//VARIÁVEIS MATRIZ NOVA
int soma = 0;
int soma1 = 0;
int soma2 = 0;
int cont = 0;
///////////////////////
//VARIÁVEIS DE COORDENADAS.
int numero, linha, coluna, nivel;
int defcol = 2, deflin = 1;

////////////////////
//VARIÁVEIS DO JOGO
///////////////////
//VARIÁVEIS BOOLEANAS QUE INDICAM "NOVO JOGO", "FINAL DE JOGO" E "AJUDA".
bool novo, final, ajuda;

/////////////////
//VETORES DO JOGO
/////////////////
//ARRAY CONTENDO AS DIFICULDADES DO JOGO REFERENTE A CADA NÍVEL.
char *dificuldade[4] = {"INDEFINIDO","FACIL","MEDIO","DIFICIL"};

////////////////
//MATRIZES NOVAS
////////////////
//MATRIZ PRINCIPAL DE MODELO
int matriz[MAX_LEN][MAX_LEN] =
  {{ 3, 2, 0, 1, 1, 3, 3, 1, 1},
   { 1, 3, 1, 2, 2, 1, 1, 2, 0},
   { 1, 2, 1, 0, 3, 1, 3, 1, 2},
	 { 1, 3, 2, 3, 1, 1, 0, 2, 3},
   { 0, 1, 3, 3, 2, 0, 1, 1, 1},
   { 1, 2, 1, 2, 1, 1, 3, 2, 1},
	 { 3, 1, 3, 1, 3, 0, 0, 2, 1},
   { 1, 2, 1, 1, 2, 3, 1, 3, 2},
   { 2, 0, 1, 1, 2, 1, 1, 1, 3}};

//MATRIZ PRINCIPAL DE USO
int grade[MAX_LEN][MAX_LEN];

//MATRIZ TEMPORÁRIA
int mtztmp[MAX_LEN][MAX_LEN];

////////////////////////
//PROTÓTIPOS DE FUNÇÕES DO JOGO:
////////////////////////		
void resolucao1366x768();			//PROTÓTIPO DE FUNÇÃO PARA DEIXAR A TELA DO JOGO EM TELA GRANDE
void gotoxy(int x, int y);
void contorno();					//PROTÓTIPO DE FUNÇÃO PARA IMPRIMIR O CONTORNO DE TELA EM QUALQUER TELA
void bemvindo();					//PROTÓTIPO DE FUNÇÃO TELA BEM VINDO AO SUDOKU
void cadusu();						//PROTÓTIPO DE FUNÇÃO PARA CADASTRAR USUÁRIO
void menu();						//PROTÓTIPO DE FUNÇÃO PARA ABRIR O MENU INICIAL
int login();
//void dificuldade();					//PROTÓTIPO DE FUNÇÃO PARA ABRIR A TELA DE DIFICULDADE
void telainicial();

/////////////////////////////////////////////////////////////////////////////////
/// DEFINE CABEÇALHO DOS PROCEDURES/FUNÇÕES UTILIZADOS DA MATRIZ NOVA
////////////////////////////////////////////////////////////////////////////////
//void gotoxy(int col, int lin);		//PROTÓTIPO DE FUNÇÃO GOTOXY PARA CHAMAR A FUNÇÃO GOTOXY EM OUTRAS PARTES DO CÓDIGO
void textcolor(color iColor);		//PROTÓTIPO DE FUNÇÃO TEXTCOLOR: DEFINE A COR DE PRIMEIRO PLANO DOS TEXTOS
void textbackground(color iColor);	//PROTÓTIPO DE FUNÇÃO TEXTBACKGROUND: DEFINE A COR DE FUNDO DAS LETRAS.
void gerar_grade();
void print_str_color(char *s, color c);
void print_int_color(char *m, int i, color c);
bool checar_posicao(int lin, int col, int numero);
bool tenta_colocar(int i, int j, int k);
bool coordenada_valida(int lin, int col);
bool numerovalido(int numero);
void escrever(int lin, int col, int numero);
void jogar();
bool continuar();
void print_ajuda();
void terminar(int op);
int menu_nivel();
int ler_valor(char *prompt);
void tela_padrao(bool reset);
void desenha_tela();
void gerar_tela();
void somamatriz();

//ANOTAÇÕES EBNER
//Sleep(VALOR DO SLEEP);
//gotoxy(HORIZONTAL,VERTICAL);
//textbackground(BLUE); COR DE FUNDO
//textcolor(BLUE); COR DO TEXTO
//midi

//RANKING
int somar = 0;

//VARIÁVEIS GLOBAIS:
////////////////////
int sleepcb = 20;			//VARIÁVEL DO SLEEP DO PRINT DA LINHA DE CIMA E DE BAIXO
int sleeped = 20;			//VARIÁVEL DO SLEEP DO PRINT DA LINHA DA ESQUERDA E DA DIREITA	
int escolhamenu = 0;		//VARIÁVEL DA ESCOLHA DO MENU DA TELA DO BEM VINDO
int escolhamenu1 = 0;		//VARIÁVEL DA ESCOLHA DO MENU DA TELA DO MENU PRINCIPAL
//VARIAVEIS DO CADASTRO;
////////////////////////
char nome[20];
char login_cad[25];
char senha[100];
char password[10];
//VARIAVEIS DO LOGIN
////////////////////
char login_log[100], senha_log[100], str[100];
int tamanho=100;
char s[20];
int escolha = 0;

//VARIAVEIS DA FUNÇÃO DE COLOCAR ASTERISCO NO CAMPO DE SENHA
////////////////////////////////////////////////////////////
char c;
char pos = 0;
int linhabaixo = 169;
//int tamanho=100;
//char str[100];

//INÍCIO FUNÇÕES FIO
////////////////////
void gotoxy(int x, int y){			//FUNÇÃO GOTOXY PARA CHAMAR A FUNÇÃO GOTOXY EM OUTRAS PARTES DO CÓDIGO
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}

void textcolor(color iColor) {			//FUNÇÃO TEXTCOLOR: DEFINE A COR DE PRIMEIRO PLANO DOS TEXTOS
	HANDLE hl = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	BOOL b = GetConsoleScreenBufferInfo(hl, &bufferInfo);
	bufferInfo.wAttributes &= 0x00F0;
	SetConsoleTextAttribute (hl, bufferInfo.wAttributes |= iColor);
	return;
}

void textbackground(color iColor) {		//FUNÇÃO TEXTBACKGROUND: DEFINE A COR DE FUNDO DAS FONTES.
	HANDLE hl = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	BOOL b = GetConsoleScreenBufferInfo(hl, &bufferInfo);
	bufferInfo.wAttributes &= 0x000F;
	SetConsoleTextAttribute (hl, bufferInfo.wAttributes |= (iColor << 4));
	return;
}

//FIM FUNÇÕES FIO
/////////////////

void resolucao1366x768(){				//FUNÇÃO PARA DEIXAR A TELA DO JOGO EM TELA GRANDE
	keybd_event ( VK_MENU, 0x36, 0, 0 ); 
	keybd_event ( VK_RETURN, 0x1C, 0, 0 );
	keybd_event ( VK_RETURN, 0x1C, KEYEVENTF_KEYUP, 0 ); 
	keybd_event ( VK_MENU, 0x38, KEYEVENTF_KEYUP, 0 );	
}

void bemvindo(){						//FUNÇÃO TELA BEM VINDO AO SUDOKU

	for(int l = 0;l<169;l++){			//LINHA CIMA DA ESQUERDA PARA DIREITA / LINHA BAIXO DA DIREITA PARA ESQUERDA	
	gotoxy(l,1);
		Sleep(sleepcb);
		textbackground(CORMODIFICADA);
		printf(" ");
			
	gotoxy(linhabaixo,44);						
		printf(" ");
	linhabaixo--;
	}	
		
	for(int l = 2;l<44;l++){			//LINHA DIREITA DE CIMA PARA BAIXO  	//LINHA ESQUERDA DE CIMA PARA BAIXO	
		textbackground(CORPADRAO);
		gotoxy(168,l);  
	    Sleep(sleeped);						
		printf("%c\n",220);				
		gotoxy(1,l);
		Sleep(sleeped);				
		printf("%c\n",220);				//LINHA ESQUERDA DE CIMA PARA BAIXO	
	}	
	
	gotoxy(53,10);		
	printf("______ ________  ___           _   _ _____ _   _______ _____");
    gotoxy(53,11);
	printf("| ___ \\  ___|  \\/  |          | | | |_   _| \\ | |  _  \\  _  |");	
    gotoxy(53,12);
	printf("| |_/ / |__ | .  . |  ______  | | | | | | |  \\| | | | | | | |");
    gotoxy(53,13);
	printf("| ___ \\  __|| |\\/| | |______| | | | | | | | . ` | | | | | | |");
    gotoxy(53,14);
	printf("| |_/ / |___| |  | |          \\ \\_/ /_| |_| |\\  | |/ /\\ \\_/ /");
    gotoxy(53,15);
	printf("\\____/\\____/\\_|  |_/           \\___/ \\___/\\_| \\_/___/  \\___/");
    
	gotoxy(73,18);
	printf("  ___  _____");
    gotoxy(73,19); 
	printf(" / _ \\|  _  |");
    gotoxy(73,20);
	printf("/ /_\\ \\ | | |");
    gotoxy(73,21);
	printf("|  _  | | | |");
    gotoxy(73,22);
	printf("| | | \\ \\_/ /");
    gotoxy(73,23); 
	printf("\\_| |_/\\___/");
    
	gotoxy(63,29);
	printf(" _____ _   _______ _____ _   ___   _");
    gotoxy(63,30);
	printf("/  ___| | | |  _  \\  _  | | / / | | |");
    gotoxy(63,31);
	printf("\\ `--.| | | | | | | | | | |/ /| | | |");
    gotoxy(63,32);
	printf(" `--. \\ | | | | | | | | |    \\| | | |");
    gotoxy(63,33);
	printf("/\\__/ / |_| | |/ /\\ \\_/ / |\\  \\ |_| |");
    gotoxy(63,34);
	printf("\\____/ \\___/|___/  \\___/\\_| \\_/\\___/");

	gotoxy(45,17);
	for(int l = 0;l<75;l++){			   //LINHA DE BAIXO DO "BEMVINDO"
	//Sleep(2);
	textbackground(CORMODIFICADA);
	printf(" ");
	}
	
	gotoxy(66,25);
	for(int l = 0;l<25;l++){			   //LINHA DE BAIXO DO "AO"
	//Sleep(2);
	printf(" ");
	}
	
	gotoxy(45,36);
	for(int l = 0;l<75;l++){			   //LINHA DE BAIXO DO "SUDOKU"
	//Sleep(2);
	printf(" ");
	}
	
	textbackground(CORPADRAO);	
	gotoxy(155,42);
	printf("VERSAO 2.0 \n\n");			   //PRINTF DA VERSÃO DO JOGO

	gotoxy(2,42);
	textbackground(CORMODIFICADA);
	textcolor(BLACK);
	printf("DESENVOLVIDO POR-EBNER SILVA - UNICESUMAR 2017\n\n");			   //PRINTF DOS DESENVOLVEDORES
	
//----------------------------------------------------------------------------------------------
//LOADING
	textbackground(CORPADRAO);
	textcolor(WHITE);
	gotoxy(44,39);
	for(int l=0;l<77;l++){				   //LINHA DE CIMA DO LOADING
	printf("%c",196);	
	}
	
	gotoxy(44,41);
	for(int l=0;l<77;l++){				   //LINHA DE BAIXO DO LOADING
	printf("%c",196);	
	}
	
	gotoxy(44,40);
	printf("%c",186);					   //BARRA LATERAL ESQUERDA DO LOADING
	
	gotoxy(120,40);						   //BARRA LATERAL DIREITA DO LOADING
	printf("%c",186);
	
	gotoxy(46,40);
	for(int l=0;l<37;l++){				   //CARACTERES DO LOADING 
	Sleep(150);
	printf("%c ", 178);
	}
	
	printf("\n\n");	

//----------------------------------------------------------------------------------------------
//ENTRANDO NO MENU INICIAL
	gotoxy(62,42);
	Sleep(100);
	printf("DIGITE QUALQUER TECLA PARA CONTINUAR! \n\n\n");			
	fflush(stdin);
	escolhamenu = getch();
	system("CLS");
}

void telainicial(){
	
	gotoxy(1,1);	
	for(int l = 0;l<168;l++){			//LINHA CIMA DA ESQUERDA PARA DIREITA	
		Sleep(sleepcb);
		textbackground(CORMODIFICADA);
		printf(" ");
	}	
	
	for(int l = 2;l<44;l++){			//LINHA DIREITA DE CIMA PARA BAIXO  	//LINHA ESQUERDA DE CIMA PARA BAIXO	
		textbackground(CORPADRAO);
		gotoxy(168,l);  						
		printf("%c\n",220);				
		gotoxy(1,l);				
		printf("%c\n",220);				//LINHA ESQUERDA DE CIMA PARA BAIXO	
	}	
	
	gotoxy(65,22);
	printf("[1] - LOGIN");
	gotoxy(65,27);			
	printf("[2] - CADASTRAR USUARIO");
	gotoxy(65,32);			
	printf("[0]-SAIR");
	
	textbackground(CORMODIFICADA);
	gotoxy(1,44);
	for(int l = 0;l<168;l++){			   //LINHA BAIXO ESQUERDA PARA DIREITA						
	printf(" ");
	}
	
	textbackground(CORPADRAO);
	gotoxy(65,23);
	for(int l = 0;l<12;l++){			   //LINHA DE BAIXO DO "LOGIN"
	printf("%c",220);
	}
	
	gotoxy(65,28);
	for(int l = 0;l<23;l++){			   //LINHA DE BAIXO DO "CADASTRAR USUARIO"
	printf("%c",220);
	}
	
	gotoxy(65,33);
	for(int l = 0;l<10;l++){			   //LINHA DE BAIXO DO "SAIR"
	printf("%c",220);
	}
	
	gotoxy(155,42);
	printf("VERSAO 2.0 \n\n");			   //PRINTF DA VERSÃO DO JOGO
	
}
	
void menu(){							//FUNÇÃO DA TELA DO MENU PRINCIPAL
	system("CLS");
	escolha = 0;
	
	gotoxy(1,1);	
	for(int l = 0;l<168;l++){			//LINHA CIMA DA ESQUERDA PARA DIREITA	
		//Sleep(sleepcb);
		textbackground(CORMODIFICADA);
		printf(" ");
	}	
	
	for(int l = 2;l<44;l++){			//LINHA DIREITA DE CIMA PARA BAIXO  	//LINHA ESQUERDA DE CIMA PARA BAIXO	
		textbackground(CORPADRAO);
		gotoxy(168,l);  						
		printf("%c\n",220);				
		gotoxy(1,l);				
		printf("%c\n",220);				//LINHA ESQUERDA DE CIMA PARA BAIXO	
	}	
		
	gotoxy(60,11);
	printf("___  ___ _____ _   _ _   _");
	gotoxy(60,12);
	printf("|  \\/  ||  ___| \\ | | | | |");
	gotoxy(60,13);			
	printf("| .  . || |__ |  \\| | | | |");
	gotoxy(60,14);
	printf("| |\\/| ||  __|| . ` | | | |");
	gotoxy(60,15);			
	printf("| |  | || |___| |\\  | |_| |");
	gotoxy(60,16);			
	printf("\\_|  |_/\\____/\\_| \\_/\\___/ ");
	gotoxy(65,22);
	printf("[1] - LOGIN");
	gotoxy(65,27);			
	printf("[2] - CADASTRAR USUARIO");
	gotoxy(65,32);			
	printf("[0]-SAIR");
	
	textbackground(CORMODIFICADA);
	gotoxy(1,44);
	for(int l = 0;l<168;l++){			   //LINHA BAIXO ESQUERDA PARA DIREITA						
	printf(" ");
	}
	
	gotoxy(57,18);
	for(int l = 0;l<32;l++){			   //LINHA DE BAIXO DO "MENU"
	textbackground(CORMODIFICADA);
	printf(" ");
	}
	
	textbackground(CORPADRAO);
	gotoxy(65,23);
	for(int l = 0;l<12;l++){			   //LINHA DE BAIXO DO "LOGIN"
	printf("%c",220);
	}
	
	gotoxy(65,28);
	for(int l = 0;l<23;l++){			   //LINHA DE BAIXO DO "CADASTRAR USUARIO"
	printf("%c",220);
	}
	
	gotoxy(65,33);
	for(int l = 0;l<10;l++){			   //LINHA DE BAIXO DO "SAIR"
	printf("%c",220);
	}
	
	gotoxy(155,42);
	printf("VERSAO 2.0 \n\n");			   //PRINTF DA VERSÃO DO JOGO
	
	fflush(stdin);
	escolhamenu1 = getch();
	
	switch(escolhamenu1){		
				
				case '1':
				system("CLS");	
					
				if(login()==0){
				
				final = false;
				while(!final) {   
   						novo = false;
    					nivel = 0;

  					
					if (!AUTO_PREENCHER) {
		  				nivel = menu_nivel();
				    } else {
 	 	  				nivel = 1;
	  				}
	  
  						gerar_grade();
						void somamatriz();	
  							while(!final && !novo) { 
								   gerar_tela(); 
								   
								   for(int i=0;i<100;i++){
										senha_log[i] = '\0';
								   }
								   
 								if(soma==405){
       	 							final = true;
									novo = true;
			
									textcolor(YELLOW);
									gotoxy(50,30);
									system("CLS");
									printf("PARABENS, VOCE CONSEGUIU FECHAR O JOGO!!\n\n\n\n");
									printf("PONTUACAO : %d ",somar);
									system("PAUSE");
									textcolor(WHITE);
									system("CLS");
									soma = 0;
									
    							}	
							}
				}
					
				textbackground(BLACK);
				printf("\n\nJogo encerrado.\n");	
					
				}else{
					system("CLS");	
					menu();
				}
				
				break;	
			
				case '2':
				system("CLS");	
				cadusu();			
				break;
				
				case '0':
				escolhamenu1 = 0;
				break;
			}			
	
	system("CLS");
}

void cadusu(){							//FUNÇÃO DA TELA DE CADASTRO DE USUÁRIO
	
	gotoxy(1,1);	
	for(int l = 0;l<168;l++){			//LINHA CIMA DA ESQUERDA PARA DIREITA	
		textbackground(CORMODIFICADA);
		printf(" ");
	}	
	
	for(int l = 2;l<44;l++){			//LINHA DIREITA DE CIMA PARA BAIXO  	//LINHA ESQUERDA DE CIMA PARA BAIXO	
		textbackground(CORPADRAO);
		gotoxy(168,l);  						
		printf("%c\n",220);				
		gotoxy(1,l);				
		printf("%c\n",220);				//LINHA ESQUERDA DE CIMA PARA BAIXO	
	}

	gotoxy(60,11);
	printf(" _____   ___ ______  ___   _____ ___________ _____ ");
	gotoxy(60,12);
	printf("/  __ \\ / _ \\|  _  \\/ _ \\ /  ___|_   _| ___ \\  _  |");
	gotoxy(60,13);
	printf("| /  \\// /_\\ \\ | | / /_\\ \\ `--.   | | | |_/ / | | |");
	gotoxy(60,14);
	printf("| |    |  _  | | | |  _  | `--. \\ | | |    /| | | |");
	gotoxy(60,15);
	printf("| \\__/\\| | | | |/ /| | | |/\\__/ / | | | |\\ \\ \\_/ /");
	gotoxy(60,16);
	printf(" \\____/\\_| |_/___/ \\_| |_/\\____/  \\_/ \\_| \\_|\\___/ ");
	
	gotoxy(59,18);
	for(int l = 0;l<52;l++){			   //LINHA DE BAIXO DO "CADASTRO"
	textbackground(CORMODIFICADA);
	printf(" ");
	}
	textbackground(CORPADRAO);
    
    gotoxy(65,32);
	printf("DIGITE O LOGIN: ");
    
    gotoxy(65,37);
	printf("DIGITE A SENHA: ");
	
	gotoxy(65,33);
	for(int l = 0;l<18;l++){			   //LINHA DE BAIXO DO "LOGIN"
	printf("%c",220);
	}
	
	gotoxy(65,38);
	for(int l = 0;l<18;l++){			   //LINHA DE BAIXO DO "SENHA"
	printf("%c",220);
	}
	
	textbackground(CORMODIFICADA);
	gotoxy(1,44);
	for(int l = 0;l<168;l++){			   //LINHA BAIXO ESQUERDA PARA DIREITA						
	printf(" ");
	}
	
	textbackground(CORPADRAO);	
	gotoxy(155,42);
	printf("VERSAO 2.0 \n\n");			   //PRINTF DA VERSÃO DO JOGO

//----------------------------------------------------------------------------------------------
//CAMPO DE DÍGITO DE LOGIN	
	gotoxy(84,31);
	for(int l=0;l<45;l++){				   //LINHA DE CIMA DO CAMPO DE LOGIN
	printf("%c",196);	
	}
	
	gotoxy(84,33);
	for(int l=0;l<45;l++){				   //LINHA DE BAIXO DO CAMPO DE LOGIN
	printf("%c",196);	
	}
	
	gotoxy(84,32);
	printf("%c",186);					   //BARRA LATERAL ESQUERDA DO CAMPO DE LOGIN
	
	gotoxy(128,32);						   //BARRA LATERAL DIREITA DO CAMPO DE LOGIN
	printf("%c",186);

//----------------------------------------------------------------------------------------------
//CAMPO DE DÍGITO DE SENHA	
	gotoxy(84,36);
	for(int l=0;l<45;l++){				   //LINHA DE CIMA DO CAMPO DE SENHA
	printf("%c",196);	
	}
	
	gotoxy(84,38);
	for(int l=0;l<45;l++){				   //LINHA DE BAIXO DO CAMPO DE SENHA
	printf("%c",196);	
	}
	
	gotoxy(84,37);
	printf("%c",186);					   //BARRA LATERAL ESQUERDA DO CAMPO DE SENHA
	
	gotoxy(128,37);						   //BARRA LATERAL DIREITA DO CAMPO DE SENHA
	printf("%c",186);	

//----------------------------------------------------------------------------------------------
//GRAVANDO OS DADOS DO CADASTRO DE USUÁRIO NAS VARIÁVEIS	
	gotoxy(85,32);
	scanf("%s",login_cad);
	fflush(stdin);
	gotoxy(85,37);	

//----------------------------------------------------------------------------------------------	
//WHILE PARA DIGITAR '*' NO LUGAR DO QUE ESTÁ SENDO DIGITADO NA SENHA E TAMBÉM GRAVAR A SENHA NO ARQUIVO TXT JUNTO COM O NOME E O LOGIN!!
	do {
        c = getch();
        
        if( isprint(c) ) 
        {
            senha[ pos++ ] = c;
            printf("%c", '*');
        }
        else if( c == 8 && pos )
        {
            senha[ pos-- ] = '\0';
            printf("%s", "\b \b");
        }
    } while( c != 13 );
	
	FILE *file;  		//CRIANDO UM PONTEIRO PARA GRAVAR OS DADOS DE CADASTRO
    file = fopen(login_cad,"w");
    fprintf(file,"%s",senha);
	fclose(file);
	
	system("CLS");	
}

int login(){							//FUNÇÃO DA TELA DE LOGIN

	gotoxy(1,1);
	for(int l = 0;l<168;l++){			//LINHA CIMA DA ESQUERDA PARA DIREITA
	
							
	printf("%c", 220);
	}	

	for(int l = 0;l<43;l++){			//LINHA DIREITA DE CIMA PARA BAIXO
	gotoxy(168,l);  
							
	printf("%c\n",220);
		
	gotoxy(1,l);
										//LINHA ESQUERDA DE CIMA PARA BAIXO	
	printf("%c\n",220);
	}
	
	gotoxy(60,11);	
	printf(" _     _____ _____ _____ _   _"); 
	gotoxy(60,12);
	printf("| |   |  _  |  __ \\_   _| \\ | |");
	gotoxy(60,13);
	printf("| |   | | | | |  \\/ | | |  \\| |");
	gotoxy(60,14);
	printf("| |   | | | | | __  | | | . ` |");
	gotoxy(60,15);
	printf("| |___\\ \\_/ / |_\\ \\_| |_| |\\  |");
	gotoxy(60,16);
	printf("\\_____/\\___/ \\____/\\___/\\_| \\_/");
	
	gotoxy(58,17);
	for(int l = 0;l<35;l++){			   //LINHA DE BAIXO DO "LOGIN"
	//Sleep(2);
	printf("%c",220);
	}
	
	gotoxy(1,43);
	for(int l = 0;l<168;l++){			   //LINHA BAIXO ESQUERDA PARA DIREITA					
	printf("%c",220);
	}
	
	gotoxy(155,42);
	printf("VERSAO 1.4 \n\n");			   //PRINTF DA VERSÃO DO JOGO	
	
	gotoxy(65,27);
	printf("DIGITE O LOGIN:");
	
	gotoxy(65,32);
	printf("DIGITE A SENHA:");
		
	gotoxy(65,28);
	for(int l = 0;l<18;l++){			   //LINHA DE BAIXO DO "LOGIN"
	printf("%c",220);
	}

	gotoxy(65,33);
	for(int l = 0;l<18;l++){			   //LINHA DE BAIXO DA "SENHA"
	printf("%c",220);
	}
		
//------------------------------------------------------------------------------------------------	
//CAMPO DE DÍGITO DE LOGIN
	gotoxy(84,26);
	for(int l=0;l<45;l++){				   //LINHA DE CIMA DO CAMPO DE LOGIN
	printf("%c",196);	
	}
	
	gotoxy(84,33);
	for(int l=0;l<45;l++){				   //LINHA DE BAIXO DO CAMPO DE LOGIN
	printf("%c",196);	
	}
	
	gotoxy(84,32);
	printf("%c",186);					   //BARRA LATERAL ESQUERDA DO CAMPO DE LOGIN
	
	gotoxy(128,32);						   //BARRA LATERAL DIREITA DO CAMPO DE LOGIN
	printf("%c",186);
//------------------------------------------------------------------------------------------------	
//CAMPO DE DÍGITO DE SENHA
	gotoxy(84,31);
	for(int l=0;l<45;l++){				   //LINHA DE CIMA DO CAMPO DE SENHA
	printf("%c",196);	
	}
	
	gotoxy(84,28);
	for(int l=0;l<45;l++){				   //LINHA DE BAIXO DO CAMPO DE SENHA
	printf("%c",196);	
	}
	
	gotoxy(84,27);
	printf("%c",186);					   //BARRA LATERAL ESQUERDA DO CAMPO DE SENHA
	
	gotoxy(128,27);						   //BARRA LATERAL DIREITA DO CAMPO DE SENHA
	printf("%c",186);
//------------------------------------------------------------------------------------------------

int escolha2 = 0;
	
	gotoxy(85,27);
	scanf("%s",&login_log);
	fflush(stdin);
	
	FILE* file;
	file = fopen(login_log,"r");
	
	if(file){
		
		textcolor(CORMODIFICADA);
		gotoxy(35,3);
		printf("USUARIO JA CADASTRADO");
		system("PAUSE");
		textcolor(WHITE);
	
	}else{
		
		textcolor(CORMODIFICADA);
		gotoxy(45,3);
		printf("USUARIO NAO CADASTRADO!!   -   ");
		system("PAUSE");
		textcolor(WHITE);
		return 1;					
	}
		gotoxy(85,32);
		scanf("%s",&senha_log);
		
		fflush(stdin);
		fscanf(file,"%s",s);
		fclose(file);
		if(!strcmp(senha_log,s)){
			return 0;
	
		}else{
			printf("SENHA INCORRETA!");
			system("PAUSE");
			return 1;
		}
	
}

//NÃO ESTOU USANDO ESSA FUNÇÃO DA DIFICULDADE AINDA!!!
void dificuldadelay(){

	gotoxy(1,1);	
	for(int l = 0;l<168;l++){			//LINHA CIMA DA ESQUERDA PARA DIREITA	
		textbackground(CORMODIFICADA);
		printf(" ");
	}	
	
	for(int l = 2;l<44;l++){			//LINHA DIREITA DE CIMA PARA BAIXO  	//LINHA ESQUERDA DE CIMA PARA BAIXO	
		textbackground(CORPADRAO);
		gotoxy(168,l);  						
		printf("%c\n",220);				
		gotoxy(1,l);				
		printf("%c\n",220);				//LINHA ESQUERDA DE CIMA PARA BAIXO	
	}	
	
	gotoxy(49,11);	
	printf("______ ___________ _____ _____ _   _ _    ______  ___ ______ _____"); 
	gotoxy(49,12);
	printf("|  _  \\_   _|  ___|_   _/  __ \\ | | | |   |  _  \\/ _ \\|  _  \\  ___|");
	gotoxy(49,13);
	printf("| | | | | | | |_    | | | /  \\/ | | | |   | | | / /_\\ \\ | | | |__");
	gotoxy(49,14);	
	printf("| | | | | | |  _|   | | | |   | | | | |   | | | |  _  | | | |  __|"); 
	gotoxy(49,15);
	printf("| |/ / _| |_| |    _| |_| \\__/\\ |_| | |___| |/ /| | | | |/ /| |___");
	gotoxy(49,16);
	printf("|___/  \\___/\\_|    \\___/ \\____/\\___/\\_____/___/ \\_| |_/___/ \\____/");
	textbackground(CORPADRAO);
	gotoxy(65,22);
	printf("SELECIONE A DIFICULDADE:");
	gotoxy(65,27);
	printf("[1] - FACIL");
	gotoxy(65,32);
	printf("[2] - MEDIO");	
	gotoxy(65,37);
	printf("[3] - DIFICIL");
	
	textbackground(CORMODIFICADA);
	gotoxy(1,44);
	for(int l = 0;l<168;l++){			   //LINHA BAIXO ESQUERDA PARA DIREITA						
	printf(" ");
	}
	
	gotoxy(47,18);
	for(int l = 0;l<70;l++){			   //LINHA DE BAIXO DA "DIFICULDADE"
	printf(" ");
	}
	
	textbackground(CORPADRAO);
	gotoxy(65,23);
	for(int l = 0;l<25;l++){			   //LINHA DE BAIXO DO "SELECIONE A DIFICULDADE"
	printf("%c",220);
	}
	
	gotoxy(65,28);
	for(int l = 0;l<12;l++){			   //LINHA DE BAIXO DO "FACIL"
	printf("%c",220);
	}
	
	gotoxy(65,33);
	for(int l = 0;l<12;l++){			   //LINHA DE BAIXO DO "MEDIO"
	printf("%c",220);
	}
	
	gotoxy(65,38);
	for(int l = 0;l<14;l++){			   //LINHA DE BAIXO DO "DIFICIL"
	printf("%c",220);
	}
	
	gotoxy(155,42);
	printf("VERSAO 1.4 \n\n");			   //PRINTF DA VERSÃO DO JOGO

/*	
	escolhadific = getch();

	system("cls");
	
		if(escolhadific=='1'){
						
					//dific = FACIL;
					}
						else if(escolhadific=='2'){
						
						//dific = MEDIO;
					
						}	
							else if(escolhadific=='3'){
						
							//dific = DIFICIL;
		
							}
*/
	system("CLS");	
	
}

//FUNÇÕES DA MATRIZ NOVA
////////////////////////
void gerar_moldura() {
	int x, c, l;
	
	c = defcol + 1, 
	l = 9;
	//Linha vertical esquerda.//
	for(x=l; x<l+13; x++) { 
		gotoxy(c, x); 	
    printf("%c", 179);
  }
  
	//Linha horizontal superior//
  for(x=c; x<c+30; x++) { 
    gotoxy(x, l); 			
    printf("%c", 196);
  }
  
  //Linha vertical direita//
	for(x=l; x<l+13; x++) { 
    gotoxy(c + 30, x); 
    printf("%c", 179);
  }
  
  //Linha horizontal inferior.//
  for(x=c; x<c+30; x++) { 
    gotoxy(x, 21); 
    printf("%c", 196);
  }
  
  //Canto esquerdo superior
  gotoxy(c, l); 
  printf("%c", 218);

  //Canto direito superior
  gotoxy(c + 30, l); 
  printf("%c", 191);

  //Canto esquerdo inferior
  gotoxy(c, 21); 
  printf("%c", 192);

	//Canto direito inferior
  gotoxy(c + 30, 21); 
  printf("%c", 217);
  
}

void somamatriz(){			    //FUNÇÃO QUE SOMA TODA A MATRIZ E VERIFICA SE JÁ CHEGOU NO FIM DO JOGO!			
	for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                if(grade[i][j]!=0){
                soma = soma + grade[i][j];
                soma1 = soma1+mtztmp[i][j];
            	soma2 = soma2+matriz[i][j];
				}
        	}
    }	
}

void gerar_grade() {
	int i,j,k;

	//tira uma cópia de matriz em grade...
	for(i = 0; i < MAX_LEN; i++) {
  	for(j = 0; j < MAX_LEN; j++) {
      grade[i][j] = matriz[i][j];
    }
  }

	//Números aleatórios...
  srand((unsigned)time(NULL));
	int x = rand()%10; 

	for(i = 0; i < MAX_GRD; i++, x++) {
  	for(j = 0; j < MAX_GRD; j++, x+=MAX_GRD) {
		 	for(k = 0; k < MAX_GRD*MAX_GRD; k++, x++) {
		 		if (AUTO_PREENCHER) {
          grade[MAX_GRD*i+j][k] = (x % (MAX_GRD*MAX_GRD)) + 1;
        } else {
					if (grade[MAX_GRD*i+j][k] < nivel) 
					  grade[MAX_GRD*i+j][k] = 0;
		 		  if (grade[MAX_GRD*i+j][k] != 0) {
		 		  	grade[MAX_GRD*i+j][k] = (x % (MAX_GRD*MAX_GRD)) + 1;
					}
				}
      }
    }
  }
  
	//tira uma cópia de grade em mtztmp...
	for(i = 0; i < MAX_LEN; i++) {
  	for(j = 0; j < MAX_LEN; j++) {
      mtztmp[i][j] = grade[i][j];
	}
  }
somamatriz();
  
  return;
}

void print_str_color(char *s, color c) {
	textcolor(c);
	printf(s);
}

void print_int_color(char *m, int i, color c) {
	textcolor(c);
	printf(m, i);
	return;
}

void desenha_grade() {
  int i,j,y;
 	
  //printf("SOMA : %d SOMA 1 : %d SOMA 2 : %d",soma,soma1,soma2);	
 
  gotoxy(defcol, 8);print_str_color("   1  2  3   4  5  6   7  8  9  ", COLOR_ALL);
  gotoxy(defcol, 9);print_str_color(" +---------+---------+---------+", COLOR_ALL);

  y = 10;
  for (i = 0; i < MAX_LEN; i++) {
  	gotoxy(defcol, y);print_int_color("%d", i+1, COLOR_ALL);
		print_str_color("|", COLOR_ALL);
		for (j = 0; j < MAX_LEN; j++) {
			if (grade[i][j] != 0) {
				if (checar_posicao(i, j, grade[i][j])) 
					print_int_color(" %d ", grade[i][j], COLOR_BASE);
				else
				  print_int_color(" %d ", grade[i][j], COLOR_ALL);
	  	} else
	  	  print_str_color(" ? ", CORMODIFICADA);
			if (j % MAX_GRD == 2) 
				print_str_color("|", COLOR_ALL);
		}
		y += 1;
		if (i % MAX_GRD == 2) {
	  	gotoxy(defcol, y);print_str_color(" +---------+---------+---------+", COLOR_ALL);
	  	y += 1;
	  }
  }

 //Substitui a moldura atual por uma melhor
  gerar_moldura();

	return;
}

bool checar_posicao(int lin, int col, int numero) {
	if (mtztmp[lin][col]==0)
		return 1;
	else
	 	return 0;	
}

bool tenta_colocar(int i, int j, int k) {
	int c,l;

  for (l = 0; l < MAX_LEN; l++)
		if ((grade[l][j] == k) && (mtztmp[l][j] != 0))
	  	return 0;
  
	for (c = 0; c < MAX_LEN; c++)
		if ((grade[i][c] == k) && (mtztmp[i][c] != 0))
	  	return 0;
  
	for (l = i - i % 3; l < i - i % 3 +3; l++)
		for (c = j - j % 3; c < j - j % 3 + 3; c++)
	  	if ((grade[l][c] == k) && (mtztmp[l][c] != 0))
    		return 0;

  grade[i][j] = k;
  
	return 1;
}

bool coordenada_valida(int lin, int col) {
  if(lin>=0 && lin <9 && col>=0 && col <9)
	  return 1;
  else
	  return 0;
}

bool numerovalido(int numero) {
  if(numero>0 && numero <= 9)
	  return 1;
  else
	  return 0;
}

void escrever(int lin, int col, int numero) {
	grade[lin][col]=numero;
	return;
}

void jogar() {
	char s[300];

	strcpy(s, "");
	
	if (coordenada_valida(linha-1, coluna-1)) {
	  strcat(s, "\nCoordenada valida.");
	  if (numerovalido(numero)) {
		  strcat(s, "\nNumero valido.");
		  if (checar_posicao(linha-1, coluna-1, numero)) {
			  strcat(s, "\nPosicao vazia.");
			  if (tenta_colocar(linha-1, coluna-1, numero)) {
				  strcat(s, "\nQuadrante OK.");
					escrever(linha-1, coluna-1, numero);
					soma = soma + numero;
					somar = somar+100;
			  } else {
				   strcat(s, "\nValor existente na linha, coluna ou no mesmo quadrante.");
			  		somar = somar-10;
			  }
		  } else {
			  strcat(s, "\nPosicao ja esta ocupada.");
				somar = somar-10;  
		  }
		} else {
			strcat(s, "\nNumero invalido.");
			somar = somar-10;
		}	
	}	else{
		strcat(s, "\nCoordenada invalida.");
		somar = somar-10;
	}		
	
	if (s != "") {
		printf(s);
		printf("\n\n");
		printf(PAUSE_MSG);
		getch();
	}
	
	return;  
}

void print_ajuda() {
	tela_padrao(false);
	
	gotoxy(defcol, 3);printf("O objetivo do jogo e completar todos os quadrados utilizando");
	gotoxy(defcol, 4);printf("numeros de 1 a 9. Para completa-los, seguiremos a seguinte regra:"); 
	gotoxy(defcol, 5);printf("Nao podem haver numeros repetidos nas linhas horizontais e verticais,");
	gotoxy(defcol, 6);printf("assim como nos quadrados grandes.");
  printf(PAUSE_MSG);
	getch();
	
	return;
}

void terminar(int op) {
	if (op == 99) {
		final = true;
	} else if (op == 88) {
    novo = true;
	} else if (op == 77) {
		ajuda = true;
		print_ajuda();
	}
	return;
}

bool continuar() {
	return (!final && !novo && !ajuda);
}

int menu_nivel() {
	int n = 0;
/*	
	gotoxy(1,1);	
	for(int l = 0;l<168;l++){			//LINHA CIMA DA ESQUERDA PARA DIREITA	
		textbackground(CORMODIFICADA);
		printf(" ");
	}	
	
	for(int l = 2;l<44;l++){			//LINHA DIREITA DE CIMA PARA BAIXO  	//LINHA ESQUERDA DE CIMA PARA BAIXO	
		textbackground(CORPADRAO);
		gotoxy(168,l);  						
		printf("%c\n",220);				
		gotoxy(1,l);				
		printf("%c\n",220);				//LINHA ESQUERDA DE CIMA PARA BAIXO	
	}	
	
	gotoxy(49,11);	
	printf("______ ___________ _____ _____ _   _ _    ______  ___ ______ _____"); 
	gotoxy(49,12);
	printf("|  _  \\_   _|  ___|_   _/  __ \\ | | | |   |  _  \\/ _ \\|  _  \\  ___|");
	gotoxy(49,13);
	printf("| | | | | | | |_    | | | /  \\/ | | | |   | | | / /_\\ \\ | | | |__");
	gotoxy(49,14);	
	printf("| | | | | | |  _|   | | | |   | | | | |   | | | |  _  | | | |  __|"); 
	gotoxy(49,15);
	printf("| |/ / _| |_| |    _| |_| \\__/\\ |_| | |___| |/ /| | | | |/ /| |___");
	gotoxy(49,16);
	printf("|___/  \\___/\\_|    \\___/ \\____/\\___/\\_____/___/ \\_| |_/___/ \\____/");
	textbackground(CORPADRAO);
	gotoxy(65,22);
	printf("SELECIONE A DIFICULDADE:");
	gotoxy(65,27);
	printf("[1] - FACIL");
	gotoxy(65,32);
	printf("[2] - MEDIO");	
	gotoxy(65,37);
	printf("[3] - DIFICIL");
	
	textbackground(CORMODIFICADA);
	gotoxy(1,44);
	for(int l = 0;l<168;l++){			   //LINHA BAIXO ESQUERDA PARA DIREITA						
	printf(" ");
	}
	
	gotoxy(47,18);
	for(int l = 0;l<70;l++){			   //LINHA DE BAIXO DA "DIFICULDADE"
	printf(" ");
	}
	
	textbackground(CORPADRAO);
	gotoxy(65,23);
	for(int l = 0;l<25;l++){			   //LINHA DE BAIXO DO "SELECIONE A DIFICULDADE"
	printf("%c",220);
	}
	
	gotoxy(65,28);
	for(int l = 0;l<12;l++){			   //LINHA DE BAIXO DO "FACIL"
	printf("%c",220);
	}
	
	gotoxy(65,33);
	for(int l = 0;l<12;l++){			   //LINHA DE BAIXO DO "MEDIO"
	printf("%c",220);
	}
	
	gotoxy(65,38);
	for(int l = 0;l<14;l++){			   //LINHA DE BAIXO DO "DIFICIL"
	printf("%c",220);
	}
	
	gotoxy(155,42);
	printf("VERSAO 1.4 \n\n");			   //PRINTF DA VERSÃO DO JOGO
	*/
    while(!final && !novo) { 		
    tela_padrao(true);
    gotoxy(defcol, 3);printf("Digite [99 + ENTER] para encerrar.\n");
	gotoxy(defcol, 4);printf("Digite [77 + ENTER] para obter ajuda.\n");
	  
    
	
	
	gotoxy(defcol, 6);
    n = ler_valor("Digite um nivel (1 a 3): ");
		if ((n >= 1) && (n <= 3))soma = 0;	break;
	}
	return n;
}

int ler_valor(char *prompt) {
	int n = 0;

	while(continuar()) {
		printf(prompt);
		scanf("%d", &n); 
		fflush(stdin);
  	terminar(n);

		if ((n >= 0) && (n <= 9)) {
			break;
	  }
	}
	return n;
}

void tela_padrao(bool reset) {
	if (nivel > 3) nivel = 0;
	if (reset) ajuda = false;
	
  textbackground(CORPADRAO);
  void resolucao1366x768();
  system("cls");

  textbackground(CORMODIFICADA);textcolor(CORPADRAO);
  gotoxy(defcol, 1);printf("SUSOKU VER: %s - %s - NIVEL: %s\n\n", APP_VERSION, COPY_RIGHT, dificuldade[nivel]);
  textbackground(CORPADRAO);textcolor(WHITE);
	
  return;
}

void desenha_tela() {
  tela_padrao(true);
  
	if (!AUTO_PREENCHER) {
	  gotoxy(defcol, 3);printf("Digite [99 + ENTER] para encerrar.\n");
 		gotoxy(defcol, 4);printf("Digite [88 + ENTER] para trocar o nivel.\n");
 		gotoxy(defcol, 5);printf("Digite [77 + ENTER] para obter ajuda.\n");
 		gotoxy(defcol, 7);
 	}
 	
  desenha_grade(); 
  //printf("\n");	
  
  return;
}

void gerar_tela() {
  desenha_tela();
  	
	if (AUTO_PREENCHER) {
		printf("\n");
		printf(PAUSE_MSG);
		getch();
		terminar(99);
	} else {
	  gotoxy(defcol, 23);linha = ler_valor("Digite uma linha: ");
  	gotoxy(defcol, 24);coluna = ler_valor("Digite uma coluna: ");
		gotoxy(defcol, 25);numero = ler_valor("Digite o numero: ");
	}
	
	if (continuar()) {		
	  jogar();
	}
	return;
}

//FIM FUNÇÕES DA MATRIZ NOVA
////////////////////////////

int main(int argc, char** argv) {
resolucao1366x768();
bemvindo();	
escolhamenu1 = 1;

	while(escolhamenu1!=0){		//WHILE DE COMPARAÇÃO PARA ACESSAR O MENU INICIAL DE OPÇÕES	
		system("CLS");
		menu();				
	}		
	return 0;
}
