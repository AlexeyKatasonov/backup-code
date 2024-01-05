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
#include "functions.h"

#include <iostream>
std::thread* thread = nullptr;
#pragma once
namespace MyApp

{





    std::string mainplay(int Rcase, int playlistnum)           // randomsongefromall = 0 // randomplaylist = 1 
                                                                                        // notrandomplaylist =2
    {

        filestuff mainstuff;

        int loop_num;
        if (Rcase == 0)
        {
            const std::string path = "\music\\*.mp3";
            mainstuff.vec_of_files = mainstuff.list_of_files_in_path(path.c_str());
            mainstuff.number_of_mp3 = mainstuff.number_of_files_in_path(path.c_str());
            mainstuff.vec_num_list = mainstuff.num_array(mainstuff.number_of_mp3, 1);

            loop_num = mainstuff.number_of_mp3;

        }

        else
        {

            const std::string path = "\pl\\*.pl";
            mainstuff.vec_of_files = mainstuff.list_of_files_in_path(path.c_str());
            mainstuff.number_of_playlists = mainstuff.number_of_files_in_path(path.c_str());
            mainstuff.number_of_songs_in_file = mainstuff.number_of_songs_in_playlist("\pl\\" + mainstuff.vec_of_files[playlistnum]);
            mainstuff.vec_num_list = mainstuff.num_array(mainstuff.number_of_songs_in_file, Rcase);
            mainstuff.vec_of_songs = mainstuff.list_of_songs_in_file("\pl\\" + mainstuff.vec_of_files[playlistnum]);
            loop_num = mainstuff.number_of_songs_in_file;

        }


        std::string mp3name;
        std::string songnameJ;

        for (uint32_t x = 0; x < loop_num; x++)
        {
            if (Rcase == 0)
            {

                songnameJ = mainstuff.vec_of_files[mainstuff.vec_num_list[x] - 1] + "\"";
                mp3name = "mp3_" + std::to_string(mainstuff.vec_num_list[x]);

            }
            else
            {


                mp3name = "mp3_" + std::to_string(mainstuff.vec_num_list[x]);
                if (Rcase == 2)
                    songnameJ = mainstuff.vec_of_songs[mainstuff.vec_num_list[x]] + ".mp3\"";
                else
                    songnameJ = mainstuff.vec_of_songs[mainstuff.vec_num_list[x] - 1] + ".mp3\"";
            }


            playsong(songnameJ, mp3name, "music\\");

        }
        return "-";



    }


    void RenderUI()
    {
        bool truej = true;

        ImGui::Begin("Main Stuff", &truej, ImGuiWindowFlags_MenuBar);
        if (ImGui::Button("Random Song"))
        {

            filestuff randomsongall;
            randomsongall.vec_of_songs = randomsongall.list_of_files_in_path("\music\\*.mp3");

            randomsongall.number_of_mp3 = randomsongall.number_of_files_in_path("\music\\*.mp3");

            //std::cout << randomsongall.number_of_mp3;

            thread = new std::thread(mainplay, 0, 0);
            thread->detach();

        }

        static ImGuiTableFlags flags1 = ImGuiTableFlags_BordersV;
        static bool show_headers = false;


        int fr_random_songe = 2;
        static bool randosonge = false;
        ImGui::Checkbox("Random Song Order in playlist", &randosonge);
        ImGui::SameLine();

        ImGui::Separator();
        if (randosonge == true)
        {
            fr_random_songe = 1;
        }

        if (ImGui::BeginTable("", 1, flags1))
        {

            filestuff tablethings;

            tablethings.vec_of_files = tablethings.list_of_files_in_path("\pl\\*.pl");

            for (int row = 0; row < tablethings.number_of_files_in_path("\pl\\*.pl") + 1; row++)
            {

                ImGui::TableNextRow();
                for (int column = 0; column < 1; column++)
                {
                    ImGui::TableSetColumnIndex(column);
                    if (row == 0)
                    {

                        ImGui::Text("ALL PLAYLISTS", ImGui::GetContentRegionAvail().x);
                    }
                    else
                    {

                        std::string playlistname = std::string((tablethings.vec_of_files)[row - 1].begin(), (tablethings.vec_of_files)[row - 1].end());

                        char buf[32];
                        sprintf(buf, playlistname.substr(0, playlistname.length() - 3).c_str(), column, row);

                        


                        if (ImGui::Button(buf, ImVec2(-FLT_MIN, 0.0f)))
                        {
                            thread = new std::thread(mainplay, fr_random_songe, row - 1);
                            thread->detach();

                        }
                    }

                }
            }
            ImGui::EndTable();


        }



        //ImGui::ShowDemoWindow();
        ImGui::End();

        ImGui::SetNextWindowPos(ImVec2(350, 0));
        bool j = true;



        ImGui::Begin("playlist stuff", &j, ImGuiWindowFlags_MenuBar);


       static char buf1[64] = "";

        ImGui::InputText("Playlist Name", buf1, 64);
        std::string fil_ename = buf1;
        std::ofstream ofstream1;

        if (ImGui::Button("Create"))
        {
            
            ofstream1.open("pl\\" + fil_ename+  ".pl");
            ofstream1.close();
        }
  
        bool addsonges = false;
        static bool osuidk = false;
        ImGui::Checkbox("add songes to playlist", &osuidk);
        ImGui::SameLine();

        ImGui::Separator();
        if (osuidk == true)
        {
            addsonges = true;
        }

        std::vector<std::string> new_playlist_songs_vec;

        filestuff osu;
        //osu.number_of_files_in_path("\music\\*.mp3");
        osu.number_of_mp3 = osu.number_of_files_in_path("\music\\*.mp3");
        osu.vec_of_songs = osu.list_of_files_in_path("\music\\*.mp3");



      
        ImGui::TextColored(ImVec4(1, 1, 0, 1), "ALL  SONGES");
        ImGui::BeginChild("Scrolling");
        for (int n = 0; n < osu.number_of_mp3; n++)
        {
            std::string jb = osu.vec_of_songs[n];
            //ImGui::Text(jb.c_str(), n+1);

            
            if (ImGui::Button(jb.substr(0, jb.length() - 4).c_str()))
            {
                //std::cout << jb;
                std::string mp3name = "mp3_" + std::to_string(n + 1);

                
                if (addsonges == false) //make_playlist == 
                {

                    

                    thread = new  std::thread(playsong, jb + "\"", mp3name, "music\\");

                    // thread = new std::thread(mainplay(0, 3));
                    thread->detach();
                }
                else
                {
                    std::ofstream ofstream2("pl\\" + fil_ename + ".pl", std::ios::app);
                    ofstream2 << jb.substr(0, jb.length() - 4);
                    ofstream2 << std::endl;
                    ofstream2.close();
                   
                }

            }
        }

        ImGui::EndChild();


        ImGui::End();                                                                                                                             //HERE


 
    }



    }


 


