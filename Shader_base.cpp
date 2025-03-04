#include "pch.h"
#include "Shader_base.h"
#if __has_include("Shader_base.g.cpp")
#include "Shader_base.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::Vulkan::implementation
{
    int32_t Shader_base::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void Shader_base::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void Shader_base::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        Button().Content(box_value(L"Clicked"));
    }
}
