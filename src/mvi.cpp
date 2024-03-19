#include "include/inst.h"
#include "include/mv.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        Err("Missing File", __LINE__, __FILE_NAME__).fatal();
    }

    Inst::init_inst_map();

    Mv mv = Mv();

    mv.program_from_file(argv[1]);

    mv.debug = (std::string(argv[argc-1]) == "debug");

    Result r = mv.run();

    if (r.is_err()) {
        r.get_err().fatal();
    }
}
