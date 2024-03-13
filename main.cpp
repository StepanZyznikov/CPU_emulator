#include "CPU.h"

//default file_path: R"(C:\Users\stepa\Documents\From_OneDrive\STUDY\HSE\AIAYA\Cpp\CPU_emulator\prog.txt)"

//int main(int argc, char *argv[]) {
//    if (argc >= 1)
//        cpu::execute_file(argv[0]);
//    return 0;
//}

int main(){
    cpu::execute_file(R"(C:\Users\stepa\Documents\From_OneDrive\STUDY\HSE\AIAYA\Cpp\CPU_emulator\prog.txt)");
    return 0;
}