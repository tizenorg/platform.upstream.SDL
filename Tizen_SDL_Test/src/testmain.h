#include <SDL.h>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

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
#define MESSAGE_BG				"res/testmessage.bmp"
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
#define SHAPE_BG					"res/testshape.bmp"
#define SPRITE2_BG				"res/testsprite2.bmp"
#define SPRITEMINIMAL_BG			"res/testspriteminimal.bmp"
#define STREAMING_BG			"res/teststreaming.bmp"
#define THREAD_BG				"res/testthread.bmp"
#define TIMER_BG					"res/testtimer.bmp"
#define VER_BG					"res/testver.bmp"
#define VIEWPORT_BG				"res/testviewport.bmp"
#define TOTURETHREAD_BG		"res/toturethread.bmp"
#define TOBEADD1_BG				"res/tobeadded.bmp"
#define TOBEADD2_BG				"res/tobeadded.bmp"
#define TOBEADD3_BG				"res/tobeadded.bmp"
#define TOBEADD4_BG				"res/tobeadded.bmp"
#define TOBEADD5_BG				"res/tobeadded.bmp"
#define TOBEADD6_BG				"res/tobeadded.bmp"
#define TOBEADD7_BG				"res/tobeadded.bmp"


#define AUTOTEST_BT 				0
#define INTERTEST_BT 			1

#define LOOPWAVE_BT 			2
#define LOOPWAVEQUEUE_BT 		3
#define ATOMIC_BT 				4
#define AUDIOHOTPLUG_BT 		5
#define AUDIOINFO_BT 				6
#define CHESSBOARD_BT			7
#define DISPLAYINFO_BT			8
#define DRAW2_BT 				9
#define DROPFILE_BT 				10
#define ERROR_BT					11
#define FILE_BT 					12
#define FILESYSTEM_BT 			13
#define GLES_BT 					14
#define GLES2_BT 				15
#define HIT_BT 					16
#define ICONV_BT 					17
#define IME_BT 					18
#define INTERSECTION_BT			19
#define KEYS_BT					20
#define LOADSO_BT				21
#define LOCK_BT					22
#define MESSAGE_BT				23
#define MULTIAUDIO_BT			24
#define OVERLAY2_BT				25
#define PLATFORM_BT				26
#define RELATIVE_BT				27
#define RENDERCOPYEX_BT		28
#define RENDERTARGET_BT		29
#define RESAMPLE_BT				30
#define SCALE_BT					31
#define SEM_BT					32
#define SHADER_BT				33
#define SHAPE_BT					34
#define SPRITE2_BT				35
#define SPRITEMINIMAL_BT			36
#define STREAMING_BT			37
#define THREAD_BT				38
#define TIMER_BT					39
#define VER_BT					40
#define VIEWPORT_BT				41
#define TOTURETHREAD_BT		42
#define TOBEADD1_BT				43
#define TOBEADD2_BT				44
#define TOBEADD3_BT				45
#define TOBEADD4_BT				46
#define TOBEADD5_BT				47
#define TOBEADD6_BT				48
#define TOBEADD7_BT				49




#define MAINPAGE 				0
#define INTERPAGE 				1
#define NOTIFYPAGE				2

#define INTERACTIVE_ROW 			6
#define INTERACTIVE_COLUM		8

typedef struct
{
	int type;
	SDL_bool state;
	int x;
	int y;
}Button;


