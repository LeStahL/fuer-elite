#ifndef PAL_WIN32_H
#define PAL_WIN32_H

#include "common.h"

void *malloc(size_t size)
{
	return GlobalAlloc(GMEM_ZEROINIT, size);
}

HWAVEOUT hWaveOut;
WAVEHDR header = { 0, 0, 0, 0, 0, 0, 0, 0 };

HDC hdc;
HGLRC glrc;

int flip_buffers()
{
	SwapBuffers(hdc);

	MSG msg = { 0 };
	while ( PeekMessageA( &msg, NULL, 0, 0, PM_REMOVE ) )
	{
		if ( msg.message == WM_QUIT ) {
			return FALSE;
		}
		TranslateMessage( &msg );
		DispatchMessageA( &msg );
	}

	return TRUE;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
		case WM_KEYDOWN:
			switch(wParam)
			{
				case VK_ESCAPE:
					ExitProcess(0);
					break;
				case VK_SPACE:
					// pause/unpaused render timer
					paused = !paused;
					if(paused)
						waveOutPause(hWaveOut);
					else
						waveOutRestart(hWaveOut);
					break;
			}
			break;
		case WM_RBUTTONDOWN:
			ExitProcess(0);
			break;

		default:
			break;

	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK DialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
		case WM_COMMAND:
			UINT id =  LOWORD(wParam);
			HWND hSender = (HWND)lParam;

			switch(id)
			{
				case 5:
				{
					int index = SendMessage(hSender, CB_GETCURSEL, 0, 0);
					if(index == 0)
					{
						w = 1920;
						h = 1080;
					}
					else if(index == 1)
					{
						w = 960;
						h = 540;
					}
					else if(index == 2)
					{
						w = 1024;
						h = 768;
					}
				}
					break;
				case 6:
					muted = !muted;
					if(muted)
						SendMessage(hSender, BM_SETCHECK, BST_CHECKED, 0);
					else
						SendMessage(hSender, BM_SETCHECK, BST_UNCHECKED, 0);
					break;
				case 7:
					DestroyWindow(hwnd);
					PostQuitMessage(0);
					break;
				case 8: // Full screen Antialiasing
				{
					int index = SendMessage(hSender, CB_GETCURSEL, 0, 0);
					fsaa = (index + 1)*(index + 1);
				}
					break;
				case 9: // Texture buffer size
				{
					int index = SendMessage(hSender, CB_GETCURSEL, 0, 0);
					texs = 128;
					for(int i=0; i<index; ++i)
						texs *= 2;
					block_size = texs*texs;
				}
					break;
				case 10:
				{
					override_index = SendMessage(hSender, CB_GETCURSEL, 0, 0);
					scene_override = override_index > 0;
				}
				break;
			}
			break;

		case WM_CLOSE:
			ExitProcess(0);
			break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI demo(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
#ifdef DEBUG
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
#endif

	// Display settings selector
	WNDCLASS wca = { 0 };
	wca.lpfnWndProc   = DialogProc;
	wca.hInstance     = hInstance;
	wca.lpszClassName = L"Settings";
	RegisterClass(&wca);
	HWND lwnd = CreateWindowEx(
		0,                              // Optional window styles.
		L"Settings",                     // Window class
		demoname,    // Window text
		WS_OVERLAPPEDWINDOW,            // Window style

		// Size and position
		200, 200, 300, 300,

		NULL,       // Parent window
		NULL,       // Menu
		hInstance,  // Instance handle
		NULL        // Additional application data
		);

	// Add "Resolution: " text
	HWND hResolutionText = CreateWindow(WC_STATIC, "Resolution: ", WS_VISIBLE | WS_CHILD | SS_LEFT, 10,15,100,100, lwnd, NULL, hInstance, NULL);

	// Add resolution Combo box
	HWND hResolutionComboBox = CreateWindow(WC_COMBOBOX, TEXT(""),
	 CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
	 100, 10, 175, 80, lwnd, (HMENU)5, hInstance,
	 NULL);

	// Add items to resolution combo box and select full HD
	const char *fullhd = "1920*1080",
		*halfhd = "960*540",
		*normal = "1024*768";
	SendMessage(hResolutionComboBox,(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) (fullhd));
	SendMessage(hResolutionComboBox,(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) (halfhd));
	SendMessage(hResolutionComboBox,(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) (normal));
	SendMessage(hResolutionComboBox, CB_SETCURSEL, 0, 0);

	// Add mute checkbox
	HWND hMuteCheckbox = CreateWindow(WC_BUTTON, TEXT("Mute"),
					 WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
					 10, 40, 100, 20,
					 lwnd, (HMENU) 6, hInstance, NULL);

	// Add "Antialiasing: " text
	HWND hAntialiasingText = CreateWindow(WC_STATIC, "FSAA: ", WS_VISIBLE | WS_CHILD | SS_LEFT, 10,65,100,100, lwnd, NULL, hInstance, NULL);

	// Add Fullscreen Antialiasing combo box
	HWND hFSAAComboBox= CreateWindow(WC_COMBOBOX, TEXT(""),
	 CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
	 100, 60, 175, 280, lwnd, (HMENU)8, hInstance,
	 NULL);

	// Populate with entries
	const char *fsaa1= "None",
		*fsaa4 = "4*FSAA",
		*fsaa9 = "9*FSAA",
		*fsaa16 = "16*FSAA",
		*fsaa25 = "25*FSAA";
	SendMessage(hFSAAComboBox,(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) (fsaa1));
	SendMessage(hFSAAComboBox,(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) (fsaa4));
	SendMessage(hFSAAComboBox,(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) (fsaa9));
	SendMessage(hFSAAComboBox,(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) (fsaa16));
	SendMessage(hFSAAComboBox,(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) (fsaa25));
	SendMessage(hFSAAComboBox, CB_SETCURSEL, 4, 0);

	// Add "SFX Buffer: " text
	HWND hTXAAText = CreateWindow(WC_STATIC, "SFX Buffer: ", WS_VISIBLE | WS_CHILD | SS_LEFT, 10,95,100,100, lwnd, NULL, hInstance, NULL);

	// Add SFX buffer size combo box
	HWND hTXAAComboBox= CreateWindow(WC_COMBOBOX, TEXT(""),
	 CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
	 100, 90, 175, 280, lwnd, (HMENU)9, hInstance,
	 NULL);

	// Populate with entries
	const char *buf128= "128^2 px",
		*buf256 = "256^2 px",
		*buf512 = "512^2 px",
		*buf1024 = "1024^2 px";
	SendMessage(hTXAAComboBox,(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) (buf128));
	SendMessage(hTXAAComboBox,(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) (buf256));
	SendMessage(hTXAAComboBox,(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) (buf512));
	SendMessage(hTXAAComboBox,(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) (buf1024));
	//SendMessage(hTXAAComboBox, CB_SETCURSEL, 3, 0);
	SendMessage(hTXAAComboBox, CB_SETCURSEL, 2, 0);

	// Add "Antialiasing: " text
	HWND hSceneText = CreateWindow(WC_STATIC, "Scene: ", WS_VISIBLE | WS_CHILD | SS_LEFT, 10,125,100,100, lwnd, NULL, hInstance, NULL);

	// Add scene selector
	HWND hSceneComboBox = CreateWindow(WC_COMBOBOX, TEXT(""),
	 CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
	 100, 120, 175, 280, lwnd, (HMENU)10, hInstance,
	 NULL);

	// Populate with entries
	const char *all_scenes = "All scenes",
		*logo210_scene= "Team210 Logo";
//         *logoendeavor_scene = "Planet rotation",
//         *surface_scene = "Surface with pipes",
//         *hangar_outside_scene = "Hangar outside",
//         *nr4_scene = "NR4 Graffiti build-up",
//         *qm_scene = "QM Graffiti build-up",
//         *trip_scene = "Trip scene",
//         *fourtwenty_scene = "Four-twenty scene",
//         *greet_scene = "Greetings",
//         *solskogen_scene = "Solskogen";
	SendMessage(hSceneComboBox,(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) (all_scenes));
	SendMessage(hSceneComboBox,(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) (logo210_scene));
//     SendMessage(hSceneComboBox,(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) (logoendeavor_scene));
//     SendMessage(hSceneComboBox,(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) (surface_scene));
//     SendMessage(hSceneComboBox,(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) (hangar_outside_scene));
//     SendMessage(hSceneComboBox,(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) (nr4_scene));
//     SendMessage(hSceneComboBox,(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) (qm_scene));
//     SendMessage(hSceneComboBox,(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) (trip_scene));
//     SendMessage(hSceneComboBox,(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) (fourtwenty_scene));
//     SendMessage(hSceneComboBox,(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) (greet_scene));
//     SendMessage(hSceneComboBox,(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) (solskogen_scene));
	SendMessage(hSceneComboBox, CB_SETCURSEL, 0, 0);

	// Add start button
	HWND hwndButton = CreateWindow(WC_BUTTON,"Party!",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,185,165,90,90,lwnd,(HMENU)7,hInstance,NULL);

	// Show the selector
	ShowWindow(lwnd, TRUE);
	UpdateWindow(lwnd);

	MSG msg = { 0 };
	while(GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

#ifdef DEBUG
	printf("Rendering Demo with:\nSound ");
//     if(muted)printf("muted");
//     else printf("playing");
	printf("\nResolution: %d * %d\n", w, h);
	printf("FSAA: %d*\n", fsaa);
#endif

	// Display demo window
	CHAR WindowClass[]  = "Team210 Demo Window";

	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
	wc.lpfnWndProc = &WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WindowClass;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	// Get full screen information
	HMONITOR hmon = MonitorFromWindow(0, MONITOR_DEFAULTTONEAREST);
	MONITORINFO mi = { sizeof(mi) };
	GetMonitorInfo(hmon, &mi);

	// Create the window.
	HWND hwnd = CreateWindowEx(
		0,                                                          // Optional window styles.
		WindowClass,                                                // Window class
		":: NR4^QM/Team210 :: GO - MAKE A DEMO ::",                                 // Window text
		WS_POPUP | WS_VISIBLE,                                      // Window style
		mi.rcMonitor.left,
		mi.rcMonitor.top,
		mi.rcMonitor.right - mi.rcMonitor.left,
		mi.rcMonitor.bottom - mi.rcMonitor.top,                     // Size and position

		NULL,                                                       // Parent window
		NULL,                                                       // Menu
		hInstance,                                                  // Instance handle
		0                                                           // Additional application data
	);

	// Show it
	ShowWindow(hwnd, TRUE);
	UpdateWindow(hwnd);

	// Create OpenGL context
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
		PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
		32,                   // Colordepth of the framebuffer.
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,                   // Number of bits for the depthbuffer
		8,                    // Number of bits for the stencilbuffer
		0,                    // Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	hdc = GetDC(hwnd);

	int  pf = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, pf, &pfd);

	glrc = wglCreateContext(hdc);
	wglMakeCurrent(hdc, glrc);

	// OpenGL extensions
	glGetProgramiv = (PFNGLGETPROGRAMIVPROC) wglGetProcAddress("glGetProgramiv");
	glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC) wglGetProcAddress("glGetProgramInfoLog");
	glGetShaderiv = (PFNGLGETSHADERIVPROC) wglGetProcAddress("glGetShaderiv");
	glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC) wglGetProcAddress("glGetShaderInfoLog");
	glCreateShader = (PFNGLCREATESHADERPROC) wglGetProcAddress("glCreateShader");
	glCreateProgram = (PFNGLCREATEPROGRAMPROC) wglGetProcAddress("glCreateProgram");
	glShaderSource = (PFNGLSHADERSOURCEPROC) wglGetProcAddress("glShaderSource");
	glCompileShader = (PFNGLCOMPILESHADERPROC) wglGetProcAddress("glCompileShader");
	glAttachShader = (PFNGLATTACHSHADERPROC) wglGetProcAddress("glAttachShader");
	glLinkProgram = (PFNGLLINKPROGRAMPROC) wglGetProcAddress("glLinkProgram");
	glUseProgram = (PFNGLUSEPROGRAMPROC) wglGetProcAddress("glUseProgram");
	glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC) wglGetProcAddress("glGetUniformLocation");
	glUniform2f = (PFNGLUNIFORM2FPROC) wglGetProcAddress("glUniform2f");
	glUniform1f = (PFNGLUNIFORM1FPROC) wglGetProcAddress("glUniform1f");
	glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC) wglGetProcAddress("glGenFramebuffers");
	glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC) wglGetProcAddress("glBindFramebuffer");
	glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC) wglGetProcAddress("glFramebufferTexture2D");
	glNamedRenderbufferStorageEXT = (PFNGLNAMEDRENDERBUFFERSTORAGEEXTPROC) wglGetProcAddress("glNamedRenderbufferStorage");
	glActiveTexture = (PFNGLACTIVETEXTUREPROC) wglGetProcAddress("glActiveTexture");
	glUniform1i = (PFNGLUNIFORM1IPROC) wglGetProcAddress("glUniform1i");

	load_demo();

	// Main loop
	t_start = 0.;
	while(flip_buffers())
	{
		static MMTIME MMTime = { TIME_SAMPLES, 0};
		waveOutGetPosition(hWaveOut, &MMTime, sizeof(MMTIME));
		t_now = ((double)MMTime.u.sample)/( 44100.0);

		draw();
	}

	return 0;
}

void initialize_sound()
{
	hWaveOut = 0;
	int n_bits_per_sample = 16;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, channels, sample_rate, sample_rate*channels*n_bits_per_sample / 8, channels*n_bits_per_sample / 8, n_bits_per_sample, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

	header.lpData = smusic1;
	header.dwBufferLength = 4 * music1_size;
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
}

#endif
