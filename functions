#include "Appthing.h"
#include "imgui.h"
#include <Windows.h>
#include <string>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <stdexcept>
#include <limits>
#include <stdlib.h>
#include <fileapi.h>    
#include <stdlib.h>     
#include <time.h>
#pragma once

#include <iostream>




    
void  playsong( std::string& songname,  std::string& mp3, const std::string& filepathextra) //
{
    // play mp3 + filepath thing covert to LPCWSTR thinfg idk	// play mp3 + filepath thing covert to LPCWSTR thinfg idk
    std::string filepath = "open \"" + filepathextra;

    filepath += songname + " type mpegvideo alias " + mp3;

    //std::cout << filepath;
    // std::string stemp = std::string(filepath.begin(), filepath.end());

    std::string playmp3 = "play " + mp3;
    //  std::string stemp2 = std::string(playmp3.begin(), playmp3.end());

    const std::string playmp3wait = "play " + mp3 + " wait";
    // const wchar_t* stemp3 = playmp3wait.c_str(); //std::string stemp3 = std::string(playmp3wait.begin(), playmp3wait.end());

    std::string playmp3close = "close " + mp3;
    // std::string stemp4 = std::string(playmp3close.begin(), playmp3close.end());


    std::string playmp3test = "pause " + mp3;

    //
 
    mciSendString(filepath.c_str(), NULL, 0, NULL);
    mciSendString(playmp3.c_str(), NULL, 0, NULL);
    mciSendString(playmp3wait.c_str(), NULL, 0, NULL);
    //mciSendString(playmp3test.c_str(), NULL, 0, NULL);

    mciSendString(playmp3close.c_str(), NULL, 0, 0);
}

    class filestuff
    {
    public: //functions

        std::vector<std::string> list_of_files_in_path(const LPCSTR& j)
        {
            std::string songname;
            std::vector<std::string> listOfFiles;
            LPCSTR filer = j;
            WIN32_FIND_DATA FindFileData;
            HANDLE findfile;
            findfile = FindFirstFile(filer, &FindFileData);
            int numberoffiles = 1;

            if (INVALID_HANDLE_VALUE == findfile)
            {
                std::cout << "error" << GetLastError() << std::endl;
            }
            else
            {
                listOfFiles.push_back(FindFileData.cFileName);
            }

            while (FindNextFileA(findfile, &FindFileData))
            {
                listOfFiles.push_back(FindFileData.cFileName);
                numberoffiles++;
            }
            FindClose(findfile);
            return listOfFiles;
        }

        int number_of_files_in_path(const LPCSTR& j)
        {
            std::string songname;
            std::vector<std::string> listOfFiles;                          //"\C:\\Users\\User\\Desktop\\Diabarha high quality\\*.mp3"
            LPCSTR filer = j;
            WIN32_FIND_DATA FindFileData;
            HANDLE findfile;
            findfile = FindFirstFile(filer, &FindFileData);
            int numberoffiles = 1;

            if (INVALID_HANDLE_VALUE == findfile)
            {
                std::cout << "error" << GetLastError() << std::endl;
            }
            else
            {
                listOfFiles.push_back(FindFileData.cFileName);
            }

            while (FindNextFileA(findfile, &FindFileData))
            {
                listOfFiles.push_back(FindFileData.cFileName);
                numberoffiles++;
            }
            FindClose(findfile);
            return numberoffiles;
        }

        int number_of_songs_in_playlist(std::string& filepath)
        {
            std::ifstream file(filepath);
            std::string wabungus;

            int x = 0;
            while (!file.eof()) {

                std::getline(file, wabungus);
                x++;
            }

            return x;
        }

        std::vector<std::string> list_of_songs_in_file(std::string& filepath)
        {
            std::ifstream file(filepath);
            std::vector<std::string> filenames;
            std::string wabungus;
            int x = 0;
            while (!file.eof()) {

                std::getline(file, wabungus);
                filenames.push_back(wabungus);
                x++;
            }

            return filenames;
        }

        std::vector<int> num_array(int number_of_files, int Rcase)       // 1 for rand 2 for not rand
        {
            std::vector<int> value;
            /// int* value = new int[number_of_files];
            int n;

            //std::cout <<    "h\n";

            if (Rcase == 1)
            {


                srand(time(NULL)); //always seed your RNG before using it

                //generate random numbers:
                for (int i = 0; i < number_of_files; i++)
                {
                    bool check; //variable to check or number is already used
                   // int n; //variable to store the number in
                    do
                    {

                        n = rand() % number_of_files + 1;
                        //check or number is already used:
                        check = true;
                        for (int j = 0; j < i; j++)
                            if (n == value[j]) //if number is already used
                            {
                                check = false; //set check to false
                                break; //no need to check the other elements of value[]
                            }
                    } while (!check); //loop until new, unique number is found

                    //std::cout << n << std::endl;

                    value.push_back(n); //store the generated number in the array
                    //std::cout << value[i] << std::endl;

                }

            }
            else
            {
                for (int x = 0; x < number_of_files; x++)
                {
                    value.push_back(x);
                }
            }

            return value;

        }



    public: // var
        int number_of_playlists;
        int number_of_mp3;
        int number_of_songs_in_file;

        std::vector<std::string> vec_of_files;
        //std::vector<std::string> vec_of_playlists;
        std::vector<std::string> vec_of_songs;
        std::vector<int>vec_num_list;

    }; 
