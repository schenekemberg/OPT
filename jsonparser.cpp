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

void JsonParser::parse_grasp_input(std::string xjson_input)
{

}
