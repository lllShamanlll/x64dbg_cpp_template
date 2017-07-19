#ifndef _PLUGIN_MAIN_H_
#define _PLUGIN_MAIN_H_

#include "pluginsdk/bridgemain.h"
#include "pluginsdk/_plugins.h"

#include "pluginsdk/_scriptapi_argument.h"
#include "pluginsdk/_scriptapi_assembler.h"
#include "pluginsdk/_scriptapi_bookmark.h"
#include "pluginsdk/_scriptapi_comment.h"
#include "pluginsdk/_scriptapi_debug.h"
#include "pluginsdk/_scriptapi_flag.h"
#include "pluginsdk/_scriptapi_function.h"
#include "pluginsdk/_scriptapi_gui.h"
#include "pluginsdk/_scriptapi_label.h"
#include "pluginsdk/_scriptapi_memory.h"
#include "pluginsdk/_scriptapi_misc.h"
#include "pluginsdk/_scriptapi_module.h"
#include "pluginsdk/_scriptapi_pattern.h"
#include "pluginsdk/_scriptapi_register.h"
#include "pluginsdk/_scriptapi_stack.h"
#include "pluginsdk/_scriptapi_symbol.h"

#include "pluginsdk/capstone/capstone.h"
#include "pluginsdk/DeviceNameResolver/DeviceNameResolver.h"
#include "pluginsdk/jansson/jansson.h"
#include "pluginsdk/lz4/lz4file.h"
#include "pluginsdk/TitanEngine/TitanEngine.h"
#include "pluginsdk/XEDParse/XEDParse.h"
#include "pluginsdk/yara/yara.h"

#ifdef _WIN64
#pragma comment(lib, "pluginsdk/x64dbg.lib")
#pragma comment(lib, "pluginsdk/x64bridge.lib")
#pragma comment(lib, "pluginsdk/capstone/capstone_x64.lib")
#pragma comment(lib, "pluginsdk/DeviceNameResolver/DeviceNameResolver_x64.lib")
#pragma comment(lib, "pluginsdk/jansson/jansson_x64.lib")
#pragma comment(lib, "pluginsdk/lz4/lz4_x64.lib")
#pragma comment(lib, "pluginsdk/TitanEngine/TitanEngine_x64.lib")
#pragma comment(lib, "pluginsdk/XEDParse/XEDParse_x64.lib")
#pragma comment(lib, "pluginsdk/yara/yara_x64.lib")
#else // _WIN64
#pragma comment(lib, "pluginsdk/x32dbg.lib")
#pragma comment(lib, "pluginsdk/x32bridge.lib")
#pragma comment(lib, "pluginsdk/capstone/capstone_x86.lib")
#pragma comment(lib, "pluginsdk/DeviceNameResolver/DeviceNameResolver_x86.lib")
#pragma comment(lib, "pluginsdk/jansson/jansson_x86.lib")
#pragma comment(lib, "pluginsdk/lz4/lz4_x86.lib")
#pragma comment(lib, "pluginsdk/TitanEngine/TitanEngine_x86.lib")
#pragma comment(lib, "pluginsdk/XEDParse/XEDParse_x86.lib")
#pragma comment(lib, "pluginsdk/yara/yara_x86.lib")
#endif //_WIN64

#include <string>

#define Cmd(x) DbgCmdExecDirect(x)
#define Eval(x) DbgValFromString(x)
#define PLUG_EXPORT extern "C" __declspec(dllexport)

#define PLUGIN_MESSAGE(...) _plugin_logprintf("[" PLUGIN_NAME "] " __VA_ARGS__)

#define PLUGIN_COMMAND(Name)                              \
  static bool Name(int argc, char *argv[]);               \
  namespace plugin_utils_tmp##Name {                      \
      bool tmp = add_command(std::string(#Name), (Name)); \
  }                                                       \
  static bool Name(int argc, char *argv[])

#define PLUGIN_EXPRESSION_FUNCTION(Name, Argc, Userdata)                     \
  static duint Name(int argc, duint *argv, void *userdata);                  \
  namespace plugin_utils_tmp##Name {                                         \
      bool tmp = add_expression_function(std::string(#Name), (Name), (Argc), \
                                         (Userdata));                        \
  }                                                                          \
  static duint Name(int argc, duint *argv, void *userdata)

bool add_command(const std::string &command_name, CBPLUGINCOMMAND command);
bool add_expression_function(const std::string &function_name,
                             CBPLUGINEXPRFUNCTION function,
                             int arc,
                             void* userdata);

#endif // _PLUGIN_MAIN_H_
