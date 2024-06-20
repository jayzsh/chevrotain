#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>
#include "nlohmann/json.hpp"

#define __JSON_PREFIX__ ""
#define __JSON_POSTFIX__ ".json"
#define __JSON_FCOUNT__ 0x1a
#define __INDEX_OF_SMALL_A__ 0x61
#define __JSON_DIR__ "wordset-dictionary/data/"
#define __NULL_STR__ "null_str"

class dword
{
    private:
        std::vector<nlohmann::json> js_vect;
        nlohmann::json *js_ptr;

        std::string rootw_word;
        std::string rootw_wordset_id;
        std::vector<std::string> rootw_meanings_id;
        std::vector<std::string> rootw_meanings_def;
        std::vector<std::string> rootw_meanings_example;
        std::vector<std::string> rootw_meanings_speech_part;
        std::vector<std::vector<std::string>> rootw_meanings_synonyms;
        std::vector<std::string> rootw_suggestions;

        bool ERR_JSON_MAP_NOT_FOUND;
        bool ERR_ROOTW_NOT_FOUND;
        bool ERR_FATAL_EXIT_FLAG;
        std::vector<std::string> err_node;

    public:    
        dword ()
        {  
            this->ERR_JSON_MAP_NOT_FOUND = false;
            this->ERR_ROOTW_NOT_FOUND = false;

            for (int i = 0; i < __JSON_FCOUNT__; i++)
            { 
                std::fstream fs;
                char tmp_ch = __INDEX_OF_SMALL_A__ + i;
                std::string tmp_str = __JSON_DIR__;
                tmp_str += __JSON_PREFIX__;
                tmp_str.push_back (tmp_ch);
                tmp_str += __JSON_POSTFIX__;
                fs.open (tmp_str);
                js_vect.push_back (nlohmann::json::parse (fs));
            }
        }

        void trim ();
        void init (std::string);
        void console_prt_print (bool);

        void extr_dword_suggestion ();
        void extr_rootw_wordset_id ();
        void extr_rootw_meanings_def ();
        void extr_rootw_meanings_id ();
        void extr_rootw_meanings_example ();
        void extr_rootw_meanings_speech_part ();
        void extr_rootw_meanings_synonyms ();
        
        std::string get_rootw_wordset_id ()
            { return rootw_word; }
        std::vector<std::string> get_rootw_meanings_def ()
            { return rootw_meanings_def; }
        std::vector<std::string> get_rootw_meanings_id ()
            { return rootw_meanings_id; }
        std::vector<std::string> get_rootw_meanings_example ()
            { return rootw_meanings_example; }
        std::vector<std::string> get_rootw_meanings_speech_part ()
            { return rootw_meanings_speech_part; }
        std::vector<std::vector<std::string>> get_rootw_meanings_synonyms ()
            { return rootw_meanings_synonyms; }
};

void dword::init (std::string entry)
{
    this->rootw_word = entry; trim ();
    switch (this->rootw_word.at (0))
    {
        case 'a' : this->js_ptr = &js_vect[ 0]; break;
        case 'b' : this->js_ptr = &js_vect[ 1]; break;
        case 'c' : this->js_ptr = &js_vect[ 2]; break;
        case 'd' : this->js_ptr = &js_vect[ 3]; break;
        case 'e' : this->js_ptr = &js_vect[ 4]; break;
        case 'f' : this->js_ptr = &js_vect[ 5]; break;
        case 'g' : this->js_ptr = &js_vect[ 6]; break;
        case 'h' : this->js_ptr = &js_vect[ 7]; break;
        case 'i' : this->js_ptr = &js_vect[ 8]; break;
        case 'j' : this->js_ptr = &js_vect[ 9]; break;
        case 'k' : this->js_ptr = &js_vect[10]; break;
        case 'l' : this->js_ptr = &js_vect[11]; break;
        case 'm' : this->js_ptr = &js_vect[12]; break;
        case 'n' : this->js_ptr = &js_vect[13]; break;
        case 'o' : this->js_ptr = &js_vect[14]; break;
        case 'p' : this->js_ptr = &js_vect[15]; break;
        case 'q' : this->js_ptr = &js_vect[16]; break;
        case 'r' : this->js_ptr = &js_vect[17]; break;
        case 's' : this->js_ptr = &js_vect[18]; break;
        case 't' : this->js_ptr = &js_vect[19]; break;
        case 'u' : this->js_ptr = &js_vect[20]; break;
        case 'v' : this->js_ptr = &js_vect[21]; break;
        case 'w' : this->js_ptr = &js_vect[22]; break;
        case 'x' : this->js_ptr = &js_vect[23]; break;
        case 'y' : this->js_ptr = &js_vect[24]; break;
        case 'z' : this->js_ptr = &js_vect[25]; break;
         default : ERR_ROOTW_NOT_FOUND = true;
    }
    if (!ERR_JSON_MAP_NOT_FOUND)
    {
        extr_rootw_wordset_id ();
    }
    if (!ERR_ROOTW_NOT_FOUND)
    {
        extr_rootw_meanings_def ();
        extr_rootw_meanings_id ();
        extr_rootw_meanings_example ();
        extr_rootw_meanings_speech_part ();
        extr_rootw_meanings_synonyms ();
    }
    else
        extr_dword_suggestion ();
}

void dword::console_prt_print (bool debug_mode)
{
    std::cout << "      word: " << this->rootw_word << std::endl;
    if (debug_mode)
        std::cout << "wordset_id: " << this->rootw_wordset_id << std::endl;
    std::cout << std::endl;
    for (int i = 0; i < this->rootw_meanings_id.size(); i++)
    {    
        std::cout << i + 1 << ". ";
        if (debug_mode)
            std::cout << "[" << this->rootw_meanings_id[i] << "] ";
        std::cout << "(" << this->rootw_meanings_speech_part[i] << ") ";
        std::cout << this->rootw_meanings_def[i];
        if (this->rootw_meanings_synonyms[i].size () != 0)
        {
            std::cout << "\n\t Synonyms: ";
            for (int j = 0; j < this->rootw_meanings_synonyms[i].size(); j++)
                std::cout << this->rootw_meanings_synonyms[i][j] << ((j != this->rootw_meanings_synonyms[i].size() - 1) ? ", " : "");
        }
        if (this->rootw_meanings_example[i] != __NULL_STR__)
            std::cout << "\n\tExample: " << this->rootw_meanings_example[i];
        std::cout << std::endl << std::endl;
    }
}

void dword::trim ()
{
    std::string entry = this->rootw_word;
    int i = 0, j = entry.size() - 1;
    while (isspace (entry.at (i)))
        i++; // extraction starts from final i
    while (isspace (entry.at (j)))
        j--; //extraction ends at final j
    this->rootw_word = entry.substr (i, j - i + 1);
}

void dword::extr_dword_suggestion ()
{
    std::cout << "Suggestion here!";
}

void dword::extr_rootw_wordset_id ()
{
    try { this->rootw_wordset_id = (*this->js_ptr)[this->rootw_word]["wordset_id"].get<std::string> (); }
    catch (...)
    {
        this->ERR_ROOTW_NOT_FOUND = true;
    }
}

void dword::extr_rootw_meanings_def ()
{
    for (auto& lvl : (*this->js_ptr)[this->rootw_word]["meanings"])
        this->rootw_meanings_def.push_back (lvl["def"].get<std::string> ());
}

void dword::extr_rootw_meanings_id ()
{
    for (auto& lvl : (*this->js_ptr)[this->rootw_word]["meanings"])
        this->rootw_meanings_id.push_back (lvl["id"].get<std::string> ());
}

void dword::extr_rootw_meanings_example ()
{
    for (auto& lvl : (*this->js_ptr)[this->rootw_word]["meanings"])
        if (lvl.contains ("example"))
            this->rootw_meanings_example.push_back (lvl["example"].get<std::string> ());
        else
            this->rootw_meanings_example.push_back (__NULL_STR__);
}

void dword::extr_rootw_meanings_speech_part ()
{
    for (auto& lvl : (*this->js_ptr)[this->rootw_word]["meanings"])
        this->rootw_meanings_speech_part.push_back (lvl["speech_part"].get<std::string> ());
}

void dword::extr_rootw_meanings_synonyms ()
{
	std::vector<std::string> syn_vect, tmp;
    int i = 0;
    for (auto& lvl_1 : (*this->js_ptr)[this->rootw_word]["meanings"])
    {
            if (lvl_1.contains ("synonyms"))
                for (auto& lvl_2 : lvl_1["synonyms"])
                    syn_vect.push_back (lvl_2);
            syn_vect.push_back (__NULL_STR__);
    }
    while (i < syn_vect.size ())
    {
        if (syn_vect[i] != __NULL_STR__)
            tmp.push_back (syn_vect[i]);
        else
        {
            this->rootw_meanings_synonyms.push_back (tmp);
            tmp.clear ();
        }
        i++;
    }
}

int main ()
{
    // optional
    std::string input;
    std::cout << "\nEnter a word: "; 
    getline (std::cin, input);
    std::cout << std::endl;
    dword word;
    std::cout << sizeof (word);
    /* std::ifstream f("jsondb.bin", std::ios::binary);
    f.read ((char*) &word, sizeof (word)); */
    word.init (input);
    word.console_prt_print (true);
    return 0;
}