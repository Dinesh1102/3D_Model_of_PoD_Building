// built upon the model provided by https://github.com/Abhishek572002/3D_POD_USING_openGL

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

#include <math.h>
#include <iostream>
#include <vector>

#include <cstdlib> // for getRandomNumber() and sgetRandomNumber()
#include <ctime>   // for time()
#include <cmath>   // for trigonometric functions
#define PI 3.14
using namespace std;


int maxDepth = 10; //used in tree function to control the depth of branching allowed
bool lighting = false; //used to toggle lighting
GLfloat position[] = {0, 0, 0, 1};

int ptr = 0; // keeps track of which idx in randomNumbers was most recently called in getRandomNumber()
int randomNumbers[100000]; // used to store a sequence of pseudo-random numbers to deterministically render random generation with seeding
// utility to fetch pseudo-random numbers from randomNumbers[]
int getRandomNumber()
{
    ptr++;
    return randomNumbers[ptr - 1];
}

//function to set the lighting
void setLighting()
{
    GLfloat lig_diff[] = {0.8, 0.8, 0.8, 1.0};  //diffuse light component
    GLfloat lig_amb[] = {1, 1, 1, 0.5}; //ambient light component
    GLfloat light_position[] = {100.0, 100.0, 0, 1}; //position of light

    glClearColor(0.3, 0.4, 0.8, 1);
    glShadeModel(GL_SMOOTH); //shading component uses SMOOTH SHADING

    //add defined components to a light source
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lig_diff);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHTING);

    GLfloat ambient[] = {0.8, 0.8, 0.8, 1}; //ambient light component
    GLfloat spotexpo[] = {5};   //spot exponent component
    GLfloat quadAttenuation[] = {1};    //quadratic attenuation to make it realisitc

    //add defined components to a light source
    glLightfv(GL_LIGHT2, GL_POSITION, position);
    glLightfv(GL_LIGHT2, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, lig_diff);
    glLightfv(GL_LIGHT2, GL_SPOT_EXPONENT, spotexpo);
    glLightfv(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, quadAttenuation);
    
    //add material properties
    GLfloat shininess = 20;
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess); // The shininess parameter
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    // glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1); 
    // // glEnable(GL_LIGHT5);
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT6);
}

//set color and add material properties
void setMyColor(vector<float> col)
{
    GLfloat color[] = {col[0], col[1], col[2]};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
}

//add name to a building
void building_name(string s, int x, int y, int z)
{
    glColor3f(1, 0, 0);
    for (float i = 0; i < s.size(); i++)
    {
        glPushMatrix();
        setMyColor({1, 0, 0});
        glTranslatef(x + 2.1f * i, y, z + 0.0);
        glScalef(0.04, 0.02, 1);
        glLineWidth(3);
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, s[i]);
        glPopMatrix();
    }
}

//function to draw a circle on xy plane
void drawCircle(float x, float y, float z, float r)
{
    float i = 0.0f;
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(x, y, z); // Center
    for (i = 0.0f; i <= 360; i++)
        glVertex3f(r * cos(M_PI * i / 180.0) + x, r * sin(M_PI * i / 180.0) + y, z);
    glEnd();
}

// function to draw road
void draw_road()
{
    glColor3f(1, 0.9, 0.9);

    setMyColor({1, 0.9, 0.9});
    glBegin(GL_POLYGON);
    glVertex3f(-10, 0.1, -300);
    glVertex3f(10, 0.1, -300);
    glVertex3f(10, 0.1, 12);
    glVertex3f(-10, 0.1, 12);
    glEnd();
    setMyColor({1, 0.9, 0.9});
    glBegin(GL_POLYGON);
    glVertex3f(22, 0.1, 30);
    glVertex3f(29, 0.1, 30);
    glVertex3f(39, 0.1, 0);
    glVertex3f(30, 0.1, 0);
    glEnd();
    setMyColor({1, 0.9, 0.9});
    glBegin(GL_POLYGON);
    glVertex3f(46, 0.1, 30);
    glVertex3f(50, 0.1, 30);
    glVertex3f(52, 0.1, 0);
    glVertex3f(46, 0.1, 0);
    glEnd();
    setMyColor({1, 0.9, 0.9});
    glBegin(GL_POLYGON);
    glVertex3f(-62, 0.1, 30);
    glVertex3f(-54, 0.1, 30);
    glVertex3f(-47, 0.1, 0);
    glVertex3f(-54, 0.1, 0);
    glEnd();

    setMyColor({1, 0.9, 0.9});
    glBegin(GL_POLYGON);
    glVertex3f(-300, 0.1, 50);
    glVertex3f(-300, 0.1, 30);
    glVertex3f(300, 0.1, 30);
    glVertex3f(300, 0.1, 50);
    glEnd();
    //-85 0.1 -35
    setMyColor({1, 0.9, 0.9});
    glBegin(GL_POLYGON);
    glVertex3f(-300, 0.1, -35);
    glVertex3f(-60, 0.1, -34);
    glVertex3f(-64, 0.1, -51);
    glVertex3f(-300, 0.1, -52);
    glEnd();
    setMyColor({1, 0.9, 0.9});
    glBegin(GL_POLYGON);
    glVertex3f(-75, 0.1, -35);
    glVertex3f(-75, 0.1, -28);
    glVertex3f(-10, 0.1, -28);
    glVertex3f(-10, 0.1, -37);
    glVertex3f(-13, 0.1, -37);
    glVertex3f(-60, 0.1, -34);
    glEnd();
    setMyColor({1, 0.9, 0.9});
    glBegin(GL_POLYGON);
    glVertex3f(-50, 0.1, -28);
    glVertex3f(-50, 0.1, -18);
    glVertex3f(-40, 0.1, -18);
    glVertex3f(-40, 0.1, -28);
    glEnd();
    setMyColor({1, 0.9, 0.9});
    glBegin(GL_POLYGON);
    glVertex3f(-80, 0.1, -50);
    glVertex3f(-80, 0.1, -59);
    glVertex3f(-10, 0.1, -59);
    glVertex3f(-10, 0.1, -53);
    glVertex3f(-15, 0.1, -51);
    glVertex3f(-60, 0.1, -53);
    glEnd();
    setMyColor({1, 0.9, 0.9});
    glBegin(GL_POLYGON);
    glVertex3f(-62, 0.1, -54);
    glVertex3f(-55, 0.1, -54);
    glVertex3f(-58, 0.1, -74);
    glVertex3f(-64, 0.1, -74);
    glEnd();
    setMyColor({1, 0.9, 0.9});
    glBegin(GL_POLYGON);
    glVertex3f(10, 0.1, -58);
    glVertex3f(95, 0.1, -58);
    glVertex3f(95, 0.1, -55);
    glVertex3f(300, 0.1, -55);
    glVertex3f(300, 0.1, -35);
    glVertex3f(85, 0.1, -35);
    glVertex3f(85, 0.1, -32);
    glVertex3f(10, 0.1, -30);
    glEnd();
    setMyColor({1, 0.9, 0.9});
    glBegin(GL_POLYGON);
    glVertex3f(30, 0.1, -54);
    glVertex3f(36, 0.1, -54);
    glVertex3f(33, 0.1, -74);
    glVertex3f(27, 0.1, -74);
    glEnd();
    setMyColor({1, 0.9, 0.9});
    glBegin(GL_POLYGON);
    glVertex3f(40, 0.1, -33);
    glVertex3f(46, 0.1, -33);
    glVertex3f(45, 0.1, -3);
    glVertex3f(39, 0.1, -3);
    glEnd();
    setMyColor({1, 0.9, 0.9});
    glBegin(GL_POLYGON);
    glVertex3f(10, 0.1, -120);
    glVertex3f(95, 0.1, -120);
    glVertex3f(95, 0.1, -110);
    glVertex3f(300, 0.1, -110);
    glVertex3f(300, 0.1, -85);
    glVertex3f(85, 0.1, -95);
    glVertex3f(10, 0.1, -92);
    glEnd();
    setMyColor({1, 0.9, 0.9});
    glBegin(GL_POLYGON);
    glVertex3f(37, 0.1, -120);
    glVertex3f(42, 0.1, -120);
    glVertex3f(42, 0.1, -130);
    glVertex3f(37, 0.1, -130);
    glEnd();
    setMyColor({1, 0.9, 0.9});
    glBegin(GL_POLYGON);
    glVertex3f(38, 0.1, -82);
    glVertex3f(43, 0.1, -82);
    glVertex3f(43, 0.1, -102);
    glVertex3f(38, 0.1, -102);
    glEnd();
}
//function to draw a hemi-sphere (used as bulb for street-lights)
void drawHemisphere(float R)
{
    // set the emiissive material to emit yellowish light when light hits it
    GLfloat emission[] = {1.0f, 1.0f, 0.0f, 1.0f};
    glPushAttrib(GL_LIGHTING_BIT);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
    int i, j;

    glRotatef(90, 1.0, 0.0, 0.0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FRONT_FACE);

    int p = 60; // Number of longitudinal slices in the hemisphere.
    int q = 40; // Number of latitudinal slices in the hemisphere.

    for (j = 0; j < q; j++)
    {
        // draw One latitudinal triangle strip.
        glBegin(GL_TRIANGLE_STRIP);
        for (i = 0; i <= p; i++)
        {
            glVertex3f(R * cos((float)(j + 1) / q * PI / 2.0) * cos(2.0 * (float)i / p * PI),
                       R * sin((float)(j + 1) / q * PI / 2.0),
                       R * cos((float)(j + 1) / q * PI / 2.0) * sin(2.0 * (float)i / p * PI));
            glVertex3f(R * cos((float)j / q * PI / 2.0) * cos(2.0 * (float)i / p * PI),
                       R * sin((float)j / q * PI / 2.0),
                       R * cos((float)j / q * PI / 2.0) * sin(2.0 * (float)i / p * PI));
        }
        glEnd();
    }
    glPopAttrib();
}

//function to draw a solid cylinder (used as pole for street-lights)
void draw_cylinder(GLfloat radius, GLfloat height, GLfloat R, GLfloat G, GLfloat B)
{
    GLfloat x = 0.0;
    GLfloat y = 0.0;
    GLfloat angle = 0.0;
    GLfloat angle_stepsize = 0.1;

    /* Draw the tube */
    glColor3f(R, G, B);
    glBegin(GL_QUAD_STRIP);
    angle = 0.0;
    while (angle < 2 * PI)
    {
        x = radius * cos(angle);
        y = radius * sin(angle);
        glVertex3f(x, y, height);
        glVertex3f(x, y, 0.0);
        angle = angle + angle_stepsize;
    }

    glVertex3f(radius, 0.0, height);
    glVertex3f(radius, 0.0, 0.0);
    glEnd();

    /* Draw the circle on top of cylinder */
    glColor3f(R, G, B);
    glBegin(GL_POLYGON);
    angle = 0.0;
    while (angle < 2 * PI)
    {
        x = radius * cos(angle);
        y = radius * sin(angle);
        glVertex3f(x, y, height);
        angle = angle + angle_stepsize;
    }
    glVertex3f(radius, 0.0, height);
    glEnd();

    /* Draw the circle at the bottom of cylinder */
    glColor3f(R, G, B);
    glBegin(GL_POLYGON);
    angle = 0.0;
    while (angle < 2 * PI)
    {
        x = radius * cos(angle);
        y = radius * sin(angle);
        glVertex3f(x, y, 0.0);
        angle = angle + angle_stepsize;
    }
    glVertex3f(radius, 0.0, 0.0);

    glEnd();
}

//function to draw a street-light of one type (bigger one as found in front of pods)
void drawStreetLight(float x, float y, float z)
{
    // creating a light source that will be placed inside the street light bulb
    glPushMatrix();
    glScalef(0.4f, 0.4f, 0.4f);
    glPushMatrix();
    GLfloat light_ambient[] = {1.0, 1.0, 0.0, 1.0};
    GLfloat light_diffuse[] = {1, 1, 0, 1.0};
    GLfloat light_specular[] = {1.0, 1.0, 0.0, 1.0};
    GLfloat light_position[] = { x, y+18.5f, z-1.8f, 1.0 };

    GLfloat quad[] = {0.008};
    // glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glLightfv(GL_LIGHT6, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT6, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT6, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT6, GL_QUADRATIC_ATTENUATION, quad);

    glLightfv(GL_LIGHT6, GL_POSITION, light_position);
    GLfloat spot_direction[] = {0, 0, -1};
    glLightfv(GL_LIGHT6, GL_SPOT_DIRECTION, spot_direction);
    glLightf(GL_LIGHT6, GL_SPOT_CUTOFF, 180.0);
    glPopMatrix();

    // street light
    // first line
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(-90, 1, 0, 0);
    draw_cylinder(0.5, 20, 0, 0, 0);
    glTranslatef(-x, -y, -z);
    glRotatef(90, 1, 0, 0);
    glPopMatrix();

    // second line

    glPushMatrix();
    glTranslatef(x, y, z);
    glTranslatef(0, 19, -3.7);
    draw_cylinder(0.25, 5, 0, 0, 0);
    glTranslatef(-x, -y, -z);
    glTranslatef(-0, -19, -3.7);
    glPopMatrix();

    // hemisphere
    glPushMatrix();
    glTranslatef(x, y + 18.7, z - 2);
    glRotatef(90, 1, 0, 0);
    // You can draw the street light here, make sure it's lit up properly
    glColor3f(1, 1, 1);
    drawHemisphere(1.2);
    glTranslatef(-x, -y - 18.7, -z + 2);
    glRotatef(-90, 1, 0, 0);
    glPopMatrix();
    glPopMatrix();
}

//function to draw a street-light of one type (smaller one as of found in the gardens in between the pods)
void drawLightPole(GLfloat radius, GLfloat height, float x, float y, float z)
{
    
    glPushMatrix();
    glTranslatef(0, 0, -5);
    glPushMatrix();
    glScalef(0.05f, 0.05f, 0.05f);
    glPushMatrix();
    glRotatef(90, -1, 0, 0);
    glColor3f(0, 0, 0);

    glutSolidCylinder(radius, height, 8, 8);

    GLfloat emission[] = {1, 1, 1, 1};
    glPushAttrib(GL_LIGHTING_BIT);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
    glPushMatrix();
    glTranslatef(0, 0, height);
    // glColor3f(1, 1, 1);
    glutSolidCylinder(radius, height / 5, 8, 8);
    glPopMatrix();
    glPopAttrib();

    glPushMatrix();
    glTranslatef(0, 0, height * 1.2);
    glColor3f(0, 0, 0);
    glutSolidCylinder(radius, height / 10, 8, 8);
    glPopMatrix();

    glPushMatrix();
    GLfloat light_ambient[] = {0.9, 0.9, 0.9, 1.0};
    GLfloat light_diffuse[] = {1, 1, 1, 1.0};
    GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_position[] = {0, 0, height * 1.1f, 1.0};

    GLfloat quad[] = {0.0001};
    // glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, quad);

    glLightfv(GL_LIGHT1, GL_POSITION, light_position);
    GLfloat spot_direction[] = {0, -1, 0};
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 180.0);
    glPopMatrix();

    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
}

//function to draw the ground and fencing around the surroundings
void draw_ground()
{
    glColor3f(0.74, 0.62, 0.51);
    setMyColor({0.74, 0.62, 0.51});
    glBegin(GL_POLYGON);
    glVertex3f(-300, -0.1, -300);
    glVertex3f(-300, -0.1, 300);
    glVertex3f(300, -0.1, 300);
    glVertex3f(300, -0.1, -300);
    glEnd();

    // fencing
    glColor3f(0.67, 0.34, 0);
    glPushMatrix();
    setMyColor({0.67, 0.34, 0});
    glTranslatef(-300, 0, -300);
    glScalef(6, 20, 600);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    glColor3f(0.6, 0.3, 0);
    glPushMatrix();
    setMyColor({0.6, 0.3, 0});
    glTranslatef(-300, 0, -300);
    glScalef(600, 20, 6);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    glColor3f(0.67, 0.34, 0);
    glPushMatrix();
    setMyColor({0.67, 0.34, 0});
    glTranslatef(300, 0, -300);
    glScalef(6, 20, 600);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();
}

//function to draw a window of one type (that looks like a rectangle with circles on both sides)
void make_window(float xe, float ye, float offset, float l, float b, float xc, float yc, float zc)
{
    l -= 0.5;
    glColor3f(0.6, 0.6, 0.6);
    glPushMatrix();
    setMyColor({0.6, 0.6, 0.6});
    glTranslatef(xc, yc, zc);
    glTranslatef(xe, ye, offset);
    glScalef(l, b, 0);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    glNormal3f(0, 0, -offset);
    setMyColor({0.6, 0.6, 0.6});
    drawCircle(xe + xc, ye + b / 2 + yc, offset + zc, b / 2);
    glNormal3f(0, 0, -offset);
    setMyColor({0.6, 0.6, 0.6});
    drawCircle(xe + l + xc, ye + b / 2 + yc, offset + zc, b / 2);
}

//function to draw an entrance of a floor to which bridges are connected
void make_door(float xe, float ye, float offset, float l, float b, float xc, float yc, float zc)
{
    glColor3f(0.6, 0.6, 0.6);
    glPushMatrix();
    setMyColor({0.6, 0.6, 0.6});
    glTranslatef(xc, yc, zc);
    glTranslatef(xe, ye, offset);
    glScalef(l, b, 0);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();
}

//function to draw a window of other type (that looks just like a rectangle)
void make_floor_window(float xe, float ye, float offset, float l, float b, float xc, float yc, float zc)
{
    glColor3f(0.6, 0.6, 0.6);
    glPushMatrix();
    setMyColor({0.6, 0.6, 0.6});
    glTranslatef(xc, yc, zc);
    glTranslatef(xe, ye, offset);
    glScalef(l, b, 0);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();
}

//function used to draw a line between 2 points used while drawing the bridge
void drawBridge(float x1, float y1, float z1, float x2, float y2, float z2, float r, float g, float b)
{
    // Calculate midpoint between the two base points for the first bridge point
    glColor3f(r, g, b);

    glBegin(GL_LINES);
    glVertex3f(x1, y1, z1); // Base 1
    glVertex3f(x2, y2, z2); // Bridge point 1
    glEnd();
}

struct Point3D
{
    float x;
    float y;
    float z;
};

//to calculate the points that are equally spaced between 2 end-points of the bridge used to draw the bridge
std::vector<Point3D> getEquallySpacedPoints(const Point3D &startPoint, const Point3D &endPoint, int numPoints)
{
    std::vector<Point3D> points;

    // Calculate step size for each dimension
    float deltaX = (endPoint.x - startPoint.x) / (numPoints + 1);
    float deltaY = (endPoint.y - startPoint.y) / (numPoints + 1);
    float deltaZ = (endPoint.z - startPoint.z) / (numPoints + 1);

    // Generate intermediate points
    points.push_back(startPoint);
    for (int i = 1; i <= numPoints; ++i)
    {
        Point3D intermediatePoint;
        intermediatePoint.x = startPoint.x + i * deltaX;
        intermediatePoint.y = startPoint.y + i * deltaY;
        intermediatePoint.z = startPoint.z + i * deltaZ;
        points.push_back(intermediatePoint);
    }
    points.push_back(endPoint);
    return points;
}

//function to draw a cuboid that is present in combination with another below the bridge
void drawCuboid(Point3D startPoint1, Point3D startPoint3, Point3D reqpoint1, Point3D reqpoint2, Point3D point5, Point3D point6, Point3D point7, Point3D point8, float r, float g, float b)
{
    glBegin(GL_QUADS);
    // Top face
    glColor3f(r, g, b); // Faded white color

    glVertex3f(startPoint1.x, startPoint1.y, startPoint1.z);
    glVertex3f(reqpoint1.x, reqpoint1.y, reqpoint1.z);
    glVertex3f(reqpoint2.x, reqpoint2.y, reqpoint2.z);
    glVertex3f(startPoint3.x, startPoint3.y, startPoint3.z);

    // Front face
    glVertex3f(startPoint1.x, startPoint1.y, startPoint1.z);
    glVertex3f(reqpoint1.x, reqpoint1.y, reqpoint1.z);
    glVertex3f(point5.x, point5.y, point5.z);
    glVertex3f(point8.x, point8.y, point8.z);

    // Back face
    glVertex3f(startPoint3.x, startPoint3.y, startPoint3.z);
    glVertex3f(reqpoint2.x, reqpoint2.y, reqpoint2.z);
    glVertex3f(point7.x, point7.y, point7.z);
    glVertex3f(point6.x, point6.y, point6.z);

    // Bottom face
    glVertex3f(point5.x, point5.y, point5.z);
    glVertex3f(point6.x, point6.y, point6.z);
    glVertex3f(point7.x, point7.y, point7.z);
    glVertex3f(point8.x, point8.y, point8.z);

    // Right face
    glVertex3f(reqpoint1.x, reqpoint1.y, reqpoint1.z);
    glVertex3f(reqpoint2.x, reqpoint2.y, reqpoint2.z);
    glVertex3f(point7.x, point7.y, point7.z);
    glVertex3f(point8.x, point8.y, point8.z);

    // Left face
    glVertex3f(startPoint1.x, startPoint1.y, startPoint1.z);
    glVertex3f(startPoint3.x, startPoint3.y, startPoint3.z);
    glVertex3f(point6.x, point6.y, point6.z);
    glVertex3f(point5.x, point5.y, point5.z);

    glEnd();
}

//mid-point of 2 points
Point3D calculateMidpoint(const Point3D &point1, const Point3D &point2)
{
    Point3D midpoint;
    midpoint.x = (point1.x + point2.x) / 2.0f;
    midpoint.y = (point1.y + point2.y) / 2.0f;
    midpoint.z = (point1.z + point2.z) / 2.0f;
    return midpoint;
}

//function to draw the bottom face of the bridge
void bridgebottom(Point3D point1, Point3D point2, Point3D point3, Point3D point4)
{
    Point3D midpoint = calculateMidpoint(point1, point2);

    float length = point2.x - point1.x;

    float offset = 0.1f * length;

    // Calculate left and right points
    Point3D leftPoint1 = {midpoint.x + offset, midpoint.y, midpoint.z};
    Point3D rightPoint1 = {midpoint.x - offset, midpoint.y, midpoint.z};
    midpoint = calculateMidpoint(point3, point4);
    // std::cout << "Midpoint: (" << midpoint.x << ", " << midpoint.y << ", " << midpoint.z << ")\n";
    Point3D leftPoint2 = {midpoint.x + offset, midpoint.y, midpoint.z};
    Point3D rightPoint2 = {midpoint.x - offset, midpoint.y, midpoint.z};

    Point3D leftPoint3 = {leftPoint1.x, leftPoint1.y - 0.75f, leftPoint1.z};
    Point3D rightPoint3 = {rightPoint1.x, rightPoint1.y - 0.75f, rightPoint1.z};
    Point3D leftPoint4 = {leftPoint2.x, leftPoint2.y - 0.75f, leftPoint2.z};
    Point3D rightPoint4 = {rightPoint2.x, rightPoint2.y - 0.75f, rightPoint2.z};

    std::vector<Point3D> intermediatePoints = getEquallySpacedPoints(leftPoint3, leftPoint4, 16);
    std::vector<Point3D> intermediatePoints1 = getEquallySpacedPoints(rightPoint3, rightPoint4, 16);
    drawCuboid(leftPoint1, rightPoint1, rightPoint2, leftPoint2, leftPoint3, rightPoint3, rightPoint4, leftPoint4, 0.85f, 0.85f, 0.85f);
    Point3D slant1 = intermediatePoints[1];
    Point3D slant2 = intermediatePoints1[1];
    Point3D slantopp1 = intermediatePoints[2];
    Point3D slantopp2 = intermediatePoints1[2];

    leftPoint3 = {slant1.x, slant1.y, slant1.z};
    rightPoint3 = {slant2.x, slant2.y, slant2.z};
    leftPoint4 = {slantopp1.x, slantopp1.y - 0.75f, slantopp1.z};
    rightPoint4 = {slantopp2.x, slantopp2.y - 0.75f, slantopp2.z};
    slant1 = intermediatePoints[15];
    slant2 = intermediatePoints1[15];
    leftPoint3 = {slantopp1.x, slantopp1.y - 0.75f, slantopp1.z};
    rightPoint3 = {slantopp2.x, slantopp2.y - 0.75f, slantopp2.z};
}


void bridge_helper(Point3D startPoint1, Point3D endPoint1, Point3D startPoint3, Point3D endPoint3)
{
    std::vector<Point3D> intermediatePoints = getEquallySpacedPoints(startPoint3, endPoint3, 12);
    std::vector<Point3D> intermediatePoints1 = getEquallySpacedPoints(startPoint1, endPoint1, 12);
    Point3D firstpoint = intermediatePoints[1];
    Point3D firstpoint2 = intermediatePoints1[1];
    intermediatePoints = getEquallySpacedPoints(startPoint1, firstpoint, 6);
    intermediatePoints1 = getEquallySpacedPoints(startPoint3, firstpoint2, 6);
    Point3D reqpoint1 = intermediatePoints[3];
    Point3D reqpoint2 = intermediatePoints1[3];
    Point3D point5 = {startPoint1.x, startPoint1.y - 1.5f, startPoint1.z};
    Point3D point6 = {startPoint3.x, startPoint3.y - 1.5f, startPoint3.z};
    Point3D point52 = {endPoint1.x, endPoint1.y - 1.0f, endPoint1.z};
    Point3D point62 = {endPoint3.x, endPoint3.y - 1.0f, endPoint3.z};
    Point3D point7 = {reqpoint1.x, reqpoint1.y - 1.25f, reqpoint1.z};
    Point3D point8 = {reqpoint2.x, reqpoint2.y - 1.25f, reqpoint2.z};
    drawCuboid(startPoint1, startPoint3, reqpoint2, reqpoint1, point5, point6, point8, point7, 0.98f, 0.98f, 0.98f);

    Point3D newpoint1 = intermediatePoints[1];
    Point3D newpoint2 = intermediatePoints1[1];

    Point3D point11 = {newpoint1.x, newpoint1.y - 2.5f - 0.01f, newpoint1.z};
    Point3D point12 = {newpoint2.x, newpoint2.y - 2.5f - 0.01f, newpoint2.z};
    Point3D point13 = {point7.x, point7.y - 1.25f - 0.01f, point7.z};
    Point3D point14 = {point8.x, point8.y - 1.25f - 0.01f, point8.z};
    drawCuboid(point5, point6, point8, point7, point11, point12, point14, point13, 0.98f, 0.98f, 0.98f);
    drawCuboid(point7, point8, point6, point5, point13, point14, point12, point11, 0.98f, 0.98f, 0.98f);
    newpoint1 = intermediatePoints[6];
    newpoint2 = intermediatePoints1[6];
    point13 = {newpoint1.x, newpoint1.y - 1.25f - 0.02f, newpoint1.z};
    point14 = {newpoint2.x, newpoint2.y - 1.25f - 0.02f, newpoint2.z};
    Point3D point15 = {newpoint1.x, newpoint1.y - 2.5f - 0.02f, newpoint1.z};
    Point3D point16 = {newpoint2.x, newpoint2.y - 2.5f - 0.02f, newpoint2.z};
    intermediatePoints = getEquallySpacedPoints(startPoint3, endPoint3, 12);
    intermediatePoints1 = getEquallySpacedPoints(startPoint1, endPoint1, 12);
    endPoint1 = intermediatePoints[11];
    endPoint3 = intermediatePoints1[11];
    point5 = {reqpoint1.x, reqpoint1.y - 0.4f, reqpoint1.z};
    point6 = {reqpoint2.x, reqpoint2.y - 0.4f, reqpoint2.z};
    point52 = {endPoint1.x, endPoint1.y - 0.4f, endPoint1.z};
    point62 = {endPoint3.x, endPoint3.y - 0.4f, endPoint3.z};
    glColor3f(0.7f, 0.7f, 0.7f); // Steel color

    drawCuboid(reqpoint1, reqpoint2, endPoint3, endPoint1, point5, point6, point62, point52, 0.85f, 0.85f, 0.85f);
    bridgebottom(point5, point6, point52, point62);
}

void buildbridge(Point3D pod1first, Point3D pod1second, Point3D pod2first, Point3D pod2second)
{
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.5f, 0.5f);
    glVertex3f(pod1first.x, pod1first.y, pod1first.z);
    glVertex3f(pod1second.x, pod1second.y, pod1second.z);
    glVertex3f(pod2second.x, pod2second.y, pod2second.z);
    glVertex3f(pod2first.x, pod2first.y, pod2first.z);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1.0f, 0.6f, 0.5f);
    glVertex3f(pod1first.x, pod1first.y + 2, pod1first.z); // Base 1
    glVertex3f(pod2first.x, pod2first.y + 2, pod2first.z); // Bridge point 1
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1.0f, 0.6f, 0.5f);
    glVertex3f(pod1second.x, pod1second.y + 2, pod1second.z);
    glVertex3f(pod2second.x, pod2second.y + 2, pod2second.z);
    glEnd();
    Point3D startPoint = {pod1second.x - 0.0001f, pod1second.y + 2 - 0.0001f, pod1second.z - 0.0001f};
    Point3D endPoint = {pod2second.x - 0.0001f, pod2second.y + 2 - 0.0001f, pod2second.z - 0.0001f};
    Point3D startPoint1 = {pod1second.x - 0.0001f, pod1second.y - 0.01f, pod1second.z - 0.0001f};
    Point3D endPoint1 = {pod2second.x - 0.0001f, pod2second.y - 0.01f, pod2second.z - 0.0001f};
    // Get 6 equally spaced points between the start and end points
    std::vector<Point3D> intermediatePoints = getEquallySpacedPoints(startPoint, endPoint, 12);
    std::vector<Point3D> intermediatePoints1 = getEquallySpacedPoints(startPoint1, endPoint1, 12);
    for (size_t i = 0; i < intermediatePoints.size(); ++i)
    {
        drawBridge(intermediatePoints[i].x, intermediatePoints[i].y, intermediatePoints[i].z,
                   intermediatePoints1[i].x, intermediatePoints1[i].y, intermediatePoints1[i].z,
                   1.0, 0.6, 0.5);
    }

    Point3D startPoint2 = {pod1first.x - 0.0001f, pod1first.y + 2.0f, pod1first.z - 0.0001f};
    Point3D endPoint2 = {pod2first.x - 0.0001f, pod2first.y + 2.0f, pod2first.z - 0.0001f};
    Point3D startPoint3 = {pod1first.x - 0.0001f, pod1first.y - 0.01f, pod1first.z - 0.0001f};
    Point3D endPoint3 = {pod2first.x - 0.0001f, pod2first.y - 0.01f, pod2first.z - 0.0001f};
    // Get 6 equally spaced points between the start and end points
    intermediatePoints = getEquallySpacedPoints(startPoint2, endPoint2, 12);
    intermediatePoints1 = getEquallySpacedPoints(startPoint3, endPoint3, 12);
    for (size_t i = 0; i < intermediatePoints.size(); ++i)
    {
        drawBridge(intermediatePoints[i].x, intermediatePoints[i].y, intermediatePoints[i].z,
                   intermediatePoints1[i].x, intermediatePoints1[i].y, intermediatePoints1[i].z,
                   1.0, 0.6, 0.5);
    }
    drawBridge(pod1first.x, pod1first.y + 1.5, pod1first.z, pod2first.x, pod2first.y + 1.5, pod2first.z, 1, 0.5, 0.5);
    drawBridge(pod1first.x, pod1first.y + 1, pod1first.z, pod2first.x, pod2first.y + 1, pod2first.z, 1, 0.5, 0.5);
    drawBridge(pod1first.x, pod1first.y + 0.5, pod1first.z, pod2first.x, pod2first.y + 0.5, pod2first.z, 1, 0.5, 0.5);
    drawBridge(pod1first.x, pod1first.y, pod1first.z, pod2first.x, pod2first.y, pod2first.z, 1, 0.5, 0.5);

    drawBridge(pod1second.x, pod1second.y + 1.5, pod1second.z, pod2second.x, pod2second.y + 1.5, pod2second.z, 1, 0.5, 0.5);
    drawBridge(pod1second.x, pod1second.y + 1, pod1second.z, pod2second.x, pod2second.y + 1, pod2second.z, 1, 0.5, 0.5);
    drawBridge(pod1second.x, pod1second.y + 0.5, pod1second.z, pod2second.x, pod2second.y + 0.5, pod2second.z, 1, 0.5, 0.5);
    drawBridge(pod1second.x, pod1second.y, pod1second.z, pod2second.x, pod2second.y, pod2second.z, 1, 0.5, 0.5);
    bridge_helper(startPoint1, endPoint1, startPoint3, endPoint3);
    bridge_helper(endPoint1, startPoint1, endPoint3, startPoint3);
}

//there would be different types of floors which are made according to how they exist and facilitate for drawing bridges
//function to draw ground floor of a pod
void floor_0(int x, int y, int z, int sx)
{

    // concrete building.
    glColor3f(0.8, 0.8, 0.8);
    glPushMatrix();
    setMyColor({0.8, 0.8, 0.8});
    glTranslatef(x, y, z);
    glScalef(sx, 9, -18);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    // openway 1
    glColor3f(0.6, 0.6, 0.6);
    glPushMatrix();
    setMyColor({0.6, 0.6, 0.6});
    glTranslatef(x, y, z);
    glTranslatef(16, 0, 0.1);
    glScalef(6, 5, 0);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    // circle
    glNormal3f(0, 0, 1);
    setMyColor({0.6, 0.6, 0.6});
    drawCircle(x + 23.5, y + 3.5, z + 0.1, 0.5);

    // windows column1

    make_window(26, 4, 0.1, 6, 1, x, y, z);
    make_window(26, 2, 0.1, 6, 1, x, y, z);

    // openway 2
    glColor3f(0.6, 0.6, 0.6);
    glPushMatrix();
    setMyColor({0.6, 0.6, 0.6});
    glTranslatef(x, y, z);
    glTranslatef(33, 0, 0.1);
    glScalef(4, 5, 0);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    // windows column2
    make_window(42, 4, 0.1, 3, 1, x, y, z);
    make_window(40, 2, 0.1, 5, 1, x, y, z);

    // windows column3
    make_window(46, 1, 0.1, 3, 1, x, y, z);

    // backside
    make_door(6, 0, -0.1, 3, 4, x, y, z - 18);
    make_floor_window(11, 1, -0.1, 3, 3, x, y, z - 18);
    make_door(17, 0, -0.1, 3, 4, x, y, z - 18);
    make_door(22, 0, -0.1, 1, 3, x, y, z - 18);

    // openway
    glColor3f(0.6, 0.6, 0.6);
    glPushMatrix();
    setMyColor({0.6, 0.6, 0.6});
    glTranslatef(x, y, z - 18);
    glTranslatef(26, 0, -0.1);
    glScalef(5, 5, 0);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    make_door(32, 0, -0.1, 3, 4, x, y, z - 18);
    make_floor_window(37, 1, -0.1, 3, 3, x, y, z - 18);
    make_floor_window(43, 1, -0.1, 3, 3, x, y, z - 18);
    make_door(47, 0, -0.1, 3, 4, x, y, z - 18);
    // make_door(56,-0,0.1,3,4,x,y,z-18);
}

//function to draw a type of floor of a pod
void floor_2(int x, int y, int z, int sx)
{
    // concrete building
    glColor3f(0.8, 0.8, 0.8);
    glPushMatrix();
    setMyColor({0.8, 0.8, 0.8});
    glTranslatef(x, y, z);
    glScalef(sx, 9, -18);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    // openway
    glColor3f(0.6, 0.6, 0.6);
    glPushMatrix();
    setMyColor({0.6, 0.6, 0.6});
    glTranslatef(x, y, z);
    glTranslatef(20.5, 3, 0.1);
    glScalef(4.5, 3, 0);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    // windows column1
    make_window(6, 5, 0.1, 3, 1, x, y, z);
    make_window(6, 2, 0.1, 3, 1, x, y, z);

    // windows column2
    make_window(10, 4, 0.1, 3, 1, x, y, z);
    make_window(10, 2, 0.1, 3, 1, x, y, z);

    // windows column3
    make_window(14, 5, 0.1, 3, 1, x, y, z);
    make_window(14, 2, 0.1, 5, 1, x, y, z);

    // windows column4
    make_window(26, 5, 0.1, 6, 1, x, y, z);
    make_window(26, 3, 0.1, 2, 1, x, y, z);
    make_window(29, 2, 0.1, 3, 1, x, y, z);

    // windows column5
    make_window(32, 5, 0.1, 3, 1, x, y, z);
    make_window(32, 2, 0.1, 3, 1, x, y, z);

    // windows column6
    make_window(36, 4, 0.1, 3, 1, x, y, z);
    make_window(36, 2, 0.1, 3, 1, x, y, z);

    // small door
    glColor3f(0.6, 0.6, 0.6);
    glPushMatrix();
    setMyColor({0.6, 0.6, 0.6});
    glTranslatef(x, y, z);
    glTranslatef(40, 3, 0.1);
    glScalef(2, 3, 0);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    // circle
    drawCircle(x + 43.5, y + 3.5, z + 0.1, 0.5);

    // windows column7
    make_window(46, 5, 0.1, 3, 1, x, y, z);
    make_window(46, 2, 0.1, 3, 1, x, y, z);

    // windows column8
    make_window(49.5, 5, 0.1, 3, 1, x, y, z);
    make_window(49.5, 3, 0.1, 3, 1, x, y, z);

    // backside
    y += 1;
    make_door(6, 0, -0.1, 3, 4, x, y, z - 18);
    make_floor_window(11, 1, -0.1, 3, 3, x, y, z - 18);
    make_door(17, 0, -0.1, 3, 4, x, y, z - 18);
    make_door(22, 0, -0.1, 1, 3, x, y, z - 18);

    // openway
    glColor3f(0.6, 0.6, 0.6);
    glPushMatrix();
    setMyColor({0.6, 0.6, 0.6});
    glTranslatef(x, y - 1, z - 18);
    glTranslatef(26, 0, -0.1);
    glScalef(5, 5, 0);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    make_door(32, 0, -0.1, 3, 4, x, y, z - 18);
    make_floor_window(37, 1, -0.1, 3, 3, x, y, z - 18);
    make_floor_window(43, 1, -0.1, 3, 3, x, y, z - 18);
    make_door(47, 0, -0.1, 3, 4, x, y, z - 18);
    make_door(56, -0, 0.1, 3, 4, x, y, z - 18);
}

//function to draw a type of floor of a pod
void floor_23(int x, int y, int z, int sx)
{
    // concrete building
    glColor3f(0.8, 0.8, 0.8);
    glPushMatrix();
    setMyColor({0.8, 0.8, 0.8});
    glTranslatef(x, y, z);
    glScalef(sx, 9, -18);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    // openway
    glColor3f(0.6, 0.6, 0.6);
    glPushMatrix();
    setMyColor({0.6, 0.6, 0.6});
    glTranslatef(x + 11.5f, y - 2, z);
    glTranslatef(20.5, 3, 0.1);
    glScalef(4.5, 5, 0);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    // windows column1
    make_window(6, 5, 0.1, 3, 1, x, y, z);
    make_window(6, 2, 0.1, 3, 1, x, y, z);

    // windows column2
    make_window(10, 4, 0.1, 3, 1, x, y, z);
    make_window(10, 2, 0.1, 3, 1, x, y, z);

    // windows column3
    make_window(14, 5, 0.1, 3, 1, x, y, z);
    make_window(14, 2, 0.1, 5, 1, x, y, z);

    // windows column4
    x = x - 9;
    make_window(26, 5, 0.1, 6, 1, x, y, z);
    make_window(26, 3, 0.1, 2, 1, x, y, z);
    make_window(29, 2, 0.1, 3, 1, x, y, z);

    // windows column5
    make_window(32, 5, 0.1, 3, 1, x, y, z);
    make_window(32, 2, 0.1, 3, 1, x, y, z);

    // windows column6
    make_window(36, 4, 0.1, 3, 1, x, y, z);
    make_window(36, 2, 0.1, 3, 1, x, y, z);
    x = x + 9;
    // small door
    glColor3f(0.6, 0.6, 0.6);
    glPushMatrix();
    setMyColor({0.6, 0.6, 0.6});
    glTranslatef(x, y, z);
    glTranslatef(40, 3, 0.1);
    glScalef(2, 3, 0);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    // circle
    drawCircle(x + 43.5, y + 3.5, z + 0.1, 0.5);

    // windows column7
    make_window(46, 5, 0.1, 3, 1, x, y, z);
    make_window(46, 2, 0.1, 3, 1, x, y, z);

    // windows column8
    make_window(49.5, 5, 0.1, 3, 1, x, y, z);
    make_window(49.5, 3, 0.1, 3, 1, x, y, z);

    // backside
    y += 1;
    make_door(6, 0, -0.1, 3, 4, x, y, z - 18);
    make_floor_window(11, 1, -0.1, 3, 3, x, y, z - 18);
    make_door(17, 0, -0.1, 3, 4, x, y, z - 18);
    make_door(22, 0, -0.1, 1, 3, x, y, z - 18);

    // openway
    glColor3f(0.6, 0.6, 0.6);
    glPushMatrix();
    setMyColor({0.6, 0.6, 0.6});
    glTranslatef(x, y - 1, z - 18);
    glTranslatef(26, 0, -0.1);
    glScalef(5, 5, 0);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    make_door(32, 0, -0.1, 3, 4, x, y, z - 18);
    make_floor_window(37, 1, -0.1, 3, 3, x, y, z - 18);
    make_floor_window(43, 1, -0.1, 3, 3, x, y, z - 18);
    make_door(47, 0, -0.1, 3, 4, x, y, z - 18);
    make_door(56, -0, 0.1, 3, 4, x, y, z - 18);
}

//function to draw a type of floor of a pod
void floor_h2(int x, int y, int z, int sx)
{
    // concrete building
    glColor3f(0.8, 0.8, 0.8);
    glPushMatrix();
    setMyColor({0.8, 0.8, 0.8});
    glTranslatef(x, y, z);
    glScalef(sx, 9, -18);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    // openway
    glColor3f(0.6, 0.6, 0.6);
    glPushMatrix();
    setMyColor({0.6, 0.6, 0.6});
    glTranslatef(x, y, z);
    glTranslatef(20.5, 3, 0.1);
    glScalef(4.5, 3, 0);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    // windows column1
    make_window(6, 5, 0.1, 3, 1, x, y, z);
    make_window(6, 2, 0.1, 3, 1, x, y, z);

    // windows column2
    make_window(10, 4, 0.1, 3, 1, x, y, z);
    make_window(10, 2, 0.1, 3, 1, x, y, z);

    // windows column3
    make_window(14, 5, 0.1, 3, 1, x, y, z);
    make_window(14, 2, 0.1, 5, 1, x, y, z);

    // windows column4
    make_window(26, 5, 0.1, 6, 1, x, y, z);
    make_window(26, 3, 0.1, 2, 1, x, y, z);
    make_window(29, 2, 0.1, 3, 1, x, y, z);

    // windows column5
    make_window(32, 5, 0.1, 3, 1, x, y, z);
    make_window(32, 2, 0.1, 3, 1, x, y, z);

    // windows column6
    make_window(36, 4, 0.1, 3, 1, x, y, z);
    make_window(36, 2, 0.1, 3, 1, x, y, z);

    // small door
    glColor3f(0.6, 0.6, 0.6);
    glPushMatrix();
    setMyColor({0.6, 0.6, 0.6});
    glTranslatef(x, y - 3.0f, z);
    glTranslatef(45 - 1.3f, 3, 0.1);
    glScalef(4.5, 5, 0);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();


    // backside
    y += 1;
    make_door(6, 0, -0.1, 3, 4, x, y, z - 18);
    make_floor_window(11, 1, -0.1, 3, 3, x, y, z - 18);
    make_door(17, 0, -0.1, 3, 4, x, y, z - 18);
    make_door(22, 0, -0.1, 1, 3, x, y, z - 18);

    // openway
    glColor3f(0.6, 0.6, 0.6);
    glPushMatrix();
    setMyColor({0.6, 0.6, 0.6});
    glTranslatef(x, y - 1, z - 18);
    glTranslatef(26, 0, -0.1);
    glScalef(5, 5, 0);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    make_door(32, 0, -0.1, 3, 4, x, y, z - 18);
    make_floor_window(37, 1, -0.1, 3, 3, x, y, z - 18);
    make_floor_window(43, 1, -0.1, 3, 3, x, y, z - 18);
    make_door(47, 0, -0.1, 3, 4, x, y, z - 18);
    make_door(56, -0, 0.1, 3, 4, x, y, z - 18);
}

//function to draw a type of floor of a pod
void floor_h(int x, int y, int z, int sx)
{
    // concrete building
    glColor3f(0.8, 0.8, 0.8);
    glPushMatrix();
    setMyColor({0.8, 0.8, 0.8});
    glTranslatef(x, y, z);
    glScalef(sx, 9, -18);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    
    // openway
    glColor3f(0.6, 0.6, 0.6);
    glPushMatrix();
    setMyColor({0.6, 0.6, 0.6});
    glTranslatef(x, y, z);
    glTranslatef(20.5, 3, 0.1);
    glScalef(4.5, 3, 0);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    // windows column1
    make_window(6, 5, 0.1, 3, 1, x, y, z);
    make_window(6, 2, 0.1, 3, 1, x, y, z);

    // windows column2
    make_window(10, 4, 0.1, 3, 1, x, y, z);
    make_window(10, 2, 0.1, 3, 1, x, y, z);

    // windows column3
    make_window(14, 5, 0.1, 3, 1, x, y, z);
    make_window(14, 2, 0.1, 5, 1, x, y, z);

    // windows column4
    make_window(26, 5, 0.1, 6, 1, x, y, z);
    make_window(26, 3, 0.1, 2, 1, x, y, z);
    make_window(29, 2, 0.1, 3, 1, x, y, z);

    // windows column5
    make_window(32, 5, 0.1, 3, 1, x, y, z);
    make_window(32, 2, 0.1, 3, 1, x, y, z);

    // windows column6
    make_window(36, 4, 0.1, 3, 1, x, y, z);
    make_window(36, 2, 0.1, 3, 1, x, y, z);

    // small door
    glColor3f(0.6, 0.6, 0.6);
    glPushMatrix();
    setMyColor({0.6, 0.6, 0.6});
    glTranslatef(x, y - 0.3f, z);
    glTranslatef(40, 3, 0.1);
    glScalef(4.5, 5, 0);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    // circle
    // drawCircle(x + 43.5, y + 3.5, z + 0.1, 0.5);

    // windows column7
    make_window(46, 5, 0.1, 3, 1, x, y, z);
    make_window(46, 2, 0.1, 3, 1, x, y, z);

    // windows column8
    make_window(49.5, 5, 0.1, 3, 1, x, y, z);
    make_window(49.5, 3, 0.1, 3, 1, x, y, z);

    // backside
    y += 1;
    make_door(6, 0, -0.1, 3, 4, x, y, z - 18);
    make_floor_window(11, 1, -0.1, 3, 3, x, y, z - 18);
    make_door(17, 0, -0.1, 3, 4, x, y, z - 18);
    make_door(22, 0, -0.1, 1, 3, x, y, z - 18);

    // openway
    glColor3f(0.6, 0.6, 0.6);
    glPushMatrix();
    setMyColor({0.6, 0.6, 0.6});
    glTranslatef(x, y - 1, z - 18);
    glTranslatef(26, 0, -0.1);
    glScalef(5, 5, 0);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    make_door(32, 0, -0.1, 3, 4, x, y, z - 18);
    make_floor_window(37, 1, -0.1, 3, 3, x, y, z - 18);
    make_floor_window(43, 1, -0.1, 3, 3, x, y, z - 18);
    make_door(47, 0, -0.1, 3, 4, x, y, z - 18);
    make_door(56, -0, 0.1, 3, 4, x, y, z - 18);
}

//function to draw a floor that is a bit inside compared to others
void floor_in(int x, int y, int z, int sx)
{
    // concrete building.
    glColor3f(0.7, 0.7, 0.7);
    glPushMatrix();
    setMyColor({0.7, 0.7, 0.7});
    glTranslatef(x, y, z);
    glScalef(sx, 9, -18);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    make_door(6, 0, 0.1, 3, 4, x, y, z);
    make_floor_window(11, 1, 0.1, 3, 3, x, y, z);
    make_door(17, 0, 0.1, 3, 4, x, y, z);
    make_door(22, 0, 0.1, 1, 3, x, y, z);

    // openway
    glColor3f(0.6, 0.6, 0.6);
    glPushMatrix();
    setMyColor({0.6, 0.6, 0.6});
    glTranslatef(x, y, z);
    glTranslatef(26, 0, 0.1);
    glScalef(5, 7, 0);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    make_door(32, 0, 0.1, 3, 4, x, y, z);
    make_floor_window(37, 1, 0.1, 3, 3, x, y, z);
    make_floor_window(43, 1, 0.1, 3, 3, x, y, z);
    make_door(47, 0, 0.1, 3, 4, x, y, z);
    make_door(52, 0, 0.1, 3, 4, x, y, z);

    // backside
    z = z - 19.0;
    glColor3f(0.6, 0.6, 0.6);
    drawCircle(x + 8.5, y + 6.5, z + 0.1, 0.5);

    // windows column1
    make_window(10, 6, 0.1, 3, 1, x, y, z);

    // windows column2
    make_window(13, 4, 0.1, 3, 1, x, y, z);
    make_window(13, 2, 0.1, 3, 1, x, y, z);

    // windows column3
    make_window(17, 4, 0.1, 3, 1, x, y, z);
    make_window(17, 2, 0.1, 3, 1, x, y, z);

    // openway(need this)
    glColor3f(0.6, 0.6, 0.6);
    glPushMatrix();
    setMyColor({0.6, 0.6, 0.6});
    glTranslatef(x, y, z);
    glTranslatef(22, 4 - 0.3, 0.1);
    glScalef(5, 4, 0);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    // circle
    drawCircle(x + 28.5, y + 5.5, z + 0.1, 0.5);

    // small door
    glColor3f(0.6, 0.6, 0.6);
    glPushMatrix();
    setMyColor({0.6, 0.6, 0.6});
    glTranslatef(x, y, z);
    glTranslatef(32, 4, 0.1);
    glScalef(2, 3, 0);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    // windows column4
    make_window(35, 6, 0.1, 3, 1, x, y, z);
    make_window(35, 4, 0.1, 3, 1, x, y, z);

    // windows column5
    make_window(39, 4, 0.1, 3, 1, x, y, z);
    make_window(39, 2, 0.1, 3, 1, x, y, z);

    // windows column6
    make_window(43, 6, 0.1, 6, 1, x, y, z);
    make_window(46, 4, 0.1, 3, 1, x, y, z);

    // small door
    glColor3f(0.6, 0.6, 0.6);
    glPushMatrix();
    setMyColor({0.6, 0.6, 0.6});
    glTranslatef(x, y, z);
    glTranslatef(50, 4, 0.1);
    glScalef(2, 3, 0);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    // small circle
    drawCircle(x + 53.5, y + 5.5, z + 0.1, 0.5);

    // windows column7
    make_window(55, 4, 0.1, 3, 1, x, y, z);
}

//function to draw a type of floor of a pod
void floor_h1(int x, int y, int z, int sx)
{
    // concrete building.
    glColor3f(0.7, 0.7, 0.7);
    glPushMatrix();
    setMyColor({0.7, 0.7, 0.7});
    glTranslatef(x, y, z);
    glScalef(sx, 9, -18);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    make_door(6, 0, 0.1, 3, 4, x, y, z);
    make_floor_window(11, 1, 0.1, 3, 3, x, y, z);
    make_door(17, 0, 0.1, 3, 4, x, y, z);
    make_door(22, 0, 0.1, 1, 3, x, y, z);

    // openway
    glColor3f(0.6, 0.6, 0.6);
    glPushMatrix();
    setMyColor({0.6, 0.6, 0.6});
    glTranslatef(x, y, z);
    glTranslatef(26, 0, 0.1);
    glScalef(5, 7, 0);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    make_door(32, 0, 0.1, 3, 4, x, y, z);
    make_floor_window(37, 1, 0.1, 3, 3, x, y, z);
    make_floor_window(43, 1, 0.1, 3, 3, x, y, z);
    make_door(47, 0, 0.1, 3, 4, x, y, z);
    make_door(52, 0, 0.1, 3, 4, x, y, z);

    // backside
    z = z - 19.0;
    glColor3f(0.6, 0.6, 0.6);
    drawCircle(x + 8.5, y + 6.5, z + 0.1, 0.5);

    // windows column1
    make_window(10, 6, 0.1, 3, 1, x, y, z);

    // windows column2
    make_window(13, 4, 0.1, 3, 1, x, y, z);
    make_window(13, 2, 0.1, 3, 1, x, y, z);

    // windows column3
    make_window(17, 4, 0.1, 3, 1, x, y, z);
    make_window(17, 2, 0.1, 3, 1, x, y, z);

    // openway(need this)
    glColor3f(0.6, 0.6, 0.6);
    glPushMatrix();
    setMyColor({0.6, 0.6, 0.6});
    glTranslatef(x, y, z);
    glTranslatef(22, 4 - 0.3, 0.1);
    glScalef(5, 4, 0);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    // circle
    drawCircle(x + 28.5, y + 5.5, z + 0.1, 0.5);

    // small door
    glColor3f(0.6, 0.6, 0.6);
    glPushMatrix();
    setMyColor({0.6, 0.6, 0.6});
    glTranslatef(x, y, z);
    glTranslatef(32, 4, 0.1);
    glScalef(2, 3, 0);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    // windows column4
    make_window(35, 6, 0.1, 3, 1, x, y, z);
    make_window(35, 4, 0.1, 3, 1, x, y, z);

    // windows column5
    make_window(39, 4, 0.1, 3, 1, x, y, z);
    make_window(39, 2, 0.1, 3, 1, x, y, z);

    // windows column6
    make_window(43, 6, 0.1, 6, 1, x, y, z);
    make_window(46, 4, 0.1, 3, 1, x, y, z);

    // small door
    glColor3f(0.6, 0.6, 0.6);
    glPushMatrix();
    setMyColor({0.6, 0.6, 0.6});
    glTranslatef(x, y, z);
    glTranslatef(50, 4, 0.1);
    glScalef(2, 3, 0);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    // small circle
    glColor3f(0.6, 0.6, 0.6);
    glPushMatrix();
    setMyColor({0.6, 0.6, 0.6});
    glTranslatef(x + 53.5, y + 5.5 - 3.5, z + 0.1);
    glScalef(5, 4.7, 0);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();
    Point3D pod1first = {x + 53.5f + 3.0f + 0.5f, y + 5.5f - 3.5f, z - 0.2f};
    Point3D pod1second = {x + 53.5f + 0.5f, y + 5.5f - 3.5f, z - 0.2f};
    Point3D pod2first = {x + 53.5f - 4.5f, y + 5.5f - 3.2f, z - 48.95f};
    Point3D pod2second = {x + 53.5f - 7.5f, y + 5.5f - 3.2f, z - 48.95f};
    // the four points are the base of the bridge
    buildbridge(pod1first, pod1second, pod2first, pod2second);
}

//function to draw silicon pod
void silicon(int x, int y, int z)
{
    floor_0(x + 1, y + 0, z + 0, 63);
    floor_2(x - 1, y + 7, z + 0, 63);
    floor_2(x + 1, y + 14, z + 0, 63);
    floor_2(x - 1, y + 21, z + 0, 63);
    floor_h2(x + 1, y + 28, z + 0, 63);
    floor_2(x - 1, y + 35, z + 0, 63);
    floor_2(x + 1, y + 42, z + 0, 63);
    floor_2(x - 1, y + 49, z + 0, 63);
}

//function to draw titanium pod
void titanium(int x, int y, int z)
{
    floor_in(x + 1, y + 0, z + 0, 67);
    floor_2(x + 6, y + 7, z + 4, 59);
    floor_in(x - 1, y + 14, z + 0, 69);
    floor_2(x + 1, y + 21, z + 4, 63);
    floor_h1(x - 1, y + 28, z + 0, 63);
    floor_2(x + 1, y + 35, z + 4, 63);
}

//function to draw vanadium pod
void vanadium(int x, int y, int z)
{
    floor_0(x + 4, y + 0, z + 4, 55);
    floor_in(x - 1, y + 7, z + 0, 67);
    floor_2(x + 2, y + 14, z + 4, 61);
    floor_h1(x - 3, y + 21, z + 0, 69);
    floor_2(x + 2, y + 28, z + 4, 59);
}

//function to draw chromium pod
void chromium(int x, int y, int z)
{
    floor_0(x + 2, y + 0, z + 0, 63);
    floor_2(x + 2, y + 7, z + 0, 60);
    floor_2(x - 2, y + 14, z + 0, 59);
    floor_h(x + 2, y + 21, z + 0, 60);
    floor_2(x - 2, y + 28, z + 0, 59);
    floor_2(x + 2, y + 35, z + 0, 60);
}

//function to draw manganese pod
void manganese(int x, int y, int z)
{
    floor_in(x + 1, y + 0, z + 0, 64);
    floor_23(x + 4, y + 7, z + 4, 59);
    floor_in(x + 1, y + 14, z + 0, 60);
    floor_in(x + 8, y + 22, z + 0, 58);
    floor_2(x + 9, y + 28, z + 6, 59);
}

//function to draw a branch of the tree
void drawBranch(float parentLength, float parentRadius, int depth, int branchingFactor, float altitude, float zAngle)
{
    // if max depth is reached, we simply terminate the process
    if (depth > maxDepth)
        return;
    
    // branches should have smaller radius and length compared to their parent branch
    float branchRadius = parentRadius * (depth) / (depth + 1);
    float branchLength = parentLength * (depth) / (depth + 1);
	
    // calculating the random offshoot of the current branch from its parent 
    float phi = static_cast<float>(getRandomNumber() % 361 - 180);
    float theta = static_cast<float>(getRandomNumber() % 121 - 60);

    glPushMatrix();
    glRotatef(theta, 1, 0, 0);

    glPushMatrix();
    glRotatef(phi, 0, 0, 1);

    glColor3f(0.64f, 0.16f, 0.16f);
    // probability of a new branches ofshooting is 2/3
    if (getRandomNumber() > RAND_MAX / 3)
    {
        glutSolidCylinder(branchRadius, branchLength, 8, 8);

        for (int i = 0; i < branchingFactor; i++)
        {
            float heightFromBase = (0.5f + (getRandomNumber() * 1.0f / RAND_MAX) * 0.5f) * branchLength;
            glPushMatrix();
            glTranslatef(0, 0, heightFromBase);
            drawBranch(branchLength, branchRadius, depth + 1, branchingFactor, altitude + heightFromBase * cos(zAngle), zAngle + theta);
            glPopMatrix();
        }

        glPushMatrix();
        glTranslatef(0, 0, branchLength);
        glColor3f(0.64f, 0.16f, 0.16f);
        glutSolidCone(branchRadius, branchLength, 8, 8);

        glColor3f(0.14f, 0.8f, 0.14f); // Green color
        // 18,53,36
        glTranslatef(0, 0, branchLength);
        glutSolidSphere(atan(altitude) * branchRadius * 2, 8, 8); // for fruits.
        glTranslatef(0, 0, -branchLength);

        glPopMatrix();
    }
    else
    {
        glColor3ub(105, 75, 55);
        glutSolidCone(branchRadius, branchLength, 8, 8);

        glColor3f(0.0f, 1.0f, 0.0f); // Green color
        glTranslatef(0, 0, branchLength);
        glutSolidSphere(atan(altitude) * branchRadius * 2, 8, 8); // for fruits.
        glTranslatef(0, 0, -branchLength);
    }

    glPopMatrix();
    glPopMatrix();
}

//function to draw a tree that generates a different tree every-time it is called based on the seed value it gets as input
void drawTree(int seed, float depth, GLfloat radius)
{
    ptr = seed;
    maxDepth = depth;
    GLfloat height = 3.0;
    int branchingFactor = 4.5;

    glColor3f(105.0 / 255.0, 75.0 / 255.0, 55.0 / 255.0);

    glPushMatrix();
    glRotatef(90, -1, 0, 0);

    glutSolidCylinder(radius, height, 30, 30);

    for (int i = 0; i < branchingFactor; i++)
    {
        float heightFromBase = (0.5f + ((getRandomNumber() * 0.5f) / RAND_MAX)) * height;
        glTranslatef(0, 0, heightFromBase);
        glColor3f(105.0 / 255.0, 75.0 / 255.0, 55.0 / 255.0);
        drawBranch(height, radius * 2, 1, branchingFactor, heightFromBase, 0);
        glTranslatef(0, 0, -heightFromBase);
    }

    glPushMatrix();
    glTranslatef(0, 0, height);

    drawBranch(height, radius * 2, 1, branchingFactor, height, 0);
    glPopMatrix();
    glPopMatrix();
}

//function to draw a garden around pods and color it
void draw_garden(float x, float y, float z)
{
    glLineWidth(5.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    setMyColor({1.0f, 1.0f, 1.0f});
    // quadrant
    glBegin(GL_LINE_LOOP);
    glVertex3f(x, y, z);
    glVertex3f(x, y, z);
    for (float i = 180.0f; i >= 90.0f; i -= 0.1f)
    {
        float radians = M_PI * i / 180.0f;
        float xCoord = 65.0f * cosf(radians) + x;
        float zCoord = 55.0f * sinf(radians) + z;
        glVertex3f(xCoord, y, zCoord);
    }
    glVertex3f(x + 26, y, z + 55);
    glVertex3f(x + 28, y, z + 47);
    glVertex3f(x, y, z + 47);
    glEnd();
    glColor3f(0.2f, 0.6f, 0.1f); // Natural green for grass
    glBegin(GL_POLYGON);
    glVertex3f(x, y, z);
    for (float i = 180.0f; i >= 90.0f; i -= 0.1f)
    {
        float radians = M_PI * i / 180.0f;
        float xCoord = 65.0f * cosf(radians) + x;
        float zCoord = 55.0f * sinf(radians) + z;
        glVertex3f(xCoord, y, zCoord);
    }
    glEnd();

    glColor3f(0.2f, 0.6f, 0.1f); // Natural green for grass
    glBegin(GL_POLYGON);
    glVertex3f(x, y, z + 54);
    glVertex3f(x + 26, y, z + 54);
    glVertex3f(x + 28, y, z + 47);
    glVertex3f(x, y, z + 47);
    glEnd();
    // Draw titanium front outline
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINE_LOOP);
    // cout<<x+35<<" "<<y<<" "<<z+47<<endl;

    glVertex3f(x + 35, y, z + 47);
    glVertex3f(x + 33, y, z + 55);
    glVertex3f(x + 63, y, z + 55);
    glVertex3f(x + 80, y, z + 53);
    glVertex3f(x + 110, y, z + 53);
    glVertex3f(x + 112, y, z + 47);
    glEnd();

    // Fill titanium front with green
    glColor3f(0.2f, 0.6f, 0.1f); // Natural green for grass

    glBegin(GL_POLYGON);
    glVertex3f(x + 35, y, z + 47);
    glVertex3f(x + 33, y, z + 55);
    glVertex3f(x + 63, y, z + 55);
    glVertex3f(x + 80, y, z + 53);
    glVertex3f(x + 110, y, z + 53);
    glVertex3f(x + 112, y, z + 47);
    glEnd();
    glColor3f(1.0f, 1.0f, 1.0f); // Green color
    // Draw vanadium front outline
    glBegin(GL_LINE_LOOP);
    glVertex3f(x + 120, y, z + 47);
    glVertex3f(x + 118, y, z + 53);
    glVertex3f(x + 131, y, z + 55);
    glVertex3f(x + 131, y, z + 47);
    glEnd();

    // Fill vanadium front with green
    glColor3f(0.2f, 0.6f, 0.1f); // Natural green for grass

    glBegin(GL_POLYGON);
    glVertex3f(x + 120, y, z + 47);
    glVertex3f(x + 118, y, z + 53);
    glVertex3f(x + 131, y, z + 55);
    glVertex3f(x + 131, y, z + 47);
    glEnd();
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINE_LOOP);
    glVertex3f(x + 136, y, z + 47);
    glVertex3f(x + 136, y, z + 55);
    glVertex3f(x + 180, y, z + 55);
    glVertex3f(x + 180, y, z);
    glVertex3f(x + 170, y, z);
    glVertex3f(x + 170, y, z + 47);
    glEnd();
    glColor3f(0.2f, 0.6f, 0.1f); // Natural green for grass

    glBegin(GL_POLYGON);
    glVertex3f(x + 136, y, z + 47);
    glVertex3f(x + 136, y, z + 55);
    glVertex3f(x + 180, y, z + 55);
    glVertex3f(x + 180, y, z + 47);
    //  glVertex3f(x + 170, y, z + 47);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(x + 170, y, z + 47);
    glVertex3f(x + 180, y, z + 47);
    glVertex3f(x + 180, y, z);
    glVertex3f(x + 170, y, z);
    glEnd();

    // beside chromium
    glColor3f(1.0f, 1.0f, 1.0f); // White color
    glBegin(GL_LINE_LOOP);
    glVertex3f(x + 180, y, z - 20);
    glVertex3f(x + 180, y, z - 60);
    glVertex3f(x + 170, y, z - 60);
    glVertex3f(x + 170, y, z - 20);
    glEnd();

    // Fill the inside with green
    glColor3f(0.2f, 0.6f, 0.1f); // Natural green for grass

    glBegin(GL_POLYGON);
    glVertex3f(x + 180, y, z - 20);
    glVertex3f(x + 180, y, z - 60);
    glVertex3f(x + 170, y, z - 60);
    glVertex3f(x + 170, y, z - 20);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f); // White color
    glBegin(GL_LINE_LOOP);
    glVertex3f(x + 170, y, z - 80);
    glVertex3f(x + 180, y, z - 80);
    for (float i = 90.0f; i >= 0.0f; i -= 0.1f)
    {
        float radians = M_PI * i / 180.0f;
        float xCoord = 10.0f * cosf(radians) + x + 180;
        float zCoord = z - 90 + 10.0f * sinf(radians);
        glVertex3f(xCoord, y, zCoord);
    }
    glVertex3f(x + 190, y, z - 120);
    for (float i = 360.0f; i >= 270.0f; i -= 0.1f)
    {
        float radians = M_PI * i / 180.0f;
        float xCoord = 10.0f * cosf(radians) + x + 180;
        float zCoord = z - 120 + 10.0f * sinf(radians);
        glVertex3f(xCoord, y, zCoord);
    }
    glVertex3f(x + 100, y, z - 130);
    glVertex3f(x + 100, y, z - 120);
    glVertex3f(x + 170, y, z - 120);
    glEnd();

    glColor3f(0.2f, 0.6f, 0.1f); // Natural green for grass

    glBegin(GL_POLYGON);
    glVertex3f(x + 170, y, z - 80);
    glVertex3f(x + 180, y, z - 80);
    for (float i = 90.0f; i >= 0.0f; i -= 0.1f)
    {
        float radians = M_PI * i / 180.0f;
        float xCoord = 10.0f * cosf(radians) + x + 180;
        float zCoord = z - 90 + 10.0f * sinf(radians);
        glVertex3f(xCoord, y, zCoord);
    }
    glEnd();
    glColor3f(0.2f, 0.6f, 0.1f); // Natural green for grass

    glBegin(GL_POLYGON);
    glVertex3f(x + 190, y, z - 120);
    for (float i = 360.0f; i >= 270.0f; i -= 0.1f)
    {
        float radians = M_PI * i / 180.0f;
        float xCoord = 10.0f * cosf(radians) + x + 180;
        float zCoord = z - 120 + 10.0f * sinf(radians);
        glVertex3f(xCoord, y, zCoord);
    }
    glVertex3f(x + 100, y, z - 130);
    glVertex3f(x + 100, y, z - 120);
    glVertex3f(x + 170, y, z - 120);
    glEnd();

    glColor3f(0.2f, 0.6f, 0.1f); // Natural green for grass

    glBegin(GL_POLYGON);
    glVertex3f(x + 170, y, z - 80);
    glVertex3f(x + 180, y, z - 80);
    for (float i = 90.0f; i >= 0.0f; i -= 0.1f)
    {
        float radians = M_PI * i / 180.0f;
        float xCoord = 10.0f * cosf(radians) + x + 180;
        float zCoord = z - 90 + 10.0f * sinf(radians);
        glVertex3f(xCoord, y, zCoord);
    }
    glVertex3f(x + 190, y, z - 120);
    for (float i = 360.0f; i >= 270.0f; i -= 0.1f)
    {
        float radians = M_PI * i / 180.0f;
        float xCoord = 10.0f * cosf(radians) + x + 180;
        float zCoord = z - 120 + 10.0f * sinf(radians);
        glVertex3f(xCoord, y, zCoord);
    }
    glVertex3f(x + 170, y, z - 120);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f); // White color
                                 // behind titanium
    glBegin(GL_LINE_LOOP);
    glVertex3f(x + 25, y, z + 1);
    glVertex3f(x + 21, y, z - 16);
    glVertex3f(x + 70, y, z - 16);
    glVertex3f(x + 72, y, z - 2);
    glEnd();

    // Fill the inside with green
    glColor3f(0.2f, 0.6f, 0.1f); // Natural green for grass

    glBegin(GL_POLYGON);
    glVertex3f(x + 25, y, z + 1);
    glVertex3f(x + 21, y, z - 16);
    glVertex3f(x + 70, y, z - 16);
    glVertex3f(x + 72, y, z - 2);
    glEnd();
    glColor3f(1.0f, 1.0f, 1.0f); // White color
    // behind vanadium
    glBegin(GL_LINE_LOOP);
    glVertex3f(x + 108, y, z + 2);
    glVertex3f(x + 103, y, z - 13);
    glVertex3f(x + 147, y, z - 13);
    glVertex3f(x + 137, y, z + 4);
    glEnd();

    // Fill the inside with green
    glColor3f(0.2f, 0.6f, 0.1f); // Natural green for grass

    glBegin(GL_POLYGON);
    glVertex3f(x + 108, y, z + 2);
    glVertex3f(x + 103, y, z - 13);
    glVertex3f(x + 147, y, z - 13);
    glVertex3f(x + 137, y, z + 4);
    glEnd();
    glColor3f(1.0f, 1.0f, 1.0f); // White color
    // behind chromium
    glBegin(GL_LINE_LOOP);
    glVertex3f(x + 125, y, z - 60);
    glVertex3f(x + 120, y, z - 78);
    glVertex3f(x + 147, y, z - 78);
    glVertex3f(x + 137, y, z - 60);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex3f(x + 115, y, z - 62);
    glVertex3f(x + 110, y, z - 76);
    glVertex3f(x + 102, y, z - 76);
    glVertex3f(x + 102, y, z - 62);
    glEnd();

    // Fill the inside with green
    glColor3f(0.2f, 0.6f, 0.1f); // Natural green for grass

    glBegin(GL_POLYGON);
    glVertex3f(x + 125, y, z - 60);
    glVertex3f(x + 120, y, z - 78);
    glVertex3f(x + 147, y, z - 78);
    glVertex3f(x + 137, y, z - 60);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(x + 115, y, z - 62);
    glVertex3f(x + 110, y, z - 76);
    glVertex3f(x + 102, y, z - 76);
    glVertex3f(x + 102, y, z - 62);
    glEnd();
    glColor3f(1.0f, 1.0f, 1.0f); // White color
    // behind silicon
    glBegin(GL_LINE_LOOP);
    glVertex3f(x + 10, y, z - 125);
    glVertex3f(x + 5, y, z - 70);
    glVertex3f(x + 18, y, z - 64);
    glVertex3f(x + 52, y, z - 72);
    glVertex3f(x + 62, y, z - 64);
    glVertex3f(x + 70, y, z - 80);
    glVertex3f(x + 55, y, z - 125);
    glEnd();

    // Fill the inside with green
    glColor3f(0.2f, 0.6f, 0.1f); // Natural green for grass

    glBegin(GL_POLYGON);
    glVertex3f(x + 10, y, z - 125);
    glVertex3f(x + 5, y, z - 70);
    glVertex3f(x + 18, y, z - 64);
    glVertex3f(x + 52, y, z - 72);
    glVertex3f(x + 62, y, z - 64);
    glVertex3f(x + 70, y, z - 80);
    glVertex3f(x + 55, y, z - 125);
    glEnd();

    glLineWidth(1.0f);
}

//function to set frame rate 
void timer(int value)
{
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0); // 60 FPS
}

//main display function
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //draws a series of trees and street lights along with them as we can see in the front-side of our pods
    for (int i = 0; i <= 2; i++)
    {
        if (i != 0)
        {
            glPushMatrix();
            glTranslatef(-8 + i * 14, 0, 14);
            glPushMatrix();

            drawStreetLight(0, 0, 16.0f);

            glPopMatrix();
            glScalef(0.8f, 0.8f, 0.8f);

            drawTree(getRandomNumber() % 1000, 6.5, 0.15f);

            glTranslatef(+8 - i * 14, 0, -14);
            glPopMatrix();
        }

        glPushMatrix();
        glTranslatef(-8 - i * 14, 0, 14);
        glPushMatrix();

        drawStreetLight(0, 0, 16.0f);
        glPopMatrix();
        glScalef(0.8f, 0.8f, 0.8f);
        drawTree(getRandomNumber() % 1000, 6.5, 0.15f);

        glTranslatef(+8 + i * 14, 0, -14);
        glPopMatrix();
    }
    for (int i = 0; i <= 3; i++)
    {
        glPushMatrix();
        glTranslatef(40 + i * 12, 0, 14);
        glPushMatrix();

        drawStreetLight(0, 0, 16.0f);
        glPopMatrix();
        glScalef(0.8f, 0.8f, 0.8f);
        drawTree(getRandomNumber() % 1000, 6.5, 0.15f);
        glTranslatef(-40 - i * 12, 0, -14);
        glPopMatrix();
    }
    for (int k = 0; k <= 9; k++)
    {
        float i = k;
        if (k > 3)
        {
            i += 1.5;
        }
        if (k > 6)
        {
            i += 1;
            glPushMatrix();
            glTranslatef(90, 0, 14 - i * 14);
            glPushMatrix();
            drawStreetLight(38.0f, 0.0f, 0.0f);
            glPopMatrix();
            glScalef(0.8f, 0.8f, 0.8f);
            drawTree(getRandomNumber() % 1000, 6.5, 0.15f);
            glTranslatef(-90, 0, -14 + i * 14);
            glPopMatrix();
        }
        else
        {
            glPushMatrix();
            glTranslatef(90, 0, 14 - i * 14);
            glPushMatrix();

            drawStreetLight(16.0f, 0.0f, 0.0f);
            glPopMatrix();
            glScalef(0.8f, 0.8f, 0.8f);
            drawTree(getRandomNumber() % 1000, 6.5, 0.15f);
            glTranslatef(-90, 0, -14 + i * 14);
            glPopMatrix();
        }
    }

    for (int k = -1; k <= 3; k++)
    {
        float i = k + 1.5;
        glPushMatrix();
        glTranslatef(90 - i * 14, 0, -160);
        glPushMatrix();

        drawStreetLight(0.0f, 0.0f, -16.0f);
        glPopMatrix();
        glScalef(0.8f, 0.8f, 0.8f);
        drawTree(getRandomNumber() % 1000, 6.5, 0.15f);
        glTranslatef(-90 + i * 14, 0, +160);
        glPopMatrix();
    }

    for (int k = 1; k <= 6; k++)
    {

        float i = k + 1.8;
        if (k > 3)
        {
            i += 2.2;
        }
        glPushMatrix();
        glTranslatef(90 - i * 14, 0, -40);

        glScalef(0.8f, 0.8f, 0.8f);

        drawLightPole(10, 100, 0, 0, 0);
        drawTree(getRandomNumber() % 1000, 6.5, 0.15f);

        glTranslatef(-90 + i * 14, 0, +40);
        glPopMatrix();
    }
    for (int k = 1; k <= 3; k++)
    {

        float i = k + 1.8;
        if (k > 3)
        {
            i += 2.2;
        }
        glPushMatrix();
        glTranslatef(92 - i * 14, 0, -103);

        drawLightPole(10, 100, 0, 0, 0);
        glScalef(0.8f, 0.8f, 0.8f);
        drawTree(getRandomNumber() % 1000, 6.5, 0.15f);

        glTranslatef(-92 + i * 14, 0, +103);
        glPopMatrix();
    }

    glPushMatrix();
    glTranslatef(-50, 0, -130);
    glScalef(2.0f, 3.0f, 2.0f);
    drawTree(getRandomNumber() % 1000, 7, 0.35);
    glTranslatef(50, 0, +130);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-110 + 5, 0, -10);
    glScalef(2.0f, 3.0f, 2.0f);
    drawTree(getRandomNumber() % 1000, 7, 0.35);
    glTranslatef(110 - 5, 0, +10);
    glPopMatrix();

    //draws building along with their names on top of them
    building_name("Silicon", 23 - 80, 58.5, 0 - 68);
    building_name("Titanium", 23 - 80, 44.5, 5);
    building_name("Vanadium", 23 + 10, 37.5, 5);
    building_name("Chromium", 23 + 10, 44.5, 0 - 68);
    building_name("Manganese", 23 + 10, 37.5, 0 - 122);
    silicon(-80, 0, -68);
    titanium(-80, 0, 0);
    vanadium(10, 0, 0);
    chromium(10, 0, -68);
    manganese(10, 0, -130);
    draw_ground();
    draw_road();

    //draw bridges
    Point3D pod1first = {33.5f + 0.7f-2.4f, 11.0f - 1.0f, -19.0f + 1.0f - 0.85f};
    Point3D pod1second = {37.8f - 0.7f-2.4f, 11.0f - 1.0f, -19.0f + 1.0f - 0.85f};
    Point3D pod2first = {33.5f + 0.7f - 0.2f, 11.0f - 0.4f, -68.0 + 0.12f};
    Point3D pod2second = {37.8f - 0.7f - 0.2f, 11.0f - 0.4f, -68.0f + 0.10f};
    // the four points are the base of the bridge
    buildbridge(pod1first, pod1second, pod2first, pod2second);
   pod1first = {53.5+3+0.5f-15.0f, 6.0f+5.5-3.5, -40.2f-25.0f-21.0f};
    pod1second = {53.5+0.5f-15.0f, 6.0f+ 5.5-3.5, -40.2f-25.0f-21.0f};
    pod2first = {53.5-4.5f, 6.0f+ 5.5-3.2, -40.2f-48.95f-25.0f-11.9f};
    pod2second = {53.5-7.5f, 6.0f+5.5-3.2, -40.2f-48.95f-25.0f-11.9f};
    // the four points are the base of the bridge
    buildbridge(pod1first, pod1second, pod2first, pod2second);
     pod1first = {-58.0f, 19.0f - 1.0f, -19.0f + 1.0f - 0.85f};
     pod1second = {-61.0f, 19.0f - 1.0f, -19.0f + 1.0f - 0.85f};
     pod2first = {-55.0f, 19.0f - 1.5f, -68.0 + 0.12f};
     pod2second = {-58.0f, 18.0f-1.5f, -68.0f + 0.10f};
    buildbridge(pod1first, pod1second, pod2first, pod2second);
    
    //draw the 2-D garden by stacking them to appear as 3-D
    for (float i = 0; i < 1.0; i += 0.01)
    {
        draw_garden(-85, i, -35);
    }

    glFlush();
    glutSwapBuffers();
}

//init function that runs when the program starts
void init(void)
{
    glClearColor(0.5, 0.6, 0.9, 0.0);
    glMatrixMode(GL_MODELVIEW); // The modelview matrix in OpenGL combines the model and view matrices to represent the position, orientation, and scale of objects being rendered.
    if (lighting)
        setLighting();
    else
        glDisable(GL_LIGHTING);
    //"glEnable(GL_DEPTH_TEST);" enables the depth buffer test, which is used for rendering 3D scenes with proper depth perception.
    glEnable(GL_DEPTH_TEST);
}

//function that sets the keyboard functionalities
void keyboard(unsigned char key, int x, int y)
{
    GLfloat matrix[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, matrix);

    float DOF[3];
    DOF[0] = matrix[2];  // x
    DOF[1] = matrix[6];  // y
    DOF[2] = matrix[10]; // z

    switch (key)
    {
    case 'a':
    case 'A':
        glTranslatef(5.0 * DOF[2], 0.0, 5.0 * -DOF[0]);
        break;
    case 'd':
    case 'D':
        glTranslatef(5.0 * -DOF[2], 0.0, 5.0 * DOF[0]);
        break;
    case 'w':
    case 'W':
        glTranslatef(5.0 * DOF[0], 0.0, 5.0 * DOF[2]);
        break;
    case 's':
    case 'S':
        glTranslatef(5.0 * -DOF[0], 0.0, 5.0 * -DOF[2]);
        break;
    case 'Q':
    case 'q':
        glTranslatef(0.0, 5.0, 0.0);
        break;
    case 'e':
    case 'E':
        glTranslatef(0.0, -5.0, 0.0);
        break;
    case 'l':
    case 'L':
        lighting = !lighting;
        init();
        break;
    case ' ':
        matrix[2] = matrix[6] = 0;
        matrix[10] = 1;
        GLfloat m[16] = {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f};
        glLoadMatrixf(m);
    }
    glutPostRedisplay();
}

//function to add functionalities to arrow keys
void catchKey(int key, int x, int y)
{
    GLfloat matrix[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, matrix);

    float DOF[3];
    DOF[0] = matrix[2];  // x
    DOF[1] = matrix[6];  // y
    DOF[2] = matrix[10]; // z

    switch (key)
    {
    case GLUT_KEY_DOWN:
        glRotatef(-2, 1, 0, 0);
        break;
    case GLUT_KEY_UP:
        glRotatef(2, 1, 0, 0);
        break;
    case GLUT_KEY_LEFT:
        glRotatef(2, 0, 1, 0);
        break;
    case GLUT_KEY_RIGHT:
        glRotatef(2, 0, -1, 0);
        break;

        glutPostOverlayRedisplay();
    }
}

//function to resize the graphical viewport
void resize(int width, int height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, width / (height | 1), 1.0, 630.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, -15, -300);

}

int main(int argc, char **argv)
{
    for (int i = 0; i < 1e5; i++)
    {
        randomNumbers[i] = rand();
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1100, 1100);
    glutInitWindowPosition(100, 10);
    glutCreateWindow("3D model");
    init();
    glutTimerFunc(0, timer, 0);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(resize);
    glutSpecialFunc(catchKey);
    glutMainLoop();
    return 0;
}
