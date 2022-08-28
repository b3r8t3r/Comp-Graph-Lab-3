#include "GL/glut.h"
#include <windows.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

#define easy
#ifdef easy

const int window_side_size = 600;
const int view_side_size = 25;
const int period = 50;

struct color_t
{
    double r, g, b, a;
    void setThis() const
    {
        const color_t& color = *this;
        glColor4d(color.r, color.g, color.b, color.a);
    }
};

const color_t black = { 0, 0, 0, 1 };
const color_t blue = { 0, 0.2, 0.4, 1 };
const color_t green = { 0, 255, 0.0, 1 };
const color_t red = { 255, 0, 0, 1 };
const color_t orange = { 1, 0.5, 0.5, 1 };
const color_t grey = { 0.2, 0.2, 0.2, 0.5 };

void DrawFatPixel(int x, int y, color_t color = black)
{
    color.setThis();
    glBegin(GL_POLYGON);
    glVertex2d(x - 0.5, y - 0.5);
    glVertex2d(x - 0.5, y + 0.5);
    glVertex2d(x + 0.5, y + 0.5);
    glVertex2d(x + 0.5, y - 0.5);
    glEnd();
}

void DrawCell()
{
    glLineWidth(1);
    black.setThis();

    for (int i = -view_side_size; i <= view_side_size; ++i)
    {
        glBegin(GL_LINES);
        glVertex2f(i + 0.5f, -view_side_size + .0f);
        glVertex2f(i + 0.5f, view_side_size + .0f);
        glVertex2f(-view_side_size + .0f, i + 0.5f);
        glVertex2f(view_side_size + .0f, i + 0.5f);
        glEnd();
    }
}

void DrawAxes()
{
    glLineWidth(2);
    red.setThis();
    glBegin(GL_LINES);
    glVertex2i(-view_side_size, 0);
    glVertex2i(view_side_size, 0);
    glVertex2i(0, -view_side_size);
    glVertex2i(0, view_side_size);
    glEnd();
}

void Initialize()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-view_side_size, view_side_size, -view_side_size, view_side_size, -1.0, 1.0);
}

void DrawRegin(int x, int y, int tikcs)
{
    //первая форма для заливки
    int bitmap[20][20] = {  //Right
    { 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 }, //Top
    { 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 }, //
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1 }, //
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 1, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 3, 3, 1, 0, 0, 0, 0, 1 }, //
    { 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 }, //
    { 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 }, //
    { 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1 }, //
    { 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 3, 3, 1, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 1, 0, 0, 0, 0, 1 }, //
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 }, //
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0 },
    { 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 }
    };  //Left

    int xs[100000], ys[100000];
    int i = 1, p = 0;

    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            if (bitmap[i][j] == 1)
            {
                DrawFatPixel(-5 - i, j - 20, black);
            }
        }
    }

    do
    {
        if (!bitmap[x][y])
        {
            bitmap[x][y] = 2;
            DrawFatPixel(-5 - x, y - 20, green);
        }
        else
        {
            x = xs[p];
            y = ys[p];
            p++;
            continue;
        }

        if (!bitmap[x][y - 1])
        {
            xs[i - 1] = x;
            ys[i - 1] = y - 1;
            i++;
        }
        if (!bitmap[x - 1][y])
        {
            xs[i - 1] = x - 1;
            ys[i - 1] = y;
            i++;
        }
        if (!bitmap[x + 1][y])
        {
            xs[i - 1] = x + 1;
            ys[i - 1] = y;
            i++;
        }
        if (!bitmap[x][y + 1])
        {
            xs[i - 1] = x;
            ys[i - 1] = y + 1;
            i++;
        }

        x = xs[p];
        y = ys[p];
        p++;
    } while (tikcs-- && p != i);
}

void Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    int x = 6, y = 15;
    static int ticks = 0;
    ticks++;
    DrawRegin(x, y, ticks);
    DrawCell();
    DrawAxes();
    glFlush();
}

void OnTimer(int value)
{
    glutPostRedisplay();
    glutTimerFunc(period, OnTimer, 0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(window_side_size, window_side_size);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("AB-021");
    Initialize();
    glutDisplayFunc(Draw);
    glutTimerFunc(period, OnTimer, 0);
    glutMainLoop();
    return 0;
}
#endif 

//#define postrochno
#ifdef postrochno
GLint const WINDOW_WIDTH = 600;// ширина
GLint const WINDOW_HEIGHT = 600;// высота
GLint SPOSZ_X, SPOSZ_Y;
int z = 0;

struct Coords      // Координаты точек
{
    int x, y;
};

bool operator == (const Coords& a, const Coords& b)    // если координаты совпадают
{
    return a.x == b.x && a.y == b.y;
}

bool Sort1(Coords a, Coords b)//функция для сортировки при равных у
{
    if (a.y == b.y) return (a.x < b.x);
    else return (a.y > b.y);
}

bool Sort2(Coords a, Coords b)//функция для сортировки при равных по х
{
    if (a.x == b.x) return (a.y < b.y);
    else return (a.x < b.x);
}

vector <Coords> PixelsOfAllLine;
vector <Coords> CoordsOfAllHeight;
vector <Coords> PixelsOfLine;
vector <Coords> CoordsOfHeight;
vector <Coords> PixelsOfPouring;

void Draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(0.0f, 0.0f, 0.0f);
    // координатная сетка
    for (unsigned int i = 0; i <= WINDOW_WIDTH; i += 10)
    {
        glBegin(GL_LINE_STRIP);
        for (unsigned int g = 0; g <= WINDOW_HEIGHT; g += 10)
            glVertex2f(i, g);
        glEnd();
    }
    for (unsigned int i = 0; i <= WINDOW_HEIGHT; i += 10)
    {
        glBegin(GL_LINE_STRIP);
        for (unsigned int g = 0; g <= WINDOW_WIDTH; g += 10)
            glVertex2f(g, i);
        glEnd();
    }
    // координатная сетка
    glTranslatef(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 1);
    glBegin(GL_QUADS);
    // типа пиксели границы
    for (unsigned int i = 0; i < PixelsOfAllLine.size(); i++)
    {
        glVertex2f(PixelsOfAllLine[i].x, PixelsOfAllLine[i].y);
        glVertex2f(PixelsOfAllLine[i].x + 10, PixelsOfAllLine[i].y);
        glVertex2f(PixelsOfAllLine[i].x + 10, PixelsOfAllLine[i].y + 10);
        glVertex2f(PixelsOfAllLine[i].x, PixelsOfAllLine[i].y + 10);
    }

    glColor3f(0.0f, 1.0f, 1.0f);
    // типа пиксели заливки
    for (int i = 0; i <= z; i++)
    {
        glVertex2f(PixelsOfPouring[i].x, PixelsOfPouring[i].y);
        glVertex2f(PixelsOfPouring[i].x + 10, PixelsOfPouring[i].y);
        glVertex2f(PixelsOfPouring[i].x + 10, PixelsOfPouring[i].y + 10);
        glVertex2f(PixelsOfPouring[i].x, PixelsOfPouring[i].y + 10);
    }
    glEnd();
    glFlush();
    glutSwapBuffers();
}

void Initialization()   // фон 
{
    glClearColor(1, 1, 1, 1.0);// задаем цвет фона
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1, 1);// устанавливаем главную систему координат
    glMatrixMode(GL_MODELVIEW);
}

void LineBuild(int point1, int point2)// симметричный ЦДА
{
    Coords a;
    int x1 = CoordsOfHeight[point1].x,
        y1 = CoordsOfHeight[point1].y,
        x2 = CoordsOfHeight[point2].x,
        y2 = CoordsOfHeight[point2].y;
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    int error = deltaX - deltaY;
    a.x = x2 * 10;
    a.y = y2 * 10;
    PixelsOfLine.push_back(a);

    while (x1 != x2 || y1 != y2)
    {
        a.x = x1 * 10;
        a.y = y1 * 10;
        PixelsOfLine.push_back(a);
        const int error2 = error * 2;
        if (error2 > -deltaY)
        {
            error -= deltaY;
            x1 += signX;
        }
        if (error2 < deltaX)
        {
            error += deltaX;
            y1 += signY;
        }
    }
}

void PouringForZatravka(int x, int y)
{
    bool f1 = false, f2 = false, f3 = false, f4 = false;
    Coords a;
    for (unsigned int i = 0; i < PixelsOfAllLine.size(); i++)
        if (x == PixelsOfAllLine[i].x && y == PixelsOfAllLine[i].y) return;
    a.x = x;
    a.y = y;
    PixelsOfPouring.push_back(a);

    for (unsigned int j = 0; j < 4; j++)
        for (unsigned int i = 0; i < PixelsOfPouring.size(); i++)
            switch (j)
            {
            case 0: { if (x + 10 == PixelsOfPouring[i].x && y == PixelsOfPouring[i].y) f1 = true; break; }
            case 1: { if (x - 10 == PixelsOfPouring[i].x && y == PixelsOfPouring[i].y) f2 = true; break; }
            case 2: { if (x == PixelsOfPouring[i].x && y + 10 == PixelsOfPouring[i].y) f3 = true; break; }
            case 3: { if (x == PixelsOfPouring[i].x && y - 10 == PixelsOfPouring[i].y) f4 = true; break; }
            }
    if (!f1)
        PouringForZatravka(x + 10, y);

    if (!f2)
        PouringForZatravka(x - 10, y);

    if (!f3)
        PouringForZatravka(x, y + 10);

    if (!f4)
        PouringForZatravka(x, y - 10);
}

void timing(int val)
{
    if (z < PixelsOfPouring.size())
    {
        Draw();
        z++;
        glutTimerFunc(10, timing, 1);
    }
    else
    {
        z--;
        Draw();
    }
}
void glyt(int x, int y) {
    Coords a;
    a.x = x; a.y = y;
    CoordsOfHeight.push_back(a);
    a.x++;
    CoordsOfHeight.push_back(a);
    a.x--;
    a.y++;
    CoordsOfHeight.push_back(a);
    a.y--;
    a.x--;
    CoordsOfHeight.push_back(a);
    a.x++;
    a.y--;
    CoordsOfHeight.push_back(a);

}
int main(int argc, char** argv)
{
    srand(time(NULL));

    bool flag = false;
    bool Eflag = false;
    bool F = false;
    bool FAE = false;
    char act;
    Coords a;
    unsigned int Hval;

    a.x = rand() % 26 + 2;
    a.y = rand() % 20 - 28;
    glyt(a.x, a.y);

    a.x = rand() % 24 - 28;
    a.y = rand() % 20 - 28;
    glyt(a.x, a.y);

    a.x = rand() % 24 - 28;
    a.y = rand() % 16 + 4;
    glyt(a.x, a.y);

    a.x = rand() % 10 - 5;
    a.y = rand() % 10 + 18;
    glyt(a.x, a.y);

    a.x = rand() % 22 + 6;
    a.y = rand() % 12 + 4;
    glyt(a.x, a.y);

    /*a.x = 25;
    a.y = 25;
    glyt(a.x, a.y);

    a.x = 15;
    a.y = -15;
    glyt(a.x, a.y);

    a.x = -14;
    a.y = -14;
    glyt(a.x, a.y);

    a.x = -15;
    a.y = 15;
    glyt(a.x, a.y);*/

    

    for (int i = -50; i < 60; i += 10)  
    {
        a.x = 50; a.y = i;
        PixelsOfAllLine.push_back(a);
        a.x = i; a.y = 50;
        PixelsOfAllLine.push_back(a);
        a.x = -50; a.y = -i;
        PixelsOfAllLine.push_back(a);
        a.x = -i; a.y = -50;
        PixelsOfAllLine.push_back(a);

    }

    for (unsigned int i = 0; i < CoordsOfHeight.size() - 5; i += 5) LineBuild(i, i + 5);
    LineBuild(0, CoordsOfHeight.size() - 5);

    PixelsOfAllLine.reserve(PixelsOfAllLine.size() + PixelsOfLine.size());
    PixelsOfAllLine.insert(PixelsOfAllLine.end(), PixelsOfLine.begin(), PixelsOfLine.end());
    CoordsOfAllHeight.reserve(CoordsOfAllHeight.size() + CoordsOfHeight.size());
    CoordsOfAllHeight.insert(CoordsOfAllHeight.end(), CoordsOfHeight.begin(), CoordsOfHeight.end());
    CoordsOfHeight.clear();
    PixelsOfLine.clear();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("AB-021");
    //Регистрация обрабатываемых событий
    glutDisplayFunc(Draw);
    glutTimerFunc(100, timing, 1);
    Initialization();
    sort(CoordsOfAllHeight.begin(), CoordsOfAllHeight.end(), Sort1);
    sort(PixelsOfAllLine.begin(), PixelsOfAllLine.end(), Sort2);
    PixelsOfAllLine.resize(unique(PixelsOfAllLine.begin(), PixelsOfAllLine.end()) - PixelsOfAllLine.begin());
    for (int i = -WINDOW_WIDTH / 2; i <= WINDOW_WIDTH / 2; i += 10)
    {
        for (unsigned int j = 0; j < PixelsOfAllLine.size(); j++)
            if (PixelsOfAllLine[j].x == i && PixelsOfAllLine[j].y == 0)
            {
                F = true;
                SPOSZ_X = i;
                SPOSZ_Y = 0;
                break;
            }
            else
            {
                if (F)
                {
                    SPOSZ_X = i;
                    SPOSZ_Y = 0;
                    FAE = true;
                    break;
                }
            }
        if (FAE)
            break;
    }
    PouringForZatravka(SPOSZ_X, SPOSZ_Y);
    glutMainLoop();
    return 0;
}   
#endif 
