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

std::string JsonParser::parse_grasp_output()
{

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
void JsonParser::parse_grasp_input(std::string xjson_input)
{

    QJsonObject json_obj = create_json_object(xjson_input);
    int n_boxes = json_obj["num_box_type"].toInt();
    pg->n_box_type = n_boxes;
    initialize_grasp_input_parameters(n_boxes);

    QJsonArray M;
    M = json_obj["M"].toArray();
    pg->container_h = json_obj["container_h"].toDouble();
    pg->container_l = json_obj["container_l"].toDouble();
    pg->container_w = json_obj["container_w"].toDouble();

    for(size_t i = 0; i < static_cast<size_t>(M.size()) ; i++)
    {
        QJsonArray col = M[static_cast<int>(i)].toArray();
        pg->vv_box_lwh[i][0] =                  col[0].toDouble();
        pg->vv_box_lwh[i][1] =                  col[1].toDouble();
        pg->vv_box_lwh[i][2] =                  col[2].toDouble();
        pg->v_box_b[i] =                        col[3].toInt();
        QString buffer =                        col[4].toString();
        pg->v_box_ID[i] = buffer.toStdString();
        pg->vv_box_allowed_orientation[i][0] =  col[5].toInt();
        pg->vv_box_allowed_orientation[i][1] =  col[6].toInt();
        pg->vv_box_allowed_orientation[i][2] =  col[7].toInt();
        pg->vv_box_allowed_orientation[i][3] =  col[8].toInt();
        pg->vv_box_allowed_orientation[i][4] =  col[9].toInt();
        pg->vv_box_allowed_orientation[i][5] =  col[10].toInt();
     }


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
