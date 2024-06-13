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
    //py::print(hex);
    auto hashedPassword = hex.cast<std::string>();
    //std::cout << message;
    return hashedPassword;
}

void connect_to_mongodb()
{
    py::scoped_interpreter guard{};
    py::object MongoClient = py::module_::import("pymongo.mongo_client").attr("MongoClient");
    py::object ServerApi = py::module_::import("pymongo.server_api").attr("ServerApi");

    py::str uri = "mongodb+srv://@cluster0.ltqknhb.mongodb.net/?retryWrites=true&w=majority&appName=Cluster0";

    py::object sa = ServerApi('1');
    py::object client = MongoClient(uri, "server_api"_a=sa);
    try
    {
        //client.admin.command('ping')
        py::object ad = client.attr("admin");
        ad.attr("command")("ping");
        cout << "success" << endl;
    }
    catch (...)
    {
        cout << "exception occurred" << endl;
    }
}

int main()
{
    // // Username
    // string username, password; 
    // cout << "Type your username: "; // Type a number and press enter
    // cin >> username; // Get user input from the keyboard
    // cout << "Your username is: " << username << endl; // Display the input value

    // // set to hide input
    // termios oldt;
    // tcgetattr(STDIN_FILENO, &oldt);
    // termios newt = oldt;
    // newt.c_lflag &= ~ECHO;
    // tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // // Password
    // cout << "Type your password: "; // Type a number and press enter
    // cin >> password;
    // cout << "Your password is: " << password << endl; // Display the input value

    // // set back to show input mode
    // tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    // string hashed_password = Hash(password);


    connect_to_mongodb();
    return 0;
}