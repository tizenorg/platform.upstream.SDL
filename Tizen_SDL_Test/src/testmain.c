#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include "testmain.h"

SDL_Surface* createSurface(const char* file)
{
	SDL_Surface* imageSurface;
	imageSurface = SDL_LoadBMP(file);
	if(NULL == imageSurface)
	{
		SDL_Log("Fail in SDL_LoadBMP: %s", SDL_GetError());
	}
	
	return imageSurface;
}

SDL_Texture* loadTexture(SDL_Renderer* ren ,SDL_Surface* sur)
{
	SDL_Texture* texture = NULL;
	
	if(sur != NULL)
	{
		texture = SDL_CreateTextureFromSurface(ren, sur);
		SDL_FreeSurface(sur);
		
		if(NULL == texture)
		{
			SDL_Log("Fail in SDL_CreateTextureFromSurface: %s", SDL_GetError());
		}
		else
		{
			//SDL_Log("Succeed to create texture from surface!\n");
		}
	}
	
	return texture;
}

void renderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(ren, tex, NULL, &dst);
	SDL_DestroyTexture(tex);
}

void ClearScreen()
{
	
}

void  switchstate(SDL_bool* a, SDL_bool* b)
{
	SDL_bool tmp; 
	tmp = *b;
	*b = *a;
	*a = tmp;
}

void DrawAutomationPage(SDL_Renderer* ren)
{
	SDL_Surface* surface = createSurface(MAINPAGE_BG);
	SDL_Texture* texture = loadTexture(ren, surface);

	
	renderTexture(texture, ren, 0, 0);

}

void DrawAutomationNotify(SDL_Renderer* ren, int x, int y)
{
	SDL_Surface* surface = createSurface(AUTOTEST_NOTIFICATION);
	SDL_Texture* texture = loadTexture(ren, surface);

	
	renderTexture(texture, ren, x, y);
}

void DrawMainPage(SDL_Renderer* ren)
{
	SDL_Surface* surface = createSurface(MAINPAGE_BG);
	
	SDL_Texture* texture = loadTexture(ren, surface);
	
	renderTexture(texture, ren, 0, 0);
}

void DrawButton(Button b,SDL_Renderer* ren)
{
	SDL_Surface* surface = NULL;
	switch(b.type)
	{
		case AUTOTEST_BT:
			surface = createSurface(AUTOTEST_BT_BG);
			break;
		case INTERTEST_BT:
			surface = createSurface(INTERTEST_BT_BG);
			break;
		case LOOPWAVE_BT:
			surface = createSurface(LOOPWAVE_BG);
			break;
		case LOOPWAVEQUEUE_BT:
			surface = createSurface(LOOPWAVEQUEUE_BG);
			break;
		case ATOMIC_BT:
			surface = createSurface(ATOMIC_BG);
			break;
		case AUDIOHOTPLUG_BT:
			surface = createSurface(AUDIOHOTPLUG_BG);
			break;
		case AUDIOINFO_BT:
			surface = createSurface(AUDIOINFO_BG);
			break;
		case CHESSBOARD_BT:
			surface = createSurface(CHESSBOARD_BG);
			break;
		case DISPLAYINFO_BT:
			surface = createSurface(DISPLAYINFO_BG);
			break;
		case DRAW2_BT:
			surface = createSurface(DRAW2_BG);
			break;
		case DROPFILE_BT:
			surface = createSurface(DROPFILE_BG);
			break;
		case ERROR_BT:
			surface = createSurface(ERROR_BG);
			break;
		case FILE_BT:
			surface = createSurface(FILE_BG);
			break;
		case FILESYSTEM_BT:
			surface = createSurface(FILESYSTEM_BG);
			break;
		case GLES_BT:
			surface = createSurface(GLES_BG);
			break;
		case GLES2_BT:
			surface = createSurface(GLES2_BG);
			break;
		case HIT_BT:
			surface = createSurface(HIT_BG);
			break;
		case ICONV_BT:
			surface = createSurface(ICONV_BG);
			break;
		case IME_BT:
			surface = createSurface(IME_BG);
			break;
		case INTERSECTION_BT:
			surface = createSurface(INTERSECTION_BG);
			break;
		case KEYS_BT:
			surface = createSurface(KEYS_BG);
			break;
		case LOADSO_BT:
			surface = createSurface(LOADSO_BG);
			break;
		case LOCK_BT:
			surface = createSurface(LOCK_BG);
			break;
		case MESSAGE_BT:
			surface = createSurface(MESSAGE_BG);
			break;
		case MULTIAUDIO_BT:
			surface = createSurface(MULTIAUDIO_BG);
			break;
		case OVERLAY2_BT:
			surface = createSurface(OVERLAY2_BG);
			break;
		case PLATFORM_BT:
			surface = createSurface(PLATFORM_BG);
			break;
		case RELATIVE_BT:
			surface = createSurface(RELATIVE_BG);
			break;
		case RENDERCOPYEX_BT:
			surface = createSurface(RENDERCOPYEX_BG);
			break;
		case RENDERTARGET_BT:
			surface = createSurface(RENDERTARGET_BG);
			break;
		case RESAMPLE_BT:
			surface = createSurface(RESAMPLE_BG);
			break;
		case SCALE_BT:
			surface = createSurface(SCALE_BG);
			break;
		case SEM_BT:
			surface = createSurface(SEM_BG);
			break;
		case SHADER_BT:
			surface = createSurface(SHADER_BG);
			break;
		case SHAPE_BT:
			surface = createSurface(SHAPE_BG);
			break;
		case SPRITE2_BT:
			surface = createSurface(SPRITE2_BG);
			break;
		case SPRITEMINIMAL_BT:
			surface = createSurface(SPRITEMINIMAL_BG);
			break;
		case STREAMING_BT:
			surface = createSurface(STREAMING_BG);
			break;
		case THREAD_BT:
			surface = createSurface(THREAD_BG);
			break;
		case TIMER_BT:
			surface = createSurface(TIMER_BG);
			break;
		case VER_BT:
			surface = createSurface(VER_BG);
			break;
		case VIEWPORT_BT:
			surface = createSurface(VIEWPORT_BG);
			break;
		case TOTURETHREAD_BT:
			surface = createSurface(TOTURETHREAD_BG);
			break;
		case TOBEADD1_BT:
			surface = createSurface(TOBEADD1_BG);
			break;
		case TOBEADD2_BT:
			surface = createSurface(TOBEADD2_BG);
			break;
		case TOBEADD3_BT:
			surface = createSurface(TOBEADD3_BG);
			break;
		case TOBEADD4_BT:
			surface = createSurface(TOBEADD4_BG);
			break;
		case TOBEADD5_BT:
			surface = createSurface(TOBEADD5_BG);
			break;
		case TOBEADD6_BT:
			surface = createSurface(TOBEADD6_BG);
			break;
		case TOBEADD7_BT:
			surface = createSurface(TOBEADD7_BG);
			break;
		default:
			break;
				

	}

	
	if(b.state == SDL_TRUE)
	{
		//printf("====b.type is %d====\n", b.type);
		SDL_SetColorKey(surface, SDL_TRUE | SDL_RLEACCEL , SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
		
	}
	
	SDL_Texture* texture = loadTexture(ren, surface);
	
	renderTexture(texture, ren, b.x, b.y);
	
}

void DrawInterractivePage(render)
{
	SDL_Surface* surface = createSurface(MAINPAGE_BG);
	
	SDL_Texture* texture = loadTexture(render, surface);
	
	renderTexture(texture, render, 0, 0);

}


void DrawInterractiveButtons(Button b[INTERACTIVE_ROW][INTERACTIVE_COLUM], SDL_Renderer * ren)
{
	int i, j;
	for(i = 0; i < INTERACTIVE_ROW; i++)
	{
		for(j = 0; j < INTERACTIVE_COLUM; j++)
		{
			DrawButton(b[i][j], ren);

		}

	}

}


void InitInteractiveButtons(Button button[INTERACTIVE_ROW][INTERACTIVE_COLUM])
{
	int tmpType = LOOPWAVE_BT;
	int i, j;

	for(i = 0; i < INTERACTIVE_ROW; i++)
	{
		for(j = 0; j < INTERACTIVE_COLUM; j++)
		{
			button[i][j].x =  (j+1)*40 + (j) * 200;
			button[i][j].y =  (i+1)*25 + (i) *  150;
			button[i][j].state = SDL_FALSE;
			button[i][j].type = tmpType;
			tmpType++;
			
		}

	}

	button[0][0].state = SDL_TRUE;


}

int main(int argc, char*argv[])
{
	SDL_SetMainReady();
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Fail in SDL_Init: %s\n", SDL_GetError());
		return 1;
	}
	
	SDL_Window* window = NULL;
	SDL_Renderer* render = NULL;
	
	window = SDL_CreateWindow("Testmain", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if(NULL == window)
	{
		SDL_Log("Fail in SDL_CreateWindow: %s\n", SDL_GetError());
		return 1;
	}
	
	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(NULL == render)
	{
		SDL_Log("Fail in SDL_CreateRenderer: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}
	
	SDL_RenderClear(render);
	
	DrawMainPage(render);
	Button AutomationButton;
	AutomationButton.type = AUTOTEST_BT;
	AutomationButton.state = SDL_TRUE;
	AutomationButton.x = 660;
	AutomationButton.y = 100;
	DrawButton(AutomationButton, render);

	Button InteractiveButton;
	InteractiveButton.type = INTERTEST_BT;
	InteractiveButton.state = SDL_FALSE;
	InteractiveButton.x = 660;
	InteractiveButton.y = 300;
	DrawButton(InteractiveButton, render);
	
	SDL_RenderPresent(render);

	SDL_Event e;
	SDL_bool quit = SDL_FALSE;
	int page = MAINPAGE;

	Button button[INTERACTIVE_ROW+1][INTERACTIVE_COLUM];
	int InteractButtonRow, InteractButtonColumn;
	pid_t pid;
	
	//InitInteractiveButtons(button);
	
	while(!quit)
	{
		while(SDL_PollEvent(&e))
		{
			if(e.type == SDL_KEYDOWN)
			{
				//printf("The key code is %d\n", e.key.keysym.sym);
				//printf("The key is %s", SDL_GetKeyName(e.key.keysym.sym));
				
				//up && down && left && right
				if(e.key.keysym.sym == SDLK_F20 || e.key.keysym.sym == SDLK_EXECUTE || e.key.keysym.sym == SDLK_F22 || e.key.keysym.sym == SDLK_F23)
				{
					if(page == MAINPAGE)
					{
						switchstate(&AutomationButton.state, &InteractiveButton.state);
						DrawMainPage(render);
						DrawButton(AutomationButton, render);
						DrawButton(InteractiveButton, render);
					
						SDL_RenderPresent(render);

					}
					else if (page == INTERPAGE)
					{
						
						switch(e.key.keysym.sym)
						{
							case SDLK_F20:
								printf("F20 up\n");
								if(InteractButtonRow > 0)
								{
									switchstate(&button[InteractButtonRow][InteractButtonColumn].state, &button[InteractButtonRow-1][InteractButtonColumn].state);
									DrawInterractivePage(render);
									DrawInterractiveButtons(button,render);
									InteractButtonRow--;
									SDL_RenderPresent(render);

								}
								break;
								
							case SDLK_EXECUTE:
								printf("down\n");
								if(InteractButtonRow <= INTERACTIVE_ROW - 2)
								{
									switchstate(&button[InteractButtonRow][InteractButtonColumn].state, &button[InteractButtonRow + 1][InteractButtonColumn].state);
									DrawInterractivePage(render);
									DrawInterractiveButtons(button,render);
									InteractButtonRow++;
									SDL_RenderPresent(render);

								}
								break;
								
							case SDLK_F22:
								printf("left\n");
								if(InteractButtonColumn > 0)
								{
									switchstate(&button[InteractButtonRow][InteractButtonColumn].state, &button[InteractButtonRow][InteractButtonColumn - 1].state);
									DrawInterractivePage(render);
									DrawInterractiveButtons(button,render);
									InteractButtonColumn--;
									SDL_RenderPresent(render);

								}
								break;
								
							case SDLK_F23:
								printf("right\n");
								if(InteractButtonColumn <= INTERACTIVE_COLUM - 2)
								{
									switchstate(&button[InteractButtonRow][InteractButtonColumn].state, &button[InteractButtonRow][InteractButtonColumn + 1].state);
									DrawInterractivePage(render);
									DrawInterractiveButtons(button,render);
									InteractButtonColumn++;
									SDL_RenderPresent(render);
								

								}
								break;
								
							default:
								break;	



						}
					}
					
				}
				//press button enter to start selected test
				if(e.key.keysym.sym == SDLK_7)    
				{
					if(page == MAINPAGE)
					{

						if(AutomationButton.state == SDL_TRUE)
						{
							DrawAutomationPage(render);
							DrawAutomationNotify(render, 560, 340);
							SDL_RenderPresent(render);
							
							pid = fork();

							if (pid < 0)
							{
								printf("Error in craete new process!\n");
								return 1;
							}
							else if (pid == 0)
							{
								execl("./testautomation", "testautomation" ,(char*)0);
							}
							else
							{
								wait();
								DrawMainPage(render);
								DrawButton(AutomationButton, render);
								DrawButton(InteractiveButton, render);
								SDL_RenderPresent(render);
								page = MAINPAGE;

							}

						}
						else if (InteractiveButton.state == SDL_TRUE)
						{
							InitInteractiveButtons(button);
							InteractButtonRow = 0;
							InteractButtonColumn = 0;
							DrawInterractivePage(render);
							DrawInterractiveButtons(button,render);
							page = INTERPAGE;
							SDL_RenderPresent(render);
						}

					}
					else if(page == INTERPAGE)
					{
							DrawAutomationPage(render);
							DrawAutomationNotify(render, 560, 340);
							SDL_RenderPresent(render);
							page = NOTIFYPAGE;
							pid = fork();

							if (pid < 0)
							{
								printf("Error in craete new process!\n");
								return 1;
							}
							else if (pid == 0)
							{
								
								switch(button[InteractButtonRow][InteractButtonColumn].type)
								{
									
									case LOOPWAVE_BT:
										SDLTest_Log("-------loopwave test start-------");
										execl("./loopwave", "loopwave" ,(char*)0);
										break;
									case LOOPWAVEQUEUE_BT:
										SDLTest_Log("-------loopwavequeue test start-------");
										execl("./loopwavequeue", "loopwavequeue", (char*)0);
										break;
									case ATOMIC_BT:
										SDLTest_Log("-------atomic test start-------");
										execl("./testautomic", "testautomic", (char*)0);
										break;
									case AUDIOHOTPLUG_BT:
										SDLTest_Log("-------audiohotplug test start-------");
										execl("./testaudiohotplug", "testaudiohotplug", (char*)0);
										break;
									case AUDIOINFO_BT:
										SDLTest_Log("-------audioinfo test start-------");
										execl("./testaudioinfo", "testaudioinfo", (char*)0);
										break;
									case CHESSBOARD_BT:
										SDLTest_Log("-------draw chessboard test start-------");
										execl("./testdrawchessboard", "testdrawchessboard", (char*)0);
										break;
									case DISPLAYINFO_BT:
										SDLTest_Log("-------displayinfo test start-------");
										execl("./testdisplayinfo", "testdisplayinfo",  (char*)0);
										break;
									case DRAW2_BT:
										SDLTest_Log("-------draw2 test start-------");
										execl("./testdraw2", "testdraw2", (char*)0);
										break;
									case DROPFILE_BT:
										SDLTest_Log("-------dropfile test start-------");
										execl("./testdorpfile", "testdorpfile", (char*)0);
										break;
									case ERROR_BT:
										SDLTest_Log("-------error test start-------");
										execl("./testerror", "testerror", (char*)0);
										break;
									case FILE_BT:
										SDLTest_Log("-------file test start-------");
										execl("./testfile", "testfile", (char*)0);
										break;
									case FILESYSTEM_BT:
										SDLTest_Log("-------filesystem test start-------");
										execl("./testfilesystem", "testfilesystem", (char*)0);
										break;
									case GLES_BT:
										SDLTest_Log("-------gles test start-------");
										execl("./testgles", "testgles", (char*)0);
										break;
									case GLES2_BT:
										SDLTest_Log("-------gles2 test start-------");
										execl("./testgles2", "testgles2", (char*)0);
										break;
									case HIT_BT:
										SDLTest_Log("-------hit test start-------");
										execl("./testhit", "testhit", (char*)0);
										break;
									case ICONV_BT:
										SDLTest_Log("-------iconv test start-------");
										execl("./testconv", "testconv", (char*)0);
										break;
									case IME_BT:
										SDLTest_Log("-------IME test start-------");
										execl("./testtime", "testtime", (char*)0);
										break;
									case INTERSECTION_BT:
										SDLTest_Log("-------intersection test start-------");
										execl("./testintersection", "testintersection", (char*)0);
										break;
									case KEYS_BT:
										SDLTest_Log("-------keys test start-------");
										execl("./testkes", "testkes", (char*)0);
										break;
									case LOADSO_BT:
										SDLTest_Log("-------loadso test start-------");
										execl("./testloadso", "testloadso", (char*)0);
										break;
									case LOCK_BT:
										SDLTest_Log("-------lock test start-------");
										execl("./testlock", "testlock", (char*)0);
										break;
									case MESSAGE_BT:
										SDLTest_Log("-------message test start-------");
										execl("./testmessage", "testmessage", (char*)0);
										break;
									case MULTIAUDIO_BT:
										SDLTest_Log("-------multiaudio test start-------");
										execl("./testmultiaudio", "testmultiaudio", (char*)0);
										break;
									case OVERLAY2_BT:
										SDLTest_Log("-------overlay2 test start-------");
										execl("testoverlay2", "testoverlay2", (char*)0);
										break;
									case PLATFORM_BT:
										SDLTest_Log("-------platform test start-------");
										execl("./testplatform","testplatform", (char*)0);
										break;
									case RELATIVE_BT:
										SDLTest_Log("-------relative test start-------");
										execl("./testrelative", "testrelative", (char*)0);
										break;
									case RENDERCOPYEX_BT:
										SDLTest_Log("-------rendercopyex test start-------");
										execl("./testrendercopyex", "testrendercopyex", (char*)0);
										break;
									case RENDERTARGET_BT:
										SDLTest_Log("-------rendercopytarget test start-------");
										execl("./testrendertarget", "testrendertarget", (char*)0);
										break;
									case RESAMPLE_BT:
										SDLTest_Log("-------resample test start-------");
										execl("./testresample", "testresample", (char*)0);
										break;
									case SCALE_BT:
										SDLTest_Log("-------scale test start-------");
										execl("./testscale", "testscale", (char*)0);
										break;
									case SEM_BT:
										SDLTest_Log("-------semaphore test start-------");
										execl("./testsem", "testsem", (char*)0);
										break;
									case SHADER_BT:
										SDLTest_Log("-------shader test start-------");
										execl("./testshader", "testshader", (char*)0);
										break;
									case SHAPE_BT:
										SDLTest_Log("-------shape test start-------");
										execl("./testshape", "testshape", "res/sample.bmp", (char*)0);
										break;
									case SPRITE2_BT:
										SDLTest_Log("-------sprite2 test start-------");
										execl("./testsprite2", "testsprite2", (char*)0);
										break;
									case SPRITEMINIMAL_BT:
										SDLTest_Log("-------testsptiteminimal test start-------");
										execl("./testspriteminimal", "testspriteminimal", (char*)0);
										break;
									case STREAMING_BT:
										SDLTest_Log("-------streaming test start-------");
										execl("./teststreaming", "teststreaming", (char*)0);
										break;
									case THREAD_BT:
										SDLTest_Log("-------thread test start-------");
										execl("./testthread", "testthread", (char*)0);
										break;
									case TIMER_BT:
										SDLTest_Log("-------timer test start-------");
										execl("./testtimer", "testtimer", (char*)0);
										break;
									case VER_BT:
										SDLTest_Log("-------version test start-------");
										execl("./testver", "testver", (char*)0);
										break;
									case VIEWPORT_BT:
										SDLTest_Log("-------viewport test start-------");
										execl("./testviewport", "testviewport", 0);
										break;
									case TOTURETHREAD_BT:
										SDLTest_Log("-------torturethread test start-------");
										execl("./torturethread", "torturethread", 0);
										break;
									default:
										break;


								}
									
								
							}
							else
							{
								wait();
								DrawInterractivePage(render);
								DrawInterractiveButtons(button,render);
								SDL_RenderPresent(render);
								page = INTERPAGE;

							}

					}
					
				}
				if(e.key.keysym.sym == SDLK_f)
				{
					if(page == INTERPAGE)
					{

						DrawMainPage(render);
						DrawButton(AutomationButton, render);
						DrawButton(InteractiveButton, render);
						SDL_RenderPresent(render);
						page = MAINPAGE;
					}

				}
			}
			
		}
	}
	
	//SDL_Delay(10000);
	
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return 0;

}
