#include "sha-1.hpp"

sha_1_hash::sha_1_hash(string& file_name) {
    ifstream input_stream(file_name);
    if (input_stream) {
        mybyte b;
        int i;
        while (!input_stream.eof()) {
            input_stream >> b;
            data_bytes.push_back(b);
            i++;
        }
        data_bytes.pop_back();

        pad();
        transfer_to_word();
        input_stream.close();
    } else {
        cout << "open file error" << endl;
    }
}

void sha_1_hash::pad() {
    unsigned long long int data_size = data_bytes.size() * 8;
    unsigned long long int d = ((447 - data_size) % 512 + 512) % 512;

    int zero_bytes_number = (d + 1) / 8 - 1;

    mybyte first_padding_byte = 0x80;
    data_bytes.push_back(first_padding_byte);

    for (int i = 0; i < zero_bytes_number; i++) {
        data_bytes.push_back(0);
    }

    mybyte* data_size_array = (mybyte*)&data_size;
    for (int i = 7; i >= 0; i--) {
        data_bytes.push_back(data_size_array[i]);
    }

    return;
}

void sha_1_hash::transfer_to_word() {
    for (int i = 0; i < data_bytes.size(); i += 4) {
        data.push_back(byte_to_word(&data_bytes[i]));
    }
    return;
}

word sha_1_hash::byte_to_word(mybyte* array) {
    word ret = 0;
    for (int i = 0; i < 4; i++) {
        ret = ((ret << 8) | array[i]);
    }

    return ret;
}

string sha_1_hash::digest() {
    int group_number = data.size() / 16;
    for (int i = 0; i < group_number; i++) {
        digest_one_round(&data[16*i]);
    }

    return transform_to_string();
}

string sha_1_hash::transform_to_string(){
    stringstream ss;
    string ret;

    for(int i = 0;i < 5;i++){
        ss << hex << state[i];
    }
    ss >> ret;
    return ret;
}

void sha_1_hash::digest_one_round(word* one_group) {
    word word_array[80];

    for (int i = 0; i < 16; i++) {
        word_array[i] = one_group[i];
    }

    for (int i = 16; i < 80; i++) {
        word_array[i] = rotl(1, (word_array[i - 3] ^ word_array[i - 8] ^
                                 word_array[i - 14] ^ word_array[i - 16]));
    }

    word A = state[0];
    word B = state[1];
    word C = state[2];
    word D = state[3];
    word E = state[4];

    for (int i = 0; i < 80; i++) {
        word temp = rotl(5, A) + functions[i / 20](B, C, D) + E +
                    word_array[i] + K[i / 20];

        E = D;
        D = C;
        C = rotl(30, B);
        B = A;
        A = temp;

    }

    state[0] += A;
    state[1] += B;
    state[2] += C;
    state[3] += D;
    state[4] += E;
}
void sha_1_hash::print_state(){
    cout << "current state:" << endl;
    for(int i = 0;i < 5;i++){
        cout << hex << state[i];
    }
    cout << endl;
}
word sha_1_hash::rotl(int shift_bit, word number) {
    return ((number << shift_bit) | (number >> (32 - shift_bit)));
}
word sha_1_hash::function1(word b, word c, word d) {
    return ((b & c) | ((~b) & d));
}
word sha_1_hash::function2(word b, word c, word d) { return b ^ c ^ d; }
word sha_1_hash::function3(word b, word c, word d) {
    return (b & c) | (b & d) | (c & d);
}