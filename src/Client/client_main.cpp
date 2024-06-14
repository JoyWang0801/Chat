#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <pybind11/embed.h>

using namespace std;
namespace py = pybind11;
using namespace pybind11::literals;

string Hash(string password) {
    py::scoped_interpreter guard{};
    py::module_ hashlib = py::module_::import("hashlib");
    py::object sha256 = hashlib.attr("sha256")();
    py::bytes bPassword = py::bytes(password); // Password
    sha256.attr("update")(bPassword);
    py::str hex = sha256.attr("hexdigest")();
    auto hashedPassword = hex.cast<std::string>();
    //std::cout << message;
    return hashedPassword;
}

void connect_to_mongodb(string username, string password, int action)
{
    // Import
    py::scoped_interpreter guard{};
    py::object MongoClient = py::module_::import("pymongo.mongo_client").attr("MongoClient");
    py::object ServerApi = py::module_::import("pymongo.server_api").attr("ServerApi");
    py::object dotenv = py::module_::import("dotenv").attr("load_dotenv");
    py::object os = py::module_::import("os");

    // Get uri from .env
    dotenv();
    py::str uri = os.attr("getenv")("ATLAS_URI");

    // Connect
    py::object sa = ServerApi('1');
    py::object client = MongoClient(uri, "server_api"_a=sa);
    py::object collection = client["User"]["User"];

    // Create info
    //py::dict UserInfo("username"_a="myoi", "password"_a="mina");
    //py::dict UserInfo("username"_a="123", "password"_a="321");

    py::dict UserInfo("username"_a=username, "password"_a=password);

    if(action == 1) // Create user
    {
        py::object insert_result = collection.attr("insert_one")(UserInfo);
        bool success = insert_result.attr("acknowledged").cast<bool>();
        if(success != true)
        {
            cout << "Error occured, wasn't able to create user." << endl;
        }
    }
    else if(action == 2) // Sign in
    {
        py::object find_result = collection.attr("find_one")(UserInfo);
        if(find_result.is_none())
        {
            cout << "not an existing user" << endl;
        }
        else{
            py::print(find_result);

        }
    }
}

int main()
{
    int choice;
    cout << "Make your choice \n1.Create account \n2.Log in "; // Type a number and press enter
    cin >> choice; // Get user input from the keyboard

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

    // Hash and insert to db
    string hashed_password = Hash(password);
    connect_to_mongodb(username, hashed_password, choice);

    return 0;
}