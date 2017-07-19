# x64dbg_cpp_template
Simple, easy to use template plugin for x64dbg.

## Why?

All you have to do with this template, to start implementing your x64dbg plugin logic: rename folder.

### Prerequisites

CMake have to be installed on your system.
You can download it here: https://cmake.org/download/

### Installation

Clone this repo

```
git clone https://github.com/lllShamanlll/x64dbg_cpp_template.git
```

Rename directory to the name what you want

```
mv x64dbg_cpp_template your_plugin_name
```

Move to build directory

```
cd your_plugin_name/build
```

Run CMake(for instance we'll generate x64 solution for VS2015)

```
cmake -G "Visual Studio 14 2015 Win64" ..
```

### Usage

Just open **your_plugin_name/src/plugin.cpp** & modify template functions body

```
PLUGIN_COMMAND(templateCommand) {
    PLUGIN_MESSAGE("templateCommand runs successfully.\n");
    return true;
}

PLUGIN_EXPRESSION_FUNCTION(templateFunction, 0, nullptr) {
    PLUGIN_MESSAGE("templateFunction runs successfully.\n");
    return true;
}
```

Or add new one

```
PLUGIN_COMMAND(MyFancyCommand) {
    PLUGIN_MESSAGE("MyFancyCommand runs successfully.\n");
    return true;
}
```

You've no need to manage commands by hand, it goes automatically. Just implement your stuff & leave boring stuff to machines.
