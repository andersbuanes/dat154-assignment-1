// Assignment1.cpp : Defines the entry point for the application.
//

#include <algorithm>
#include <list>
#include <random>

#include "framework.h"
#include "Assignment1.h"
#include "stdafx.h"
#include "Constants.h"
#include "Car.h"
#include "Draw.h"
#include "Shapes.h"
#include "Colors.h"
#include "Constants.h"
#include "Intersection.h"
#include "Direction.h"

#define MAX_LOADSTRING 100

#define IDM_ABOUT 104
#define IDM_EXIT 105
#define IDD_DIALOG1 129

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

RECT screensize;                                // screen size
bool** states;                                  // array storing traffic light states
int westState = 0;                              // tracking of west road light state
int northState = 2;                             // tracking of north road light state
int state = 0;                                  // overall state tracker
int change = 0;

bool redState[] = { TRUE, FALSE, FALSE };
bool readyState[] = { TRUE, TRUE, FALSE };
bool greenState[] = { FALSE, FALSE, TRUE };
bool stoppingState[] = { FALSE, TRUE, FALSE };

int pn = 10;                                    // spawn rate probability for north road
int pe = 10;                                    // spawn rate probability for east road
int pw = 10;                                    // spawn rate probability for west road
int ps = 10;                                    // spawn rate probability for south road

std::list<Road> roads; 
std::list<Road>::iterator road_it;
std::list<Car> carsNorth;
std::list<Car> carsWest;
std::list<Car>::iterator car_it;
Intersection intersection;// = Intersection(roads, state);
TrafficLight lightNorth;// = TrafficLight(200, 70, states[northState]);
TrafficLight lightWest;// = TrafficLight(200, 70, states[westState]);
Road roadNorth;// = Road(carsNorth, lightNorth, pn);
Road roadWest;// = Road(carsWest, lightWest, pw);

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    SpawnRateDialog(HWND, UINT, WPARAM, LPARAM);

void DrawCars(HDC* hdc, RECT &rc, std::list<Car> cars, std::list<Car>::iterator it);
void ChangeLightStates();
void UpdateCars(HWND Hwnd, std::list<Car> cars, std::list<Car>::iterator it);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_ASSIGNMENT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ASSIGNMENT1));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ASSIGNMENT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_ASSIGNMENT1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   GetClientRect(hWnd, &screensize);
   
   states = new bool* [4];
   states[0] = redState;
   states[1] = readyState;
   states[2] = greenState;
   states[3] = stoppingState;

   lightNorth = TrafficLight(200, 70, states[northState]);
   lightWest = TrafficLight(200, 70, states[westState]);

   roadNorth = Road(carsNorth, lightNorth, pn);
   roadWest = Road(carsWest, lightWest, pw);

   roads.push_front(roadNorth);
   roads.push_front(roadWest);

   intersection = Intersection(roads, state);

   roads.push_front(roadNorth);
   roads.push_front(roadWest);

   SetTimer(hWnd, IDT_TRAFFICLIGHTTIMER, 3000, (TIMERPROC)NULL);
   SetTimer(hWnd, IDT_CARSPAWNTIMER, 1000, (TIMERPROC)NULL);
   SetTimer(hWnd, IDT_CARUPDATETIMER, 30, (TIMERPROC)NULL);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{   
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_TIMER:
       {
        RECT rc;
        GetClientRect(hWnd, &rc);
        int centerX = rc.right / 2;
        int centerY = rc.right / 2;
            switch (wParam)
            {
            case IDT_TRAFFICLIGHTTIMER:
                ChangeLightStates();
                InvalidateRect(hWnd, NULL, false);
                break;
            case IDT_CARUPDATETIMER:
                GetClientRect(hWnd, &screensize);
                roadNorth.MoveCars(hWnd, screensize);
                roadWest.MoveCars(hWnd, screensize);
                /*
                for (car_it = cars.begin(); car_it != cars.end(); ++it)
                {
                    if (it-> y > rc.bottom - 10 || it->x > rc.right - 10)
                    {
                        cars.erase(it);
                        break;
                    }
                    auto it2 = it;
                    it2++;
                    if (it->direction)
                    {
                        auto next = std::find_if(it2, cars.end(), [](auto& c) {return c.direction; });
                        if (next != end(cars) && it->direction)
                        {
                            if (it->y + 40 >= next->y && it->x == next->x)
                            {
                                continue;
                            }
                        }
                        if (state == 2 || state == 3)
                        {
                            it->Move();
                            InvalidateRect(hWnd, 0, false);
                        }
                        else
                        {
                            if (it->y < (rc.bottom/2) - ROAD_WIDTH - 20 || it->y > (rc.bottom/2)+ ROAD_WIDTH)
                            {
                                it->Move();
                                InvalidateRect(hWnd, 0, false);
                            }
                        }
                    }
                    else
                    {
                        auto next = std::find_if(it2, cars.end(), [](auto& c) { return !c.direction; });
                        if (next != end(cars) && !it->direction)
                        {
                            if (it->x + 40 >= next->x && it->y == next->y)
                                continue;
                        }
                        if (intersection.state == 0 || state == 1)
                        {
                            it->Move();
                            InvalidateRect(hWnd, 0, false);
                        }
                        else
                        {
                            if (it->x < (rc.right/2) - ROAD_WIDTH - 20 || it->x > (rc.right/2) + ROAD_WIDTH)
                            {
                                it->Move();
                                InvalidateRect(hWnd, 0, false);
                            }
                        }
                    }
                }
                */
                InvalidateRect(hWnd, NULL, false);
                break;
            case IDT_CARSPAWNTIMER:
                RECT rc;
                GetClientRect(hWnd, &screensize);

                std::random_device rd;                          // initialise seed
                std::mt19937 rng(rd());                         // Mersenne-Twister random-number engine
                std::uniform_int_distribution<int> p(0, 100);   // probability of spawn
                std::uniform_int_distribution<int> speed(3, 7); // car speed interval
                std::uniform_int_distribution<int> lane(0, 1);  // car lane spawn
                auto randWest = p(rng);
                auto randNorth = p(rng);

                if (randWest <= pw)
                {
                    int spawn = lane(rng);
                    int y = 0;
                    if (spawn == 0)
                    {
                        y = (screensize.bottom / 2) - 25;
                    }
                    else {
                        y = (screensize.bottom / 2) + 25;
                    }
                    roadWest.cars.push_front(Car(10, y, EAST, RGB(rand() % 255, rand() % 255, rand() % 255)));
                }
                if (randNorth <= pn)
                {
                    int spawn = lane(rng);
                    int x = 0;
                    if (spawn == 0)
                    {
                        x = (screensize.right / 2) - 25;
                    }
                    else {
                        x = (screensize.right / 2) + 25;
                    }
                    roadNorth.cars.push_front(Car(x, 10, SOUTH, RGB(rand() % 255, rand() % 255, rand() % 255)));
                }
                break;
            }
       }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC phdc = BeginPaint(hWnd, &ps);
            RECT rc;
            GetClientRect(hWnd, &rc);
            
            // Create virtual device context for double buffering
            HDC hdc = CreateCompatibleDC(phdc);
            HBITMAP bm = CreateCompatibleBitmap(phdc, rc.right, rc.bottom);
            SelectObject(hdc, bm);

            HBRUSH bg = CreateSolidBrush(RGB(255, 255, 255));
            HGDIOBJ hOrg = SelectObject(hdc, bg);
            Rect(&hdc, 0, 0, rc.right, rc.bottom, RGB(255, 255, 255));
            
            intersection.DrawRoads(&hdc, screensize);

            // Draw northern road lights
            lightNorth.DrawTrafficLight(&hdc, screensize, true, states[northState]);
            
            // Draw western road lights
            lightWest.DrawTrafficLight(&hdc, screensize, false, states[westState]);

            
            //DrawTrafficLight(&hdc, screensize, true, states[northState]);
            //DrawTrafficLight(&hdc, screensize, false, states[westState]);

            roadNorth.DrawCars(&hdc, screensize);
            roadWest.DrawCars(&hdc, screensize);

            /* old drawing logic
            DrawRoads(&hdc, rc);
            DrawTrafficLight(&hdc, rc, -60, -60, states[westState]);
            DrawTrafficLight(&hdc, rc, -60, 310, states[northState]);
            DrawCars(&hdc, rc, cars, it);
            */

            BitBlt(phdc, 0, 0, rc.right, rc.bottom, hdc, 0, 0, SRCCOPY);

            DeleteObject(bg);
            DeleteObject(bm);
            DeleteDC(hdc);
            

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case VK_LEFT:
            if (pw - 10 >= 0)
            {
                pw -= 10;
                InvalidateRect(hWnd, 0, false);
            }
            break;
        case VK_RIGHT:
            if (pw + 10 <= 100)
            {
                pw += 10;
                InvalidateRect(hWnd, 0, false);
            }
            break;
        case VK_UP:
            if (pn + 10 <= 100)
            {
                pn += 10;
                InvalidateRect(hWnd, 0, false);
            }
            break;
        case VK_DOWN:
            if (pn - 10 >= 0)
            {
                pn -= 10;
                InvalidateRect(hWnd, 0, false);
            }
            break;
        default: 
            break;
        }
        break;
    }
    case WM_SIZE:
        GetClientRect(hWnd, &screensize);
        InvalidateRect(hWnd, 0, false);
        break;
    case WM_SIZING:
        GetClientRect(hWnd, &screensize);
        InvalidateRect(hWnd, 0, false);
        break;
    case WM_DESTROY:
        KillTimer(hWnd, IDT_CARSPAWNTIMER);
        KillTimer(hWnd, IDT_CARUPDATETIMER);
        KillTimer(hWnd, IDT_TRAFFICLIGHTTIMER);
        carsNorth.clear();
        carsWest.clear();
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

void UpdateCars(HWND hWnd, std::list<Car> cars, std::list<Car>::iterator it)
{
    for (it = cars.begin(); it != cars.end(); ++it)
    {
        /*
        if (it->y > screensize.bottom - 10 || it->x > screensize.right - 10)
        {
            cars.erase(it);
            break;
        }
        */
        auto it2 = it;
        it2++;
        if (it->direction)
        {
            auto next = std::find_if(it2, cars.end(), [](auto& c) {return c.direction; });
            if (next != end(cars) && it->direction)
            {
                if (it->y + 40 >= next->y && it->x == next->x)
                {
                    continue;
                }
            }
            if (state == 2 || state == 3)
            {
                it->Move();
                InvalidateRect(hWnd, 0, false);
            }
            else
            {
                if (it->y < (screensize.bottom / 2) - ROAD_WIDTH - 20 || it->y >(screensize.bottom / 2) + ROAD_WIDTH)
                {
                    it->Move();
                    InvalidateRect(hWnd, 0, false);
                }
            }
        }
        else
        {
            auto next = std::find_if(it2, cars.end(), [](auto& c) { return !c.direction; });
            if (next != end(cars) && !it->direction)
            {
                if (it->x + 40 >= next->x && it->y == next->y)
                    continue;
            }
            if (intersection.state == 0 || state == 1)
            {
                it->Move();
                InvalidateRect(hWnd, 0, false);
            }
            else
            {
                if (it->x < (screensize.right / 2) - ROAD_WIDTH - 20 || it->x >(screensize.right / 2) + ROAD_WIDTH)
                {
                    it->Move();
                    InvalidateRect(hWnd, 0, false);
                }
            }
        }
    }
}

void DrawCars(HDC* hdc, RECT &rc, std::list<Car> cars, std::list<Car>::iterator it)
{   
    const auto end = cars.end();

    for (it = cars.begin(); it != end; ++it)
    {
        DrawCar(hdc, rc, *it);
    }
}

void ChangeLightStates()
{
    westState++;
    northState++;
    state++;

    if (state == 4)
        state = 0;

    if (westState == 4)
        westState = 0;

    if (northState == 4)
        northState = 0;
}


void PrintRates(HDC* hdc)
{

}

