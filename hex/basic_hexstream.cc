/*
    basic_hexstream.cc

    Implementation for the hexstream class.
*/
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "basic_hexstream.hpp"

namespace AraHaan {
namespace experimental {
void __fastcall basic_hexstream::AddCharacter(int character) {
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

void __fastcall basic_hexstream::setoptions(bool append_0x, bool writehexseparator, int maxarray,
                int filesize, bool usetabs, unsigned char* memblock) {
    append0x = append_0x;
    writehexseparater = writehexseparator;
    max_array = maxarray;
    file_size = filesize;
    use_tabs = usetabs;
    mem_block = memblock;
}

int __fastcall basic_hexstream::get_currentarray() {
    return current_array;
}

int __fastcall basic_hexstream::get_maxarray() {
    return max_array;
}

void __fastcall basic_hexstream::set_currentarray(int currentarray) {
    current_array = currentarray;
}

bool __fastcall basic_hexstream::get_tabs() {
    return use_tabs;
}

int __fastcall basic_hexstream::get_filesize() {
    return file_size;
}

unsigned char* __fastcall basic_hexstream::get_memblock() {
    return mem_block;
}

const std::string __fastcall basic_hexstream::str() {
    return base_hexstream.str();
}

const std::string __fastcall basic_hexstream::str(std::string info) {
    base_hexstream.str(info);
    return base_hexstream.str();
}

void __fastcall basic_hexstream::clear() {
    data_cleared = true;
    base_hexstream.clear();
    base_hexstream.str("");
}

basic_hexstream& __fastcall operator<<(basic_hexstream& Hexstream, std::ifstream& fileStream) {
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

basic_hexstream& __fastcall operator<<(basic_hexstream& Hexstream, std::fstream& fileStream) {
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

basic_hexstream& __fastcall operator<<(basic_hexstream& Hexstream, int character) {
    Hexstream.AddCharacter(character);
    return Hexstream;
}

std::string& __fastcall operator>>(basic_hexstream& Hexstream, std::string& String) {
    String += Hexstream.str();
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
    if(!data_cleared) {
        clear();
    }
}
}
}
