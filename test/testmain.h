#include <SDL.h>

#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 1280

#define INTERACTIVEPAGE_BT_WIDTH  120
#define INTERACTIVEPAGE_BT_HEIGHT 135

#define MAINPAGE_BT_WIDTH 500
#define MAINPAGE_BT_HEIGHT 120

#define MAINPAGE_BG "res/bg.bmp"
#define AUTOTEST_BT_BG "res/AutomationTest.bmp"
#define INTERTEST_BT_BG "res/InteractiveTest.bmp"
#define AUTOTEST_BG "res/bg.bmp"
#define AUTOTEST_NOTIFICATION "res/AutomationNotify.bmp"

#define LOOPWAVE_BG 			"res/loopwave.bmp"
#define LOOPWAVEQUEUE_BG 		"res/loopwavequeue.bmp"
#define ATOMIC_BG 				"res/testatomic.bmp"
#define AUDIOHOTPLUG_BG 		"res/testaudiohotplug.bmp"
#define AUDIOINFO_BG 				"res/testaudioinfo.bmp"
#define CHESSBOARD_BG			"res/testchessboard.bmp"
#define DISPLAYINFO_BG 			"res/testdisplayinfo.bmp"
#define DRAW2_BG 				"res/testdraw2.bmp"
#define DROPFILE_BG 				"res/testdropfile.bmp"
#define ERROR_BG				"res/testerror.bmp"
#define FILE_BG 					"res/testfile.bmp"
#define FILESYSTEM_BG 			"res/testfilesystem.bmp"
#define GLES_BG 					"res/testgles.bmp"
#define GLES2_BG 				"res/testgles2.bmp"
#define HIT_BG 					"res/testhit.bmp"
#define ICONV_BG 					"res/testiconv.bmp"
#define IME_BG 					"res/testime.bmp"
#define INTERSECTION_BG			"res/testintersection.bmp"
#define KEYS_BG					"res/testkeys.bmp"
#define LOADSO_BG				"res/testloadso.bmp"
#define LOCK_BG					"res/testlock.bmp"
#define MULTIAUDIO_BG			"res/testmultiaudio.bmp"
#define OVERLAY2_BG				"res/testoverlay2.bmp"
#define PLATFORM_BG				"res/testplatform.bmp"
#define RELATIVE_BG				"res/testrelative.bmp"
#define RENDERCOPYEX_BG		"res/testrendercopyex.bmp"
#define RENDERTARGET_BG		"res/testrendertarget.bmp"
#define RESAMPLE_BG				"res/testresample.bmp"
#define SCALE_BG					"res/testscale.bmp"
#define SEM_BG					"res/testsem.bmp"
#define SHADER_BG				"res/testshader.bmp"
#define SPRITE2_BG				"res/testsprite2.bmp"
#define SPRITEMINIMAL_BG			"res/testspriteminimal.bmp"
#define STREAMING_BG			"res/teststreaming.bmp"
#define THREAD_BG				"res/testthread.bmp"
#define TIMER_BG					"res/testtimer.bmp"
#define VER_BG					"res/testver.bmp"
#define VIEWPORT_BG				"res/testviewport.bmp"
#define TOTURETHREAD_BG		"res/testtoturethread.bmp"
#define TOBEADD1_BG				"res/testadded.bmp"


enum
{
	AUTOTEST_BT,
	INTERTEST_BT,
	LOOPWAVE_BT,
	LOOPWAVEQUEUE_BT,
	ATOMIC_BT ,
	AUDIOHOTPLUG_BT ,
	AUDIOINFO_BT ,
	CHESSBOARD_BT,
	DISPLAYINFO_BT,
	DRAW2_BT ,
	DROPFILE_BT,
	ERROR_BT,
	FILE_BT ,
	FILESYSTEM_BT,
	GLES_BT ,
	GLES2_BT,
	HIT_BT ,
	ICONV_BT,
	IME_BT,
	INTERSECTION_BT,
	KEYS_BT,
	LOADSO_BT,
	LOCK_BT,
	MULTIAUDIO_BT,
	OVERLAY2_BT,
	PLATFORM_BT,
	RELATIVE_BT,
	RENDERCOPYEX_BT,
	RENDERTARGET_BT,
	RESAMPLE_BT,
	SCALE_BT,
	SEM_BT,
	SHADER_BT,
	SPRITE2_BT,
	SPRITEMINIMAL_BT,
	STREAMING_BT,
	THREAD_BT,
	TIMER_BT,
	VER_BT,
	VIEWPORT_BT,
	TOTURETHREAD_BT,
	TOBEADD1_BT

};


#define MAINPAGE 				0
#define INTERPAGE 				1
#define NOTIFYPAGE				2

#define INTERACTIVE_ROW 			8
#define INTERACTIVE_COLUM		5

#define Main_ROW 					2
#define Main_COLUM 				1

typedef struct
{
	int type;
	SDL_bool state;
	int x;
	int y;
}Button;

typedef struct
{
	int row;
	int column;

}Vec2;


