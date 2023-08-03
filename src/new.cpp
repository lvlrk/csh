#include <iostream>
#include <vector>
#include <string>

class Shell {
public:
    class Cmd {
    public:
        Cmd();
    };

    int Run();

    // command-line options
    bool noCompile = false;
private:
    bool run = true;

    std::string rawline;
    std::string prompt = "csh>";
};

Shell::Cmd::Cmd() {}

int Shell::Run() {
    while(run) {
        std::cout << prompt;

        if(!std::getline(std::cin, rawline)) run = false;

        std::cout << '\n';
    }

    return 0;
}

int main(int argc, char **argv) {
    Shell sh;

    std::vector<std::string> args;
    for(int i = 1; i < argc; i++) args.push_back(argv[i]);

    if(args.size() > 0) {
        for(const std::string arg: args) {
            if(arg == "--help") {
                std::cout << "Usage: csh [-n]\n\n";
                std::cout << "      --help         print this help and exit\n";
                std::cout << "      --version      output version information and exit\n";
                std::cout << "  -n, --no-compile   don't compile code on exit\n";

                return 0;
            }
            if(arg == "--version") {
                std::cout << "csh-0.1\n";

                return 0;
            }
            if(arg == "-n" || arg == "--no-compile") {
                sh.noCompile = true;
            }
        }
    }

    return sh.Run();
}
