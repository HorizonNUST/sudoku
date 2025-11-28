# Code Design

- Folders name correspond directly to the namespaces of the classes.
  - e.g `engine/gui/elements/UIElement.hpp` corresponds to `engine::gui::elements::UIElement` class.
  - **EXCEPTION:** `utils/constants.hpp` has namespace `CONSTANTS`.

## Class

- Class names are in `PascalCase`.
  - e.g `MainLayoutGroup` in `MainLayoutGroup.hpp`.

- Private Member variables are prefixed with `m_` and are in `snake_case`.
  - e.g `m_main_menu_layout` in `MainLayoutGroup` class.

- Private Member functions are in `camelCase` with no `m_` prefix.
  - e.g `createMainMenuLayout()` in `MainLayoutGroup` class.

- Public Member Variables should not be used.
  - If necessary, use `GetX` and `SetX` functions as inline; `X` being the variable name in `PascalCase`.

- Public Member functions are in `PascalCase`.
  - e.g `ClearLayout()` in `UILayout` class.


### EXAMPLE

```cpp
class ExampleClass
{
private:
    int m_example_variable = 0;
    void exampleFunction();
    
public:
    ExampleClass();
    ~ExampleClass();

    void DoSomething();

    inline int GetExampleVariable() const { return m_example_variable; }
    inline void SetExampleVariable(int value) { m_example_variable = value; }
};
```
