 #include <glut.h>
int counterCOINS = 0;
int health = 5;
bool gameStarted = false;
bool collect = false;
bool gameOver = false;
int collX = 700;
bool collision = false;
int charX = 100;
int charY = 320;
int screenWidth = 800;
int screenHeight = 800;
int sx1 = 200;
bool isColliding = false;
int sy = 0;
bool collectedThisFrame = false;
int speed = 20;
bool gamePaused = false;
void resetGame() {
    counterCOINS = 0;
    health = 5;
    gameStarted = true;
    collect = false;
    gameOver = false;
    collX = 700;
    collision = false;
    charX = 100;
    charY = 320;
    sx1 = 200;
    isColliding = false;
    sy = 0;
    collectedThisFrame = false;
    speed = 20;
    gamePaused = false;
}
void drawHeart() {
    glBegin(GL_POLYGON);
    glColor3f(0.89, 0.17, 0.18);
    glVertex2i(100, 800);
    glVertex2i(150, 750);
    glVertex2i(100, 700);
    glVertex2i(50, 750);
    glEnd();
}
void changeColor() {
    if (collect) {
        glColor3f(1, 1, 1);
    }
    else {
        glColor3f(0.99, 0.73, 0.12);
    }
}
void drawCollision() {
    glBegin(GL_POLYGON);
    glColor3f(0.2f, 0.2f, 0.2f);
    glVertex2i(800, 200);
    glVertex2i(780, 200);
    glVertex2i(780, 180);
    glVertex2i(750, 180);
    glVertex2i(720, 180);
    glVertex2i(720, 200);
    glVertex2i(700, 200);
    glVertex2i(700, 0);
    glVertex2i(800, 0);
    glEnd();
}
void drawCounterCoins() {
    glPushMatrix();
    GLUquadric* quadric1 = gluNewQuadric();
    double radius1 = 50;
    int slices1 = 30;
    glColor3f(0.99, 0.73, 0.12);
    glTranslatef(600, 750, 0);
    gluDisk(quadric1, 0, radius1, slices1, 1);
    glPopMatrix();
    glPushMatrix();
    GLUquadric* quadric2 = gluNewQuadric();
    double radius2 = 35;
    int slices2 = 30;
    glColor3f(1.00, 0.55, 0.00);
    glTranslatef(600, 750, 0);
    gluDisk(quadric2, 0, radius2, slices2, 1);
    glPopMatrix();
}
void drawCoins() {
    glPushMatrix();
    GLUquadric* quadric1 = gluNewQuadric();
    double radius1 = 50;
    int slices1 = 30;
    changeColor();
    glTranslatef(200, 180, 0);
    gluDisk(quadric1, 0, radius1, slices1, 1);
    glPopMatrix();
    glPushMatrix();
    GLUquadric* quadric2 = gluNewQuadric();
    double radius2 = 35;
    int slices2 = 30;
    glColor3f(1.00, 0.55, 0.00);
    glTranslatef(200, 180, 0);
    gluDisk(quadric2, 0, radius2, slices2, 1);
    glPopMatrix();
}
void changeColor2() {
    if (collision) {
        glColor3f(1, 0, 0);
    }
    else {
        glColor3f(0, 0, 0);
    }
}
void drawChar() {
    glPushMatrix();
    // Head
    GLUquadric* quadric1 = gluNewQuadric();
    double radius1 = 40;   // Adjust the head radius
    int slices1 = 20;      // Adjust the number of slices
    changeColor2();
    glTranslatef(charX, charY, 0); // Adjust the position of the head based on charX and charY
    gluDisk(quadric1, 0, radius1, slices1, 1);
    glPopMatrix();
    // Body
    glBegin(GL_LINES);
    changeColor2();
    glVertex2i(charX, charY - 20);
    glVertex2i(charX, charY - 70);
    glVertex2i(charX, charY - 70);
    glVertex2i(charX - 80, charY - 120);
    glVertex2i(charX, charY - 70);
    glVertex2i(charX + 75, charY - 120);
    glVertex2i(charX, charY - 70);
    glVertex2i(charX, charY - 220);
    glVertex2i(charX, charY - 220);
    glVertex2i(charX + 55, charY - 320);
    glVertex2i(charX, charY - 220);
    glVertex2i(charX - 64, charY - 320);
    glEnd();
}
void drawText(float x, float y, const char* text) {
    glRasterPos2f(x, y);
    for (int i = 0; text[i] != '\0'; ++i) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
}
void drawNumber(float x, float y, int value) {
    glRasterPos2f(x, y);

    // Convert the integer to characters
    int temp = value, numDigits = 0;
    do {
        temp /= 10;
        numDigits++;
    } while (temp != 0);

    char buffer[10];
    for (int i = numDigits - 1; i >= 0; i--) {
        buffer[i] = '0' + value % 10;
        value /= 10;
    }
    // Draw the characters
    for (int i = 0; i < numDigits; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, buffer[i]);
    }
}
void checkCollision() {
    if (charX + 40 >= collX && charX - 40 <= collX + 100 && charY + 220 >= sy && charY <= sy + 530) {
        if (!isColliding && health > 0) {
            collision = true;
            isColliding = true;
            health--;
            if (health == 0) {
                gameOver = true;
            }
        }
    }
    else {
        collision = false;
        isColliding = false;
    }
}
void drawStopText() {
    drawText(250, 400, "GAME PAUSED");
    drawText(250, 350, "Press 'x' to Resume");
}
void drawGameOverText() {
    glColor3f(1.0, 0.0, 0.0);
    drawText(300, 400, "GAME OVER!");
    drawText(300, 350, "Press Esc to Exit");
    drawText(250, 300, "Press Enter for New Game");
}
void gameRun() {
    glBegin(GL_QUADS);
    glColor3f(0.05, 0.63, 0.91);
    glVertex2f(0, 0);
    glVertex2f(screenWidth, 0);
    glVertex2f(screenWidth, screenHeight);
    glVertex2f(0, screenHeight);
    glEnd();
    drawHeart();
    // Draw counter coins
    drawCounterCoins();
    glPushMatrix();
    glTranslated(sx1 - 100, sy, 0);
    drawCoins();
    glPopMatrix();
    glPushMatrix();
    glTranslated(collX - 600, sy, 0);
    drawCollision();
    glPopMatrix();
    // Draw character
    drawChar();
    // Draw counterCOINS value
    glColor3f(1.0, 0.0, 0.0);
    drawNumber(700, 740, counterCOINS);
    glColor3f(1.0, 0.0, 0.0);
    drawNumber(200, 740, health);
    glFlush();
}
void startScreen() {

    glColor3f(1.00, 0.00, 0.00);
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(screenWidth, 0);
    glVertex2f(screenWidth, screenHeight);
    glVertex2f(0, screenHeight);
    glEnd();
    glColor3f(0.00, 0.48, 0.24);
    glBegin(GL_QUADS);
    glVertex2f(200, 200);
    glVertex2f(600, 200);
    glVertex2f(600, 600);
    glVertex2f(200, 600);
    glEnd();
    glColor3f(0.0, 0.0, 0.0);
    drawText(280, 500, "**Super Pedro Game**");
    drawText(280, 450, "Press Click Left to Start ");
    drawText(280, 300, "Press x to Pause ");
    drawText(280, 400, "Press Esc to Exit");
    drawText(280, 350, "Use Arrow Keys or Mouse to Move");
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    if (gameOver) {
        drawGameOverText();
    }
    else if (gamePaused) {
        drawStopText();
    }
    else if (gameStarted) {
        gameRun();
    }

    else {
        startScreen();
    }

    glFlush();
}
void passiveMotion(int x, int y) {

    charX = x;
    charY = screenHeight - y;
    glutPostRedisplay();
}
void specFuncUp(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP: charY -= 400;  break;
    default:
        break;
    }
    glutPostRedisplay();
}
void mouseClick(int button, int state, int x, int y) {
    switch (button) {
    case GLUT_LEFT_BUTTON:

        gameStarted = true;
        break;

    }
    glutPostRedisplay();
}
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 13: // Enter key
        if (gameOver) {
            resetGame();
        }
        break;
    case 27: // Escape key
        exit(0);
        break;
    case 'x':

        gamePaused = !gamePaused;
        break;

    }
    glutPostRedisplay();
}
void checkCollection() {
  
    if (charX + 40 >= sx1 && charX - 40 <= sx1 + 100 && charY + 220 >= sy && charY <= sy + 530) {
        if (!collectedThisFrame) {
            collect = true;
            counterCOINS++;
            collectedThisFrame = true;
            speed -= 1;
            if (speed == 0) {
                speed = 0;
            }
        }
    }

    else {
        collect = false;
        collectedThisFrame = false;
    }
}
void Timer(int valu) {
    sx1 -= 17;

    collX -= 15;
    if (gamePaused) {
        glutTimerFunc(speed, Timer, 0);
        return;
    }
    if (sx1 < -200) {
        sx1 = 800;

    }

    if (collX < -200) {
        collX = 800;
    }

    checkCollection();
    checkCollision();
    glutPostRedisplay();
    glutTimerFunc(speed, Timer, 0);
}
void specialKeys(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:
        charY += 400;
        charX += 400;


        break;
    case GLUT_KEY_DOWN:
        charY -= 10;

        break;
    case GLUT_KEY_LEFT:
        charX -= 10;
        break;
    case GLUT_KEY_RIGHT:
        charX += 10;
        break;
    }


    if (charX > screenWidth) {
        charX = 0;
    }
    else if (charX < 0) {
        charX = screenWidth;
    }

    if (charY > screenHeight) {
        charY = 0;
    }
    else if (charY < 0) {
        charY = screenHeight;
    }

    glutPostRedisplay();
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(300, 0);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Super Pedro Game");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
   glutPassiveMotionFunc(passiveMotion);
    glutSpecialUpFunc(specFuncUp);
    glutMouseFunc(mouseClick);
    glutTimerFunc(speed, Timer, 0);
    gluOrtho2D(0, screenWidth, 0, screenHeight);
    glutMainLoop();
    return 0;
}

