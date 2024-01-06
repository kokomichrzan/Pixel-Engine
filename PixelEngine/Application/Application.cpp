#include "Application.h"

//// Entry Point //////////////////////////

#ifdef _DEBUG
int main() {
    PE::Application App = PE::Application();
    return 0;
}
#else
int WinMain() {
    PE::Application App = PE::Application();
    return 0;
}
#endif