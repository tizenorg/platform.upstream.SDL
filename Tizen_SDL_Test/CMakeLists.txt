INCLUDE(FindPkgConfig)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(sdl2_test C CXX)

IF("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "armv7l") 
ADD_DEFINITIONS("-DARCH_ARMV7") 
ELSE() 
ADD_DEFINITIONS("-DARCH_I586") 
ENDIF()

IF("${CMAKE_BUILD_TYPE}" STREQUAL "") 
	SET(CMAKE_BUILD_TYPE "Debug") 
ENDIF("${CMAKE_BUILD_TYPE}" STREQUAL "") 
	MESSAGE("Build type: ${CMAKE_BUILD_TYPE}")

IF(NOT DEFINED PACKAGE_NAME) 
	SET(PACKAGE_NAME "org.tizen.${PROJECT_NAME}") 
ENDIF(NOT DEFINED PACKAGE_NAME)
IF(NOT DEFINED RESDIR)
    SET(RESDIR "${PREFIX}/res")
ENDIF(NOT DEFINED RESDIR)

set(SDL_MAJOR_VERSION 2)
set(SDL_MINOR_VERSION 0)
set(SDL_MICRO_VERSION 4)
set(SDL_INTERFACE_AGE 0)
set(SDL_BINARY_AGE 4)
set(SDL_VERSION "${SDL_MAJOR_VERSION}.${SDL_MINOR_VERSION}.${SDL_MICRO_VERSION}")

set(LIBNAME SDL2)
set(CMAKE_C_FLAGS "-g -O2")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-multichar")

ADD_DEFINITIONS(-D__TIZEN__)
INCLUDE(FindPkgConfig)
pkg_check_modules(APPS_PKGS REQUIRED

	dlog
)
FOREACH(flag ${APPS_PKGS_CFLAGS})
    SET(EXTRA_CFLAGS "${EXTRA_CFLAGS} ${flag}")
ENDFOREACH(flag)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EXTRA_CFLAGS}")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${EXTRA_CFLAGS}")

INCLUDE_DIRECTORIES(
		    ${CMAKE_SOURCE_DIR}/include/
		   )
LINK_DIRECTORIES(
			${CMAKE_SOURCE_DIR}/lib/
			)

set(MAIN_SOURCE 
		src/common/SDL_test_assert.c
		src/common/SDL_test_common.c
		src/common/SDL_test_compare.c
		src/common/SDL_test_crc32.c
		src/common/SDL_test_font.c
		src/common/SDL_test_fuzzer.c
		src/common/SDL_test_harness.c
		src/common/SDL_test_imageBlit.c
		src/common/SDL_test_imageBlitBlend.c
		src/common/SDL_test_imageFace.c
		src/common/SDL_test_imagePrimitives.c
		src/common/SDL_test_imagePrimitivesBlend.c
		src/common/SDL_test_log.c
		src/common/SDL_test_md5.c
		src/common/SDL_test_random.c
	)
set (SDL_TEST_SOURCE
		src/testmain.c
	)
set (AUTOMATION_SOURCE

		src/test/testautomation.c 
		src/test/testautomation_audio.c 
		src/test/testautomation_clipboard.c 
		src/test/testautomation_events.c 
		src/test/testautomation_hints.c
		src/test/testautomation_keyboard.c 
		src/test/testautomation_main.c 
		src/test/testautomation_mouse.c 
		src/test/testautomation_pixels.c 
		src/test/testautomation_platform.c 
		src/test/testautomation_rect.c 
		src/test/testautomation_render.c 
		src/test/testautomation_rwops.c 
		src/test/testautomation_sdltest.c 
		src/test/testautomation_stdlib.c 
		src/test/testautomation_surface.c 
		src/test/testautomation_syswm.c 
		src/test/testautomation_timer.c 
		src/test/testautomation_video.c 
	)
set (LOOPWAVE_SOURCE
	src/test/loopwave.c
	)
set (LOOPWAVEQUEUE_SOURCE
	src/test/loopwavequeue.c
	)
set (AUTOMIC_SOURCE
	src/test/testatomic.c
	)
set (AUDIOHOTPLUGIN_SOURCE
	src/test/testaudiohotplug.c
	)
set (AUDIOINFO_SOURCE
	src/test/testaudioinfo.c
	)
set (DISPLAYINFO_SOURCE
	src/test/testdisplayinfo.c
	)
set (DRAW2_SOURCE
	src/test/testdraw2.c
	)
set (DRAWCHESSBOARD_SOURCE
	src/test/testdrawchessboard.c
	)
set (DORPFILE_SOURCE
	src/test/testdropfile.c
	)
set (ERROR_SOURCE
	src/test/testerror.c
	)
set (FILE_SOURCE
	src/test/testfile.c
	)
set (FILESYSTEM_SOURCE
	src/test/testfilesystem.c
	)
set (GLES_SOURCE
	src/test/testgles.c
	)
set (GLES2_SOURCE
		src/test/testgles2.c
	)
set (HIT_SOURCE
		src/test/testhittesting.c
	)
set (CONV_SOURCE
		src/test/testiconv.c
	)
set (TIME_SOURCE
		src/test/testime.c
	)
set (INTERSECTION_SOURCE
		src/test/testintersections.c
	)
set (KEYS_SOURCE
		src/test/testkeys.c
	)
set (LOADSO_SOURCE
		src/test/testloadso.c
	)
set (LOCK_SOURCE
		src/test/testlock.c
	)
set (MESSAGE_SOURCE
		src/test/testmessage.c
	)
set (MULTIAUDIO_SOURCE
		src/test/testmultiaudio.c
	)
set (OVERLAY2_SOURCE
		src/test/testoverlay2.c
	)
set (PLATFORM_SOURCE
		src/test/testplatform.c
	)
set (RELATIVE_SOURCE
		src/test/testrelative.c
	)
set (RENDERCOPYEX_SOURCE
		src/test/testrendercopyex.c
	)
set (RENDERTARGET_SOURCE
		src/test/testrendertarget.c
	)
set (RESAMPLE_SOURCE
		src/test/testresample.c
	)
set (SCALE_SOURCE
		src/test/testscale.c
	)
set (SEM_SOURCE
		src/test/testsem.c
	)
set (SHADER_SOURCE
		src/test/testshader.c
	)
set (SHAPE_SOURCE
		src/test/testshape.c
	)
set (SPRITE2_SOURCE
		src/test/testsprite2.c
	)
set (SPRITEMINIMAL_SOURCE
		src/test/testspriteminimal.c
	)
set (STREAMING_SOURCE
		src/test/teststreaming.c
	)
set (THREAD_SOURCE
		src/test/testthread.c
	)
set (TIMER_SOURCE
		src/test/testtimer.c
	)
set (VER_SOURCE
		src/test/testver.c
	)
set (VIEWPORT_SOURCE
		src/test/testviewport.c
	)
set (TORTURETHREAD_SOURCE
		src/test/torturethread.c
	)
	#${PROJECT_NAME}
add_executable(testmain ${MAIN_SOURCE} ${SDL_TEST_SOURCE})
TARGET_LINK_LIBRARIES(testmain SDL2-2.0)
	
add_executable(testautomation ${MAIN_SOURCE} ${AUTOMATION_SOURCE})
TARGET_LINK_LIBRARIES(testautomation SDL2-2.0)
	
add_executable(loopwave ${MAIN_SOURCE} ${LOOPWAVE_SOURCE})
TARGET_LINK_LIBRARIES(loopwave SDL2-2.0)

add_executable(loopwavequeue ${MAIN_SOURCE} ${LOOPWAVEQUEUE_SOURCE})
TARGET_LINK_LIBRARIES(loopwavequeue SDL2-2.0)
	
add_executable(testautomic ${MAIN_SOURCE} ${AUTOMIC_SOURCE})
TARGET_LINK_LIBRARIES(testautomic SDL2-2.0)

add_executable(testaudiohotplug ${MAIN_SOURCE} ${AUDIOHOTPLUGIN_SOURCE})
TARGET_LINK_LIBRARIES(testaudiohotplug SDL2-2.0)

add_executable(testaudioinfo ${MAIN_SOURCE} ${AUDIOINFO_SOURCE})
TARGET_LINK_LIBRARIES(testaudioinfo SDL2-2.0)

add_executable(testdisplayinfo ${MAIN_SOURCE} ${DISPLAYINFO_SOURCE})
TARGET_LINK_LIBRARIES(testdisplayinfo SDL2-2.0)

add_executable(testdraw2 ${MAIN_SOURCE} ${DRAW2_SOURCE})
TARGET_LINK_LIBRARIES(testdraw2 SDL2-2.0)

add_executable(testdrawchessboard ${MAIN_SOURCE} ${DRAWCHESSBOARD_SOURCE})
TARGET_LINK_LIBRARIES(testdrawchessboard SDL2-2.0)

add_executable(testdorpfile ${MAIN_SOURCE} ${DRAWCHESSBOARD_SOURCE})
TARGET_LINK_LIBRARIES(testdorpfile SDL2-2.0)

add_executable(testerror ${MAIN_SOURCE} ${ERROR_SOURCE})
TARGET_LINK_LIBRARIES(testerror SDL2-2.0)

add_executable(testfile ${MAIN_SOURCE} ${FILE_SOURCE})
TARGET_LINK_LIBRARIES(testfile SDL2-2.0)

add_executable(testfilesystem ${MAIN_SOURCE} ${FILESYSTEM_SOURCE})
TARGET_LINK_LIBRARIES(testfilesystem SDL2-2.0)

add_executable(testgles ${MAIN_SOURCE} ${GLES_SOURCE})
TARGET_LINK_LIBRARIES(testgles SDL2-2.0 GLESv1_CM EGL)

add_executable(testgles2 ${MAIN_SOURCE} ${GLES2_SOURCE})
TARGET_LINK_LIBRARIES(testgles2 SDL2-2.0 GLESv2 EGL)

add_executable(testhit ${MAIN_SOURCE} ${HIT_SOURCE})
TARGET_LINK_LIBRARIES(testhit SDL2-2.0)

add_executable(testconv ${MAIN_SOURCE} ${CONV_SOURCE})
TARGET_LINK_LIBRARIES(testconv SDL2-2.0)

add_executable(testtime ${MAIN_SOURCE} ${TIME_SOURCE})
TARGET_LINK_LIBRARIES(testtime SDL2-2.0)

add_executable(testintersection ${MAIN_SOURCE} ${INTERSECTION_SOURCE})
TARGET_LINK_LIBRARIES(testintersection SDL2-2.0)

add_executable(testkes ${MAIN_SOURCE} ${KEYS_SOURCE})
TARGET_LINK_LIBRARIES(testkes SDL2-2.0)

add_executable(testloadso ${MAIN_SOURCE} ${LOADSO_SOURCE})
TARGET_LINK_LIBRARIES(testloadso SDL2-2.0)

add_executable(testlock ${MAIN_SOURCE} ${LOCK_SOURCE})
TARGET_LINK_LIBRARIES(testlock SDL2-2.0)

add_executable(testmessage ${MAIN_SOURCE} ${MESSAGE_SOURCE})
TARGET_LINK_LIBRARIES(testmessage SDL2-2.0)

add_executable(testmultiaudio ${MAIN_SOURCE} ${MULTIAUDIO_SOURCE})
TARGET_LINK_LIBRARIES(testmultiaudio SDL2-2.0)

add_executable(testoverlay2 ${MAIN_SOURCE} ${OVERLAY2_SOURCE})
TARGET_LINK_LIBRARIES(testoverlay2 SDL2-2.0)

add_executable(testplatform ${MAIN_SOURCE} ${PLATFORM_SOURCE})
TARGET_LINK_LIBRARIES(testplatform SDL2-2.0)

add_executable(testrelative ${MAIN_SOURCE} ${RELATIVE_SOURCE})
TARGET_LINK_LIBRARIES(testrelative SDL2-2.0)

add_executable(testrendercopyex ${MAIN_SOURCE} ${RENDERCOPYEX_SOURCE})
TARGET_LINK_LIBRARIES(testrendercopyex SDL2-2.0)

add_executable(testrendertarget ${MAIN_SOURCE} ${RENDERTARGET_SOURCE})
TARGET_LINK_LIBRARIES(testrendertarget SDL2-2.0)

add_executable(testresample ${MAIN_SOURCE} ${RESAMPLE_SOURCE})
TARGET_LINK_LIBRARIES(testresample SDL2-2.0)

add_executable(testscale ${MAIN_SOURCE} ${SCALE_SOURCE})
TARGET_LINK_LIBRARIES(testscale SDL2-2.0)

add_executable(testsem ${MAIN_SOURCE} ${SEM_SOURCE})
TARGET_LINK_LIBRARIES(testsem SDL2-2.0)

add_executable(testshader ${MAIN_SOURCE} ${SHADER_SOURCE})
TARGET_LINK_LIBRARIES(testshader SDL2-2.0 GLESv2 EGL)

add_executable(testshape ${MAIN_SOURCE} ${SHAPE_SOURCE})
TARGET_LINK_LIBRARIES(testshape SDL2-2.0)

add_executable(testsprite2 ${MAIN_SOURCE} ${SPRITE2_SOURCE})
TARGET_LINK_LIBRARIES(testsprite2 SDL2-2.0)

add_executable(testspriteminimal ${MAIN_SOURCE} ${SPRITEMINIMAL_SOURCE})
TARGET_LINK_LIBRARIES(testspriteminimal SDL2-2.0)

add_executable(teststreaming ${MAIN_SOURCE} ${STREAMING_SOURCE})
TARGET_LINK_LIBRARIES(teststreaming SDL2-2.0)

add_executable(testthread ${MAIN_SOURCE} ${THREAD_SOURCE})
TARGET_LINK_LIBRARIES(testthread SDL2-2.0)

add_executable(testtimer ${MAIN_SOURCE} ${TIMER_SOURCE})
TARGET_LINK_LIBRARIES(testtimer SDL2-2.0)

add_executable(testver ${MAIN_SOURCE} ${VER_SOURCE})
TARGET_LINK_LIBRARIES(testver SDL2-2.0)

add_executable(testviewport ${MAIN_SOURCE} ${VIEWPORT_SOURCE})
TARGET_LINK_LIBRARIES(testviewport SDL2-2.0)

add_executable(torturethread ${MAIN_SOURCE} ${TORTURETHREAD_SOURCE})
TARGET_LINK_LIBRARIES(torturethread SDL2-2.0)

# Install
INSTALL(TARGETS testmain DESTINATION /opt/usr/apps/org.tizen.sdl2_test/)
INSTALL(TARGETS testautomation DESTINATION /opt/usr/apps/org.tizen.sdl2_test/)
INSTALL(TARGETS loopwave DESTINATION /opt/usr/apps/org.tizen.sdl2_test/)
INSTALL(TARGETS loopwavequeue DESTINATION /opt/usr/apps/org.tizen.sdl2_test/)
INSTALL(TARGETS testautomic DESTINATION /opt/usr/apps/org.tizen.sdl2_test/)
INSTALL(TARGETS testaudiohotplug DESTINATION /opt/usr/apps/org.tizen.sdl2_test/)
INSTALL(TARGETS testaudioinfo DESTINATION /opt/usr/apps/org.tizen.sdl2_test/)
INSTALL(TARGETS testdisplayinfo DESTINATION /opt/usr/apps/org.tizen.sdl2_test/)
INSTALL(TARGETS testdraw2 DESTINATION /opt/usr/apps/org.tizen.sdl2_test/)
INSTALL(TARGETS testdrawchessboard DESTINATION /opt/usr/apps/org.tizen.sdl2_test/)
INSTALL(TARGETS testdorpfile DESTINATION /opt/usr/apps/org.tizen.sdl2_test/)
INSTALL(TARGETS testerror DESTINATION /opt/usr/apps/org.tizen.sdl2_test/)
INSTALL(TARGETS testfile DESTINATION /opt/usr/apps/org.tizen.sdl2_test/)
INSTALL(TARGETS testfilesystem DESTINATION /opt/usr/apps/org.tizen.sdl2_test/)
INSTALL(TARGETS testgles DESTINATION /opt/usr/apps/org.tizen.sdl2_test/)
INSTALL(TARGETS testgles2 DESTINATION /opt/usr/apps/org.tizen.sdl2_test/)
INSTALL(TARGETS testhit DESTINATION /opt/usr/apps/org.tizen.sdl2_test/)
INSTALL(TARGETS testconv DESTINATION /opt/usr/apps/org.tizen.sdl2_test/)
INSTALL(TARGETS testtime DESTINATION /opt/usr/apps/org.tizen.sdl2_test/)
INSTALL(TARGETS testintersection DESTINATION /opt/usr/apps/org.tizen.sdl2_test/)
INSTALL(TARGETS testkes DESTINATION /opt/usr/apps/org.tizen.sdl2_test/)
INSTALL(TARGETS testloadso DESTINATION /opt/usr/apps/org.tizen.sdl2_test/)
INSTALL(TARGETS testlock DESTINATION /opt/usr/apps/org.tizen.sdl2_test/)
INSTALL(TARGETS testmessage DESTINATION /opt/usr/apps/org.tizen.sdl2_test/)
INSTALL(TARGETS testmultiaudio DESTINATION /opt/usr/apps/org.tizen.sdl2_test/)
INSTALL(TARGETS testoverlay2 DESTINATION /opt/usr/apps/org.tizen.sdl2_test/)
INSTALL(TARGETS testplatform DESTINATION /opt/usr/apps/org.tizen.sdl2_test/)
INSTALL(TARGETS testrelative DESTINATION /opt/usr/apps/org.tizen.sdl2_test/)
INSTALL(TARGETS testrendercopyex DESTINATION /opt/usr/apps/org.tizen.sdl2_test/)
INSTALL(TARGETS testrendertarget DESTINATION /opt/usr/apps/org.tizen.sdl2_test/)
INSTALL(TARGETS testresample DESTINATION /opt/usr/apps/org.tizen.sdl2_test/)
INSTALL(TARGETS testscale DESTINATION /opt/usr/apps/org.tizen.sdl2_test/)
INSTALL(TARGETS testsem DESTINATION /opt/usr/apps/org.tizen.sdl2_test/)
INSTALL(TARGETS testshader DESTINATION /opt/usr/apps/org.tizen.sdl2_test/)
INSTALL(TARGETS testshape DESTINATION /opt/usr/apps/org.tizen.sdl2_test/)
INSTALL(TARGETS testsprite2 DESTINATION /opt/usr/apps/org.tizen.sdl2_test/)
INSTALL(TARGETS testspriteminimal DESTINATION /opt/usr/apps/org.tizen.sdl2_test/)
INSTALL(TARGETS teststreaming DESTINATION /opt/usr/apps/org.tizen.sdl2_test/)
INSTALL(TARGETS testthread DESTINATION /opt/usr/apps/org.tizen.sdl2_test/)
INSTALL(TARGETS testtimer DESTINATION /opt/usr/apps/org.tizen.sdl2_test/)
INSTALL(TARGETS testver DESTINATION /opt/usr/apps/org.tizen.sdl2_test/)
INSTALL(TARGETS testviewport DESTINATION /opt/usr/apps/org.tizen.sdl2_test/)
INSTALL(TARGETS torturethread DESTINATION /opt/usr/apps/org.tizen.sdl2_test/)

INSTALL(DIRECTORY ${CMAKE_SOURCE_DIR}/res DESTINATION /opt/usr/apps/org.tizen.sdl2_test/)