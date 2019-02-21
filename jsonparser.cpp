#include "jsonparser.h"

JsonParser::JsonParser()
{

}

JsonParser::JsonParser(PackGRASP *xp_pg)
{
   set_PackGRASP(xp_pg);
}

void JsonParser::set_PackGRASP(PackGRASP *xp_pg)
{
    this->pg = xp_pg;
}

/**
 * @brief JsonParser::parse_grasp_output
 * @return
 * Gets all the elements that are already pre-parsed into strings from a
 * OutputSolutionGRASP, and turns them into one string in a json
 * format, the root object has 6 elements, with keys:
 *
 *  1 : root_object["unpacked_boxes"]
 *  2 : root_object["packed_boxes"]
 *  3 : root_object["packed_states"]
 *  4 : root_object["occupied_vol"]
 *  5 : root_object["run_time"]
 *  6 : root_object["status"]
 *
 *  1 is An array with objects with the folloeing keys:
 *      "ID_box"
 *      "total_unpacked_box"
 *
 *  2 and 3 are Arrays, both with the following keys:
 *      "ID_state"
 *      "ID_box"
 *      "x"
 *      "y"
 *      "z"
 *      "l"
 *      "w"
 *      "h"
 *  4 5 and 5 are simple strings
 *
 */
QJsonObject JsonParser::parse_grasp_output()
{
    std::string grasp_json_output = "";
    PackGRASP::OutputSolutionGRASP out_grasp = pg->get_pre_parse_solution();

    QJsonObject root_object;

    QJsonArray unpacked_boxes = parse_grasp_unpacked_boxes(out_grasp);
    QJsonArray packed_boxes = parse_grasp_packed_boxes(out_grasp);
    QJsonArray packed_states = parse_grasp_packed_states(out_grasp);

    root_object["unpacked_boxes"] = unpacked_boxes;
    root_object["packed_boxes"] = packed_boxes;
    root_object["packed_states"] = packed_states;
    root_object["occupied_vol"] = QString(out_grasp.occupied_vol.c_str());
    root_object["run_time"] = QString(out_grasp.run_time.c_str());
    root_object["status"] = QString(out_grasp.status.c_str());

    return root_object;
}

/**
 * @brief JsonParser::parse_grasp_input
 * @param xjson_input, string with CLP parameters in json style
 * The json has the keys:
 * num_box_type: number of different boxes, the information of the boxes
 * is passes as a array of array with key M;
 * M[i][0] : int - dimension lenght of box 0
 * M[i][1] : int - dimension width of box 0
 * M[i][2] : int - dimension lenght of box 0
 * M[i][3] : int - availability of box i
 * M[i][4] : string - ID of box i
 * M[i][5] : BOOL permitted orientation of box i
 * M[i][6] : BOOL permitted orientation of box i
 * M[i][7] : BOOL permitted orientation of box i
 * M[i][8] : BOOL permitted orientation of box i
 * M[i][9] : BOOL permitted orientation of box i
 * M[i][10] : BOOL permitted orientation of box i
 */
void JsonParser::parse_grasp_input(QJsonObject xjson_root_object)
{

    //time_limit /////////////
    pg->time_limit = xjson_root_object["time_limit"].toDouble();

    //container_dimension/////
    QJsonArray container_dimension = xjson_root_object["container"].toArray();
    pg->container_l = container_dimension[0].toDouble();
    pg->container_w = container_dimension[1].toDouble();
    pg->container_h = container_dimension[2].toDouble();

    //num_box_type ////////////
    pg->n_box_type = xjson_root_object["num_box_type"].toInt();

    initialize_grasp_input_parameters( pg->n_box_type );
    QJsonArray manifest = xjson_root_object["manifest"].toArray();
    for(size_t i = 0; i < static_cast<size_t>(manifest.size()) ; i++)
    {
        QJsonObject box_info = manifest[static_cast<int>(i)].toObject();
        //Dimension
        QJsonArray box_dimension =              box_info["dim"].toArray();
        pg->vv_box_lwh[i][0] =                  box_dimension[0].toDouble();
        pg->vv_box_lwh[i][1] =                  box_dimension[1].toDouble();
        pg->vv_box_lwh[i][2] =                  box_dimension[2].toDouble();

        //Box demand
        pg->v_box_b[i] =                        box_info["count"].toInt();

        //Box id
        pg->v_box_ID[i] =                       box_info["id"].toString().toStdString();

        //Box orientation
        QJsonArray box_orientation =            box_info["orientation"].toArray();
        pg->vv_box_allowed_orientation[i][0] =  box_orientation[0].toBool();
        pg->vv_box_allowed_orientation[i][1] =  box_orientation[1].toInt();
        pg->vv_box_allowed_orientation[i][2] =  box_orientation[2].toInt();
        pg->vv_box_allowed_orientation[i][3] =  box_orientation[3].toInt();
        pg->vv_box_allowed_orientation[i][4] =  box_orientation[4].toInt();
        pg->vv_box_allowed_orientation[i][5] =  box_orientation[5].toInt();
     }


}

/**
 * @brief JsonParser::parse_grasp_unpacked_boxes
 * @param xpre_parsed_sol
 * @return
 * Parse the information of the unpacked boxes into
 */
QJsonArray JsonParser::parse_grasp_unpacked_boxes(PackGRASP::OutputSolutionGRASP &xpre_parsed_sol)
{
    QJsonArray unpacked_boxes;

    for(size_t i = 0; i < xpre_parsed_sol.vv_out_unpacked_boxes.size(); i++)
    {
        QJsonObject row;
        row["ID_box"] =  QString(xpre_parsed_sol.vv_out_unpacked_boxes[0][0].c_str());
        row["total_unpacked_box"] = QString(xpre_parsed_sol.vv_out_unpacked_boxes[0][1].c_str());
        unpacked_boxes.append(row);
    }

    return unpacked_boxes;

}

QJsonArray JsonParser::parse_grasp_packed_boxes(PackGRASP::OutputSolutionGRASP &xpre_parsed_sol)
{
    QJsonArray packed_boxes;

    for(size_t i = 0; i < xpre_parsed_sol.vv_out_packed_boxes.size(); i++)
    {
        QJsonObject row;
        row["ID_state"] =  QString(xpre_parsed_sol.vv_out_packed_boxes[0][0].c_str());
        row["ID_box"] = QString(xpre_parsed_sol.vv_out_packed_boxes[0][1].c_str());
        row["x"] = QString(xpre_parsed_sol.vv_out_packed_boxes[0][2].c_str());
        row["y"] = QString(xpre_parsed_sol.vv_out_packed_boxes[0][3].c_str());
        row["z"] = QString(xpre_parsed_sol.vv_out_packed_boxes[0][4].c_str());
        row["l"] = QString(xpre_parsed_sol.vv_out_packed_boxes[0][5].c_str());
        row["w"] = QString(xpre_parsed_sol.vv_out_packed_boxes[0][6].c_str());
        row["h"] = QString(xpre_parsed_sol.vv_out_packed_boxes[0][7].c_str());
        packed_boxes.append(row);
    }

    return packed_boxes;
}

QJsonArray JsonParser::parse_grasp_packed_states(PackGRASP::OutputSolutionGRASP &xpre_parsed_sol)
{

    QJsonArray packed_states;

    for(size_t i = 0; i < xpre_parsed_sol.vv_out_unpacked_boxes.size(); i++)
    {
        QJsonObject row;
        row["ID_state"] =  QString(xpre_parsed_sol.vv_out_packed_states[0][0].c_str());
        row["ID_box"] = QString(xpre_parsed_sol.vv_out_packed_states[0][1].c_str());
        row["x"] = QString(xpre_parsed_sol.vv_out_packed_states[0][2].c_str());
        row["y"] = QString(xpre_parsed_sol.vv_out_packed_states[0][3].c_str());
        row["z"] = QString(xpre_parsed_sol.vv_out_packed_states[0][4].c_str());
        row["l"] = QString(xpre_parsed_sol.vv_out_packed_states[0][5].c_str());
        row["w"] = QString(xpre_parsed_sol.vv_out_packed_states[0][6].c_str());
        row["h"] = QString(xpre_parsed_sol.vv_out_packed_states[0][7].c_str());
        packed_states.append(row);
    }

    return packed_states;
}

QJsonObject JsonParser::create_json_object(std::string xjson_input)
{
    QString qsJsonArgs( xjson_input.c_str() );
    QByteArray baJsonArgs = qsJsonArgs.toLocal8Bit();
    QJsonParseError json_error;
    QJsonDocument json_doc = QJsonDocument::fromJson( baJsonArgs,&json_error );

    if ( json_error.error != QJsonParseError::NoError )
    {
        QString qsError = "Error: invalid json data: ";
        qsError += json_error.errorString();
        throw std::invalid_argument( qsError.toStdString() );
    } // if ( json_error.error != QJsonParseError::NoError ){

    if ( json_doc.isNull() || !json_doc.isObject() )
    {
        QString qsError = "Error: invalid json object: ";
        qsError += json_error.errorString();
        throw std::invalid_argument( qsError.toStdString() );
    } // if ( json_doc.isNull() || !json_doc.isObject() ){

    return json_doc.object();
}

/**
 * @brief JsonParser::initialize_grasp_input_parameters
 * @param xn_boxes
 * Initialize the structures in the PackGrasp object, (vectors)
 */
void JsonParser::initialize_grasp_input_parameters(int xn_boxes)
{
    pg->vv_box_lwh = std::vector<std::vector<double>>(static_cast<size_t>(xn_boxes),std::vector<double>(3));
    pg->v_box_b = std::vector<int>(static_cast<size_t>(xn_boxes));
    pg->v_box_ID = std::vector<std::string>(static_cast<size_t>(xn_boxes));
    pg->vv_box_allowed_orientation = std::vector<std::vector<bool>>(static_cast<size_t>(xn_boxes),std::vector<bool>(6));
}
