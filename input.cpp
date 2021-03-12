
// #include "input.hpp"
// #include "action.hpp"

// #include <memory>

// namespace maze_gl
// {

//     Input::Input()
//     {
//     }
//     bool Input::has_action()
//     {
//         return current_action != nullptr;
//     }
//     ActionRequest Input::get_action()
//     {
//         auto action = std::move(current_action);
//         current_action = nullptr;
//         return action;
//     }

//     void Input::set_action(ActionRequest action)
//     {
//         current_action = action;
//     }

// } // namespace maze_gl