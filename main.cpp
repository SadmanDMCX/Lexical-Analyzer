#include <iostream>
#include <vector>

#include "fileio.h"
#include "compiler.h"

using namespace std;
using namespace fileio;
using namespace super;

int main() {
    string data = fio.ReadFile();
    vector<string> output = compile(data);
    fio.WriteFile(vectorToString(output));

    system("pause");
    return 0;
}
