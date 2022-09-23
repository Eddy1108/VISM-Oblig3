#include "convertlazfile.h"
#include "vertex.h"

ConvertLAZfile::ConvertLAZfile(std::string txtFilePath, std::string newFileName)
    : mtxtFilePath(txtFilePath), mnewFileName(newFileName)
{

}

void ConvertLAZfile::Process()
{

    //Gets file by filename
    std::ifstream inn;
    inn.open(mtxtFilePath.c_str());

    std::ofstream ut;
    ut.open(mnewFileName.c_str());

    int numberOfLines{0};
    //Debug lines
    if(!inn.is_open())
        std::cout << "textFile not found\n";
    if(!ut.is_open())
        std::cout << "new file not made\n";

    //Find the amount of vertices
    if (inn.is_open() && ut.is_open())
    {
        std::string str;

        while (std::getline(inn, str, '\n'))
        {
            numberOfLines++;
        }
        inn.close();
    }
     inn.open(mtxtFilePath.c_str());

    //Reformat vertices
    if (inn.is_open() && ut.is_open())
    {
        //ut << std::to_string(numberOfLines) << std::endl;

        std::string str;

        int codeLine = 0;
        while (std::getline(inn, str, '\n'))
        {
            codeLine++;
            std::string var[3];
            int n = 0;
            for(int i = 0; i < str.length(); i++){
                if(str.at(i) == ' ')
                    n++;
                else
                    var[n] += str[i];
            }
            // Process str
            if(std::stof(var[2]) >= mHeightErrorLimit){ // Inkluderer ikke linjen om høyden er større en 300.
                std::cout << "Height error, line " << codeLine << std::endl;
            }
            else{
                //ut << "(" << var[0] << "," << var[1] << "," << var[2] << ") " << color << " " << uv << std::endl;
                ut << var[0] << " " << var[1] << " " << var[2] << std::endl;
            }

        }

        inn.close();
        ut.close();
    }
    std::cout << "Done converting new file\n";
}
