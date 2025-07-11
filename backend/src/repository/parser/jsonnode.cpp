
#include "repository/parser/jsonnode.h"


JSON::JSON() : impl_(std::make_shared<JSONNodeImpl>(nlohmann::json{})) {}

JSON::JSON(std::shared_ptr<JSONNodeImpl> impl) : impl_(std::move(impl)) {}

std::shared_ptr<JSON> JSON::operator[](const std::string &key) const {
    return std::make_shared<JSON>(std::make_shared<JSONNodeImpl>(impl_->data.at(key)));
}

std::shared_ptr<JSON> JSON::operator[](int index) const {
    return std::make_shared<JSON>(std::make_shared<JSONNodeImpl>(impl_->data.at(index)));
}

std::string JSON::dump(int indent) const {
    return impl_->data.dump(indent);
}

bool JSON::contains(const std::string& key) const {
    return impl_->data.contains(key);
}

bool JSON::is_object() const {
    return impl_->data.is_object();
}

bool JSON::is_array() const {
    return impl_->data.is_array();
}

std::vector<std::string> JSON::keys() const {
    std::vector<std::string> result;
    for (auto& el : impl_->data.items()) {
        result.push_back(el.key());
    }
    return result;
}

std::vector<std::string> JSON::getArrayOfStrings() const {
    std::vector<std::string> result;
    if (is_array()) {
        for (const auto& item : impl_->data) {
            result.push_back(item.get<std::string>());
        }
    }
    return result;
}
