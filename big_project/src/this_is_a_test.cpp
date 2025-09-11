// Minimal GUI launcher
#include "GUI.h"

int main() {
    GUI app;
    if (!app.init()) return 1;
    app.run();
    return 0;
}
