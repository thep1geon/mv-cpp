#include "include/mv.h"
#include <string>

int main(int argc, char** argv) {
    if (argc < 2) {
        Err("Missing File", __LINE__, __FILE_NAME__).fatal();
    }

    Inst::init_inst_map();

    Mv mv = Mv();

    mv.program_from_file(argv[1]);

    if (argc > 2 && std::string(argv[2]) == "debug") {
        mv.debug = true;
    }

    Result r = mv.run();

    if (r.is_err()) {
        r.get_err().fatal();
    }
}
