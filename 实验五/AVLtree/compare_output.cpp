#include <iostream>
#include <fstream>
#include <string>

int main() {
    //这个文件是你的程序输出的结果
    std::ifstream user_output("output_student.txt");
    std::ifstream reference_output("output.txt");

    if (!user_output.is_open()) {
        std::cerr << "无法打开用户输出文件 output_user.txt\n";
        return 1;
    }
    if (!reference_output.is_open()) {
        std::cerr << "无法打开参考输出文件 output.txt\n";
        return 1;
    }

    std::string user_line, ref_line;
    int line_number = 1;
    bool is_same = true;

    while (std::getline(user_output, user_line)) {
        if (!std::getline(reference_output, ref_line)) {
            std::cout << "输出不一致：用户输出比参考输出多。\n";
            is_same = false;
            break;
        }
        if (user_line != ref_line) {
            std::cout << "输出不一致：第 " << line_number << " 行不同。\n";
            std::cout << "用户输出：" << user_line << "\n";
            std::cout << "参考输出：" << ref_line << "\n";
            is_same = false;
            break;
        }
        ++line_number;
    }

    if (is_same && std::getline(reference_output, ref_line)) {
        std::cout << "输出不一致：参考输出比用户输出多。\n";
        is_same = false;
    }

    if (is_same) {
        std::cout << "输出一致。\n";
    }

    user_output.close();
    reference_output.close();
    return 0;
}