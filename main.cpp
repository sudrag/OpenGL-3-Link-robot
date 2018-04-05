
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>


#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

GLfloat cameraDistance = 12, cameraAngle = 0;

// angles = { Y rotation at shoulder, Z rotation at shoulder, Z rotation at elbow, X rotation at wrist }
int arm_angles[5] = {0, 0, 0, 0, 0};
enum { SHOULDER_Y, SHOULDER_Z, ELBOW_Z, WRIST_X, WRIST_Z };

void change_angle(int angle, int delta, int minimum = 0, int maximum = 180) {
    arm_angles[angle] = (arm_angles[angle] + delta) % 360;
    arm_angles[angle] = max(arm_angles[angle], minimum);
    arm_angles[angle] = min(arm_angles[angle], maximum);
}

// Construction the 3D robot
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glLoadIdentity();
    GLfloat x = cameraDistance * sin(cameraAngle);
    GLfloat z = cameraDistance * cos(cameraAngle);
    gluLookAt (x, 0.0, z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);    
    
    
    glPushMatrix();
        glRotatef((GLfloat) arm_angles[SHOULDER_Y], 0., 1., 0.);
        glRotatef((GLfloat) arm_angles[SHOULDER_Z], 0., 0., 1.);
    
        glTranslatef(1., 0., 0.);
        glPushMatrix();
            glScalef(2.0, 0.4, 1.0);
            glColor3f(1.0f, 1.0f, 1.0f);
            glutWireCube(1.);       // shoulder
        glPopMatrix();

        glTranslatef(1., 0., 0.);
        glRotatef((GLfloat) arm_angles[ELBOW_Z], 0., 0., 1.);
        glTranslatef(1., 0., 0.);
        glPushMatrix();
            glScalef(2.0, 0.4, 1.0);
            glColor3f(149./255., 138./255., 53./255.);
            glutWireCube(1.);       // elbow
        glPopMatrix();
    
        glTranslatef(1., 0., 0.);
        glRotatef((GLfloat) arm_angles[WRIST_Z], 0., 0., 1.);
        glRotatef((GLfloat) arm_angles[WRIST_X], 1., 0., 0.);

        glTranslatef(1., 0., 0.);
        glPushMatrix();
            glScalef(2.0, 0.4, 1.0);
            glColor3f(50./255., 186./255., 196./255.);
            glutWireCube(1.);       // wrist
        glPopMatrix();
    glPopMatrix();
    
    // Running the commands
    glutSwapBuffers();
}


// Calling function to resize window
void reshape(GLsizei w, GLsizei h) {
    // Size of viewport
	glViewport(0, 0, w, h);
    
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

    glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 300.0);
    
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Function to change camera based on keys
void specialKeys(int key, int x, int y) {
    GLfloat distanceDelta = 1.0, angleDelta = 5 * M_PI / 180.0;
    if(key == GLUT_KEY_UP) {
        cameraDistance -= distanceDelta;
        cameraDistance = max((GLfloat)2.0, cameraDistance);
    }
    if(key == GLUT_KEY_DOWN) {
        cameraDistance += distanceDelta;
    }
    if(key == GLUT_KEY_LEFT) {
        cameraAngle -= angleDelta;
    }
    if(key == GLUT_KEY_RIGHT) {
        cameraAngle += angleDelta;
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    int delta = 5;

    switch (key) {
        case 27: //ESC key
            exit(0);
        case 'q':
            change_angle(SHOULDER_Y, delta, -180, 0);
            break;
        case 'a':
            change_angle(SHOULDER_Y, -delta, -180, 0);
            break;
        case 'w':
            change_angle(SHOULDER_Z, delta, -90, 90);
            break;
        case 's':
            change_angle(SHOULDER_Z, -delta, -90, 90);
            break;
        case 'e':
            change_angle(ELBOW_Z, delta, 0, 135);
            break;
        case 'd':
            change_angle(ELBOW_Z, -delta, 0, 135);
            break;
        case 'r':
            change_angle(WRIST_X, delta, -45, 45);
            break;
        case 'f':
            change_angle(WRIST_X, -delta, -45, 45);
            break;
        case 't':
            change_angle(WRIST_Z, delta, -15, 90);
            break;
        case 'g':
            change_angle(WRIST_Z, -delta, -15, 90);
            break;
    }
    glutPostRedisplay();
}


// Program Main
int main(int argc, char * argv[]) {
    glutInit(&argc, argv);    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(700, 700);
    glutCreateWindow("RRR Robot");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(specialKeys);
    glutKeyboardFunc(keyboard);

    // Initializtion 
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black screen
    
    glutMainLoop();
}
