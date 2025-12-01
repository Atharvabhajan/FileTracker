#include "CommandProcessor.h"
#include <iostream>

int main(int argc, char* argv[]) {
    CommandProcessor processor;
    
    if (argc > 1) {
        // Command-line mode
        std::string command = argv[1];
        processor.processCommand(argc, argv);

        if(command == "start" ){
            std::cout << "Watcher is active. Press Ctrl+C to stop.\n";

            while(true){
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }

        return 0;
    } else {
    
        // Interactive mode
        processor.startInteractiveMode();
    }

    
    return 0;
}
