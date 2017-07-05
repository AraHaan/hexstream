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
        int get_currentarray();
        void set_currentarray(int currentarray);
        bool get_tabs();
        int get_filesize();
        unsigned char* get_memblock();
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
        void AddCharacter(int character);
        /*
            Sets if the user wants to append "0x" and write an ", "
            on every character added to the hexstream.
        */
        void setoptions(bool append_0x, bool writehexseparator, int maxarray,
                        int filesize, bool usetabs, unsigned char* memblock);
        /*
            Gets The hexstream data as a string.
        */
        const std::wstring str();
        /*
            Sets The hexstream data.
        */
        const std::wstring str(std::wstring info);
        /*
            Clears out everything in the hexstream data.
        */
        void clear();
        friend basic_whexstream& operator<< (basic_whexstream& Hexstream, std::wifstream& fileStream);
        friend basic_whexstream& operator<< (basic_whexstream& Hexstream, std::wfstream& fileStream);
        friend basic_whexstream& operator<< (basic_whexstream& Hexstream, int character);
        friend std::wstring& operator>> (basic_whexstream& Hexstream, std::wstring& String);
        basic_whexstream(bool append_0x, bool writehexseparator,
                        int maxarray,
                        int filesize, bool usetabs,
                        unsigned char* memblock);
        basic_whexstream();
        ~basic_whexstream();
    };
}
}
