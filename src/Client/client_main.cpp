#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <pybind11/embed.h>

using namespace std;
namespace py = pybind11;

string Hash(string password) {
    py::scoped_interpreter guard{};
    py::module_ hashlib = py::module_::import("hashlib");
    py::object sha256 = hashlib.attr("sha256")();
    py::bytes bPassword = py::bytes(password); // Password
    sha256.attr("update")(bPassword);
    py::str hex = sha256.attr("hexdigest")();
    //py::print(hex);
    auto hashedPassword = hex.cast<std::string>();
    //std::cout << message;
    return hashedPassword;
}

int main()
{
    // Username
    string username, password; 
    cout << "Type your username: "; // Type a number and press enter
    cin >> username; // Get user input from the keyboard
    cout << "Your username is: " << username << endl; // Display the input value

    // set to hide input
    termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    termios newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Password
    cout << "Type your password: "; // Type a number and press enter
    cin >> password;
    cout << "Your password is: " << password << endl; // Display the input value

    // set back to show input mode
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    string hashed_password = Hash(password);



    return 0;
}