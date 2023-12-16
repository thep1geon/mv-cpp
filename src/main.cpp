#include "include/mv.h"
#include <string>

int main(int argc, char** argv) {
    Inst::init_inst_map();

    Mv mv = Mv();

    if (argc > 1) {
        mv.program_from_file(argv[1]);

        if (argc > 2 && std::string(argv[2]) == "debug=true") {
            mv.m_debug = true;
        }
    }

    Result r = mv.run();

    if (r.is_err()) {
        r.get_err().fatal();
    }
}
