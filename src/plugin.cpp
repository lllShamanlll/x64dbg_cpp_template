#include "plugin.h"
#include "pluginmain.h"

PLUGIN_COMMAND(templateCommand) {
    PLUGIN_MESSAGE("templateCommand runs successfully.\n");
    return true;
}

PLUGIN_EXPRESSION_FUNCTION(templateFunction, 0, nullptr) {
    PLUGIN_MESSAGE("templateFunction runs successfully.\n");
    return true;
}


bool initializeResources() {
    return true;
}

bool uninitializeResources() {
    return true;
}

