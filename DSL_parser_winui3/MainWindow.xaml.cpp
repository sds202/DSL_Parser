#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

#include <winrt/Windows.Web.Http.h>
#include <winrt/Windows.Web.Http.Headers.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Microsoft.UI.Xaml.Media.h>
#include <winrt/Windows.UI.h>
#include <winrt/Microsoft.UI.Xaml.Input.h>
#include <winrt/Windows.System.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Microsoft.UI.h>
#include <winrt/Windows.System.Threading.h>
#include <winrt/Microsoft.UI.Dispatching.h>
#include <winrt/Microsoft.UI.Windowing.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Microsoft::UI::Xaml::Media;
using namespace Windows::Web::Http;
using namespace Windows::Foundation;

// Helper to switch back to the UI thread in WinUI 3
struct ResumeOnUIThread
{
    Microsoft::UI::Dispatching::DispatcherQueue m_dispatcher;
    bool await_ready() const { return m_dispatcher.HasThreadAccess(); }
    void await_suspend(std::coroutine_handle<> handle) const
    {
        m_dispatcher.TryEnqueue([handle] { handle.resume(); });
    }
    void await_resume() const {}
};

namespace winrt::DSL_parser_winui3::implementation
{
    MainWindow::MainWindow()
    {
        // Xaml objects should not call InitializeComponent during construction.
        // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        
        // Set initial size
        auto appWindow = AppWindow();
        if (appWindow)
        {
            appWindow.Resize({ 618, 1000 });
        }
    }

    void MainWindow::OnSendClick(Windows::Foundation::IInspectable const&, RoutedEventArgs const&)
    {
        hstring text = MessageInput().Text();
        if (text.empty()) return;

        AppendMessage(text, true);
        SendMessageAsync(text);
        MessageInput().Text(L"");
    }

    void MainWindow::OnInputKeyDown(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::Input::KeyRoutedEventArgs const& args)
    {
        if (args.Key() == Windows::System::VirtualKey::Enter)
        {
            OnSendClick(sender, nullptr);
        }
    }

    fire_and_forget MainWindow::SendMessageAsync(hstring message)
    {
        auto weak_this = get_weak();
        try
        {
            HttpClient client;
            Uri uri{ L"http://localhost:8080" };
            HttpStringContent content{ message, Windows::Storage::Streams::UnicodeEncoding::Utf8, L"text/plain" };

            HttpResponseMessage response = co_await client.PostAsync(uri, content);
            
            if (response.IsSuccessStatusCode())
            {
                hstring responseText = co_await response.Content().ReadAsStringAsync();
                if (auto strong_this = weak_this.get())
                {
                    strong_this->AppendMessage(responseText, false, true);
                }
            }
            else
            {
                if (auto strong_this = weak_this.get())
                {
                    strong_this->AppendMessage(L"Error: " + to_hstring((int)response.StatusCode()), false, true);
                }
            }
        }
        catch (hresult_error const& ex)
        {
            if (auto strong_this = weak_this.get())
            {
                strong_this->AppendMessage(L"Exception: " + ex.message(), false, true);
            }
        }
    }

    void MainWindow::AppendMessage(hstring const& message, bool isUser, bool animate)
    {
        Border border;
        border.CornerRadius({ 12, 12, 12, 12 });
        border.Padding({ 12, 8, 12, 8 });
        border.Margin({ 0, 6, 0, 6 });

        TextBlock textBlock;
        textBlock.TextWrapping(TextWrapping::Wrap);
        textBlock.MaxWidth(600);
        textBlock.FontSize(16);

        if (isUser)
        {
            textBlock.Text(message);
            border.Background(SolidColorBrush(Windows::UI::Color{ 255, 0, 120, 215 }));
            textBlock.Foreground(SolidColorBrush(Microsoft::UI::Colors::White()));
            border.HorizontalAlignment(HorizontalAlignment::Right);
        }
        else
        {
            // Transparent background for bot
            border.Background(SolidColorBrush(Microsoft::UI::Colors::Transparent()));
            textBlock.Foreground(SolidColorBrush(Microsoft::UI::Colors::Black()));
            border.HorizontalAlignment(HorizontalAlignment::Left);
            
            if (animate)
            {
                textBlock.Text(L"");
                TypewriteTextAsync(textBlock, message);
            }
            else
            {
                textBlock.Text(message);
            }
        }

        border.Child(textBlock);
        ChatPanel().Children().Append(border);
        
        ChatPanel().UpdateLayout();
        ChatScrollViewer().ChangeView(nullptr, ChatScrollViewer().ScrollableHeight(), nullptr);
    }

    fire_and_forget MainWindow::TypewriteTextAsync(TextBlock textBlock, hstring message)
    {
        auto weak_this = get_weak();
        std::wstring fullText = message.c_str();
        std::wstring currentText = L"";

        for (wchar_t c : fullText)
        {
            currentText += c;
            // Switch to UI thread to update text
            co_await ResumeOnUIThread(DispatcherQueue());
            textBlock.Text(currentText.c_str());
            
            // Scroll to bottom as we type
            if (auto strong_this = weak_this.get())
            {
                 strong_this->ChatScrollViewer().ChangeView(nullptr, strong_this->ChatScrollViewer().ScrollableHeight(), nullptr);
            }

            // Delay
            co_await winrt::resume_after(std::chrono::milliseconds(30));
        }
    }
}
