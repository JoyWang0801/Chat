#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <pybind11/embed.h>

using namespace std;
namespace py = pybind11;

int Hash() {
    py::scoped_interpreter guard{};

    py::module_ hashlib = py::module_::import("hashlib");
    py::object sha256 = hashlib.attr("sha256");
    sha256.attr("update")(1234);
    py::print(sha256.attr("hexdigest"));
    return 0;
}

int main()
{
    //Hash();
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

    return 0;
}