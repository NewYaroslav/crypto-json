#include <iostream>
#include "ico.h"
#include "imgui.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui_internal.h"
#include "imgui-SFML.h"
#include "TextEditor.h"
#include "FileBrowser/ImGuiFileBrowser.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include <crypto-json/crypto-json.hpp>

#include "include/config.hpp"
#include "include/crypto-json-config.hpp"
#include "include/fonts.hpp"
#include "include/style.hpp"
#include "include/utility.hpp"
#include "include/imgui-addons.hpp"
#include "include/icon.hpp"

//#include <fstream>
//#include <streambuf>

CryptoJsonConfig cj_config;
crypto_json_editor::Config config;

int main() {
    HWND hConsole = GetConsoleWindow();
    ShowWindow(hConsole, SW_HIDE);

    /* инициализируем окно */
    sf::RenderWindow window(sf::VideoMode(config.start_window_width, config.start_window_height), config.window_name.c_str());
    window.setFramerateLimit(config.framerate);

    /* настраиваем внешний вид программы */
    window.setIcon(crypto_json_editor_icon_256x256.width,  crypto_json_editor_icon_256x256.height,  crypto_json_editor_icon_256x256.pixel_data);
    ImGui::SFML::Init(window, false);
    ImGui::StyleColorsDark();
    init_fonts();
    init_style();

    /* создаем браузер файловой системы и редактор текста */
    imgui_addons::ImGuiFileBrowser file_dialog;
    TextEditor editor;
	auto lang = TextEditor::LanguageDefinition::JSON();
	editor.SetLanguageDefinition(lang);
	crypto_json_editor::ErrorPopup error_popup("##ErrorPopup");

	/* запускаем основной цикл */
    sf::Clock delta_clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) {
                window.close();
            } else
            if (event.type == sf::Event::Resized) {
                sf::Vector2u window_size = window.getSize();
                if (window_size.x < config.start_window_width ||
                    window_size.y < config.start_window_height) {
                    window_size.x = std::max(window_size.x, (uint32_t)config.start_window_width);
                    window_size.y = std::max(window_size.y, (uint32_t)config.start_window_height);
                    window.setSize(window_size);
                }
            }
        }

        ImGui::SFML::Update(window, delta_clock.restart());

        const size_t window_width = window.getSize().x;
		const size_t window_height = window.getSize().y;

        auto cpos = editor.GetCursorPosition();

        // ImGui::SetWindowSize(ImVec2(800, 500), ImGuiCond_FirstUseEver);

        ImGui::SetNextWindowPos(ImVec2(0,0),ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(
            window_width,
            (window_height - config.indent_basement)),
            ImGuiCond_Always);
		ImGui::Begin("CryptoJsonMainMenu", nullptr,
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_MenuBar);
		// ImGui::SetWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);

        bool file_dialog_open = false, file_dialog_save = false;
        bool clipboard_error_dialog_open = false;
		if (ImGui::BeginMenuBar()) {
			if (ImGui::BeginMenu("File")) {
				if (ImGui::MenuItem("Open")) {
					file_dialog_open = true;
				}
				if (ImGui::MenuItem("Save", nullptr, nullptr, cj_config.is_init)) {
					/* сохраняем файл */
					auto text = editor.GetText();
                    bool is_save = false;
                    if (cj_config.use_encryption) {
                        if (crypto_json::check_ecb(cj_config.type)) {
                            is_save = crypto_json::save_file(cj_config.path, text, cj_config.key, cj_config.type, cj_config.use_brotly);
                        } else {
                            is_save = crypto_json::save_file(cj_config.path, text, cj_config.key, cj_config.iv, cj_config.type, cj_config.use_brotly);
                        }
                    } else {
                        is_save = crypto_json::save_file(cj_config.path, text, cj_config.use_brotly);
                    }
                    /* */
				}
				if (ImGui::MenuItem("Save as...")) {
					file_dialog_save = true;
				}
				if (ImGui::MenuItem("Quit", "Alt-F4"))
					break;
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Edit"))
			{
				bool ro = editor.IsReadOnly();
				if (ImGui::MenuItem("Read-only mode", nullptr, &ro))
					editor.SetReadOnly(ro);
				ImGui::Separator();

				if (ImGui::MenuItem("Undo", "ALT-Backspace", nullptr, !ro && editor.CanUndo()))
					editor.Undo();
				if (ImGui::MenuItem("Redo", "Ctrl-Y", nullptr, !ro && editor.CanRedo()))
					editor.Redo();

				ImGui::Separator();

				if (ImGui::MenuItem("Copy", "Ctrl-C", nullptr, editor.HasSelection()))
					editor.Copy();
				if (ImGui::MenuItem("Cut", "Ctrl-X", nullptr, !ro && editor.HasSelection()))
					editor.Cut();
				if (ImGui::MenuItem("Delete", "Del", nullptr, !ro && editor.HasSelection()))
					editor.Delete();
				if (ImGui::MenuItem("Paste", "Ctrl-V", nullptr, !ro && ImGui::GetClipboardText() != nullptr))
					editor.Paste();

				ImGui::Separator();

				if (ImGui::MenuItem("Select all", nullptr, nullptr))
					editor.SetSelection(TextEditor::Coordinates(), TextEditor::Coordinates(editor.GetTotalLines(), 0));

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("View"))
			{
				if (ImGui::MenuItem("Dark palette"))
					editor.SetPalette(TextEditor::GetDarkPalette());
				if (ImGui::MenuItem("Light palette"))
					editor.SetPalette(TextEditor::GetLightPalette());
				if (ImGui::MenuItem("Retro blue palette"))
					editor.SetPalette(TextEditor::GetRetroBluePalette());
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		ImGui::Text("%6d/%-6d %6d lines  | %s | %s | %s | %s", cpos.mLine + 1, cpos.mColumn + 1, editor.GetTotalLines(),
			editor.IsOverwrite() ? "Ovr" : "Ins",
			editor.CanUndo() ? "*" : " ",
			editor.GetLanguageDefinition().mName.c_str(), cj_config.path.c_str());

		editor.Render("TextEditor");
		ImGui::End();


		/*====================================================================*/
		ImGui::SetNextWindowPos(ImVec2(
            0,
            (window_height - config.indent_basement)),
            ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(
            window_width,
            config.indent_basement),
            ImGuiCond_Always);

        bool is_copy_json_to_clipboard_error = false;
        ImGui::Begin("##basement", NULL,
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoTitleBar);
        {
            if (ImGui::Button("validity##ButtonValidityJson")) {
                crypto_json::JsonSax json_sax;
                auto text = editor.GetText();
                std::cout << text << std::endl;
                std::string temp = crypto_json::strip_json_comments(text, true);
                std::cout << temp << std::endl;
                crypto_json::json::sax_parse(temp, &json_sax);

                TextEditor::ErrorMarkers markers;
                for (size_t i = 0; i < json_sax.errors.size(); ++i) {
                    int line = 0;
                    std::for_each(
                            temp.begin(),
                            temp.begin() + json_sax.errors[i].first + 1,
                            [&](char ch) {
                        if (ch == '\n') ++line;
                    });
                    std::cout << line << std::endl;
                    markers.insert(std::make_pair(line, json_sax.errors[i].second));
                }
                editor.SetErrorMarkers(markers);
            }

            ImGui::SameLine();

            if (ImGui::Button("copy JSON##ButtonCopyJson")) {
                if (!crypto_json_editor::copy_json_to_clipboard(editor.GetText())) {
                    error_popup.open("ERROR", "Error copying JSON string");
                }
            }

            ImGui::SameLine();

            if (ImGui::Button("copy formated JSON##ButtonCopyJson")) {
                if (!crypto_json_editor::copy_json_to_clipboard(editor.GetText(), true)) {
                    error_popup.open("ERROR", "Error copying JSON formatted string");
                }
            }
        } // basement
        ImGui::End();
        /*====================================================================*/


        /*====================================================================*/
        if(file_dialog_open) {
            ImGui::OpenPopup("Open File##PopupOpenFile");
        }
        if(file_dialog_save) {
            ImGui::OpenPopup("Save File##PopupSaveFile");
        }

        const size_t indent_file_dialog = 64;
        const size_t file_dialog_min_width = 750;
        const size_t file_dialog_min_height = 400;
        static bool decode_settings_save_file = false;

        if(file_dialog.showFileDialog(
                "Open File##PopupOpenFile",
                imgui_addons::ImGuiFileBrowser::DialogMode::OPEN,
                ImVec2((uint64_t)std::max(file_dialog_min_width, window_width - indent_file_dialog),
                    (uint64_t)std::max(file_dialog_min_height, window_height - indent_file_dialog)),
                ".text,.txt,.json,.dat,.bin,.hex,.cjson,.cj")){

            std::cout << file_dialog.selected_fn << std::endl;      // The name of the selected file or directory in case of Select Directory dialog mode
            std::cout << file_dialog.selected_path << std::endl;    // The absolute path to the selected file
            cj_config.path = file_dialog.selected_path;
            decode_settings_save_file = false;
            ImGui::OpenPopup("Decode Settings##PopupDecodeSettings");
        }

        if(file_dialog.showFileDialog(
                "Save File##PopupSaveFile",
                imgui_addons::ImGuiFileBrowser::DialogMode::SAVE,
                ImVec2((uint64_t)std::max(file_dialog_min_width, window_width - indent_file_dialog),
                    (uint64_t)std::max(file_dialog_min_height, window_height - indent_file_dialog)),
                ".text,.txt,.json,.dat,.bin,.hex,.cjson,.cj")){
            std::cout << file_dialog.selected_fn << std::endl;      // The name of the selected file or directory in case of Select Directory dialog mode
            std::cout << file_dialog.selected_path << std::endl;    // The absolute path to the selected file
            std::cout << file_dialog.ext << std::endl;              // Access ext separately (For SAVE mode)
            //Do writing of files based on extension here
            cj_config.path = file_dialog.selected_path;
            std::cout << cj_config.path << std::endl;
            decode_settings_save_file = true;
            ImGui::OpenPopup("Decode Settings##PopupDecodeSettings");
        }
        /*====================================================================*/

        /*====================================================================*/


        ImGui::SetNextWindowPos(ImVec2(
            ((window_width - config.decode_settings_width)/2),
            ((window_height - config.decode_settings_height)/2)),
            ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(
            config.decode_settings_width,
            config.decode_settings_height),
            ImGuiCond_Always);

        bool is_decode_settings = false;
        if (ImGui::BeginPopupModal(
                "Decode Settings##PopupDecodeSettings",
                NULL,
                ImGuiWindowFlags_NoMove |
                ImGuiWindowFlags_NoResize |
                ImGuiWindowFlags_NoCollapse |
                ImGuiWindowFlags_NoTitleBar)) {
            ImGui::Checkbox("broli##CheckboxBrotli", &cj_config.use_brotly);
            ImGui::Checkbox("encryption##CheckboxAES", &cj_config.use_encryption);

            if(!cj_config.use_encryption) {
                ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
                ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
            }

            const char* algorithm_type_items[] = { "ECB", "CBC", "CFB"};
            static int algorithm_type_item_current = 2;
            ImGui::Combo("AES algorithm type##ComboAesAlgorithmType", &algorithm_type_item_current, algorithm_type_items, IM_ARRAYSIZE(algorithm_type_items));

            const char* key_size_items[] = { "256", "192", "128"};
            const size_t key_size_value[] = { 32, 24, 16};
            static int key_size_item_current = 0;
            ImGui::Combo("key size##ComboKeySize", &key_size_item_current, key_size_items, IM_ARRAYSIZE(key_size_items));
            const size_t key_size = key_size_value[key_size_item_current];

            switch(algorithm_type_item_current) {
            case 0: // ECB
                switch(key_size_item_current) {
                case 0: // 256
                    cj_config.type = crypto_json::EncryptionAlgorithmType::USE_AES_ECB_256;
                    break;
                case 1:
                    cj_config.type = crypto_json::EncryptionAlgorithmType::USE_AES_ECB_192;
                    break;
                case 2:
                    cj_config.type = crypto_json::EncryptionAlgorithmType::USE_AES_ECB_128;
                    break;
                };
                break;
            case 1: // CBC
                switch(key_size_item_current) {
                case 0: // 256
                    cj_config.type = crypto_json::EncryptionAlgorithmType::USE_AES_CBC_256;
                    break;
                case 1:
                    cj_config.type = crypto_json::EncryptionAlgorithmType::USE_AES_CBC_192;
                    break;
                case 2:
                    cj_config.type = crypto_json::EncryptionAlgorithmType::USE_AES_CBC_128;
                    break;
                };
                break;
            case 2: // CFB
                switch(key_size_item_current) {
                case 0: // 256
                    cj_config.type = crypto_json::EncryptionAlgorithmType::USE_AES_CFB_256;
                    break;
                case 1:
                    cj_config.type = crypto_json::EncryptionAlgorithmType::USE_AES_CFB_192;
                    break;
                case 2:
                    cj_config.type = crypto_json::EncryptionAlgorithmType::USE_AES_CFB_128;
                    break;
                };
                break;
            };

            if (cj_config.key.size() != key_size) {
                cj_config.key.resize(key_size);
                std::string new_key = crypto_json::to_str_hex(cj_config.key);
                cj_config.clear_key_buffer();
                std::memcpy(cj_config.key_buffer, new_key.c_str(), new_key.size());
            }

            if (cj_config.iv.size() != cj_config.key.size()) {
                cj_config.iv.resize(cj_config.key.size());
                std::string new_iv = crypto_json::to_str_hex(cj_config.iv);
                cj_config.clear_iv_buffer();
                std::memcpy(cj_config.iv_buffer, new_iv.c_str(), new_iv.size());
            }

            ImGui::InputText("key##InputTextKey", cj_config.key_buffer, sizeof(cj_config.key_buffer),
                ImGuiInputTextFlags_CharsHexadecimal | ImGuiInputTextFlags_CharsUppercase);
            ImGui::SameLine();
            if (ImGui::Button("copy##ButtonKeyCopy")) {
                crypto_json::to_clipboard(crypto_json::to_str_hex(cj_config.key));
            }
            if (decode_settings_save_file) {
                ImGui::SameLine();
                if (ImGui::Button("generate##ButtonKeyGenerate")) {
                    crypto_json::generate_key_or_iv(cj_config.key);
                    std::string new_key = crypto_json::to_str_hex(cj_config.key);
                    cj_config.clear_key_buffer();
                    std::memcpy(cj_config.key_buffer, new_key.c_str(), new_key.size());
                }
            }

            if (!crypto_json::check_ecb(cj_config.type)) {
                ImGui::InputText("iv##InputTextIv", cj_config.iv_buffer, sizeof(cj_config.iv_buffer),
                ImGuiInputTextFlags_CharsHexadecimal | ImGuiInputTextFlags_CharsUppercase);
                ImGui::SameLine();
                if (ImGui::Button("copy##ButtonIvCopy")) {
                    crypto_json::to_clipboard(crypto_json::to_str_hex(cj_config.iv));
                }
                if (decode_settings_save_file) {
                    ImGui::SameLine();
                    if (ImGui::Button("generate##ButtonIvGenerate")) {
                        crypto_json::generate_key_or_iv(cj_config.iv);
                        std::string new_iv = crypto_json::to_str_hex(cj_config.iv);
                        cj_config.clear_iv_buffer();
                        std::memcpy(cj_config.iv_buffer, new_iv.c_str(), new_iv.size());
                    }
                }
            }

            /* переносим данные из cj_config.key_buffer и cj_config.iv_buffer
             * в cj_config.key и cj_config.iv
             */
            crypto_json::convert_hex_str_to_byte(cj_config.iv_buffer, cj_config.iv);
            crypto_json::convert_hex_str_to_byte(cj_config.key_buffer, cj_config.key);

            if(!cj_config.use_encryption) {
                ImGui::PopItemFlag();
                ImGui::PopStyleVar();
            }

            if (ImGui::Button("ok##ButtonOkPopupDecodeSettings")) {
                if (decode_settings_save_file) {
                    auto text = editor.GetText();
                    bool is_save = false;
                    if (cj_config.use_encryption) {
                        if (crypto_json::check_ecb(cj_config.type)) {
                            is_save = crypto_json::save_file(cj_config.path, text, cj_config.key, cj_config.type, cj_config.use_brotly);
                        } else {
                            is_save = crypto_json::save_file(cj_config.path, text, cj_config.key, cj_config.iv, cj_config.type, cj_config.use_brotly);
                        }
                    } else {
                        is_save = crypto_json::save_file(cj_config.path, text, cj_config.use_brotly);
                    }
                    if (is_save) {

                    }
                } else {
                    std::string temp;
                    //std::cout << crypto_json::to_str_hex(cj_config.key) << std::endl;
                    //std::cout << crypto_json::to_str_hex(cj_config.iv) << std::endl;
                    if (cj_config.use_encryption) {
                        if (crypto_json::check_ecb(cj_config.type)) {
                            temp = crypto_json::load_file(cj_config.path, cj_config.key, cj_config.type, cj_config.use_brotly);
                        } else {
                            temp = crypto_json::load_file(cj_config.path, cj_config.key, cj_config.iv, cj_config.type, cj_config.use_brotly);
                        }
                    } else {
                        temp = crypto_json::load_file(cj_config.path, cj_config.use_brotly);
                    }
                    if (temp.empty()) error_popup.open("ERROR", "Data in file is missing or decoding error");
                    editor.SetText(temp);
                }
                ImGui::CloseCurrentPopup();
                cj_config.is_init = true;
            }

            ImGui::EndPopup();
        }
        /*====================================================================*/
        error_popup.show_dialog();

        window.clear(config.window_background);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}
