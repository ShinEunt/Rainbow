🌈 Rainbow Rectangle (무지개 사각형 예제)
이 프로젝트는 OpenGL(FreeGLUT)을 사용해 화면 중앙에 7가지 색이 자연스럽게 그라데이션되는 무지개 사각형을 출력하는 예제입니다.
각 색상은 정점마다 설정되어 glColor*() 함수와 함께 보간 효과를 통해 자연스럽게 연결됩니다.

✅ 주요 기능
화면 중앙에 위치한 사각형 출력

사각형은 7등분되어 각각 빨강, 주황, 노랑, 초록, 파랑, 남색, 보라로 색상 지정

각 정점에 색상을 개별로 지정하여 부드럽게 그라데이션 처리

🧩 주요 코드 설명

glBegin(GL_QUADS)	사각형(4개의 정점) 그리기 시작

glColor3f(r, g, b)	현재 정점에 적용할 색상 지정 (RGB, 0~1 범위)

glVertex2f(x, y)	실제 정점 위치 설정

glEnd()	정점 그리기 종료

glClearColor(...)	배경색 설정

glClear(...)	화면 초기화

glutDisplayFunc(...)	화면을 그릴 함수 지정

glutMainLoop()	이벤트 루프 시작 (종료 전까지 반복)


📌 예시 정점 정의 (한 색상 구간)

// 첫 번째 무지개 띠 (빨강 → 주황)
glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(x0, y0); // 좌하단
glColor3f(1.0f, 0.5f, 0.0f); glVertex2f(x1, y0); // 우하단
glColor3f(1.0f, 0.5f, 0.0f); glVertex2f(x1, y1); // 우상단
glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(x0, y1); // 좌상단
이런 식으로 총 7개의 띠를 만들어, 색상이 자연스럽게 이어지는 수평 무지개 그라데이션을 구성합니다.
