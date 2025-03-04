#include "pch.h"
#include "Shaders_base.h"
#if __has_include("Shaders_base.g.cpp")
#include "Shaders_base.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::Vulkan::implementation
{
    int32_t Shaders_base::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void Shaders_base::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void Shaders_base::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        Button().Content(box_value(L"Clicked"));
    }
}
