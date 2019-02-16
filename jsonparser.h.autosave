#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <QString>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QByteArray>
#include <QFile>
#include <iostream>
#include <vector>
#include <string>
#include "packgrasp.h"

class JsonParser
{
public:
    JsonParser();
    JsonParser(PackGRASP* xp_pg);
    void set_PackGRASP(PackGRASP* xp_pg);

    //GRASP
    std::string parse_grasp_output();
    void parse_grasp_input(std::string xjson_input);
    PackGRASP* pg;

private:
    QJsonObject create_json_object(std::string xjson_input);
    void initialize_grasp_input_parameters(int xn_boxes);


};

#endif // JSONPARSER_H
