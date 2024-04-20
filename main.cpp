#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;


class logic_gates {
public:
    static char NOT(char bit) {
        if (bit == '0')
            return '1';
        else
            return '0';
    }

    static char AND(char a, char b) {
        if (a == '1' && b == '1')
            return '1';
        else
            return '0';
    }

    static char OR(char a, char b) {
        if (a == '0' && b == '0')
            return '0';
        else
            return '1';
    }

    static char XOR(char a, char b) {
        if ((a == '1' && b == '0') || (a == '0' && b == '1'))
            return '1';
        else
            return '0';
    }
};



class flagged_prefix_adder_for_absolute_difference {
public:
    static void input_bit_carry_signal_cells(const string& first_number, const string& second_number, char result[5][2]) {
        result[4][0] = '0';
        result[4][1] = '0';

        for (int i = 3; i >= 0; i--) {
            result[i][0] = logic_gates::OR(first_number[i], logic_gates::NOT(second_number[i]));
            result[i][1] = logic_gates::AND(first_number[i], logic_gates::NOT(second_number[i]));
        }
    }

    static void modified_prefix_carry_tree(char result[5][2])   {

        // Pierwsza faza
        black_box(result[3][0], result[4][0], result[3][1], result[4][1], result, 3);
        black_box(result[1][0], result[2][0], result[1][1], result[2][1], result, 1);

        // Druga faza
        black_box(result[2][0], result[3][0], result[2][1], result[3][1], result, 2);
        black_box(result[1][0], result[3][0], result[1][1], result[3][1], result, 1);

        // Trzecia faza
        black_box(result[0][0], result[1][0], result[0][1], result[1][1], result, 0);


    }

    static void black_box(char P1, char P2, char G1, char G2, char result[5][2], int i)   {

        result[i][0] = logic_gates::AND(P1, P2);
        result[i][1] = logic_gates::OR(G1, logic_gates::AND(P1, G2));

    }

    static void output_logic(char result[5][2], char output[4], string first_number, string second_number)  {

        char p;
        char upper_line, lower_line;
        for (int i = 3; i >= 0; i--)    {
            p = logic_gates::XOR(first_number[i], logic_gates::NOT(second_number[i]));
            upper_line = '1';
            lower_line = logic_gates::XOR(p, result[i + 1][1]);
            output[i] = logic_gates::XOR(upper_line, lower_line);
        }

    }
};



class input_choice  {

public:

    static int u2_to_decimal(const std::string& binary) {

        int decimal = 0;
        if (binary[0] == '1')   {

            for (int i = 3, base = 1; i > 0; --i, base *= 2) {
                if (binary[i] == '1') {
                    decimal += base;
                }
            }

            decimal -= 8;

        }   else    {

            for (int i = 3, base = 1; i >= 0; --i, base *= 2) {
                if (binary[i] == '1') {
                    decimal += base;
                }
            }

        }

        return decimal;
    }

    static bool is_Valid_Binary(const std::string& input) {

        for (char digit : input) {
            if (digit != '0' && digit != '1') {
                return false;
            }
        }

        return input.length() == 4;
    }

    static void get_input(string* first_number, string* second_number)    {

        cout << "Please, enter first number (BIN 4 bits): ";
        cin >> *first_number;

        while (!input_choice::is_Valid_Binary(*first_number)) {
            std::cout << "Invalid input. Please enter 4 binary digits (0 or 1): ";
            std::cin >> *first_number;
        }

        cout << "Please, enter second number (BIN 4 bits): ";
        cin >> *second_number;

        while (!input_choice::is_Valid_Binary(*second_number)) {
            std::cout << "Invalid input. Please enter 4 binary digits (0 or 1): ";
            std::cin >> *second_number;
        }

    }

};

vector<string> generate()   {

    vector<string> combinations;

    for (int i = 0; i < 16; ++i) {
        string binary = "";
        int temp = i;
        for (int j = 0; j < 4; ++j) {
            binary = to_string(temp % 2) + binary;
            temp /= 2;
        }
        combinations.push_back(binary);
    }

    return combinations;
}



int main() {
    string first_number;
    string second_number;

    cout << "Welcome in flagged prefix adder for absolute difference simulator!" << endl;
    cout << "This simulator is designed to work with 4 bits binary numbers only." << endl;
    cout << endl;
    //sleep(4);

    char answer;
    bool test = false;

    do {
        input_choice::get_input(&first_number, &second_number);
        cout << "Are both " << first_number << " and " << second_number << " correct? (y/n)";
        cin >> answer;

        if (toupper(answer) == 'Y') {
            test = true;
        }

    }   while (!test);

    char result[5][2];

    int first = input_choice::u2_to_decimal(first_number);
    int second = input_choice::u2_to_decimal(second_number);

    if (first > second)    {
        string tmp = first_number;
        first_number = second_number;
        second_number = tmp;
    }

    flagged_prefix_adder_for_absolute_difference::input_bit_carry_signal_cells(first_number, second_number, result);

    cout << endl;
    cout << endl;

    cout << "Input values after input bit carry signal cells block: " << endl;

    for (auto & i : result) {
        cout << "(" << i[0] << ", " << i[1] << "), ";
    }

    cout << endl;
    cout << endl;

    flagged_prefix_adder_for_absolute_difference::modified_prefix_carry_tree(result);

    cout << "Input values after modified prefix carry tree: " << endl;

    for (auto & i : result) {
        cout << "(" << i[0] << ", " << i[1] << "), ";
    }
    char output[4];

    flagged_prefix_adder_for_absolute_difference::output_logic(result, output, first_number, second_number);

    cout << endl;
    cout << endl;

    cout << "Result value: ";

    for (char i : output) {
        cout << i;
    }

    int decimal = 0;


    for (int i = 3, base = 1; i >= 0; --i, base *= 2) {
        if (output[i] == '1') {
            decimal += base;
        }
    }

    cout << endl;
    cout << "Decimal value: ";
    cout << decimal;


    //Testing

    vector<string> combinations = generate();
    int test2 = 0;
    for (auto& combination1 : combinations) {

        for (auto& combination2 : combinations) {

            char result2[5][2];

            first = input_choice::u2_to_decimal(combination1);
            second = input_choice::u2_to_decimal(combination2);

            if (first > second)    {
                string tmp = combination1;
                combination1 = combination2;
                combination2 = tmp;
            }

            flagged_prefix_adder_for_absolute_difference::input_bit_carry_signal_cells(combination1, combination2, result2);
            flagged_prefix_adder_for_absolute_difference::modified_prefix_carry_tree(result2);

            char output2[4];

            flagged_prefix_adder_for_absolute_difference::output_logic(result2, output2, combination1, combination2);

            int decimal2 = 0;

            for (int i = 3, base = 1; i >= 0; --i, base *= 2) {
                if (output2[i] == '1') {
                    decimal2 += base;
                }
            }
            int absolute_Difference = abs(first - second);

            if (absolute_Difference != decimal2) {

                cout << "We have a problem for:" << endl;
                cout << "First:" + combination1 << endl;
                cout << "Second:" + combination2 << endl;
                cout << &"Output:" [ decimal2] << endl;
                cout << &"Output abs :" [ absolute_Difference] << endl;
                return 0;
            }
            test2++;
        }
    }
    cout << endl;
    cout << "Test should equal 256" << endl;
    cout << "Test equals: " << test2 << endl;


    return 0;
}
