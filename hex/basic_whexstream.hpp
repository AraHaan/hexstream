/*
    basic_whexstream

    Header for the whexstream class.
*/


namespace AraHaan {
namespace experimental {
    class basic_whexstream {
    private:
        std::wstringstream base_whexstream;
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
        const std::wstring __fastcall str();
        /*
            Sets The hexstream data.
        */
        const std::wstring __fastcall str(std::wstring info);
        /*
            Clears out everything in the hexstream data.
        */
        void __fastcall clear();
        friend basic_whexstream& __fastcall operator<< (basic_whexstream& Hexstream, std::wifstream& fileStream);
        friend basic_whexstream& __fastcall operator<< (basic_whexstream& Hexstream, std::wfstream& fileStream);
        friend basic_whexstream& __fastcall operator<< (basic_whexstream& Hexstream, int character);
        friend std::wstring& __fastcall operator>> (basic_whexstream& Hexstream, std::wstring& String);
        basic_whexstream(bool append_0x, bool writehexseparator,
                        int maxarray,
                        int filesize, bool usetabs,
                        unsigned char* memblock);
        basic_whexstream();
        ~basic_whexstream();
    };
}
}
