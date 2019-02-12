#include <QCoreApplication>
#include "packgrasp.h"
#include "jsonparser.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/**
 * @brief read_data_from_txt
 * @param filename
 * Data from ".txt"
 */
std::string debug_get_data_from_txt(const string xfilename)
{
    std::string json_result;

    QJsonObject json_object;

    const std::string filename = "C:\\Users\\user\\Documents\\Alexandre\\C++\\GRASP_Conteiner\\build-GRASP-Desktop_Qt_5_10_0_MinGW_32bit-Debug\\debug\\INSTANCES\\" + xfilename + ".txt";
    std::ifstream in_file(filename.c_str());

    cout << filename << endl;

    if (in_file.is_open())
    {
        string trash;

        in_file >> trash;
        double container_l = 0.0;
        double container_w = 0.0;
        double container_h = 0.0;
        in_file >> container_l;
        in_file >> container_w;
        in_file >> container_h;

        json_object["container_l"] = container_l;
        json_object["container_w"] = container_w;
        json_object["container_h"] = container_h;

        in_file >> trash;
        int num_box_type = 0;
        in_file >> num_box_type;
        json_object["num_box_type"] = num_box_type;

        in_file >> trash;
        QJsonArray json_rows;
        for (int i = 1; i <= num_box_type; i++)
        {
            QJsonArray json_cols;
            for(int col = 1; col <= 11; col++)
            {
                if (col == 5)
                {
                    in_file >> trash;
                    json_cols.append(QString(trash.c_str()));
                }else
                {
                    double in_val;
                    in_file >> in_val;
                    json_cols.append(in_val);
                }
            }
            json_rows.append(json_cols);
        }
        json_object["M"] = json_rows;

        in_file.close();
    }else
    {
        std::cout << "Unable to open file" << endl;
    }

    json_result = QJsonDocument(json_object).toJson(QJsonDocument::Compact).toStdString();

    return json_result;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //std::cout << argv[1];
    std::string json_input = debug_get_data_from_txt(argv[1]); //Simulates PHP data
    PackGRASP pack;
    JsonParser parser(&pack);
    parser.parse_grasp_input(json_input);
    pack.optimize();
    std::cout << json_input;
    return a.exec();
}
