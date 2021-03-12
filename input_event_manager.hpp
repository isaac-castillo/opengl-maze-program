#ifndef __input_event_manager__
#define __input_event_manager__

#include <unordered_map>
#include <vector>
#include "action.hpp"
#include <tuple>
#include <optional>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
namespace input
{

    enum class InputEvents
    {

        Press = GLFW_PRESS,
        Repeat = GLFW_REPEAT

    };

    enum class ActionRequest
    {

        MoveCamera = 0,
        CreateSquare,
        PlaceSquare,
        None
    };

    using ActionChoice = int;
    using Order = int;
    using Actions = std::vector<std::tuple<InputEvents, ActionChoice, Order, ActionRequest>>;

    class ActionBinding
    {
    public:
        ActionBinding(ActionRequest action);
        ActionBinding(const ActionBinding &) = default;
        void add_activation_requirement(const InputEvents &event, const ActionChoice &choice, const Order &order = 0, ActionRequest = ActionRequest::None);
        const Actions &get_activations() const;
        int count{0};
        ActionRequest get_request() const;

    private:
        ActionRequest action;
        Actions activations;
    };

    struct MouseInput
    {
        double mouseX;
        double mouseY;
    };

    struct GLFWInput
    {
        int key;
        int action;
        std::optional<MouseInput> data;
        ActionRequest request = ActionRequest::None;
    };

    using Bindings = std::unordered_map<std::string, ActionBinding *>;
    using ResolvedAction = std::pair<ActionRequest, std::optional<MouseInput>>;

    class InputEventManager
    {

    private:
        Bindings bindings;
        std::optional<MouseInput> mouseData;
        std::optional<ResolvedAction> action;
        int keysPressed = 0;

        ActionRequest activeRequest = ActionRequest::None;

    public:
        void loadBindings(const std::string &filename);
        void processInput(const GLFWInput &input);
        bool has_action() const;
        std::optional<ResolvedAction> release_action();
        void clearActive();
        void setRequest(ActionRequest request);
        Bindings get_bindings();
    };

} // namespace input
#endif