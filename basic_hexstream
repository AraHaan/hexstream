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
            Hack method that makes operator<<
            for ifstream and fstream actually compile.
            DO NOT USE OUTSIDE OF THAT.
        */
        int get_currentarray();
        /*
            Hack method that makes operator<<
            for ifstream and fstream actually compile.
            DO NOT USE OUTSIDE OF THAT.
        */
        void set_currentarray(int currentarray);
        /*
            Hack method that makes operator<<
            for ifstream and fstream actually compile.
            DO NOT USE OUTSIDE OF THAT.
        */
        bool get_tabs();
        /*
            Hack method that makes operator<<
            for ifstream and fstream actually compile.
            DO NOT USE OUTSIDE OF THAT.
        */
        int get_filesize();
        /*
            Hack method that makes operator<<
            for ifstream and fstream actually compile.
            DO NOT USE OUTSIDE OF THAT.
        */
        unsigned char* get_memblock();
        /*
            Gets The hexstream data as a string.
        */
        const std::string str();
        /*
            Sets The hexstream data.
        */
        const std::string str(std::string info);
        /*
            Clears out everything in the hexstream data.
        */
        void clear();
        friend basic_hexstream& operator<< (basic_hexstream& Hexstream, std::ifstream& fileStream);
        friend basic_hexstream& operator<< (basic_hexstream& Hexstream, std::fstream& fileStream);
        friend basic_hexstream& operator<< (basic_hexstream& Hexstream, int character);
        friend std::string& operator>> (basic_hexstream& Hexstream, std::string& String);
        basic_hexstream(bool append_0x, bool writehexseparator,
                        int maxarray,
                        int filesize, bool usetabs,
                        unsigned char* memblock);
        basic_hexstream();
        ~basic_hexstream();
    };
}
}
