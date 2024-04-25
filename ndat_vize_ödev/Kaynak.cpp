#include <GL/glut.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>

enum GameType {
    GAME_1,
    GAME_2,
    hazirlayanlar
};

GameType selectedGame = GAME_1;

float rotationX = 0.0f;
float rotationY = 0.0f;
float rotationZ = 0.0f;
float translationX = 0.0f;
float translationY = 0.0f;
float translationZ = -5.0f;

int mouseX = 0;
int mouseY = 0;
bool isMousePressed = false;

bool isAutoRotate = false;

void drawCube()
{
    glBegin(GL_QUADS);


    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);


    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);


    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);


    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);


    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);


    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);

    glEnd();


    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos3f(0.0f, 0.0f, 1.1f);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '1');

    glRasterPos3f(0.0f, 0.0f, -1.1f);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '6');

    glRasterPos3f(0.0f, 1.1f, 0.0f);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '2');

    glRasterPos3f(0.0f, -1.1f, 0.0f);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '5');

    glRasterPos3f(1.1f, 0.0f, 0.0f);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '3');

    glRasterPos3f(-1.1f, 0.0f, 0.0f);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '4');
}

void display2()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(translationX, translationY, translationZ);
    glRotatef(rotationX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotationY, 0.0f, 1.0f, 0.0f);
    if (isAutoRotate) // Otomatik d nme durumunda
    {


        int randomAngle = (rand() % 4) * 90;
        rotationX = rotationY = randomAngle;
        if (randomAngle == 90) {
            glRotatef(randomAngle, 1.0f, 0.0f, 0.0f);
        }
        if (randomAngle == 180 || randomAngle == 0) {
            glRotatef(randomAngle, 0.0f, 1.0f, 0.0f);
        }
        if (randomAngle == 270) {
            glRotatef(randomAngle, 0.0f, 0.0f, 1.0f);
        }
    }

    drawCube();
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos3f(-0.8f, -0.8f, -5.0f);
    const char* message = "Kupu hareket ettirmek icin w, a, s, d tuslarini kullanin. Sag tik ile dondurun. Rastgele dondurmek icin x tusuna basin.";
    for (const char* c = message; *c != '\0'; c++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }


    glutSwapBuffers();
}



void reshape1(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, static_cast<float>(width) / static_cast<float>(height), 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void mouse1(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        mouseX = x;
        mouseY = y;
        isMousePressed = true;
    }
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        isMousePressed = false;
    }
}

void motion(int x, int y)
{
    if (isMousePressed)
    {
        rotationX += (y - mouseY) * 0.1f;
        rotationY += (x - mouseX) * 0.1f;

        mouseX = x;
        mouseY = y;

        glutPostRedisplay();
    }
}

void keyboard1(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
        translationY += 0.1f;
        break;
    case 's':
        translationY -= 0.1f;
        break;
    case 'a':
        translationX -= 0.1f;
        break;
    case 'd':
        translationX += 0.1f;
        break;
    case 'x':
        isAutoRotate = !isAutoRotate;
        break;
    }

    glutPostRedisplay();
}


int screenWidth = 800;
int screenHeight = 600;

int ballRadius = 10;
int ballX = screenWidth / 2;
int ballY = screenHeight / 2;
int ballSpeedX = 4;
int ballSpeedY = 4;


int rectangleWidth = 80;
int rectangleHeight = 10;
int rectangleX = (screenWidth - rectangleWidth) / 2;
int rectangleY = 10;
int rectangleSpeed = 5;


bool moveLeft = false;
bool moveRight = false;

int score = 0;

void drawBall()
{
    glColor3f(0.0f, 0.0f, 1.0f);
    glPushMatrix();
    glTranslatef(ballX, ballY, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);
    for (int i = 0; i <= 360; i++)
    {
        float angle = i * 3.14159f / 180;
        glVertex2f(cos(angle) * ballRadius, sin(angle) * ballRadius);
    }
    glEnd();
    glPopMatrix();
}

void drawRectangle()
{
    glColor3f(1.0f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(rectangleX, rectangleY, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(rectangleWidth, 0.0f);
    glVertex2f(rectangleWidth, rectangleHeight);
    glVertex2f(0.0f, rectangleHeight);
    glEnd();
    glPopMatrix();
}

void drawScore()
{
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos2i(10, screenHeight - 20);
    char scoreText[20];

    for (int i = 0; scoreText[i] != '\0'; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, scoreText[i]);
    }
}

void updateBall()
{

    ballX += ballSpeedX;
    ballY += ballSpeedY;

    if (ballX + ballRadius > screenWidth || ballX - ballRadius < 0)
    {
        ballSpeedX = -ballSpeedX;
    }
    if (ballY + ballRadius > screenHeight || ballY - ballRadius < 0)
    {
        ballSpeedY = -ballSpeedY;
    }


    if (ballY - ballRadius <= rectangleY + rectangleHeight && ballX >= rectangleX && ballX <= rectangleX + rectangleWidth)
    {
        ballSpeedY = -ballSpeedY;
        score++;
        ballSpeedX++;
        ballSpeedY++;
        rectangleSpeed++;
    }


    if (ballY - ballRadius > screenHeight)
    {
        score = 0;
        ballX = screenWidth / 2;
        ballY = screenHeight / 2;
        ballSpeedX = 4;
        ballSpeedY = 4;
    }
    if (ballY - ballRadius < 0)
    {
        score = 0;
        ballSpeedX = 4;
        ballSpeedY = 4;
        rectangleSpeed = 5;
    }
}

void updateRectangle()
{
    if (moveLeft && rectangleX > 0)
    {
        rectangleX -= rectangleSpeed;
    }
    if (moveRight && rectangleX < screenWidth - rectangleWidth)
    {
        rectangleX += rectangleSpeed;
    }
}

void display1()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawBall();
    drawRectangle();
    drawScore();

    glutSwapBuffers();
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;
    }
}

void keyboardSpecial(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        moveLeft = true;
        break;
    case GLUT_KEY_RIGHT:
        moveRight = true;
        break;
    }
}

void keyboardSpecialUp(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        moveLeft = false;
        break;
    case GLUT_KEY_RIGHT:
        moveRight = false;
        break;
    }
}

void timer(int)
{
    updateBall();
    updateRectangle();
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, 0);
}


void drawText(const char* text, float x, float y) {
    glRasterPos2f(x, y);
    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text);
        text++;
    }
}


void drawBox(float x, float y, float width, float height) {

    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y - height);
    glVertex2f(x, y - height);
    glEnd();


    glLineWidth(2.0);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y - height);
    glVertex2f(x, y - height);
    glEnd();
}



void display3() {
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0f, 0.0f, 0.0f);
    drawText("Ahmet Kanadli 210401071", -0.4f, 0.4f);
    drawText("Mehmet Tagil 200401051", -0.4f, 0.2f);
    drawText("Muhammed Ali Fidan 200401001", -0.4f, 0.0f);
    drawText("Emre Baran Arca 210401017", -0.4f, -0.2f);
    drawText("Ahmet Yildirim 210401084", -0.4f, -0.4f);

    glutSwapBuffers();
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);


    glBegin(GL_QUADS);
    glColor3f(0.8, 0.8, 0.8);
    glVertex2f(-1.0, 1.0);
    glVertex2f(1.0, 1.0);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(1.0, -1.0);
    glVertex2f(-1.0, -1.0);
    glEnd();


    if (selectedGame == GAME_1)
        glColor3f(0.9, 0.9, 0.9);
    else
        glColor3f(0.7, 0.7, 0.7);
    drawBox(-0.4, 0.1, 0.8, 0.2);


    if (selectedGame == GAME_2)
        glColor3f(0.9, 0.9, 0.9);
    else
        glColor3f(0.7, 0.7, 0.7);
    drawBox(-0.4, -0.2, 0.8, 0.2);

    if (selectedGame == hazirlayanlar)
        glColor3f(0.9, 0.9, 0.9);
    else
        glColor3f(0.7, 0.7, 0.7);
    drawBox(-0.4, -0.2, 0.8, 0.2);


    glColor3f(0.0, 0.0, 0.0);
    drawText("Zar Atma Oyunu", -0.1, 0.00);


    glColor3f(0.0, 0.0, 0.0);
    drawText("Top Oyunu", -0.1, -0.30);

    glColor3f(0.0, 0.0, 0.0);
    drawText("Hazırlayanlar", -0.1, -0.55);
    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        float normalizedX = (float)x / glutGet(GLUT_WINDOW_WIDTH);
        float normalizedY = (float)(glutGet(GLUT_WINDOW_HEIGHT) - y) / glutGet(GLUT_WINDOW_HEIGHT);

        if (normalizedX >= 0.2 && normalizedX <= 0.6 && normalizedY >= 0.3 && normalizedY <= 0.5) {

            selectedGame = GAME_1;

            glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
            glutInitWindowSize(screenWidth, screenHeight);
            glutCreateWindow("Oyun");
            glutDisplayFunc(display1);
            glutReshapeFunc(reshape);
            glutKeyboardFunc(keyboard);
            glutSpecialFunc(keyboardSpecial);
            glutSpecialUpFunc(keyboardSpecialUp);
            glutTimerFunc(0, timer, 0);
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            glutMainLoop();


            std::cout << "Oyun 1 �al��t�r�l�yor..." << std::endl;
        }
        else if (normalizedX >= 0.2 && normalizedX <= 0.6 && normalizedY >= 0.5 && normalizedY <= 0.7) {

            selectedGame = GAME_2;
            glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
            glutInitWindowSize(800, 600);
            glutCreateWindow("Basit 3D Oyun Tuslar : w ,a, ,s, d, x ,sagClick");

            glEnable(GL_DEPTH_TEST);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

            glutDisplayFunc(display2);
            glutReshapeFunc(reshape1);
            glutMouseFunc(mouse1);
            glutMotionFunc(motion);
            glutKeyboardFunc(keyboard1);

            glutMainLoop();


            std::cout << "Oyun 2 �al��t�r�l�yor..." << std::endl;
        }
        else {

            glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
            glutInitWindowSize(800, 600);
            glutCreateWindow("Hazirlayanlar");

            glutDisplayFunc(display3);

            glutMainLoop();

        }
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Oyun Menusu");

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    glutMainLoop();
    return 0;
}
