#include "imgui_ui.hpp"

#include <vector>
#include "input_event_manager.hpp"
#include "primitive.hpp"
#include "camera.hpp"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

#include <glm/gtx/string_cast.hpp>
void ImguiUI::displayKeybinds(const input::Bindings &bindings, bool *p_open)
{

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;
    ImGui::Begin("Action Bindings", p_open, window_flags);

    // ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_MenuBar;

    ImGui::BeginChild("Bindings", ImGui::GetContentRegionAvail(), true, window_flags);

    for (auto &binding : bindings)
    {

        ImGui::Text("%s:", binding.first.c_str());
        ImGui::SameLine();
        for (auto &event : binding.second->get_activations())
        {
            const auto &[input_event, choice, order, request] = event;

            const char *text;
            if (choice == 340)
                text = "LSHIFT";
            else
                text = glfwGetKeyName(choice, 0);
            ImGui::Text("%s ", text);
            ImGui::SameLine();
        }
        ImGui::NewLine();
    }
    ImGui::EndChild();

    ImGui::End();
}

void ImguiUI::displayCamera(maze_gl::camera &cam, bool *p_open)
{
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoResize;

    // ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_MenuBar;

    ImGui::SetNextWindowSize(ImVec2(500, 440), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("Camera in Scene", p_open, window_flags))
    {

        ImGui::BeginGroup();
        ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing())); // Leave room for 1 line below us
        ImGui::Text("Eye");
        ImGui::PushItemWidth(80);

        ImGui::SliderFloat("X##eye", &cam.eye.x, -5.0f, 5.0f);
        ImGui::SameLine();
        ImGui::SliderFloat("Y##eye", &cam.eye.y, -5.0f, 5.0f);
        ImGui::SameLine();
        ImGui::SliderFloat("Z##eye", &cam.eye.z, -5.0f, 5.0f);
        ImGui::PopItemWidth();

        ImGui::NewLine();
        ImGui::Text("At");
        ImGui::PushItemWidth(80);

        ImGui::SliderFloat("X##at", &cam.at.x, 0.0f, 5.0f);
        ImGui::SameLine();
        ImGui::SliderFloat("Y##at", &cam.at.y, 0.0f, 5.0f);
        ImGui::SameLine();
        ImGui::SliderFloat("Z##at", &cam.at.z, 0.0f, 5.0f);
        ImGui::PopItemWidth();

        ImGui::NewLine();
        ImGui::Text("Up");
        ImGui::PushItemWidth(80);

        ImGui::SliderFloat("X##up", &cam.up.x, 0.0f, 5.0f);
        ImGui::SameLine();
        ImGui::SliderFloat("Y##up", &cam.up.y, 0.0f, 5.0f);
        ImGui::SameLine();
        ImGui::SliderFloat("Z##up", &cam.up.z, 0.0f, 5.0f);
        ImGui::PopItemWidth();

        ImGui::EndChild();
        ImGui::EndGroup();
    }

    ImGui::End();
}

void ImguiUI::displayShapes(std::vector<Primitive> &shapes, bool *p_open, Primitive *& selected_shape)
{

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoResize;

    // ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_MenuBar;

    ImGui::SetNextWindowSize(ImVec2(500, 440), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("Objects in Scene", p_open, window_flags)) 
    {

        if (shapes.size() == 0)
        {
            ImGui::Text("No Shapes in Scene!");
        }
        else
        {
            // Left
            static int selected = 0;
            {
                ImGui::BeginChild("left pane", ImVec2(150, 0), true);
                for (int i = 0; i < shapes.size(); i++)
                {
                    char label[128];
                    sprintf(label, "Shape %d", shapes[i]._VAO);
                    if (ImGui::Selectable(label, selected == i)){
                        selected = i;
                        selected_shape = &shapes[i];
                    }
                }
                ImGui::EndChild();
            }
            ImGui::SameLine();

            // Right
            {

                auto &transform = shapes[selected]._transform;

                ImGui::BeginGroup();
                ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing())); // Leave room for 1 line below us
                ImGui::Text("Scale");
                ImGui::PushItemWidth(80);

                ImGui::SliderFloat("X##scale", &transform.scale.x, 0.0f, 5.0f);
                ImGui::SameLine();
                ImGui::SliderFloat("Y##scale", &transform.scale.y, 0.0f, 5.0f);
                ImGui::SameLine();
                ImGui::SliderFloat("Z##scale", &transform.scale.z, 0.0f, 5.0f);
                ImGui::PopItemWidth();

                ImGui::NewLine();
                ImGui::Text("Rotation");
                ImGui::PushItemWidth(80);

                ImGui::SliderFloat("X##rotate", &transform.rotation.x, 0.0f, 360.0f);
                ImGui::SameLine();
                ImGui::SliderFloat("Y##rotate", &transform.rotation.y, 0.0f, 360.0f);
                ImGui::SameLine();
                ImGui::SliderFloat("Z##rotate", &transform.rotation.z, 0.0f, 360.0f);
                ImGui::PopItemWidth();

                ImGui::NewLine();
                ImGui::Text("Translation");
                ImGui::PushItemWidth(80);

                ImGui::SliderFloat("X##translate", &transform.translation.x, -5.0f, 5.0f);
                ImGui::SameLine();
                ImGui::SliderFloat("Y##translate", &transform.translation.y, -5.0f, 5.0f);
                ImGui::SameLine();
                ImGui::SliderFloat("Z##translate", &transform.translation.z, -5.0f, 5.0f);
                ImGui::PopItemWidth();

                auto comp = shapes[selected].get_transform().compute();
                ImGui::Text("%s", glm::to_string(comp).c_str());
                ImGui::EndChild();
                ImGui::EndGroup();
            }
        }
    }
    ImGui::End();
}
