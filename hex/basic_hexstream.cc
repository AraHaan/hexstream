/*
    basic_hexstream.cc

    Implementation for the hexstream class.
*/
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "basic_hexstream.hpp"
/*
disable C++ exceptions on Windows as we do not need to
catch any. This also drives down the linked binary size
as well when used in MSVC. Depending on the code it can
drop the binary size by 4 KB's or more. The less the size the
shorter the assembly language and the shorter that is the
faster the code is.

This implementation file should be able to work in Visual C++
as well as with gcc and clang with no patches whatsoever.
*/
#ifdef _WIN32
#ifdef _HAS_EXCEPTIONS
#undef _HAS_EXCEPTIONS
#define _HAS_EXCEPTIONS 0
#endif
#endif

namespace AraHaan {
namespace experimental {
void basic_hexstream::AddCharacter(int character) {
    data_cleared = false;
    if (append0x) {
        if (writehexseparater) {
            base_hexstream << "0x" << std::uppercase << std::setfill('0') <<
                std::setw(2) << std::hex << static_cast<unsigned short>(character) << ", ";
        } else {
            base_hexstream << "0x" << std::uppercase << std::setfill('0') <<
                std::setw(2) << std::hex << static_cast<unsigned short>(character);
        }
    } else {
        if (writehexseparater) {
            base_hexstream << std::uppercase << std::setfill('0') <<
                std::setw(2) << std::hex << static_cast<unsigned short>(character) << ", ";
        } else {
            base_hexstream << std::uppercase << std::setfill('0') <<
                std::setw(2) << std::hex << static_cast<unsigned short>(character);
        }
    }
}

void basic_hexstream::setoptions(bool append_0x, bool writehexseparator, int maxarray,
                int filesize, bool usetabs, unsigned char* memblock) {
    append0x = append_0x;
    writehexseparater = writehexseparator;
    max_array = maxarray;
    file_size = filesize;
    use_tabs = usetabs;
    mem_block = memblock;
}

int basic_hexstream::get_currentarray() {
    return current_array;
}

int basic_hexstream::get_maxarray() {
    return max_array;
}

void basic_hexstream::set_currentarray(int currentarray) {
    current_array = currentarray;
}

bool basic_hexstream::get_tabs() {
    return use_tabs;
}

int basic_hexstream::get_filesize() {
    return file_size;
}

unsigned char* basic_hexstream::get_memblock() {
    return mem_block;
}

const std::string basic_hexstream::str() {
    return base_hexstream.str();
}

const std::string basic_hexstream::str(std::string info) {
    base_hexstream.str(info);
    return base_hexstream.str();
}

void basic_hexstream::clear() {
    data_cleared = true;
    base_hexstream.clear();
    base_hexstream.str("");
}

/*
There is got to be a better and faster way to read the file streams and
convert each character to hex and work super fast for large files
without using a lot of memory.

I do not like forcing the end user to make a buffer just to use in this class.

I want to avoid the buffer (memblock in this case) and remove it if possible.

The operator<< overloads that takes in an std::ifstream or an std::fstream must be
made super fast for large files. Even if it is made to somehow itterate and get
more than 1 character at a time.
*/

basic_hexstream& operator<<(basic_hexstream& Hexstream, std::ifstream& fileStream) {
    std::string data;
    bool use_tabs = Hexstream.get_tabs();
    for (unsigned int l = 0; l < static_cast<unsigned int>(Hexstream.get_filesize()); l++) {
        if (Hexstream.get_currentarray() == 0) {
            if (use_tabs) {
                data += '\t';
            } else {
                data += "    ";
            }
        }
        unsigned char* memblock = Hexstream.get_memblock();
        int ch = static_cast<int>(memblock[l]);
        Hexstream.AddCharacter(ch);
        data += Hexstream.str();
        Hexstream.clear();
        int current_array = Hexstream.get_currentarray();
        Hexstream.set_currentarray(++current_array);
        if (Hexstream.get_currentarray() % Hexstream.get_maxarray() == 0) {
            if (use_tabs) {
                data = data.replace(data.length() - 1, 1, "\n\t");
            } else {
                data = data.replace(data.length() -1, 1, "\n    ");
            }
        }
    }
    Hexstream.str(data);
    return Hexstream;
}

basic_hexstream& operator<<(basic_hexstream& Hexstream, std::fstream& fileStream) {
    std::string data;
    bool use_tabs = Hexstream.get_tabs();
    for (unsigned int l = 0; l < static_cast<unsigned int>(Hexstream.get_filesize()); l++) {
        if (Hexstream.get_currentarray() == 0) {
            if (use_tabs) {
                data += '\t';
            } else {
                data += "    ";
            }
        }
        unsigned char* memblock = Hexstream.get_memblock();
        int ch = static_cast<int>(memblock[l]);
        Hexstream.AddCharacter(ch);
        data += Hexstream.str();
        Hexstream.clear();
        int current_array = Hexstream.get_currentarray();
        Hexstream.set_currentarray(++current_array);
        if (Hexstream.get_currentarray() % Hexstream.get_maxarray() == 0) {
            if (use_tabs) {
                data = data.replace(data.length() - 1, 1, "\n\t");
            } else {
                data = data.replace(data.length() -1, 1, "\n    ");
            }
        }
    }
    Hexstream.str(data);
    return Hexstream;
}

basic_hexstream& operator<<(basic_hexstream& Hexstream, int character) {
    Hexstream.AddCharacter(character);
    return Hexstream;
}

std::string& operator>>(basic_hexstream& Hexstream, std::string& String) {
    String += Hexstream.str();
    // Should I clear this stream? hmm
    Hexstream.clear();
    return String;
}

basic_hexstream::basic_hexstream(bool append_0x, bool writehexseparator,
                int maxarray,
                int filesize, bool usetabs,
                unsigned char* memblock) {
    setoptions(append_0x, writehexseparator, maxarray, filesize, usetabs, memblock);
    current_array = 0;
}

basic_hexstream::basic_hexstream() {}

basic_hexstream::~basic_hexstream() {
    // clears the data just in case.
    // This makes clearing this manually optional.
    if(!data_cleared) {
        clear();
    }
}
}
}
