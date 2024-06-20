/**
*
*   Author: 	jay.dnb@outlook.in
*   Created: 	
*
*   UNIX CPP scipt >> 
*   Synopsis: ~$
*
**/

#include <iostream>
#include <fstream>
#include "../inc/nlohmann/json.hpp"

using namespace std;

int main(int argc, char **argv)
{
	
	ifstream f ("../inc/wordset-dictionary/data/a.json");
	nlohmann::json j = nlohmann::json::parse (f);
	ofstream g ("pbyte/a", ios::binary);
	g.write ((char*) &j, sizeof (j));
	ifstream h ("pbyte/a", ios::binary);
	nlohmann::json k;
	h.read ((char*) k, sizeof (j));
	string x = j["apple"]["wordset_id"].get<string> ();
	cout << x;
	
}
