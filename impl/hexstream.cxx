/*
    hexstream.cxx

    Implementation for the hexstream
    & whexstream class.
*/
#include <string> /* for std::string and std::wstring. */
#include <cstddef> /* for std::size_t. */
#include <sstream> /* for std::stringstream and std::wstringstream. */
#include <iomanip> /* for std::setfill and std::setw. */
#include <fstream> /* for std::istream and std::wistream. */
#include "../basic_hexstream"
#include "../basic_whexstream"

std::stringstream base_hexstream;
std::wstringstream base_whexstream;
bool data_cleared, append0x, writehexseparater, use_tabs;
int max_array, current_array, file_size;
unsigned char* mem_block;

namespace AraHaan {
void basic_hexstream::AddCharacter(int character) {
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

const std::string basic_hexstream::str() {
    return base_hexstream.str();
}

const std::string basic_hexstream::str(std::string info) {
    base_hexstream.str(info);
    return base_hexstream.str();
}

void basic_hexstream::clear() {
    if (!data_cleared) {
        base_hexstream.clear();
        base_hexstream.str("");
        append0x = false;
        writehexseparater = false;
        use_tabs = false;
        max_array = 0;
        current_array = 0;
        file_size = 0;
        data_cleared = true;
    }
}

basic_hexstream& operator<<(basic_hexstream& Hexstream, std::istream& fileStream) {
    if (data_cleared) {
        data_cleared = false;
    }
    std::string data;
    for (unsigned int l = 0; l < static_cast<unsigned int>(file_size); l++) {
        if (current_array == 0) {
            if (use_tabs) {
                data += '\t';
            } else {
                data += "    ";
            }
        }
        int ch = static_cast<int>(mem_block[l]);
        Hexstream.AddCharacter(ch);
        data += Hexstream.str();
        Hexstream.clear();
        current_array = ++current_array;
        if (current_array % max_array == 0) {
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
    if (data_cleared) {
        data_cleared = false;
    }
    Hexstream.AddCharacter(character);
    return Hexstream;
}

std::string& operator>>(basic_hexstream& Hexstream, std::string& String) {
    String += Hexstream.str();
    Hexstream.clear();
    return String;
}

basic_hexstream& operator "" _hex(basic_hexstream& Hexstream, const char* s, std::size_t n) {
    for (size_t i = 0; i < n; i++) {
        Hexstream.AddCharacter(s[i]);
    }
    return Hexstream;
}

basic_hexstream::basic_hexstream(bool append_0x, bool writehexseparator,
                int maxarray,
                int filesize, bool usetabs,
                unsigned char* memblock) {
    if (data_cleared) {
        data_cleared = false;
    }
    append0x = append_0x;
    writehexseparater = writehexseparator;
    max_array = maxarray;
    file_size = filesize;
    use_tabs = usetabs;
    mem_block = memblock;
    current_array = 0;
}

basic_hexstream::basic_hexstream() {}

basic_hexstream::~basic_hexstream() {
    if(!data_cleared) {
        clear();
    }
}

void basic_whexstream::AddCharacter(int character) {
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

const std::wstring basic_whexstream::str() {
    return base_whexstream.str();
}

const std::wstring basic_whexstream::str(std::wstring info) {
    base_whexstream.str(info);
    return base_whexstream.str();
}

void basic_whexstream::clear() {
    if (!data_cleared){
        base_whexstream.clear();
        base_whexstream.str(L"");
        append0x = false;
        writehexseparater = false;
        use_tabs = false;
        max_array = 0;
        current_array = 0;
        file_size = 0;
        data_cleared = true;
    }
}

basic_whexstream& operator<<(basic_whexstream& Hexstream, std::wistream& fileStream) {
    if (data_cleared) {
        data_cleared = false;
    }
    std::wstring data;
    for (unsigned int l = 0; l < static_cast<unsigned int>(file_size); l++) {
        if (current_array == 0) {
            if (use_tabs) {
                data += L'\t';
            } else {
                data += L"    ";
            }
        }
        int ch = static_cast<int>(mem_block[l]);
        Hexstream.AddCharacter(ch);
        data += Hexstream.str();
        Hexstream.clear();
        current_array = ++current_array;
        if (current_array % max_array == 0) {
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
    if (data_cleared) {
        data_cleared = false;
    }
    Hexstream.AddCharacter(character);
    return Hexstream;
}

std::wstring& operator>>(basic_whexstream& Hexstream, std::wstring& String) {
    String += Hexstream.str();
    Hexstream.clear();
    return String;
}

basic_whexstream& operator "" _hex(basic_whexstream& Hexstream, const char* s, std::size_t n) {
    for (size_t i = 0; i < n; i++) {
        Hexstream.AddCharacter(s[i]);
    }
    return Hexstream;
}

basic_whexstream::basic_whexstream(bool append_0x, bool writehexseparator,
                int maxarray,
                int filesize, bool usetabs,
                unsigned char* memblock) {
    if (data_cleared) {
        data_cleared = false;
    }
    append0x = append_0x;
    writehexseparater = writehexseparator;
    max_array = maxarray;
    file_size = filesize;
    use_tabs = usetabs;
    mem_block = memblock;
    current_array = 0;
}

basic_whexstream::basic_whexstream() {}

basic_whexstream::~basic_whexstream() {
    if(!data_cleared) {
        clear();
    }
}
}
