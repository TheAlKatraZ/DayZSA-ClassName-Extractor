/*MIT License

Copyright (c) 2019 TheAlKatraZ

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/

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

  tinyxml2::XMLNode * pRootOrigTypes = pRootOrig->NextSibling();
  tinyxml2::XMLNode * pRootTypes = pRoot->NextSibling();

  std::cout << "Root loaded" << '\n';

  if (pRootOrig == nullptr) return tinyxml2::XML_ERROR_FILE_READ_ERROR;
  if (pRoot == nullptr) return tinyxml2::XML_ERROR_FILE_READ_ERROR;

  std::cout << "Iterating through all files" << '\n';

  std::vector<std::string> origNames;
  std::vector<std::string> names;

  for(tinyxml2::XMLElement * e = pRootOrigTypes->FirstChildElement("type"); e != NULL; e = e->NextSiblingElement("type"))
  {
      std::string name = e->Attribute("name");
      std::cout << name << '\n';
      origNames.push_back(name);
  }


  for(tinyxml2::XMLElement * e1 = pRootTypes->FirstChildElement("type"); e1 != NULL; e1 = e1->NextSiblingElement("type"))
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
