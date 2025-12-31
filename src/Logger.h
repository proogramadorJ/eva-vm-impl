 #ifndef Logger_h
 #define Logger_h

 #include <sstream>

 class ErrorLogMessage : public std::basic_ostringstream <char>{
    public:
        ~ErrorLogMessage(){
            fprintf(stderr, "Fatal error: %s\n", str().c_str());
            exit(EXIT_FAILURE);
        }
 };

 #define DIE ErrorLogMessage()
 #define log(value) std::cout << #value << " = " << (value) << "\n";
 #define log_hex(value) std::cout << #value << " = 0x" << std::hex << (int)(value) << std::dec << "\n";

 #endif