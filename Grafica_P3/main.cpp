	#include <math.h>
	#include <windows.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <conio.h>
	#include <string.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
	
	#define CIRCULO 1
	#define LINHA 2
	
	#define B_do_Andar_Click 3
	#define B_do_Correr_Click 4
	#define B_do_Parar_Click 5

	#define ID_60_PER_SECOND 1
	
	HWND B_do_Andar;
	HWND B_do_Correr;
	HWND B_do_Parar;
	
	HWND LabelFundo;
	HWND LabelAndar;	
	HWND LabelLargura;
	HWND LabelCorrer;
	HWND LabelParar;
	
	LRESULT PickCCor;
	
	HINSTANCE mainHInstance;

	//DECLARACAO DE FUNCOES
	void addCircunferencia(HWND hWnd);
	void addLinha(HWND hWnd);	
	void TransformAndUpdate(int comando, HWND hWnd);	
	void DrawWorld();
	void addElements(HWND hWnd);
	void ResetPosAcao();
	
	void setAndar(HWND hWnd);
	void setCorrer(HWND hWnd);
	void setParar(HWND hWnd);
	
	LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
	float p_vertice = 0;
	HDC hDC;

		
	//DECLARACAO JANELA PRINCIPAL
	int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow){
		
	// Window Class
	  WNDCLASS wc = {};
	  wc.lpszClassName = "Window";
	  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	  wc.lpfnWndProc = WindowProcedure;
	  wc.hInstance = hInst;
	  RegisterClass(&wc);
	  
	  mainHInstance = hInst;
	
	  // Window
	  HWND hWnd;
	  hWnd = CreateWindow(
	    wc.lpszClassName,
	    "Animação GRAFICA I",
	    WS_OVERLAPPEDWINDOW | WS_VISIBLE,
	    0, 0, 800, 550,
	    NULL, NULL, NULL, NULL
	  );
				
	  hDC = GetDC(hWnd);
	  
	  PIXELFORMATDESCRIPTOR pfd;
	  pfd.nSize        = sizeof(pfd);
	  pfd.nVersion     = 1;
	  pfd.dwFlags      = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	  pfd.iPixelType   = PFD_TYPE_RGBA;
	  pfd.cColorBits   = 32;
	  
	  int pf;
	  pf = ChoosePixelFormat(hDC, &pfd);
	  if (pf == 0) {
	    MessageBox(NULL, "ChoosePixelFormat() failed: Cannot find a suitable pixel format.", "Error", MB_OK); 
	    return 0;
	  } 
	  if (SetPixelFormat(hDC, pf, &pfd) == FALSE) {
	    MessageBox(NULL, "SetPixelFormat() failed: Cannot set format specified.", "Error", MB_OK);
	    return 0;
	  }
	  DescribePixelFormat(hDC, pf, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
      SetTimer(hWnd, ID_60_PER_SECOND, 1000/60, NULL);
	  
	  HGLRC hRC;
	  hRC = wglCreateContext(hDC);
	  wglMakeCurrent(hDC, hRC);
	
	  ShowWindow(hWnd, ncmdshow);
	  
	  MSG msg = {};
	  while(GetMessage(&msg, NULL, 0, 0)){
	    TranslateMessage(&msg);
	    DispatchMessage(&msg);
	  }
	  
	  wglMakeCurrent(NULL, NULL);
	  ReleaseDC(hWnd, hDC);
	  wglDeleteContext(hRC);
	  DestroyWindow(hWnd);
	  
	  return 0;
	}
	
	
	//CALLBACK DE COMANDOS
	LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp){
		
		PAINTSTRUCT ps;
		
		switch (msg){
			
			case WM_PAINT:
	      		addElements(hWnd);
	      		break;
				
			case WM_COMMAND:
				switch(wp){
					case B_do_Andar_Click:
						setAndar(hWnd);
						break;
					case B_do_Correr_Click:
						setCorrer(hWnd);
						break;
					case B_do_Parar_Click:
						setParar(hWnd);
						break;
				}
				break;
				
			case WM_TIMER:
	 			if(wp == ID_60_PER_SECOND){
	 				DrawWorld();
					SwapBuffers(hDC);
	 			}break;
	
		   	case WM_SIZE:
	      		glViewport(0, 0, LOWORD(lp), HIWORD(lp));
	      		PostMessage(hWnd, WM_PAINT, 0, 0);
	      		break;
			
			case WM_DESTROY:
			PostQuitMessage(0);
				return 0;
		}
		
		return DefWindowProc(hWnd, msg, wp, lp);
	}
	
	//TRIANGULO
	void setAndar(HWND hWnd) {
			MessageBox(NULL, "ANDOU!", "WARNING", MB_OK);
			return;
		}
	void setCorrer(HWND hWnd) {
			MessageBox(NULL, "CORREU!", "WARNING", MB_OK);
			return;
		}
	void setParar(HWND hWnd) {
			MessageBox(NULL, "PAROU!", "WARNING", MB_OK);
			return;
		}
		//INSTANCIA O TRIANGULO COM OS PARAMETROS
		
		
	
	
	void addElements(HWND hWnd){
		
		ResetPosAcao();
	
		CreateWindow(
			"Static",
			"Johnnie Walking - RENAN, GIOVANI E LUCAS",
			WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER,
			0, 0, 800, 20,
			hWnd,
			NULL, NULL, NULL
		);
		
		CreateWindow(
			"Static",
			"UNOESC - 2019",
			WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER,
			0, 490, 800, 30,
			hWnd,
			NULL, NULL, NULL
		);
		
		LabelFundo = CreateWindow(
			"Static",
			"",
			WS_VISIBLE | WS_CHILD | SS_CENTER | WS_EX_APPWINDOW,
			0, 0, 100, 612,
			hWnd,
			NULL, NULL, NULL
		);
		
		//ANDAR TRIANGULO
		
		LabelAndar = CreateWindow(
			"Static",
			"ANDAR!",
			WS_VISIBLE | WS_CHILD | SS_CENTER,
			20, 40, 60, 20,
			hWnd,
			NULL, NULL, NULL
		);
		
		B_do_Andar = CreateWindow(
			"Button",
			"DO IT!",
			WS_VISIBLE | WS_CHILD,
			20, 90, 60, 20,
			hWnd,
			(HMENU)B_do_Andar_Click, NULL, NULL
		);	
		
		//ANDAR FINAL
		
		//CORRER INICIO
		
		LabelCorrer = CreateWindow(
			"Static",
			"CORRER!",
			WS_VISIBLE | WS_CHILD | SS_CENTER,
			20, 140, 60, 20,
			hWnd,
			NULL, NULL, NULL
		);
		
		B_do_Correr = CreateWindow(
			"Button",
			"DO IT!",
			WS_VISIBLE | WS_CHILD,
			20, 190, 60, 20,
			hWnd,
			(HMENU)B_do_Correr_Click, NULL, NULL
		);
		
		//CORRER FINAL
		
		//PARAR INICIO
		
		LabelParar = CreateWindow(
			"Static",
			"PARAR!",
			WS_VISIBLE | WS_CHILD | SS_CENTER,
			20, 240, 60, 20,
			hWnd,
			NULL, NULL, NULL
		);
		
		B_do_Parar = CreateWindow(
			"Button",
			"DO IT!",
			WS_VISIBLE | WS_CHILD,
			20, 290, 60, 20,
			hWnd,
			(HMENU)B_do_Parar_Click, NULL, NULL
		);
		
		//PARAR FINAL
	
		DrawWorld();
		
	}
	
	//RESETA TODA A TELA COMPOSTA
	void ResetPosAcao(){
		DestroyWindow(B_do_Correr);
		DestroyWindow(LabelFundo);
		DestroyWindow(LabelAndar);
		DestroyWindow(LabelCorrer);
		DestroyWindow(B_do_Andar);
		DestroyWindow(B_do_Correr);
		DestroyWindow(B_do_Parar);
	}

	int limite = 0;

	void DrawWorld(){
	  	glViewport(100, 0, 600, 612);
		glClear(GL_COLOR_BUFFER_BIT);
	  //glTranslatef(0.0f, 0.05, 0.0f);
	  glBegin(GL_TRIANGLES);
	  glColor3f(0.0f, 0.0f, 1.0f);
	  glVertex2f(0.0, p_vertice + 0.2);
	  glColor3f(0.0f, 1.0f, 0.0f);
	  glVertex2f(0.2, p_vertice -0.2);
	  glColor3f(1.0f, 0.0f, 0.0f);
	  glVertex2f(-0.2, p_vertice -0.2);
	  glEnd();
	  
	  if(limite == 1){
		  if(p_vertice +0.2 < limite)
	  			p_vertice += 0.1;
		  	else
		  		limite = -1;
		  }else{
			if(p_vertice -0.2 > limite)
		  		p_vertice -= 0.01;
		  	else
		  		limite = 1;
		  }
	  }


