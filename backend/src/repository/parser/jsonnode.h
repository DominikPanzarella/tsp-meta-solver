#pragma once

#include "repository/parser/jsonnodeimpl.h"
#include <memory>

class JSON
{
public:
    explicit JSON(std::shared_ptr<JSONNodeImpl> impl);

    JSON();

    std::shared_ptr<JSON> operator[](const std::string &key) const;

    std::shared_ptr<JSON> operator[](int index) const;

    std::string dump(int indent = 2) const;

    bool contains(const std::string &key) const;

    bool is_object() const;

    bool is_array() const;
    
    std::vector<std::string> keys() const;

    std::vector<std::string> getArrayOfStrings() const;

    template <typename T>
    T get() const
    {
        return impl_->data.get<T>();
    }


    std::shared_ptr<JSONNodeImpl> impl_;
private:
    friend class JsonParser;
};