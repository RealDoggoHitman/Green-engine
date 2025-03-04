#pragma once

#include "Shader_base.g.h"

namespace winrt::Vulkan::implementation
{
    struct Shader_base : Shader_baseT<Shader_base>
    {
        Shader_base() 
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void ClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::Vulkan::factory_implementation
{
    struct Shader_base : Shader_baseT<Shader_base, implementation::Shader_base>
    {
    };
}
