#pragma once

#include "MainWindow.g.h"

namespace winrt::DSL_parser_winui3::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow();

        void OnSendClick(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void OnInputKeyDown(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::Input::KeyRoutedEventArgs const& args);

    private:
        winrt::fire_and_forget SendMessageAsync(winrt::hstring message);
        void AppendMessage(winrt::hstring const& message, bool isUser, bool animate = false);
        winrt::fire_and_forget TypewriteTextAsync(Microsoft::UI::Xaml::Controls::TextBlock textBlock, winrt::hstring message);
    };
}

namespace winrt::DSL_parser_winui3::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
