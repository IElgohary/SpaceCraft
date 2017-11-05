#include "GLUT/glut.h"
#include <math.h>
#include <iostream>
#include "TextureBuilder.h"

using namespace std;

int meteor1_radius = 20;
int meteor2_radius = 26;
int meteor3_radius = 10;
bool meteor1 = true;
bool meteor1_up= true;
int up_count = 0;
bool meteor2 = true;
bool meteor3 = true;
int meteor3_rotate = 0;
bool powerup = true;
int x_meteor1 = 1000;
int y_meteor1 = 300;
int x_meteor2 = 800;
int y_meteor2 = 300;
int x_meteor3 = 1600;
int y_meteor3 = 300;
int x_powerup = 2400;
int y_powerup = 300;
int powerup_rotate = 0;
int powerup_side = 50;
int x_main = 400;
int y_main = 250;
int windowHeight = 500;
int windowWidth = 800;
int base_length = 120;
bool game = true;
int speed = 2;
int life = 3;
int ship_rotate = 0;
float curve = 2;
float curve2 = 3;
int p0_3[2];
int p1_3[2];
int p2_3[2];
int p3_3[2];
int y_curve3 = 0;
int p0_2[2];
int p1_2[2];
int p2_2[2];
int p3_2[2];
int y_curve2 = 0;
bool flag = true;
int x_background = 0; 
int x_background1 = windowWidth * 2; 
GLuint texID;
GLuint texID1;

void drawQuad(int x, int y, int w, int h)
{
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);
    glEnd();
}

// draws a circle using OpenGL's gluDisk, given (x,y) of its center and tis radius
void drawCircle(int x, int y, float r)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    GLUquadric *quadObj = gluNewQuadric();
    gluDisk(quadObj, 0, r, 50, 50);
    glPopMatrix();
}

int* bezier(float t, int* p0_3,int* p1_3,int* p2_3,int* p3_3)
{
    int res [2];
	res[0]=pow((1-t),3)*p0_3[0]+3*t*pow((1-t),2)*p1_3[0]+3*pow(t,2)*(1-t)*p2_3[0]+pow(t,3)*p3_3[0];
    res[1]=pow((1-t),3)*p0_3[1]+3*t*pow((1-t),2)*p1_3[1]+3*pow(t,2)*(1-t)*p2_3[1]+pow(t,3)*p3_3[1];
    return res;
}

void powerupMovement()
{
    if (powerup) {
        powerup_rotate++;
        x_powerup -= speed;
        if (x_powerup <= -100) 
        {
            x_powerup = windowWidth + 2000;
            y_powerup = 0 + (rand() % static_cast<int>( windowHeight - powerup_side/2 + 1));
        }

        if (x_powerup >= x_main - 60 && x_powerup   <= x_main + 90 && y_powerup <= y_main + 10 && y_powerup  >= y_main- 20)
        {
            glClearColor(1, 0, 0, 0);
            x_main += 100;
            life ++;
            x_powerup = windowWidth + 2000;
            y_powerup = 0 + (rand() % static_cast<int>( windowHeight - powerup_side/2 + 1));
        }else {
            glClearColor(0, 0, 0, 0);
        }
    }
}

void obstacleMovement()
{   
    if (meteor1) {
        x_meteor1 -= speed;
        if (meteor1_up) {
            y_meteor1+= speed*4/5;
            up_count++;
            if (y_meteor1 >= windowHeight-50 || up_count >= 70) {
                meteor1_up = false;
            }
        } else {
            y_meteor1-= speed*4/5;
            up_count--;
            if (y_meteor1 <= 50 || up_count <= 0) {
                meteor1_up = true;
            }
        }
        if (x_meteor1 <= -100) 
        {
            x_meteor1 = windowWidth + 200;
            do{
                y_meteor1 = 0 + (rand() % static_cast<int>( windowHeight - meteor1_radius + 1));
            } while(y_meteor1 >= windowHeight - 70 || y_meteor1 <= 70);
            meteor1_up = true;
        }

        if (x_meteor1 + meteor1_radius >= x_main - 60 && x_meteor1 - meteor1_radius <= x_main + 90 && y_meteor1 - meteor1_radius<= y_main + 30 && y_meteor1+ meteor1_radius >= y_main-30)
        {
            glClearColor(1, 0, 0, 0);
            x_main -= 100;
            life --;
            x_meteor1 = windowWidth +200;
            y_meteor1 = 0 + (rand() % static_cast<int>( windowHeight - meteor1_radius + 1));
        }else {
            glClearColor(0, 0, 0, 0);
        }
    }
    if (meteor2) {
        p0_2[0]=0;
        p0_2[1]=372 + y_curve2;
    
        p1_2[0]=windowWidth;
        p1_2[1]=149 + y_curve2;
    
        p2_2[0]=492;
        p2_2[1]=549 + y_curve2;
    
        p3_2[0]=689;
        p3_2[1]=326 + y_curve2;

        curve2 -= 0.003;
        
        int* points= bezier(curve2, p0_2,p1_2,p2_2,p3_2);
        x_meteor2 = points[0];
        y_meteor2 = points[1];

        if (curve2 <= 0) 
        {
            curve2 = 3.0;
            points = bezier(curve2, p0_2,p1_2,p2_2,p3_2);
            x_meteor2 = points[0];
            y_meteor2 = points[1];
            y_curve2 = 0 + (rand() % static_cast<int>( 300 - meteor2_radius + 1));
           
        }

        if ((x_meteor2 + meteor2_radius  >= x_main - 60 && x_meteor2 - meteor2_radius  <= x_main + 90 && y_meteor2 - meteor2_radius <= y_main+30 && y_meteor2 + meteor2_radius >= y_main-30))
        {
            glClearColor(1, 0, 0, 0);
            x_main -= 100;
            curve2 = 2.0;
            life --;
            y_curve2 = 0 + (rand() % static_cast<int>( 300 - meteor2_radius + 1));
        }else {
            glClearColor(0, 0, 0, 0);
        }
    }

    if (meteor3) {
        
        p0_3[0]=0;
        p0_3[1]=154 + y_curve3;
    
        p1_3[0]=windowWidth;
        p1_3[1]=400 + y_curve3;
    
        p2_3[0]=8;
        p2_3[1]=400 + y_curve3;
    
        p3_3[0]=windowWidth;
        p3_3[1]=162 + y_curve3;

        curve -= 0.003;
        
        int* points= bezier(curve, p0_3,p1_3,p2_3,p3_3);
        x_meteor3 = points[0];
        y_meteor3 = points[1];

        if (curve <= 0) 
        {
            curve = 2.0;
            points = bezier(curve, p0_3,p1_3,p2_3,p3_3);
            x_meteor3 = points[0];
            y_meteor3 = points[1];
            y_curve3 = 0 + (rand() % static_cast<int>( 200 - meteor3_radius + 1));
           
        }

        if ((x_meteor3 + meteor3_radius  >= x_main - 60 && x_meteor3 - meteor3_radius  <= x_main + 90 && y_meteor3 - meteor3_radius <= y_main+30 && y_meteor3 + meteor3_radius >= y_main-30))
        {
            glClearColor(1, 0, 0, 0);
            x_main -= 100;
            curve = 2.0;
            life --;
            y_curve3 = 0 + (rand() % static_cast<int>( 200 - meteor3_radius + 1));
        }else {
            glClearColor(0, 0, 0, 0);
        }
    }
}




void backgroundMovement() { 
    
    if (flag && x_background <= -windowWidth ) {
        flag = false; 
        x_background1 = windowWidth; 
    }
    if (!flag && x_background1 <= -windowWidth * 2 ) {
        flag = true; 
        x_background = windowWidth; 
    }
    if ( x_background > -windowWidth*2) {
        x_background -= 5;
    }
    if ( x_background1 > -windowWidth*3) {
        x_background1 -= 5;
    }
    
}

void Timer(int value)
{
    backgroundMovement(); 
    obstacleMovement();
    powerupMovement();
    glutPostRedisplay();
    if (game) {
        glutTimerFunc(0, Timer, 0);
    }
}

void checkLife(){
    if ( life >= 6) {
        life = 3;
        game = false;
        glPushMatrix();
        glColor3f(0,0.5, 0.5) ;
        drawQuad(0,0,windowWidth,windowHeight);
        glPopMatrix();
        glFlush();
        for( int i = 0 ; i < 1000000000; i++);
        x_meteor1 = 3000;
        y_meteor1 = 300;
        x_meteor2 = 800;
        y_meteor2 = 300;
        x_meteor3 = 2500;
        y_meteor3 = 300;
        x_powerup = 4800;
        y_powerup = 300;
        powerup_rotate = 0;
        x_main = 400;
        y_main = 250;
        speed++;
        ship_rotate = 0;
        curve = 2;
        curve2 = 3;
        flag = true;
        x_background = 0; 
        x_background1 = windowWidth * 2; 
        game = true;
        glutTimerFunc(0, Timer, 0);
    }
    if ( life <= 0) {
        game = false;
        glPushMatrix();
        glColor3f(0.5,0, 0) ;
        drawQuad(0,0,windowWidth,windowHeight);
        glColor3f(1,1, 1);
        glPopMatrix();
    }
}


// Keyboard handler function
void Key(unsigned char key, int x, int y)
{   
    if (game) {
        if( y_main < windowHeight-50 && (key == 'w' || key == 'W')){ 
            y_main += 10;
            if (ship_rotate < 25){
                ship_rotate +=1;
            }
        }
        
        if( y_main >= 50 && (key == 'S' || key == 's')){
            if (ship_rotate > -25){
                ship_rotate -=1;
            }
            y_main -= 10;
        }

        glutPostRedisplay();
    }
}

void KeyUp(unsigned char key, int x, int y){
    if (key==27)
        exit(EXIT_SUCCESS);
    else
    if (game) {
        if((key == 'w' || key == 'W')){ 
            ship_rotate =0;
        }
        
        if((key == 'S' || key == 's')){
            ship_rotate =0;
        }

    }
    glutPostRedisplay();
}

void drawBackGround() { 
    float rep = 1;
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texID);
    glColor3f(1, 1, 1) ;
    glPushMatrix();
    glTranslatef(x_background, 0, 0);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0, windowHeight, 0);
    glTexCoord2f(rep, 0.0f);
    glVertex3f(windowWidth*2, windowHeight, 0);
    glTexCoord2f(rep, rep);
    glVertex3f(windowWidth*2, 0, 0);
    glTexCoord2f(0.0f, rep);
    glVertex3f(0, 0, 0);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texID1);
    glColor3f(1, 1, 1) ;
    glPushMatrix();
    glTranslatef(x_background1, 0, 0);
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1) ;
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0, windowHeight, 0);
    glTexCoord2f(rep, 0.0f);
    glVertex3f(windowWidth*3, windowHeight, 0);
    glTexCoord2f(rep, rep);
    glVertex3f(windowWidth*3, 0, 0);
    glTexCoord2f(0.0f, rep);
    glVertex3f(0, 0, 0);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}

void Display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawBackGround(); 
    glBindTexture(GL_TEXTURE_2D, 0);
    // Planet
    glPushMatrix();
    glColor3f(0.5, 0.5, 0);
    drawCircle(windowWidth + 50, windowHeight/2, 100);
    glPopMatrix();

    // Drawing the Ship
    glPushMatrix();
    
    glTranslated(x_main, y_main, 0);
    glRotated(ship_rotate,0,0,1);
    
    glPushMatrix();
    glColor3f(1, 1, 1);
    glBegin(GL_TRIANGLES);
    glVertex2f(0+base_length - 30, 0);
    glVertex2f(0 - base_length/3, 0 );
    glVertex2f(0 - base_length/3, 0 +30);
    glEnd();

    glColor3f(1,0.5, 0.5);
    drawQuad(0 - 10, 0, 2, 30);

    glColor3f(0.6, 0.2, 0);
    drawCircle(0, 0 +10,15);
    drawQuad(0 - base_length/2, 0, base_length, 5);
   
    glColor3f(0.6, 0.2, 0);
    glBegin(GL_TRIANGLES);
    glVertex2f(0 + 50, 0);
    glVertex2f(0 , 0 );
    glVertex2f(0, 0 +25);
    glEnd();

    glColor3f(1,0.5, 0.5);
    drawQuad(0 - 15, 0, 2, 30);

    glColor3f(1, 1, 1);
    glBegin(GL_TRIANGLES);
    glVertex2f(0+base_length/2, 0);
    glVertex2f(0 - base_length/2, 0 );
    glVertex2f(0 - base_length/2, 0 +25);
    glEnd();

    glColor3f(0.6, 0.2, 0);
    glBegin(GL_TRIANGLES);
    glVertex2f(0+base_length/3, 0);
    glVertex2f(0 - base_length/2, 0 );
    glVertex2f(0 - base_length/2, 0 -25);
    glEnd();


    glColor3f(0, 0, 0);
    drawQuad(0 - base_length/2, 0 - 10, 35, 10);
    drawCircle(0 - base_length/4, 0 - 10, 5);
    glPopMatrix();
    glPopMatrix();

    
    // Obstacles
    glColor3f(1, 0, 0);
    if(meteor1) {    
        drawCircle(x_meteor1, y_meteor1, meteor1_radius);
    }
    if(meteor2) {
        drawCircle(x_meteor2, y_meteor2, meteor2_radius);
    }
    if(meteor3) {
        drawCircle(x_meteor3, y_meteor3, meteor3_radius);
    }

    // powerup
    if(powerup) {
        glPushMatrix();
        glTranslated(x_powerup, y_powerup,0);
        glPushMatrix();
        glColor3f(0, 1, 0);
        drawQuad(0, 0, powerup_side, powerup_side);
        glPopMatrix();
        glPopMatrix();
    }

    checkLife();
    glFlush();
}

int main(int argc, char **argr)
{

    glutInit(&argc, argr);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("A1");
    glutDisplayFunc(Display);
    glColor3f(0, 0, 0);
    glutTimerFunc(0, Timer, 0);
    glutKeyboardFunc(Key);
    glutKeyboardUpFunc(KeyUp);
    gluOrtho2D(0.0, windowWidth, 0.0, windowHeight);
    loadBMP(&texID, "textures/space.bmp",windowWidth*2, windowHeight/2, true);
    loadBMP(&texID1, "textures/box.bmp",windowWidth*3, windowHeight/5, true);
    
    glutMainLoop();

    return 0;
}



