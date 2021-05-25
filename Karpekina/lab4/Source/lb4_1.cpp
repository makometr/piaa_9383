#include <iostream>
#include <vector>

using namespace std;


vector < int > CalculatingPrefixFunction (string Line)
{
  int LineLength = Line.length ();
  vector < int >prefixes (LineLength);
  prefixes[0] = 0;
  for (int i = 1; i < LineLength; i++)
    {
      int ActualLineLength = prefixes[i - 1];
      while (ActualLineLength > 0
	     && (Line[ActualLineLength] != Line[i]))
	ActualLineLength = prefixes[ActualLineLength - 1];
      if (Line[ActualLineLength] == Line[i])
	ActualLineLength++;
      prefixes[i] = ActualLineLength;
    }
  return prefixes;
}

void KnuthMorrisPratt (string FirstLine, string SecondLine, vector < int >&Result)
{
    vector<int> p = CalculatingPrefixFunction(FirstLine + "#");
    int FirstLineStep = 0;
    for(int SecondLineStep = 0; SecondLineStep < SecondLine.size(); ++SecondLineStep) 
    {
        while(FirstLineStep > 0 && FirstLine[FirstLineStep] != SecondLine[SecondLineStep]) 
            FirstLineStep = p[FirstLineStep-1];
        if(FirstLine[FirstLineStep] == SecondLine[SecondLineStep]) 
            FirstLineStep++;
        if(FirstLineStep == FirstLine.size())
            Result.push_back(SecondLineStep - FirstLine.size() + 1);
    }

}

int main ()
{
  vector < int >Result;
  string FirstLine, SecondLine;
  cin >> FirstLine;
  cin >> SecondLine;
  KnuthMorrisPratt (FirstLine, SecondLine, Result);
  if (!Result.size ())
    cout << -1;
  else
    {
      string separator;
      for (auto entry : Result)
      {
        cout << separator << entry;
        separator = ",";
      }
    }
  return 0;
}
