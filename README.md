# mcui - MAIPA's Console User Interface

## About

**mcui** (MAIPA's Console User Interface) is a C++ library designed to simplify the creation of console-based menus and input fields. It provides a structured way to build interactive terminal interfaces with minimal effort.

## Features

- **Menu System**: Easily create hierarchical console menus with selectable options.
- **User Input Handling**: Prompt users for input with a message.
- **Custom Views**: Define your own menu display style.
- **Header-Only**: Simple integration without the need for compilation.
- **Cross-Platform**: Works on **Windows, macOS, and Linux**.
- **C++20 Compatible**: Utilizes modern C++ features.

## Requirements

- **C++ Standard**: Requires **C++20** or later.
- **Dependencies**: Uses [**mstd**](https://github.com/MAIPA01/mstd) (Maipa’s Standard Library).

## Installation

No additional setup is required apart from including **mcui** headers and ensuring [**mstd**](https://github.com/MAIPA01/mstd) is available.

## Usage Examples

### Creating a Simple Menu

```cpp
#include <mcui/mcui.hpp>
#include <iostream>

using namespace std;
using namespace mcui;

void menu2OptionFunc() {
    cout << "Menu 2 Option" << endl;
}

MenuExitState menuOptionFunc() {
    return MenuExitState::Exit;
}

int main() {
    MenuBuilder::makeStandardMenu("Menu", true, false, true,
        MenuBuilder::makeStandardMenu("Menu2", true, true, false,
            MenuBuilder::makeOption("Menu2 Option 1", &menu2OptionFunc)
        ),
        MenuBuilder::makeOption("Exit", &menuOptionFunc)
    )->run();
}
```

### Creating a Simple Input Field

```cpp
#include <mcui/mcui.hpp>
#include <iostream>

using namespace std;
using namespace mcui;

int main() {
    std::string name = InputBuilder::makeInput("Name: "s)->run();
    cout << "Hello " << name << endl;
}
```

### Customizing Menu Appearance

You can define your own menu rendering style by implementing a custom **View** structure:

```cpp
struct ViewSample {
    static void printView(const std::string& menu_name,
        const mstd::ordered_map<std::string, MenuElementSPtr>& elements);
};
```

## License

This project is licensed under the **BSD 3-Clause License with Attribution Requirement**. See the [`LICENSE`](./LICENSE) file for more details.