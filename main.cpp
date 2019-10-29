#include "sha-1.hpp"

string file_name = "input_file";
int main() {

    sha_1_hash hash_func(file_name);
    string hash_value = hash_func.digest();

    cout << "哈希值为：" << hash_value << endl;
    return 0;
}