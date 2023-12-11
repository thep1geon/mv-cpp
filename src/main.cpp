#include "include/mv.h"

int main(int argc, char** argv) {
    Inst::init_inst_map();

    Mv mv = Mv();

    if (argc > 1) {
        mv.program_from_file(argv[1]);
    }

    Result r = mv.run();

    if (r.is_err()) {
        r.get_err().fatal();
    }
}
