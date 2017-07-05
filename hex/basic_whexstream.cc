/*
    basic_whexstream.cc

    Implementation for the whexstream class.
*/
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "basic_whexstream.hpp"
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
void basic_whexstream::AddCharacter(int character) {
    data_cleared = false;
    if (append0x) {
        if (writehexseparater) {
            base_whexstream << L"0x" << std::uppercase << std::setfill(L'0') <<
                std::setw(2) << std::hex << static_cast<unsigned short>(character) << L", ";
        } else {
            base_whexstream << L"0x" << std::uppercase << std::setfill(L'0') <<
                std::setw(2) << std::hex << static_cast<unsigned short>(character);
        }
    } else {
        if (writehexseparater) {
            base_whexstream << std::uppercase << std::setfill(L'0') <<
                std::setw(2) << std::hex << static_cast<unsigned short>(character) << L", ";
        } else {
            base_whexstream << std::uppercase << std::setfill(L'0') <<
                std::setw(2) << std::hex << static_cast<unsigned short>(character);
        }
    }
}

void basic_whexstream::setoptions(bool append_0x, bool writehexseparator, int maxarray,
                int filesize, bool usetabs, unsigned char* memblock) {
    append0x = append_0x;
    writehexseparater = writehexseparator;
    max_array = maxarray;
    file_size = filesize;
    use_tabs = usetabs;
    mem_block = memblock;
}

int basic_whexstream::get_currentarray() {
    return current_array;
}

int basic_whexstream::get_maxarray() {
    return max_array;
}

void basic_whexstream::set_currentarray(int currentarray) {
    current_array = currentarray;
}

bool basic_whexstream::get_tabs() {
    return use_tabs;
}

int basic_whexstream::get_filesize() {
    return file_size;
}

unsigned char* basic_whexstream::get_memblock() {
    return mem_block;
}

const std::wstring basic_whexstream::str() {
    return base_whexstream.str();
}

const std::wstring basic_whexstream::str(std::wstring info) {
    base_whexstream.str(info);
    return base_whexstream.str();
}

void basic_whexstream::clear() {
    data_cleared = true;
    base_whexstream.clear();
    base_whexstream.str(L"");
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

basic_whexstream& operator<<(basic_whexstream& Hexstream, std::wifstream& fileStream) {
    std::wstring data;
    bool use_tabs = Hexstream.get_tabs();
    for (unsigned int l = 0; l < static_cast<unsigned int>(Hexstream.get_filesize()); l++) {
        if (Hexstream.get_currentarray() == 0) {
            if (use_tabs) {
                data += L'\t';
            } else {
                data += L"    ";
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
                data = data.replace(data.length() - 1, 1, L"\n\t");
            } else {
                data = data.replace(data.length() -1, 1, L"\n    ");
            }
        }
    }
    Hexstream.str(data);
    return Hexstream;
}

basic_whexstream& operator<<(basic_whexstream& Hexstream, std::wfstream& fileStream) {
    std::wstring data;
    bool use_tabs = Hexstream.get_tabs();
    for (unsigned int l = 0; l < static_cast<unsigned int>(Hexstream.get_filesize()); l++) {
        if (Hexstream.get_currentarray() == 0) {
            if (use_tabs) {
                data += L'\t';
            } else {
                data += L"    ";
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
                data = data.replace(data.length() - 1, 1, L"\n\t");
            } else {
                data = data.replace(data.length() -1, 1, L"\n    ");
            }
        }
    }
    Hexstream.str(data);
    return Hexstream;
}

basic_whexstream& operator<<(basic_whexstream& Hexstream, int character) {
    Hexstream.AddCharacter(character);
    return Hexstream;
}

std::wstring& operator>>(basic_whexstream& Hexstream, std::wstring& String) {
    String += Hexstream.str();
    // Should I clear this stream? hmm
    Hexstream.clear();
    return String;
}

basic_whexstream::basic_whexstream(bool append_0x, bool writehexseparator,
                int maxarray,
                int filesize, bool usetabs,
                unsigned char* memblock) {
    setoptions(append_0x, writehexseparator, maxarray, filesize, usetabs, memblock);
    current_array = 0;
}

basic_whexstream::basic_whexstream() {}

basic_whexstream::~basic_whexstream() {
    // clears the data just in case.
    // This makes clearing this manually optional.
    if(!data_cleared) {
        clear();
    }
}
}
}
