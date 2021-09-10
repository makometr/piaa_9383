#include <iostream>
#include <vector>

#define KMP 1

void print(std::vector<int>& numbers) {
  for (int i = 0; i < numbers.size(); i++) {
    if (i == 0)
      std::cout << numbers[i];
    else
      std::cout << "," << numbers[i];
  }
  std::cout << "\n";
}

std::vector<int> prefixFunction(const std::string& str) {
  std::vector<int> prefixValues(str.length());
  int counter = 0;
  for (int i = 1; i < str.size(); i++) {
    if (str[counter] == str[i]) {
      prefixValues[i] = ++counter;
      continue;
    }
    if (counter == 0) {
      prefixValues[i] = 0;
      continue;
    }
    counter = prefixValues[counter-1];
    i--;
  }
  return prefixValues;
}

std::vector<int> kmp(std::string& sample, std::string& text) {
  std::vector<int> result;
  std::vector<int> samplePrefixValues = prefixFunction(sample);
  int sampleInd = 0;
  for (int textInd = 1; textInd < text.size(); textInd++) {
    while ((sampleInd > 0) and (text[textInd] != sample[sampleInd+1])) {
      sampleInd = samplePrefixValues[sampleInd];
    }
    if (text[textInd] == sample[sampleInd+1])
      sampleInd++;
    if (sampleInd == sample.size()-1) {
      result.push_back(textInd-(int)sample.size()+1);
      sampleInd = samplePrefixValues[sampleInd];
    }
  }
  if (result.empty()) {
    result.push_back(-1);
    return result;
  }
  return result;
}

int isCyclicShift(std::string& sample, std::string& text) {
  if(sample.length()!=text.length())
    return -1;
  std::vector<int> samplePrefixValues = prefixFunction(sample);
  int sampleInd = 0;
  for (int textInd = 1; textInd < 2*text.size(); textInd++) {
    while ((sampleInd > 0) and (text[textInd%text.size()] != sample[sampleInd+1])) {
      sampleInd = samplePrefixValues[sampleInd];
    }
    if (text[textInd%text.size()] == sample[sampleInd+1])
      sampleInd++;
    if (sampleInd == sample.size()-1)
      return (textInd-(int)sample.size()+1)%(int)text.size();
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
