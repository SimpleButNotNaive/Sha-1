#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

typedef unsigned char mybyte;
typedef unsigned int word;

using namespace std;

class sha_1_hash {
    word state[5] = {0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476,
                     0xc3d2e1f0};
    word K[4] = {0x5a827999, 0x6ed9eba1, 0x8f1bbcdc, 0xca62c1d6};

    word (*functions[4])(word a, word b, word c) = {function1, function2,
                                                    function3, function2};
    vector<word> data;
    vector<mybyte> data_bytes;
    void pad();
    void transfer_to_word();
    word byte_to_word(mybyte* array);
    string transform_to_string();
    void digest_one_round(word*);
    word rotl(int, word);
    void print_state();

    static word function1(word b, word c, word d);
    static word function2(word b, word c, word d);
    static word function3(word b, word c, word d);

   public:
    sha_1_hash(string& file_name);
    string digest();
};