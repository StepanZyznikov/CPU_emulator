#include "CPU.h"

//default file_path: R"(C:\Users\stepa\Documents\From_OneDrive\STUDY\HSE\AIAYA\Cpp\CPU_emulator\prog.txt)"

//int main(int argc, char *argv[]) {
//    cpu::cpu a;
//    if (argc >= 1)
//        a.execute_file(argv[0]);
//    return 0;
//}

int main(){
    //cpu::file_to_bite_code(R"(C:\Users\stepa\Documents\From_OneDrive\STUDY\HSE\AIAYA\Cpp\CPU_emulator\prog.txt)", R"(C:\Users\stepa\Documents\From_OneDrive\STUDY\HSE\AIAYA\Cpp\CPU_emulator\bite_code.txt)");
    cpu::cpu a;
    a.execute_bite_code_file(R"(C:\Users\stepa\Documents\From_OneDrive\STUDY\HSE\AIAYA\Cpp\CPU_emulator\bite_code.txt)");
    return 0;
}