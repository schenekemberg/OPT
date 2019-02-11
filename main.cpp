#include <QCoreApplication>

#include "packgrasp.h"
#include "jsonparser.h"


std::string create_json_input()
{
    std::string json_input = "input_test";

    return json_input;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    std::string json_input = create_json_input(); //Simulates PHP data
    PackGRASP pack;
    JsonParser parser(&pack);
    parser.parse_grasp_input(json_input);



    std::cout << json_input;
    return a.exec();
}
