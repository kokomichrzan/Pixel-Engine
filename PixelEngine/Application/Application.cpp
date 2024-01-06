#include "PixelEngine..h"

//// Entry Point //////////////////////////

#ifdef _DEBUG
int main() {
    PixelEngine App = PixelEngine();
    return 0;
}
#else
int WinMain() {
    PixelEngine App = PixelEngine();
    return 0;
}
#endif