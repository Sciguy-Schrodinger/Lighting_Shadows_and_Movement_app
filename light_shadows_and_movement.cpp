#include <GL/glut.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>

using namespace std;

float width = 1000;
float height = 800;

float red = 0.0f;
float green = 0.0f;
float blue = 0.0f;

bool RED = false;
bool GREEN = false;
bool BLUE = false;

float rot_x = 0.0f;
float rot_y = 0.0f;
float rot_z = 0.0f;

float translate_x = 0.0f;
float translate_y = 0.0f;
float translate_z = 0.0f;
float translate_step = 0.01f;
float translate_bounds = 1.5f;

int start_colour = rand()%3;
int start_rot_axis = rand()%3;
int start_moving_axis = rand()%3;
int dir = rand()%2;

int tilesX = 10;        
int tilesY = 10;

int TMin = 0;
int TMax = 100;
bool grow = true;

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
}

void background() {
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    int tileSizeW = width / tilesX;
    int tileSizeH = height / tilesY;
    
    for(int row = 0; row < tilesX; row++){
        for(int col = 0; col < tilesY; col++){
            float dx = (float)(row - tilesX/2) / (tilesX/2);
            float dy = (float)(col - tilesY/2) / (tilesY/2);
            float dist = sqrt(dx*dx + dy*dy);
	    
            float scale = 0.05f + 0.95f * (1.0f - (1.0f / (1.0f + 5.0f * dist * dist)));
	    
            int w = (int)(tileSizeW * scale);
            int h = (int)(tileSizeH * scale);

	    if(w < 1){
	      w = 1;
	    }

	    if(h < 1){
	      h = 1;
	    }
	    
            int x = row * tileSizeW + (tileSizeW + w) / 2;
            int y = col * tileSizeH + (tileSizeH + h) / 2;
            
            bool isBlack = (row + col) % 2 == 0;
            if(isBlack){
                glColor3f(0.0f, 0.0f, 0.0f);
	    }
            else{
                glColor3f(1.0f, 1.0f, 1.0f);
            }
	    
            glBegin(GL_QUADS);
            glVertex2i(x, y);
            glVertex2i(x + w, y);
            glVertex2i(x + w, y + h);
            glVertex2i(x, y + h);
            glEnd();
        }
    }
    
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}

void update(){
  if(start_colour == 0){
    blue = 0.0;
    green = 0.0;
    red += 0.02;

    if(red > 1.0){
      red = 0.0;
      start_colour = rand()%3;
    }
  }
  
  else if(start_colour == 1){
    blue += 0.02;
    green = 0.0;
    red = 0.0;

    if(blue > 1.0){
      blue = 0.0;
      start_colour = rand()%3;
    }
  }

  else if(start_colour == 2){
    blue = 0.0;
    green += 0.02;
    red = 0.0;

    if(green > 1.0){
      green = 0.0;
      start_colour = rand()%3;
    }
  }

  if(start_rot_axis == 0){
    rot_x = 0.0;
    rot_y = 0.0;
    rot_z += 5.0;

    if(rot_z > 360.0){
      rot_z = 0.0;
      start_rot_axis = rand()%3;
    }
  }
  
  else if(start_rot_axis == 1){
    rot_x += 5.0;
    rot_y = 0.0;
    rot_z = 0.0;

    if(rot_x > 360.0){
      rot_x = 0.0;
      start_rot_axis = rand()%3;
    }
  }

  else if(start_rot_axis == 2){
    rot_x = 0.0;
    rot_y += 5.0;
    rot_z = 0.0;

    if(rot_y > 360.0){
      rot_y = 0.0;
      start_rot_axis = rand()%3;
    }
  }

  if(start_moving_axis == 0 && dir == 0){
    translate_x += translate_step;
    if(translate_x >= translate_bounds){
      start_moving_axis = rand()%3;
      dir = rand()%2;
    }
}

  else if(start_moving_axis == 0 && dir == 1){
    translate_x -= translate_step;
    if(translate_x <= translate_bounds){
      start_moving_axis = rand()%3;
      dir = rand()%2;
    }
}

  else if(start_moving_axis == 1 && dir == 0){
    translate_y += translate_step;
    if(translate_y >= translate_bounds){
      start_moving_axis = rand()%3;
      dir = rand()%2;
    }
}
  
  else if(start_moving_axis == 1 && dir == 1){
    translate_y -= translate_step;
    if(translate_y <= -translate_bounds){
      start_moving_axis = rand()%3;
      dir = rand()%2;
    }
}

  else if(start_moving_axis == 2 && dir == 0){
    translate_z += translate_step;
    if(translate_z >= translate_bounds){
      start_moving_axis = rand()%3;
      dir = rand()%2;
    }
}

  else if(start_moving_axis == 2 && dir == 1){
    translate_z -= translate_step;
    if(translate_z <= -translate_bounds){
      start_moving_axis = rand()%3;
      dir = rand()%2;
    }
}
}

void slowUpdate(int val){
  if(grow){
    tilesX += 10;
    tilesY += 10;
  }

  else{
    tilesX -= 10;
    tilesY -= 10;
  }
  
  if((tilesX >= TMax || tilesY >= TMax) || (tilesX <= TMin || tilesY <=TMin)){
      grow = !grow;
      tilesX = (tilesX > TMax) ? TMax : (tilesX < TMin) ? TMin : tilesX;
      tilesY = tilesX; 
    }

  if(tilesX < 0){
    tilesX = 0;
  }
  
  if(tilesX > 200){
    tilesX = 200;
  }
  if(tilesY < 0){
    tilesY = 0;
  }
  if(tilesY > 200){
    tilesY = 200;
  }

  glutTimerFunc(200, slowUpdate, 0); 
 }

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    background();
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 3.0,   // eye position
              0.0, 0.0, 0.0,   // look at origin
              0.0, 1.0, 0.0);  // up vector
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat light_pos[] = {1.0f, 1.0f, 1.0f, 1.0f};  
    GLfloat light_ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat light_diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

    glEnable(GL_LIGHT1);
    GLfloat light1_pos[] = {-1.0f, 1.0f, 2.0f, 1.0f};
    glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
 
    update();

    glRotatef(rot_x,1.0f,0.0f,0.0f);
    glRotatef(rot_y,0.0f,1.0f,0.0f);
    glRotatef(rot_z,0.0f,0.0f,1.0f);

    GLfloat material_diffuse[] = {red, green, blue, 1.0f};
    
    if(start_moving_axis == 0){
    glTranslatef(translate_x,0.0f,0.0f);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
    glutSolidTeapot(0.5);
    }
    
    else if(start_moving_axis == 1){
    glTranslatef(0.0f,translate_y,0.0f);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
    glutSolidTeapot(0.5);
    }
    
    else{
    glTranslatef(0.0f,0.0f,translate_z);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
    glutSolidTeapot(0.3);
    }

    glutSwapBuffers();
}

void idle(){
  glutPostRedisplay();
}

int main(int argc, char** argv){
    srand(time(0));
    start_colour = rand()%3;
    start_rot_axis = rand()%3;
    start_moving_axis = rand()%3;
    dir = rand()%2;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutCreateWindow("Lighting, Shadows and Movement!");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(200,slowUpdate,0);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
