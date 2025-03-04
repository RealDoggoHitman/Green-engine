#pragma once

#include "Shaders_base.g.h"

namespace winrt::Vulkan::implementation
{
    struct Shaders_base : Shaders_baseT<Shaders_base>
    {
        Shaders_base() 
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
    struct Shaders_base : Shaders_baseT<Shaders_base, implementation::Shaders_base>
    {
    };
}
