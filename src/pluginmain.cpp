#include "pluginmain.h"
#include "plugin.h"
#include <map>
#include <string>

int g_pluginHandle;

struct FunctionData {
    CBPLUGINEXPRFUNCTION function;
    int argc;
    void* userdata;
};

using Commands = std::map<std::string, CBPLUGINCOMMAND>;
using ExpressionFunctions = std::map<std::string, FunctionData>;

static Commands& get_commands() {
    static Commands commands;
    return commands;
}

static ExpressionFunctions& get_expression_functions() {
  static ExpressionFunctions functions;
  return functions;
}

PLUG_EXPORT bool pluginit(PLUG_INITSTRUCT *initStruct) {
    initStruct->pluginVersion = PLUGIN_VERSION;
    initStruct->sdkVersion = PLUG_SDKVERSION;
    strncpy_s(initStruct->pluginName, PLUGIN_NAME, _TRUNCATE);
    g_pluginHandle = initStruct->pluginHandle;
    for (auto& kv : get_commands()) {
        const auto& name = kv.first;
        const auto& command = kv.second;
        if (!_plugin_registercommand(g_pluginHandle, name.c_str(), command,
                                     false)) {
            PLUGIN_MESSAGE("Error register the \"%s\" command!\n",
                           name.c_str());
        }
    }
    for (auto& kv : get_expression_functions()) {
      const auto& name = kv.first;
      const auto& function_data = kv.second;
      if (!_plugin_registerexprfunction(g_pluginHandle, name.c_str(),
                                        function_data.argc,
                                        function_data.function,
                                        function_data.userdata)) {
          PLUGIN_MESSAGE("Error register the \"%s\" expresdsion function!\n",
                         name.c_str());
      }
    }
    return initializeResources();
}

PLUG_EXPORT bool plugstop() {
    for (auto& kv : get_commands()) {
        const auto& name = kv.first;
        _plugin_unregistercommand(g_pluginHandle, name.c_str());
    }
    for (auto& kv : get_expression_functions()) {
        const auto& name = kv.first;
        _plugin_unregisterexprfunction(g_pluginHandle, name.c_str());
    }
    return uninitializeResources();
}

BOOL WINAPI DllMain(_In_ HINSTANCE hinstDLL,
                    _In_ DWORD     fdwReason,
                    _In_ LPVOID    lpvReserved) {
    return TRUE;
}

bool add_command(const std::string &command_name, CBPLUGINCOMMAND command) {
    auto& commands = get_commands();
    if (commands.find(command_name) != commands.end()) {
        PLUGIN_MESSAGE("Warning: duplicated command '%s'.",
                       command_name.c_str());
    }

    commands[command_name] = command;
    return true;
}

bool add_expression_function(const std::string &function_name,
                             CBPLUGINEXPRFUNCTION function,
                             int argc, void* userdata) {
    auto& functions = get_expression_functions();
    if (functions.find(function_name) !=
        functions.end()) {
        PLUGIN_MESSAGE("Warning: duplicated expression function '%s'.",
                       function_name.c_str());
    }

    functions[function_name] = FunctionData{function, argc, userdata};
    return true;
}
