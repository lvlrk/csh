// this file is deprecated

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

void finishdata(std::string& data, bool& can_write) {
    if(data.find("return ") == std::string::npos) data += "\n\treturn 0;\n}\n";

    can_write = false;
}

int main(int argc, char **argv) {
    bool no_compile = false;

    std::vector<std::string> args;
    for(int i = 1; i < argc; i++) args.push_back(argv[i]);

    if(args.size() > 0) {
        for(const std::string& arg: args) {
            if(arg == "--help") {
                std::cout << "Usage: csh [-n]\n"
                    "  -n, --no-compile   dont compile on exit\n";

                return 0;
            }
            if(arg == "-n" || arg == "--no-compile") {
                no_compile = true;
            }
        }
    }

    std::string srcfile = "csh.cpp";
    std::string exfile = "csho";
    std::ofstream outf("/tmp/" + srcfile);
    std::string line;
    std::string tmpline;
    std::string compile = "g++ /tmp/" + srcfile + " -o /tmp/" + exfile;
    std::string data = "\nint main() {\n";
    bool can_write = true;

    bool run = true;

    int include_p = 0;

    while(run) {
        std::cout << "csh>";

        if(!std::getline(std::cin, tmpline)) run = false;

        if(tmpline == "show") {
            std::cout << data;
        } else if(tmpline == "done") {
            finishdata(data, can_write);
        } else if(tmpline == "run") {
            goto end;
        } else if(tmpline[0] == '#') {
            if(can_write) {
                data.insert(include_p, tmpline + '\n');
                include_p += tmpline.size() + 1;
            } else {
                std::cerr << "\nerror: cannot write\n";
            }
        } else {
            if(can_write) {
                line = '\t';
                line += tmpline;
                line += '\n';

                data += line;
            } else {
                std::cerr << "\nerror: cannot write\n";
            }
        }
    }

end:
    std::cout << '\n';

    finishdata(data, can_write);

    outf.write(data.c_str(), data.size());
    outf.close();

    if(!no_compile) {
        system(compile.c_str());
        system(("/tmp/" + exfile).c_str());
    } else {
        std::cout << data;
    }

    return 0;
}
