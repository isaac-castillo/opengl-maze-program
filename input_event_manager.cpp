#include "input_event_manager.hpp"
#include <optional>
//sample

#include "MoveAction.hpp"
#include <unordered_map>
#include <string>
#include <iostream>
namespace input
{

    ActionBinding::ActionBinding(ActionRequest action_) : action(action_)
    {
    }

    void ActionBinding::add_activation_requirement(const InputEvents &event, const ActionChoice &choice, const Order &order, ActionRequest request)
    {

        activations.push_back({event, choice, order, request});
    }

    ActionRequest ActionBinding::get_request() const
    {
        return action;
    }

    const Actions &ActionBinding::get_activations() const
    {
        return activations;
    }

    void InputEventManager::loadBindings(const std::string &filename)
    {

        ActionBinding *binding = new ActionBinding(ActionRequest::MoveCamera);
        binding->add_activation_requirement(InputEvents::Press, GLFW_KEY_LEFT_SHIFT, 0);
        binding->add_activation_requirement(InputEvents::Press, GLFW_KEY_E, 1);

        bindings["move_camera"] = binding;

        ActionBinding *binding2 = new ActionBinding(ActionRequest::CreateSquare);
        binding2->add_activation_requirement(InputEvents::Press, GLFW_KEY_LEFT_SHIFT, 0);
        binding2->add_activation_requirement(InputEvents::Press, GLFW_KEY_R, 1);

        bindings["create_square"] = binding2;

        ActionBinding *binding3 = new ActionBinding(ActionRequest::PlaceSquare);
        binding3->add_activation_requirement(InputEvents::Press, GLFW_MOUSE_BUTTON_LEFT, 0, ActionRequest::CreateSquare);

        bindings["place_square"] = binding3;
    }

    void InputEventManager::processInput(const GLFWInput &input)
    {
        // std::cout << "processing the following " << input.action << " "
        //           << " " << input.key << std::endl;
        ;
        if (input.action == GLFW_PRESS)
        {
            keysPressed++;
        }
        else if (input.action == GLFW_RELEASE)
        {
            keysPressed--;
        }

        if (keysPressed == 0)
        {
            clearActive();
            return;
        }
        if (!mouseData.has_value())
        {
            mouseData = input.data;
        }
        for (auto &named_binding : bindings)
        {

            auto &binding = *named_binding.second;

            const auto &activations = binding.get_activations();
            for (const auto &event : activations)
            {

                const auto &[input_event, choice, order, request] = event;
                if (InputEvents(input.action) != input_event)
                {
                    continue;
                }

                if (input.key != choice)
                {
                    continue;
                }
                if (request != ActionRequest::None && activeRequest != request)
                {
                    // std::cout << "skipping" << std::endl;
                    continue;
                }

                binding.count++;
                if (binding.count == binding.get_activations().size())
                {
                    std::cout << "binding identified: " << named_binding.first << std::endl;
                    auto result = binding.get_request();
                    ResolvedAction finalResult{result, mouseData};
                    action = finalResult;
                    activeRequest = ActionRequest::None;
                }
            }
        }
    }

    void InputEventManager::clearActive()
    {
        for (auto &named_binding : bindings)
        {

            auto &binding = *named_binding.second;
            binding.count = 0;
        }

        // activeRequest = ActionRequest::None;
    }
    bool InputEventManager::has_action() const
    {
        return action.has_value();
    }

    std::optional<ResolvedAction> InputEventManager::release_action()
    {
        std::optional<ResolvedAction> current_action = action;

        clearActive();
        action = std::nullopt;
        mouseData = std::nullopt;

        return current_action;
    }

    void InputEventManager::setRequest(ActionRequest request)
    {
        activeRequest = request;
    }

    Bindings InputEventManager::get_bindings()
    {
        return bindings;
    }

} // namespace input