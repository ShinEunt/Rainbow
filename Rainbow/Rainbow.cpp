#pragma comment(lib, "opengl32.lib")

#include <windows.h>
#include <gl/GL.h>

LRESULT CALLBACK WndProc(HWND h, UINT m, WPARAM w, LPARAM l) {
    if (m == WM_DESTROY) { PostQuitMessage(0); return 0; }
    return DefWindowProc(h, m, w, l);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmd) {
    WNDCLASS wc = { CS_OWNDC, WndProc, 0, 0, hInst, 0, 0, 0, 0, L"GL" };
    RegisterClass(&wc);
    HWND hwnd = CreateWindow(L"GL", L"Rainbow Gradient", WS_OVERLAPPEDWINDOW, 100, 100, 800, 600, 0, 0, hInst, 0);
    ShowWindow(hwnd, nCmd);

    HDC dc = GetDC(hwnd);
    PIXELFORMATDESCRIPTOR pfd = { sizeof(pfd), 1, PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, PFD_TYPE_RGBA };
    SetPixelFormat(dc, ChoosePixelFormat(dc, &pfd), &pfd);
    HGLRC rc = wglCreateContext(dc); wglMakeCurrent(dc, rc);

    float left = -0.6f, right = 0.6f;
    float bottom = -0.4f, top = 0.4f;
    float bandWidth = (right - left) / 7.0f;

    float colors[8][3] = {
        {1.0f, 0.0f, 0.0f},  // 빨강
        {1.0f, 0.5f, 0.0f},  // 주황
        {1.0f, 1.0f, 0.0f},  // 노랑
        {0.0f, 1.0f, 0.0f},  // 초록
        {0.0f, 0.0f, 1.0f},  // 파랑
        {0.29f, 0.0f, 0.51f},// 남색
        {0.56f, 0.0f, 1.0f}, // 보라
        {0.8f, 0.4f, 1.0f}   // 연보라 (끝 처리를 부드럽게)
    };

    float v[7 * 4 * 5];  // 7개 구간 × 4꼭짓점 × (x,y,r,g,b)
    int idx = 0;

    for (int i = 0; i < 7; ++i) {
        float x0 = left + i * bandWidth;
        float x1 = x0 + bandWidth;

        float* c0 = colors[i];
        float* c1 = colors[i + 1]; // 다음 색상

        // 아래 왼쪽
        v[idx++] = x0; v[idx++] = bottom;
        v[idx++] = c0[0]; v[idx++] = c0[1]; v[idx++] = c0[2];

        // 아래 오른쪽
        v[idx++] = x1; v[idx++] = bottom;
        v[idx++] = c1[0]; v[idx++] = c1[1]; v[idx++] = c1[2];

        // 위 오른쪽
        v[idx++] = x1; v[idx++] = top;
        v[idx++] = c1[0]; v[idx++] = c1[1]; v[idx++] = c1[2];

        // 위 왼쪽
        v[idx++] = x0; v[idx++] = top;
        v[idx++] = c0[0]; v[idx++] = c0[1]; v[idx++] = c0[2];
    }

    MSG msg;
    while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE) || 1) {
        if (msg.message == WM_QUIT) break;
        TranslateMessage(&msg); DispatchMessage(&msg);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // 어두운 배경
        glClear(GL_COLOR_BUFFER_BIT);

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glVertexPointer(2, GL_FLOAT, 5 * sizeof(float), v);
        glColorPointer(3, GL_FLOAT, 5 * sizeof(float), v + 2);

        for (int i = 0; i < 7; i++) {
            glDrawArrays(GL_QUADS, i * 4, 4);
        }

        SwapBuffers(dc);
    }

    wglMakeCurrent(0, 0);
    wglDeleteContext(rc);
    ReleaseDC(hwnd, dc);
    return 0;
}
