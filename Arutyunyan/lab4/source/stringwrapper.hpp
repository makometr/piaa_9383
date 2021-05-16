#pragma once

struct StringWrapper {
    const char* data;
    std::size_t size_;

    StringWrapper(const std::string& str)
        : data(str.data()), size_(str.size()) {}

    StringWrapper(const char* c_str, std::size_t size)
        : data(c_str), size_(size) {}

    std::size_t size() const {
        return size_;
    }

    char operator[](std::size_t index) const {
        return data[index];
    }
};

class ConcatenatedStringsWrapper {
public:
    ConcatenatedStringsWrapper() = default;

    ConcatenatedStringsWrapper(std::initializer_list<StringWrapper> init_strings) {
        for (const auto& wrap : init_strings) {
            all_size += wrap.size();
            strings.push_back(wrap);
        }
    }

    ConcatenatedStringsWrapper(const StringWrapper& init_string) {
        strings.push_back(init_string);
        all_size += init_string.size();
    }

    ConcatenatedStringsWrapper(const std::string& str) {
        strings.emplace_back(str.data(), str.size());
        all_size += str.size();
    }

    std::size_t size() const {
        return all_size;
    }

    char operator[](std::size_t index) const {
        std::size_t current_size = 0;
        for (const auto& wrap : strings) {
            if (current_size + wrap.size() > index)
                return wrap[index - current_size];
            current_size += wrap.size();
        }

        throw std::out_of_range("index is out of range!");
    }

    ConcatenatedStringsWrapper operator+(const ConcatenatedStringsWrapper& init_string) const {
        ConcatenatedStringsWrapper updated;
        updated.all_size += all_size + init_string.size();
        updated.strings.insert(updated.strings.end(), strings.begin(), strings.end());
        updated.strings.insert(updated.strings.end(), init_string.strings.begin(), init_string.strings.end());
        return updated;
    }

    ConcatenatedStringsWrapper operator+(const StringWrapper& init_string) const {
        ConcatenatedStringsWrapper updated;
        updated.all_size += all_size + init_string.size();
        updated.strings.insert(updated.strings.end(), strings.begin(), strings.end());
        updated.strings.push_back(init_string);
        return updated;
    }

    ConcatenatedStringsWrapper operator+(const std::string& init_string) const {
        ConcatenatedStringsWrapper updated;
        updated.all_size += all_size + init_string.size();
        updated.strings.insert(updated.strings.end(), strings.begin(), strings.end());
        updated.strings.emplace_back(init_string);
        return updated;
    }

    std::string MakeString() const {
        std::string result;

        for (const auto& string_wrapper : strings) {
            result.append(string_wrapper.data, string_wrapper.size_);
        }

        return result;
    }

private:
    std::vector<StringWrapper> strings;
    std::size_t all_size = 0;
};