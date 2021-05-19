#pragma once

#include <vector>
#include "stringwrapper.hpp"


std::vector<int> PrefixFunction(const ConcatenatedStringsWrapper& s);

std::vector<int> KnutMorrisPratt(const ConcatenatedStringsWrapper& source,
                                 const ConcatenatedStringsWrapper& substring);

int CycleShiftDetect(const std::string& source,
                     const std::string& substring);