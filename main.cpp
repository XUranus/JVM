#include "src/BootstrapSession.h"

int main(int argc, char* argv[]) {
    BootstrapSession session(console::Command(argc, argv));
    session.run();
    return 0;
}
