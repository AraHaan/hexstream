/*
    basic_whexstream.cc

    Implementation for the whexstream class.
*/
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "basic_whexstream.hpp"

namespace AraHaan {
namespace experimental {
void __fastcall basic_whexstream::AddCharacter(int character) {
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

void __fastcall basic_whexstream::setoptions(bool append_0x, bool writehexseparator, int maxarray,
                int filesize, bool usetabs, unsigned char* memblock) {
    append0x = append_0x;
    writehexseparater = writehexseparator;
    max_array = maxarray;
    file_size = filesize;
    use_tabs = usetabs;
    mem_block = memblock;
}

int __fastcall basic_whexstream::get_currentarray() {
    return current_array;
}

int __fastcall basic_whexstream::get_maxarray() {
    return max_array;
}

void __fastcall basic_whexstream::set_currentarray(int currentarray) {
    current_array = currentarray;
}

bool __fastcall basic_whexstream::get_tabs() {
    return use_tabs;
}

int __fastcall basic_whexstream::get_filesize() {
    return file_size;
}

unsigned char* __fastcall basic_whexstream::get_memblock() {
    return mem_block;
}

const std::wstring __fastcall basic_whexstream::str() {
    return base_whexstream.str();
}

const std::wstring __fastcall basic_whexstream::str(std::wstring info) {
    base_whexstream.str(info);
    return base_whexstream.str();
}

void __fastcall basic_whexstream::clear() {
    data_cleared = true;
    base_whexstream.clear();
    base_whexstream.str(L"");
}

basic_whexstream& __fastcall operator<<(basic_whexstream& Hexstream, std::wifstream& fileStream) {
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

basic_whexstream& __fastcall operator<<(basic_whexstream& Hexstream, std::wfstream& fileStream) {
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

basic_whexstream& __fastcall operator<<(basic_whexstream& Hexstream, int character) {
    Hexstream.AddCharacter(character);
    return Hexstream;
}

std::wstring& __fastcall operator>>(basic_whexstream& Hexstream, std::wstring& String) {
    String += Hexstream.str();
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
    if(!data_cleared) {
        clear();
    }
}
}
}
