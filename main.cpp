
#include <tinyxml2.h>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

bool NameExist(std::vector<std::string> origNames, std::string name)
{
  for(int i = 0; i < origNames.size();i++)
  {
    if(origNames.at(i) == name)
    {
      return(true);
    }
  }
  std::cout << "false" << '\n';
  return(false);
}



int main()
{
  std::cout << "XML Extractor launched" << '\n';


  std::string pathToXMLOrig = "typesOrig.xml";
  std::string pathToXMLToExtract = "types.xml";
  std::string pathToOutput = "ClassNames.txt";

  tinyxml2::XMLDocument docOrig;
  tinyxml2::XMLDocument doc;

  std::cout << "Loading files" << '\n';

  tinyxml2::XMLError eResultOrig = docOrig.LoadFile(pathToXMLOrig.c_str());
  tinyxml2::XMLError eResult = doc.LoadFile(pathToXMLToExtract.c_str());

  std::cout << "Files loaded" << '\n';

  //XMLCheckResult(eResultOrig);
  //tinyxml2::XMLCheckResult(eResult);

  tinyxml2::XMLNode * pRootOrig = docOrig.FirstChild();
  tinyxml2::XMLNode * pRoot = doc.FirstChild();

  std::cout << "Root loaded" << '\n';

  if (pRootOrig == nullptr) return tinyxml2::XML_ERROR_FILE_READ_ERROR;
  if (pRoot == nullptr) return tinyxml2::XML_ERROR_FILE_READ_ERROR;

  std::cout << "Iterating through all files" << '\n';

  std::vector<std::string> origNames;
  std::vector<std::string> names;

  for(tinyxml2::XMLElement * e = pRootOrig->FirstChildElement("type"); e != NULL; e = e->NextSiblingElement("type"))
  {
      std::string name = e->Attribute("name");
      std::cout << name << '\n';
      origNames.push_back(name);
  }


  for(tinyxml2::XMLElement * e1 = pRoot->FirstChildElement("type"); e1 != NULL; e1 = e1->NextSiblingElement("type"))
  {
      std::string name = e1->Attribute("name");
      //std::cout << name << '\n';
      names.push_back(name);
  }


  std::cout << "Done listing all names" << '\n';

  std::vector<std::string> finalNames;

  for(int i = 0; i < names.size();i++)
  {
    if(!NameExist(origNames,names.at(i)))
    {
      finalNames.emplace_back(names.at(i));
    }
  }

  std::cout << "writing output file" << '\n';
  std::ofstream myfile;
  myfile.open(pathToOutput.c_str(), std::ofstream::out | std::ofstream::trunc);

  for(int i = 0; i < finalNames.size();i++)
  {
    std::cout << finalNames.at(i) << '\n';
    myfile << finalNames.at(i) << '\n';
  }

  myfile.close();

  std::cout << "done" << '\n';

  return 0;

}