#ifndef CONVERTLAZFILE_H
#define CONVERTLAZFILE_H

#include <string>

class ConvertLAZfile
{
public:
    ConvertLAZfile(std::string txtFilePath, std::string newFileName);

    void Process();
private:
    std::string mtxtFilePath{""};
    std::string mnewFileName{""};

    std::string color{"(1,0,0)"};
    std::string uv{"(1,1)"};
    int mHeightErrorLimit {300};
};

#endif // CONVERTLAZFILE_H
