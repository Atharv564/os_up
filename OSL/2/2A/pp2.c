#include <stdlib.h>

int main() {
    int return_value;

    // Execute the "ls" command
    return_value = system("ls");
    
    // Return the exit status of the system command
    return return_value;
}

