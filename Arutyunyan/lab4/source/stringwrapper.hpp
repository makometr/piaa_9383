#pragma once

struct MiniWrapper {
    const char* data;
    std::size_t size;

    char operator[](std::size_t index) const {
        return data[index];
    }
};

class StringWrapper {
public:
    StringWrapper(std::initializer_list<MiniWrapper> init_strings) {
        for (const auto& wrap : init_strings) {
            all_size += wrap.size;
            strings.push_back(wrap);
        }
    }

    std::size_t size() const {
        return all_size;
    }

    char operator[](std::size_t index) const {
        std::size_t current_size = 0;
        for (const auto& wrap : strings) {
            if (current_size + wrap.size > index)
                return wrap[index - current_size];
            current_size += wrap.size;
        }

        throw std::out_of_range("index is out of range!");
    }

private:
    std::vector<MiniWrapper> strings;
    std::size_t all_size = 0;
};