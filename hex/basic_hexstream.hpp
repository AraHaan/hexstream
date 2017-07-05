/*
    basic_hexstream

    Header for the hexstream class.
*/


namespace AraHaan {
namespace experimental {
    class basic_hexstream {
    private:
        std::stringstream base_hexstream;
        bool data_cleared, append0x, writehexseparater, use_tabs;
        int max_array, current_array, file_size;
        unsigned char* mem_block;
        int __fastcall get_currentarray();
        void __fastcall set_currentarray(int currentarray);
        int __fastcall get_maxarray();
        bool __fastcall get_tabs();
        int __fastcall get_filesize();
        unsigned char* __fastcall get_memblock();
    public:
        /*
            Adds a character to the hexstream.

            Note: This automatically appends an 0x
                to beginning of the character represented
                in hex form if the append0x arg is set to true.
                Also the separater which is a comma and a space between
                each hex is optional but by default is set to true.
                This function and this hexstream object is a must
                have for hex editors. Also the character must be in int form.
        */
        void __fastcall AddCharacter(int character);
        /*
            Sets if the user wants to append "0x" and write an ", "
            on every character added to the hexstream.
        */
        void __fastcall setoptions(bool append_0x, bool writehexseparator, int maxarray,
                        int filesize, bool usetabs, unsigned char* memblock);
        /*
            Gets The hexstream data as a string.
        */
        const std::string __fastcall str();
        /*
            Sets The hexstream data.
        */
        const std::string __fastcall str(std::string info);
        /*
            Clears out everything in the hexstream data.
        */
        void __fastcall clear();
        friend basic_hexstream& __fastcall operator<< (basic_hexstream& Hexstream, std::ifstream& fileStream);
        friend basic_hexstream& __fastcall operator<< (basic_hexstream& Hexstream, std::fstream& fileStream);
        friend basic_hexstream& __fastcall operator<< (basic_hexstream& Hexstream, int character);
        friend std::string& __fastcall operator>> (basic_hexstream& Hexstream, std::string& String);
        basic_hexstream(bool append_0x, bool writehexseparator,
                        int maxarray,
                        int filesize, bool usetabs,
                        unsigned char* memblock);
        basic_hexstream();
        ~basic_hexstream();
    };
}
}
