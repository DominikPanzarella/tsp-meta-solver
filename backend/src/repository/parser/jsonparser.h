#pragma once

#include "repository/parser/iparser.h"
#include "repository/parser/jsonnode.h"

#include "repository/configuration2/config/nearestinsertiongeneralsetting.h"


class JsonParser : public IParser {
public:

    JsonParser() = default;

    virtual JSON read(const std::string& file_path) override;

    JSON getJson();


protected:

    JSON m_json;

private:
    std::shared_ptr<NearestInsertionGeneralSetting> m_nearestInsertion;

    


};