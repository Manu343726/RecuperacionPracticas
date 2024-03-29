/*******************************************************************************
* cpp_lib32 project. C++ port of the dx_lib32 project.                         *
*                                                                              *
* Copyright (C) 2012 - 2013, Manuel Sánchez Pérez                              *                     
*                                                                              *
* This file is part of cpp_lib32 project.                                      *
*                                                                              *
* cpp_lib32 project is free software: you can redistribute it and/or modify    *
* it under the terms of the GNU Lesser General Public License as published by  *
* the Free Software Foundation, version 2 of the License.                      *
*                                                                              *
* cpp_lib32 is distributed in the hope that it will be useful,                 *
* but WITHOUT ANY WARRANTY; without even the implied warranty of               * 
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                *
* GNU Lesser General Public License for more details.                          *
*                                                                              *
 You should have received a copy of the GNU Lesser General Public License      *
 along with cpp_lib32 project. If not, see <http://www.gnu.org/licenses/>.     *
*******************************************************************************/

#ifndef DL32CONFIG_H
#define DL32CONGIG_H

#pragma once

#include <string>
#include <sstream>
using namespace std;

#define TOCSTRING(x) #x
#define CONCAT(x,y) x ## y

#ifdef _WIN32
#define DL32COMPILETIME_OS_WINDOWS
#else
#define DL32COMPILETIME_OS_LINUX
#endif //Nota: En teoría solo será compilada en windows o en linux (Por ahora solo en windows).

#ifdef DL32COMPILETIME_OS_WINDOWS
#define PATHSEPARATOR_CHAR    '\\'
#define PATHSEPARATOR_CSTRING "\\"
const string PATHSEPARATOR_STRING = (string)PATHSEPARATOR_CSTRING; 
#else
#define PATHSEPARATOR_CHAR    '/'
#define PATHSEPARATOR_CSTRING "/"
const string PATHSEPARATOR_STRING = (string)PATHSEPARATOR_CSTRING;
#endif

#define FILENAME ( strrchr( __FILE__ , PATHSEPARATOR_CHAR ) ? strrchr( __FILE__ , PATHSEPARATOR_CHAR ) + 1 : __FILE__ )

#define DL32PATHS_ROOT          "code" PATHSEPARATOR_CSTRING
#define DL32PATHS_HEADERS       DL32PATHS_ROOT "headers"  PATHSEPARATOR_CSTRING
#define DL32PATHS_UTILS_HEADERS DL32PATHS_HEADERS "utils" PATHSEPARATOR_CSTRING
#define DL32PATHS_SOURCE        DL32PATHS_ROOT "source"   PATHSEPARATOR_CSTRING
#define DL32PATHS_UTILS_SOURCE  DL32PATHS_SOURCE "utils"  PATHSEPARATOR_CSTRING
#define DL32PATHS_TESTS         DL32PATHS_ROOT "tests"    PATHSEPARATOR_CSTRING

/// @brief	unsigned int "shortcut"
typedef unsigned int uint;

// Win32API unicode settings:
#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif

#if defined( __GNUC__ )
///< Global to_string function (std::to_string not supported by GCC 4.7)
template<typename T>
std::string to_string(const T& value)
{
	stringstream stream;
	stream << value;
	return stream.str();
}
#endif /* GCC */

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief	cpp_lib32 global configuration.
/// 
/// @note	Constants initializations in dl32Config.cpp.
////////////////////////////////////////////////////////////////////////////////////////////////////
class dl32GlobalConfig
{
private: //Non-instanciable class:
	dl32GlobalConfig() {}
	dl32GlobalConfig(const dl32GlobalConfig&) {}
	dl32GlobalConfig& operator=(const dl32GlobalConfig&) {}
public:
//Global debugging settings:
//--------------------------
	static const bool debugging; ///< cpp_lib32 is in debug-mode.

//cpp_lib32 debugging console settings:
//-------------------------------------
	static const bool  dl32Console_AutoOpen;       ///< If its closed, opens debug console if this recieves a debug write instruction.
	static const char* dl32Console_AutoOpen_Title; ///< Console title for autoOpen.

//dl32Window debugging settings:
//------------------------------
	static const bool dl32Window_PromptUnhandledMessages;  ///< Prints unhandled window messages (Messages that are not part of the dl32Window events set) in debug console.
	static const bool dl32Window_PromptCallbackedMessages; ///< Prints windows messages that are processed by "WindowProcedure()" callback instead of "dl32Window::ProcessMessage()" (Standard messaging loop) in debug console. (DEPRECATED)
	
	
//dl32Timing configuration:
//-------------------------
	static const bool dl32Timing_APITiming_Enabled; ///< Internal timing (Few API functions that have timing instructions) enabled.
	static const bool dl32Timing_PromptPush;        ///< Prints dl32Timing::push() calls in debug console.
	static const bool dl32Timing_Prompt_Pop;        ///< Prints dl32Timing::pop() calls in debug console.

//dl32Math configuration:
//-----------------------
	static const float float_epsilon;               ///< cpp_lib32 floating-point comparations epsilon.

//dl32Graphics configuration:
//---------------------------
	static const bool dl32Graphics_defaults_windowed;			 ///< Default value for Windowed param of dl32Graphics ctors.
	static const bool dl32Graphics_defaults_tripleBuffer;		 ///< Default value for tripleBuffer param of dl32Graphics ctors.
	static const bool dl32Graphics_defaults_vSync;				 ///< Default value for vSync param of dl32Graphics ctors.
	static const unsigned int dl32Graphics_defaults_refreshRate; ///< Default value for refreshRate param of dl32Graphics ctors.

	static const bool dl32Graphics_Performance_DrawCallsMerging; ///< Graphics engine tries to merge consecutives draw calls in unique GPU draw call.

	static const float dl32Graphics_d3dVertex_Z;   ///< Default z value of _d3dVertex instances
	static const float dl32Graphics_d3dVertex_RHW; ///< RHW value of _d3dVertex instances
};

//LOGIC OPERATORS (FOR EASY BY PREPROCESSOR CONFIG):
////////////////////////////////////////////////////
#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

#define ANDOP(a,b) ((a == TRUE && b == TRUE) ? TRUE : FALSE) 
#define OROP(a,b)  ((a == TRUE || b == TRUE) ? TRUE : FALSE) 
#define NOTOP(a)   ((a == TRUE) ? FALSE : TRUE)

#ifndef YES
#define YES TRUE
#define NO FALSE
#endif
#ifndef ENABLED
#define ENABLED TRUE
#define DISABLED FALSE
#endif

//FLOATING-POINT COMPARING OPS: (DEPRECATED, use dl32FloatingPointHelper defined in dl32NewMath instead. https://github.com/Manu343726/cpp_lib32/blob/BigRefactoring/code/headers/dl32NewMath.h)
//////////////////////////////////////
#define DL32FLOAT_EPSILON dl32GlobalConfig::float_epsilon

#define DL32FLOAT_EQ(x,y) (((y - DL32FLOAT_EPSILON) < x) && ((y + DL32FLOAT_EPSILON) > x))
#define DL32FLOAT_NE(x,y) !DL32FLOAT_EQ(x,y)
#define DL32FLOAT_EQCERO(x) ((x < DL32FLOAT_EPSILON) && (x > -DL32FLOAT_EPSILON))
#define DL32FLOAT_NECERO(x) !DL32FLOAT_EQCERO(x)

#define DL32FLOAT_GE(x,y) (DL32FLOAT_EQ(x,y) || (x > y))
#define DL32FLOAT_LE(x,y) (DL32FLOAT_EQ(x,y) || (x < y))

//WARNINGS:
////////////////////////////
#if defined( _MSVC_VER )
#pragma warning(disable : 4290) //Visual Studio no implementa la especificación de excepciones. A cambio te lanza el 4290...
#endif /* MSVC */
#endif