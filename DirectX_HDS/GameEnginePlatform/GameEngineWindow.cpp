#include "PrecompileHeader.h"
#include "GameEngineWindow.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineImage.h>
#include "GameEngineInput.h"

// LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM)

// static 구현
std::function<LRESULT(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)> GameEngineWindow::UserMessageFunction;
HWND GameEngineWindow::HWnd = nullptr;
HDC GameEngineWindow::WindowBackBufferHdc = nullptr;
float4 GameEngineWindow::WindowSize = {800, 600};
float4 GameEngineWindow::WindowPos = { 100, 100 };
float4 GameEngineWindow::ScreenSize = { 800, 600 };
GameEngineImage* GameEngineWindow::BackBufferImage = nullptr;
GameEngineImage* GameEngineWindow::DoubleBufferImage = nullptr;
bool GameEngineWindow::IsWindowUpdate = true;
WNDCLASSEX GameEngineWindow::wcex;


LRESULT CALLBACK GameEngineWindow::MessageFunction(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
    if (nullptr != UserMessageFunction)
    {
        if (0 != UserMessageFunction(_hWnd, _message, _wParam, _lParam))
        {
            return true;
        }
    }

    switch (_message)
    {
    case WM_SETFOCUS:
    {
        GameEngineInput::IsFocusOn();
        break;
    }
    case WM_KILLFOCUS:
    {
        GameEngineInput::IsFocusOff();
        break;
    }
    case WM_KEYDOWN:
    {
        GameEngineInput::IsAnyKeyOn();
        break;
    }
    case WM_DESTROY:
    {
        // Message함수가 0을 리턴하게 만들어라.
        //  PostQuitMessage(0);
        IsWindowUpdate = false;
        break;
    }
    default:
        return DefWindowProc(_hWnd, _message, _wParam, _lParam);
    }

    return 0;
}

GameEngineWindow::GameEngineWindow() 
{
}

GameEngineWindow::~GameEngineWindow() 
{
    
}

void GameEngineWindow::WindowCreate(HINSTANCE _hInstance, const std::string_view& _TitleName, float4 _Size, float4 _Pos)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = &GameEngineWindow::MessageFunction;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = _hInstance;
    wcex.hIcon = nullptr;//LoadIcon(_hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // 흰색 
    wcex.lpszMenuName = nullptr;//MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName = "GameEngineWindowDefault";
    wcex.hIconSm = nullptr;//LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    if (0 == RegisterClassEx(&wcex))
    {
        MsgAssert("윈도우 클래스 등록에 실패했습니다.");
        return;
    }

    // hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    HWnd = CreateWindow("GameEngineWindowDefault", _TitleName.data(), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, _hInstance, nullptr);

    if (nullptr == HWnd)
    {
        MsgAssert("윈도우 클래스 생성에 실패했습니다.");
        return;
    }

    // 윈도우가 만들어지면서부터 만들어진 색깔의 2차원배열의 수정권한을 얻어오는 것이다.
    WindowBackBufferHdc = GetDC(HWnd);


    // 윈도우창의 show 여부
    ShowWindow(HWnd, SW_SHOW);
    UpdateWindow(HWnd);

    SettingWindowSize(_Size);
    SettingWindowPos(_Pos);

    // 크기를 변경해서 얻어온다.
    BackBufferImage = new GameEngineImage();
    BackBufferImage->ImageCreate(WindowBackBufferHdc);


    return;
}

void GameEngineWindow::DoubleBufferClear()
{
    DoubleBufferImage->ImageClear();
}

void GameEngineWindow::DoubleBufferRender()
{
    //static GameEngineImage* BackBufferImage;
    //static GameEngineImage* DoubleBufferImage;
    BackBufferImage->BitCopy(DoubleBufferImage, WindowSize.half(), WindowSize);
}

int GameEngineWindow::WindowLoop(
    std::function<void()> _Start,
    std::function<void()> _Loop,
    std::function<void()> _End
)
{
    if (nullptr != _Start)
    {
        _Start();
    }

    MSG msg = {};

    while (IsWindowUpdate)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (nullptr != _Loop)
            {
                _Loop();
                GameEngineInput::IsAnyKeyOff();
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);

            
            continue;
        } 

        // 데드타임
        // 데드타임에 게임을 실행하는것. 
        if (nullptr != _Loop)
        {
            _Loop();
            GameEngineInput::IsAnyKeyOff();
        }
    }

    if (nullptr != _End)
    {
        _End();
    }

    if (nullptr != BackBufferImage)
    {
        delete DoubleBufferImage;
        DoubleBufferImage = nullptr;

        delete BackBufferImage;
        BackBufferImage = nullptr;
    }

    return (int)msg.wParam;
}

void GameEngineWindow::SettingWindowSize(float4 _Size)
{

    // 윈도우 사이즈 세팅의 경우, 타이틀바와 프레임까지 생각해서 크기를 결정해주어야한다.
    RECT Rc = { 0, 0, _Size.ix(), _Size.iy() };

    ScreenSize = _Size;

    // 내가 원하는 크기를 넣으면 타이틀바까지 고려한 크기를 리턴주는 함수.
    AdjustWindowRect(&Rc, WS_OVERLAPPEDWINDOW, FALSE);

    WindowSize = { static_cast<float>(Rc.right - Rc.left), static_cast<float>(Rc.bottom - Rc.top)};
    // 0을 넣어주면 기존의 크기를 유지한다.
    SetWindowPos(HWnd, nullptr, WindowPos.ix(), WindowPos.iy(), WindowSize.ix(), WindowSize.iy(), SWP_NOZORDER);

    // 완전히 똑같은 크기의 이미지입니다.

    if (nullptr != DoubleBufferImage)
    {
        delete DoubleBufferImage;
        DoubleBufferImage = nullptr;
    }

    DoubleBufferImage = new GameEngineImage();
    DoubleBufferImage->ImageCreate(ScreenSize);


}

// 윈도우가 생성될 위치 설정
void GameEngineWindow::SettingWindowPos(float4 _Pos)
{
    WindowPos = _Pos;
    SetWindowPos(HWnd, nullptr, WindowPos.ix(), WindowPos.iy(), WindowSize.ix(), WindowSize.iy(), SWP_NOZORDER);
}

// 현재 마우스의 위치를 받아온다. 
float4 GameEngineWindow::GetMousePosition()
{
    POINT MoniterPoint;
    LPPOINT PointPtr = &MoniterPoint;
    GetCursorPos(PointPtr);
    ScreenToClient(HWnd, PointPtr);

    return { static_cast<float>(MoniterPoint.x),static_cast<float>(MoniterPoint.y) };
}

void GameEngineWindow::Release()
{
    ::UnregisterClassA(wcex.lpszClassName, wcex.hInstance);
}