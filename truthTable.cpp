#include "truthTable.h"


const char TruthToChar[4] = {'0', '1', '-', '?'};

int TruthTable::setNumVars(unsigned nV)
{
  numVars = nV;
  return 0;
}

int TruthTable::addEntry(const string &newEntry)
{
  if (newEntry.length() != numVars)
  {
    cout << "ERROR in truthTable::addEntry() - new entry has length "
         << newEntry.length() << " vs. numVars = " << numVars << endl;
    return -1;
  }
  
  vector<truthType> row(newEntry.length());
  
  for (unsigned i = 0; i < newEntry.length(); ++i)
  {
    switch(newEntry[i])
    {
      case '0': row[i] = ZERO; break;
      case '1': row[i] = ONE;  break;
      case '-': row[i] = DC;   break;
      default:
        cout << "ERROR in truthTable::addEntry() - invalid character "
             << newEntry[i] << endl;
        return -1;
    }
  }
  logic.push_back(row);
  
  return 0;
}

unsigned TruthTable::getNumEntries()
{
  return logic.size();
}

unsigned TruthTable::getNumVars()
{
  return numVars;
}

vector<string> TruthTable::getLogicString()
{
  string current;
  vector<string> return_vec;
  
  for (unsigned i = 0; i < logic.size(); ++i)
  {
    current = "";
    
    for (unsigned j = 0; j < logic[i].size(); ++j)
    {
      switch(logic[i][j])
      {
        case ZERO: current += "0"; break;
        case ONE:  current += "1"; break;
        case DC:   current += "-"; break;
        default:
          break;
      }
    }
    
    return_vec.push_back(current);
  }
  
  return return_vec;
}

int TruthTable::print()
{
  for (unsigned i = 0; i < logic.size(); ++i)
  {
    for (unsigned j = 0; j < logic[i].size(); ++j)
    {
      switch(logic[i][j])
      {
        case ZERO: cout << "0"; break;
        case ONE:  cout << "1"; break;
        case DC:   cout << "-"; break;
        default:
          cout << "ERROR in truthTable::printTable() - invalid character "
               << logic[i][j] << endl;
          return -1;
      }
    }
    cout << " 1" << endl;
  }
  return 0;
}

int TruthTable::clear()
{
  logic.clear();
  return 0;
}

