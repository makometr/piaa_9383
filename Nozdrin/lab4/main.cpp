#include <iostream>
#include <vector>

#define KMP 1

void print(std::vector<size_t> numbers) {
  for (int i = 0; i < numbers.size(); i++) {
    if (i == 0)
      std::cout << numbers[i];
    else
      std::cout << "," << numbers[i];
  }
  std::cout << "\n";
}

std::vector<size_t> prefixFunction(const std::string& str) {
  std::vector<size_t> prefixValues(str.length());
  for (int i = 1; i < str.size(); i++) {
    size_t counter = prefixValues[i-1];
    while (counter > 0 && str[counter] != str[i])
      counter = prefixValues[counter-1];
    if (str[i] == str[counter])
      counter++;
    prefixValues[i]=counter;
  }
  return prefixValues;
}

std::vector<size_t> kmp(std::string& sample, std::string& text) {
  std::vector<size_t> result;
  std::vector<size_t> samplePrefixValues = prefixFunction(sample);
  size_t sampleInd = 0;
  for (size_t textInd = 0; textInd < text.size(); textInd++) {
    if (text[textInd] == sample[sampleInd]) {
      sampleInd++;
      if (sampleInd == sample.size()) {
        result.push_back(textInd-sample.size()+1);
      }
      continue;
    }
    if (sampleInd == 0) continue;
    sampleInd = samplePrefixValues[sampleInd-1];
    textInd--;
  }
  if (result.empty())
    result.push_back(-1);
  return result;
}

int isCyclicShift(std::string& sample, std::string& text) {
  if (sample.length()!=text.length())
    return -1;
  if (sample == text)
    return 0;
  std::vector<size_t> result;
  std::vector<size_t> samplePrefixValues = prefixFunction(sample);
  size_t sampleInd = 0;
  for (size_t textInd = 0; textInd < 2*text.size(); textInd++) {
    if (text[textInd%text.size()] == sample[sampleInd]) {
      sampleInd++;
      if (sampleInd == sample.size()) {
        return textInd-sample.size()+1;
      }
      continue;
    }
    if (sampleInd == 0) continue;
    sampleInd = samplePrefixValues[sampleInd-1];
    textInd--;
  }
  return -1;
}


int main() {
  std::string sample, text;
  std::cin >> sample >> text;
#if KMP
  auto result = kmp(sample, text);
  print(result);
#else
  std:: cout << isCyclicShift(sample, text);
  return 0;
#endif
}
