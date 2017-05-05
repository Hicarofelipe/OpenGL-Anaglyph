#include <GL/glut.h>

GLfloat angle, fAspect;

float angulo = -30, velocidade = 0.5f, distance =0;;

void IncrementaAngulo()
{
	angulo += velocidade;
	if(angulo >= 360)
	{
		angulo -=360;
	}
}




// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();

	// Especifica a projeção perspectiva
	gluPerspective(angle,fAspect,0.4,500);

	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();


	// Especifica posição do observador e do alvo
	gluLookAt(0,5,10, 0,0,0, 0,1,0);
}   

void SetaCameraEsquerda(){
	// Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();

	glFrustum(-1.0f - (distance/2.0f),1.0f - (distance/2.0f), -1.0f, 1.0f , 1.0f , 50.0f);
}

void SetaCameraDireita(){
	// Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();

	glFrustum(-1.0f + (distance/2.0f),1.0f + (distance/2.0f), -1.0f, 1.0f , 1.0f , 50.0f);
}        
// Função callback chamada para fazer o desenho
void Desenha(void)
{
	
 
        IncrementaAngulo();
	glColorMask(1,1,1,1);
	// Limpa a janela e o depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f);
	
	glColorMask(0,0,1,1);


	SetaCameraEsquerda();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0,5,10, 0,0,0, 0,1,0);
	glRotatef(angulo,0,1,0);	
	glutSolidTeapot(3.0f);
	

	glClear(GL_DEPTH_BUFFER_BIT);


	glColorMask(1,0,0,1);
	SetaCameraDireita();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0,5,10, 0,0,0, 0,1,0);
	glRotatef(angulo,0,1,0);
	glutSolidTeapot(3.0f);

	glutSwapBuffers();
}

// Inicializa parâmetros de rendering
void Inicializa (void)
{ 
	GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0}; 
	GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0};	   // "cor" 
	GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};// "brilho" 
	GLfloat posicaoLuz[4]={0.0, 50.0, 50.0, 1.0};

	
 	// Especifica que a cor de fundo da janela será preta
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	
	

	// Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente); 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );

	

	angle=45;

	glEnable(GL_COLOR_MATERIAL); //se não for habilitado o objeto ficará sem cor

	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING);

	// Habilita a luz de número 0
	glEnable(GL_LIGHT0);

	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);

	// Permite o uso de mascaras de cores
	glEnable(GL_BLEND);




}



// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divisão por zero
	if ( h == 0 ) h = 1;

	// Especifica o tamanho da viewport
	glViewport(0, 0, w, h);
 
	// Calcula a correção de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;

	EspecificaParametrosVisualizacao();
}

// Função callback chamada para gerenciar eventos do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN) {  // Zoom-in
			if (angle >= 10) angle -= 5;
		}
	if (button == GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN) {  // Zoom-out
			if (angle <= 130) angle += 5;
		}
	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}

void TeclasEspeciais(int key, int x, int y)
{
	if(key == GLUT_KEY_UP)
	{
		distance += 0.01f;
	}
	if(key == GLUT_KEY_DOWN)
	{
		distance -= 0.01f;
	}
}

// Programa Principal
int main(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400,350);
	glutCreateWindow("Visualizacao 3D");
	glutDisplayFunc(Desenha);
	glutIdleFunc(Desenha);
	glutSpecialFunc(TeclasEspeciais);
	glutReshapeFunc(AlteraTamanhoJanela);
	glutMouseFunc(GerenciaMouse);
	Inicializa();
	glutMainLoop();
}
