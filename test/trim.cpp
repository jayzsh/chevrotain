#include <iostream>
#include <string>

int main ()
{
    std::string entry = "   barely     ";
    int i = 0, j = entry.size() - 1;
    
    while (isspace (entry.at (i)))
        i++; // extraction starts from final i
    while (isspace (entry.at (j)))
        j--; //extraction ends at final j
    std::string x = entry.substr (i, j-i + 1);
    std::cout << i << j << x;
}