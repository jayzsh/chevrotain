#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>
#include "nlohmann/json.hpp"

#define __JSON_DIR__ "wordset-dictionary/data"
#define __NULL_STR__ "null_str"

class dword
{
    private:
        std::string file_name;
        std::ifstream in;
        nlohmann::json js_ptr;

        std::string rootw__word;    // rootw is short for root word
        std::string rootw__wordset_id;
        std::vector<std::string> rootw__meanings__id;
        std::vector<std::string> rootw__meanings__def;
        std::vector<std::string> rootw__meanings__example;
        std::vector<std::string> rootw__meanings__speech_part;
        std::vector<std::vector<std::string>> rootw__meanings__synonyms;

        bool ERR_JSON_MAP_NOT_FOUND;
        bool ERR_ROOTW_NOT_FOUND;
        bool ERR_FATAL_EXIT_FLAG;
        std::string err_node;

    public:    
        dword ()
        {   
            this->ERR_JSON_MAP_NOT_FOUND = false;
            this->ERR_ROOTW_NOT_FOUND = false;

            if (isdigit (rootw__word.at (0)))
            {
                ERR_ROOTW_NOT_FOUND = true;
                ERR_JSON_MAP_NOT_FOUND = true;
            }

            if (!ERR_JSON_MAP_NOT_FOUND)
            {
                extr__rootw__wordset_id ();
            }

            if (!ERR_ROOTW_NOT_FOUND)
            {
                extr__rootw__meanings__def ();
                extr__rootw__meanings__id ();
                extr__rootw__meanings__example ();
                extr__rootw__meanings__speech_part ();
                extr__rootw__meanings__synonyms ();
            }
            else
                extr__dword_suggestion ();
        }

        void trim ();
        void init (std::string);
        void console_prt_print (bool);

        void extr__dword_suggestion ();
        void extr__rootw__wordset_id ();
        void extr__rootw__meanings__def ();
        void extr__rootw__meanings__id ();
        void extr__rootw__meanings__example ();
        void extr__rootw__meanings__speech_part ();
        void extr__rootw__meanings__synonyms ();
        
        std::string get__rootw__wordset_id ()
            { return rootw__word; }
        std::vector<std::string> get__rootw__meanings__def ()
            { return rootw__meanings__def; }
        std::vector<std::string> get__rootw__meanings__id ()
            { return rootw__meanings__id; }
        std::vector<std::string> get__rootw__meanings__example ()
            { return rootw__meanings__example; }
        std::vector<std::string> get__rootw__meanings__speech_part ()
            { return rootw__meanings__speech_part; }
        std::vector<std::vector<std::string>> get__rootw__meanings__synonyms ()
            { return rootw__meanings__synonyms; }
};

void dword::init (std::string entry)
{
    this->rootw__word = entry;
    this->file_name = __JSON_DIR__;
    this->file_name.push_back ('/');
    this->file_name.push_back (this->rootw__word.at (0));
    this->file_name += ".json";
    in.open (this->file_name);
    if (!in.is_open ())
        this->ERR_JSON_MAP_NOT_FOUND = true;
    else
        this->js_ptr = nlohmann::json::parse (in);
}

void dword::console_prt_print (bool debug_mode)
{
    std::cout << "      word: " << this->rootw__word << std::endl;
    if (debug_mode)
        std::cout << "wordset_id: " << this->rootw__wordset_id << std::endl;
    std::cout << std::endl;
    for (int i = 0; i < this->rootw__meanings__id.size(); i++)
    {    
        std::cout << i + 1 << ". ";
        if (debug_mode)
            std::cout << "[" << this->rootw__meanings__id[i] << "] ";
        std::cout << "(" << this->rootw__meanings__speech_part[i] << ") ";
        std::cout << this->rootw__meanings__def[i];
        if (this->rootw__meanings__synonyms[i].size () != 0)
        {
            std::cout << "\n\t Synonyms: ";
            for (int j = 0; j < this->rootw__meanings__synonyms[i].size(); j++)
                std::cout << this->rootw__meanings__synonyms[i][j] << ((j != this->rootw__meanings__synonyms[i].size() - 1) ? ", " : "");
        }
        if (this->rootw__meanings__example[i] != __NULL_STR__)
            std::cout << "\n\tExample: " << this->rootw__meanings__example[i];
        std::cout << std::endl << std::endl;
    }
}

void dword::trim ()
{
    std::string entry = this->rootw__word;
    int i = 0, j = entry.size() - 1;
    
    while (isspace (entry.at (i)))
        i++; // extraction starts from final i
    while (isspace (entry.at (j)))
        j--; // extraction ends at final j
    this->rootw__word = entry.substr (i, j - i + 1);
}

void dword::extr__dword_suggestion ()
{
    std::cout << "Suggestion here!";
}

void dword::extr__rootw__wordset_id ()
{
    try { this->rootw__wordset_id = js_ptr[this->rootw__word]["wordset_id"].get<std::string> (); }
    catch (...)
    {
        this->ERR_ROOTW_NOT_FOUND = true;
    }
}

void dword::extr__rootw__meanings__def ()
{
    for (auto& lvl : this->js_ptr[this->rootw__word]["meanings"])
        this->rootw__meanings__def.push_back (lvl["def"].get<std::string> ());
}

void dword::extr__rootw__meanings__id ()
{
    for (auto& lvl : this->js_ptr[this->rootw__word]["meanings"])
        this->rootw__meanings__id.push_back (lvl["id"].get<std::string> ());
}

void dword::extr__rootw__meanings__example ()
{
    for (auto& lvl : this->js_ptr[this->rootw__word]["meanings"])
        if (lvl.contains ("example"))
            this->rootw__meanings__example.push_back (lvl["example"].get<std::string> ());
        else
            this->rootw__meanings__example.push_back (__NULL_STR__);
}

void dword::extr__rootw__meanings__speech_part ()
{
    for (auto& lvl : this->js_ptr[this->rootw__word]["meanings"])
        this->rootw__meanings__speech_part.push_back (lvl["speech_part"].get<std::string> ());
}

void dword::extr__rootw__meanings__synonyms ()
{
	std::vector<std::string> syn_vect, tmp;
    int i = 0;
    for (auto& lvl_1 : this->js_ptr[this->rootw__word]["meanings"])
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
            this->rootw__meanings__synonyms.push_back (tmp);
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
    word.init (input);
    word.console_prt_print (true);
    return 0;
}