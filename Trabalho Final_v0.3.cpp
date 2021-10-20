#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <windows.h>

#define XW 1000
#define YW 1000

#define MENU 0
#define JOGO 1
#define RESULT 2


typedef struct{
	float r;
	float g;
	float b;
}COLOR; //estrutura de cores

typedef struct {
	char *q,*a;
	int op,correct;
	
}QUESTION; //estrutura do quizz

COLOR prim,sec; //cores do tema
char buffer[3]; //variavel para concatenação
QUESTION quizz[10]; //10 questoes principais do quizz
//constantes de tela: MENU, JOGO, RESULT
int atualQuizz = 0, tela = MENU; 

char  dataQ[20][100] = { //banco de questoes
	"Coronavirus fica vivo somente por nove dias no organismo.", 
	"A COVID-19 so eh letal em idosos.", 
	"So pessoas sintomaticas transmitem a COVID-19.", 
	"O virus exposto a uma temperatura superior a 26 graus morre.", 
	"O virus se propaga no ar.",
	"Termometros na testa provocam cancer.", 
	"Mascaras oferecem riscos a saude.", 
	"O consumo de alcool protege contra a COVID-19.", 
	"Utilizar alcool em gel nas maos altera teste de bafometro.", 
	"Quem pegou covid ja esta imunizado.",
	"Existe medicamento capaz de prevenir a Covid-19.", 
	"A vacina tem microchip.", 
	"A vacina pode transformar as pessoas em jacare.",
	"Animais de estimação podem transmitir a COVID-19 aos humanos.", 
	"Ate bebes podem ser infectados pelo Covid.", 
	"Os calcados podem transmitir covid.", 
	"O COVID-19 afeta principalmente as celulas do pulmao e intestino.",
	"O virus nao eh capaz de entrar na pele.",
	"O novo corona virus eh capaz de permanecer ativo na pele por nove horas.", 
	"Essa é a sexta pandemia que o mundo vive."
};

char dataA[20][100]={ //banco de correções
	"Voce errou! O corona virus fica vivo no organismo por cerca de 14 dias.",
	"Voce errou! A COVID-19 pode ser letal a qualquer pessoa.",
	"Voce errou! Qualquer infectado pode transmitir a COVID-19",
	"Voce errou! Eh necessario cerca de 72 graus para neutralizar o virus em segundos.",
	"Voce errou! O virus se propaga em particulas no ar, nao no ar.",
	"Voce errou! Nao ha o minimo de evidencias necessarias.",
	"Voce errou! Nao ha evidencias. Mascaras servem para protejer a saude.",
	"Voce errou! O consumo de alcool pode agravar os sintomas da COVID-19.",
	"Voce errou! A ultilizacao do alcool em gel nao altera o teste de bafometro.",
	"Voce errou! A contaminacao pode acontecer novamente.",
	"Voce errou! Nao existe tratamento precoce para COVID-19.",
	"Voce errou! Nao ha evidencias de microchips em vacinas.",
	"Voce errou! Nao existem condicoes, na realidade, de algo do tipo acontecer.",
	"Voce errou! Nao ha evidencias de transmissao por parte de animais.",
	"Voce errou! Bebes podem sim ser infectados.",
	"Voce errou! Sapatos podem levar particulas infectadas ate o organismo.",
	"Voce errou! Esses sao os orgaos mais afetados.",
	"Voce errou! Orificios nasais e bucal sao as vias de contaminacao.",
	"Voce errou! O coronavirus pode sim permanecer ativo na pele por nove horas.",
	"Voce errou! O planeta terra ja passou por 6 pandemias, incluindo a da COVID-19.",
};

int dataCorrect[]={ //definição para afirmativas fake: "0" ou fato: "1"
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1
};

char * convert(int i){ //retornar o valor em char 
	char number[11][3] = {
		"0","1","2","3","4","5","6","7","8","9","10"
	};
	return number[i];
}

void loadRandQuizz(){ //gerador de quizzes aleatorios do banco de questoes
	
	int x[10],i = 0,j,igual = 0;
	
	srand(time(NULL));
	
	do{	
		x[i] = (rand() % 20);	
		for(j = 0; j < i; j++){
			
			if(x[j] == x[i]){ //garantia de todos serem diferentes
			igual = 1;	
			}	
		}
		if(!igual){
			i++;
		}
		igual = 0;	
	}while(i<10);
	
	for(i=0;i<10;i++){ //atribuição das questões, correções e valores para cada questao do quizz a partir dos bancos de dados
		
		quizz[i].q = dataQ[x[i]]; //questao
		quizz[i].a = dataA[x[i]]; //correção
		quizz[i].op = NULL; //opção do usuario
		quizz[i].correct = dataCorrect[x[i]]; //valor correto
	}
	
}

void drawText(int x, int y, const char * string){ //desenha texto na tela
	int j = strlen(string), i;
	glRasterPos2f(x,y);
	for(i = 0; i<j; i++){
		glutBitmapCharacter (GLUT_BITMAP_TIMES_ROMAN_24 , string[i]);
	}
}
 void rodape(){ //rodape presente em todas as telas
 			glColor3f(sec.r,sec.g,sec.b);
			glBegin(GL_QUADS);
    			glVertex2f(1100,0);
				glVertex2f(1100,50);
				glVertex2f(0,50);
				glVertex2f(0,0);
    		glEnd();
    		glColor3f(prim.r,prim.g,prim.b);
 			drawText(330,10,"Trabalho de Computacao Grafica - UNIVASF");
 			glColor3f(sec.r,sec.g,sec.b);
 }


void display(){
	
	int i,j,posText;
	
	glClear(GL_COLOR_BUFFER_BIT);
	glDisable(GL_LIGHTING);
	
	 switch(tela){
	 	
	 	case MENU: //menu principal
	 		glColor3f(sec.r,sec.g,sec.b);
	 		drawText(470,800,"Fato ou Fake?");
	 		drawText(330,750,"Voce consegue reconhecer uma fake news?");
	 		drawText(330,150,"Botao direito do mouse para alterar o tema");
	 		glClearColor(prim.r,prim.g,prim.b,1);
			glColor3f(sec.r,sec.g,sec.b);
	 		//Jogar 
			 glBegin(GL_QUADS);
    			glVertex2f(450,500);
				glVertex2f(450,600);
				glVertex2f(650,600);
				glVertex2f(650,500);
    		glEnd();
			//Sair
			glBegin(GL_QUADS);
    			glVertex2f(0,1100);
				glVertex2f(0,1000);
				glVertex2f(100,1000);
				glVertex2f(100,1100);
    		glEnd();
    		
    		rodape();
		
			glColor3f(prim.r,prim.g,prim.b);
    		drawText(515,540,"Jogar!");
			drawText(500,370,"Opcoes");
			drawText(20,1040,"Sair");
	 		break;
	 		
	 	case JOGO:
			glClearColor(prim.r,prim.g,prim.b,1);
			glColor3f(sec.r,sec.g,sec.b);
			
			//caixa das questoes
			glBegin(GL_QUADS);
    			glVertex2f(1000,650);
				glVertex2f(1000,850);
				glVertex2f(100,850);
				glVertex2f(100,650);
    		glEnd();
    		
			// botao Fato
			glBegin(GL_QUADS);
    			glVertex2f(500,450);
				glVertex2f(500,550);
				glVertex2f(250,550);
				glVertex2f(250,450);
    		glEnd();
    		
			//botao Fake
			glBegin(GL_QUADS);
				glVertex2f(850,450);
				glVertex2f(850,550);
				glVertex2f(600,550);
				glVertex2f(600,450);
			glEnd();
			
			glColor3f(0,1,0);
			//barra de progresso
			glBegin(GL_QUADS);
    			glVertex2f(20+110*atualQuizz,100);
				glVertex2f(20+110*atualQuizz,120);
				glVertex2f(0,120);
				glVertex2f(0,100);
    		glEnd();
    		
			rodape();
			strcat(strcpy( buffer,"Questao ") , convert(atualQuizz+1)); //concatenar "Questao" + "(o numero da questao)"
			glColor3f(sec.r,sec.g,sec.b);
			drawText(330,150,"N para 'Fato' M para 'Fake' P para 'Pular'");
			drawText(480,990, buffer);
			glColor3f(prim.r,prim.g,prim.b);
			
			posText = (550 - (11*strlen(quizz[atualQuizz].q)/2)); //garantir posição centralizada para todas as questões
			
			drawText(posText,730, quizz[atualQuizz].q);
			drawText(330,490,"FATO");
			drawText(680,490,"FAKE");
	 		break;
	 		
	 	case RESULT:
		 	glClearColor(prim.r,prim.g,prim.b,1);
		 	glColor3f(sec.r,sec.g,sec.b);
		 	strcat(strcpy( buffer,"Questao ") , convert(atualQuizz+1));
		 	drawText(480,990, buffer);
		 	drawText(150,150,"Seta esquerda e direita para navegar | Seta para cima para ir para o Menu");
		 	
		 	//caixa de questoes
			glBegin(GL_QUADS);
    			glVertex2f(1000,650);
				glVertex2f(1000,850);
				glVertex2f(100,850);
				glVertex2f(100,650);
    		glEnd();
    		
			//caixa de correções
			glBegin(GL_QUADS);
    			glVertex2f(1000,350);
				glVertex2f(1000,550);
				glVertex2f(100,550);
				glVertex2f(100,350);
    		glEnd();
		
			rodape();
			
			for(i = 0,j = 0;i < 10; i++){ //contador de questoes certas
				if(quizz[i].op == quizz[i].correct)
					j++;
			}
			strcat(strcpy( buffer,"Numero de acertos: ") , convert(j));
			drawText(420,100,buffer);
			glColor3f(prim.r,prim.g,prim.b);
			
			posText = (550 - (11*strlen(quizz[atualQuizz].q)/2)); //garantir que a questao esteja centralizada
			drawText(posText,740, quizz[atualQuizz].q);
			
			if(quizz[atualQuizz].op != quizz[atualQuizz].correct){
				posText = (550 - (11.02*strlen(quizz[atualQuizz].a)/2));
				drawText(posText,430,quizz[atualQuizz].a);
			}
			else{
				drawText(423,430,"Parabens, voce acertou!");
			}
			
			drawText(20,1040,"Sair");
		 	break; 
		 	
	 }

	glFlush();
    glutPostRedisplay();
    glutSwapBuffers();
	
}

void tema(int op){
	switch(op) {
        case 0:
	        prim.r = prim.g = prim.b = 0;
	        sec.r = sec.g = sec.b = 1;
	        break;
        case 1:
	        sec.r = sec.g = sec.b = 0;
	        prim.r = prim.g = prim.b = 1;
	        break;
	}	
	glutPostRedisplay();
}

void MenuPrincipal(int op)
{
}

void CriaMenu() 
{
    int menu,submenu1;

    submenu1 = glutCreateMenu(tema);
    glutAddMenuEntry("Escuro",0);
    glutAddMenuEntry("Claro",1);
	
	menu = glutCreateMenu(MenuPrincipal);
    glutAddSubMenu("Temas",submenu1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
}

//Função Mouse Click
void mouse(int button, int state, int x, int y ){
	
	if(tela == MENU){
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){ 
			if((x<=600 && x>=410) && (y>=450 && y<=550)){//jogar
				tela = JOGO;
			}
			if(x>= 0 && x<=90 && y>= 0 && y<=90){ //sair
				if(MessageBox(NULL, "Você deseja mesmo sair?", "Atenção!", MB_YESNO | MB_ICONASTERISK )==6){
					exit(0);
				}
			}
		}
	}
	else if(tela == JOGO){
		
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
			if(x>=227 && x<=450 && y>= 500 && y<= 590){	//fato
				quizz[atualQuizz].op = 1;
				atualQuizz++;}
		
			if(x >=545 && x<= 775 && y>= 500 && y<= 590){ //fake
				quizz[atualQuizz].op = 0;
				atualQuizz++;}	
		
		if (atualQuizz == 10){
			tela = RESULT;
			atualQuizz = 0;
	}
		}
	}
	if (tela == RESULT){
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		if(x>= 0 && x<=90 && y>= 0 && y<=90){ //sair
				if(MessageBox(NULL, "Você deseja mesmo sair?", "Atenção!", MB_YESNO | MB_ICONASTERISK )==6){
				exit(0);
			}
		}
		}
	}

	glutPostRedisplay();
}

void special(int key, int x, int y){
	if(tela == RESULT){
		if(key == GLUT_KEY_LEFT && atualQuizz > 0){ //retroceder questao
			atualQuizz--;
		}
		if(key == GLUT_KEY_RIGHT && atualQuizz < 9){ //avançar questao
			atualQuizz++;
		}
		if(key == GLUT_KEY_UP){ //voltar para menu
			tela = MENU;
			atualQuizz = 0;
			loadRandQuizz();
		}
	}
}

void teclado(unsigned char key, int x, int y){
	
	if(key == 27){ //esc sair
		if(MessageBox(NULL, "Você deseja mesmo sair?", "Atenção!", MB_YESNO | MB_ICONASTERISK )==6){
			exit(0);
		}
	} 
	if(tela == JOGO){ 
		if(key == 78 || key == 110){//N para fato
			quizz[atualQuizz].op = 1;
			atualQuizz++;
		}
		else if(key == 77 || key == 109){ //M para fake
			quizz[atualQuizz].op = 0;
			atualQuizz++;
		}
		else if(key == 80 || key == 112){ //P para pular
			quizz[atualQuizz].op = -1;
			atualQuizz++;
		}
	}
	if (atualQuizz == 10){
		tela = RESULT;
		atualQuizz = 0;
	}
	
		
	
	glutPostRedisplay();
	
}

int main(int argc, char** argv){

	
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    loadRandQuizz();
    glutInitWindowSize(XW,YW);
    glutInitWindowPosition(500,20);
    glutCreateWindow("Fato ou Fake?");
    
    
	prim.r = prim.g = prim.b = 0; //tema primario inicial
	sec.r = sec.g = sec.b = 1; //tema secundario incial
	
	CriaMenu();	
	glutMouseFunc(mouse);
    glutDisplayFunc(display);
	glutKeyboardFunc(teclado);
	glutSpecialFunc(special);
	
    gluOrtho2D(0.0,100+XW,0.0,100+YW);
    
    glutMainLoop();
    return 0;
}
