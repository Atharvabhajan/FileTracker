#include "CommandProcessor.h"
#include <iostream>

int main(int argc, char* argv[]) {
    CommandProcessor processor;
    
    if (argc > 1) {
        // Command-line mode
        processor.processCommand(argc, argv);
    } else {
        // Interactive mode
        processor.startInteractiveMode();
    }

    return 0;
}
