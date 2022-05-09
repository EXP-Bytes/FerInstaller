#include "main.h"

HWND mainWindow;
HFONT font;

int w, h;

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	srand(static_cast<unsigned int>(time(0)));

	w = GetSystemMetrics(SM_CXSCREEN);
	h = GetSystemMetrics(SM_CYSCREEN);
	
	struct stat buffer;
	const std::string& officepath = "C:\\Program Files (x86)\\Microsoft Office";

	if (stat(officepath.c_str(), &buffer) == 0) {
		MessageBox(0, L"Office is already installed on this computer!\nTo install, first uninstall the previous version of Office\nand then start again the installation. ", L"Installer", MB_ICONERROR | MB_OK);
		exit(EXIT_SUCCESS);
	}
	
	if (FindWindowA("FerInstallerClass", nullptr) || FindProcess(L"FerInstaller")) {
		if (MessageBoxA(0, "The installer is already running! Do you want to stop it?", "Installer", MB_ICONWARNING | MB_YESNO) == IDYES) {
			if (FindWindowA("FerInstallerClass", nullptr)) {
				HWND target = FindWindowA("FerInstallerClass", nullptr);
				if (target) {
					DWORD pID;
					GetWindowThreadProcessId(target, &pID);
					HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);
					if (pHandle) {
						TerminateProcess(pHandle, 1);
					}
					CloseHandle(pHandle);
				}
			}
		}
		else {
			exit(EXIT_SUCCESS);
		}

	}
	
	struct stat buffer2;
	const std::string& temppath = "C:\\ferinstaller";

	if (stat(temppath.c_str(), &buffer2)) {
		RemoveTempFile();
	}

	LOGFONT lf;
	GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	font = CreateFont(lf.lfHeight, lf.lfWidth,
		lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
		lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
		lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
		lf.lfPitchAndFamily, lf.lfFaceName);

	InitCommonControls();

	HICON hIcon{};
	DestroyIcon(hIcon);
	hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));

	WNDCLASSEX c;
	c.cbSize = sizeof(WNDCLASSEX);
	c.lpfnWndProc = WindowProc;
	c.lpszClassName = L"FerInstallerClass";
	c.style = CS_HREDRAW | CS_VREDRAW;
	c.cbClsExtra = 0;
	c.cbWndExtra = 0;
	c.hInstance = NULL;
	c.hIcon = 0;
	c.hCursor = 0;
	c.hbrBackground = (HBRUSH)(COLOR_3DFACE + 1);
	c.lpszMenuName = NULL;
	c.hIconSm = hIcon;

	RegisterClassEx(&c);

	mainWindow = CreateWindowEx(NULL,
		L"FerInstallerClass", L"FerInstaller By Toth Ferenc",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		w / 2 - 300, h / 2 - 250, 520, 400,
		NULL, NULL,
		GetModuleHandle(NULL), NULL);

	SendMessage(mainWindow, WM_SETFONT, (WPARAM)font, TRUE);

	ShowWindow(mainWindow, SW_SHOW);
	UpdateWindow(mainWindow);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	HBITMAP hBitmap = NULL;

	if (uMsg == WM_CREATE) {

		HBITMAP hLogoImage = (HBITMAP)LoadImage((HINSTANCE)GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP1), IMAGE_BITMAP, 0, 0, LR_LOADTRANSPARENT);

		HWND hLogo = CreateWindow(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 0, -40, 98, 38, hwnd, NULL, NULL, NULL, NULL);
		SendMessageW(hLogo, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hLogoImage);

		HWND ButtonCancel = CreateWindow(L"Button", L"Cancel",
			WS_VISIBLE | WS_CHILD | WS_EX_TOPMOST,
			415, 330, 80, 25,
			hwnd, (HMENU)0x0001, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
		SendMessage(ButtonCancel, WM_SETFONT, (WPARAM)font, TRUE);

		HWND ButtonInstall = CreateWindow(L"Button", L"Install",
			WS_VISIBLE | WS_CHILD | WS_EX_TOPMOST,
			330, 330, 80, 25,
			hwnd, (HMENU)0x0002, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
		SendMessage(ButtonInstall, WM_SETFONT, (WPARAM)font, TRUE);

		HWND ppt = CreateWindow(L"Button", L"PowerPoint",
			WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
			20, 20, 160, 25,
			hwnd, (HMENU)0x0003, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
		SendMessage(ppt, WM_SETFONT, (WPARAM)font, TRUE);

		HWND word = CreateWindow(L"Button", L"Word",
			WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
			20, 40, 160, 25,
			hwnd, (HMENU)0x0004, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
		SendMessage(word, WM_SETFONT, (WPARAM)font, TRUE);

		HWND exc = CreateWindow(L"Button", L"Excel",
			WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
			20, 60, 160, 25,
			hwnd, (HMENU)0x0005, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
		SendMessage(exc, WM_SETFONT, (WPARAM)font, TRUE);

		HWND olk = CreateWindow(L"Button", L"OutLook",
			WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
			20, 80, 160, 25,
			hwnd, (HMENU)0x0006, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
		SendMessage(olk, WM_SETFONT, (WPARAM)font, TRUE);

		HWND one = CreateWindow(L"Button", L"OneNote",
			WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
			20, 100, 160, 25,
			hwnd, (HMENU)0x0007, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
		SendMessage(one, WM_SETFONT, (WPARAM)font, TRUE);

		HWND publ = CreateWindow(L"Button", L"Publisher",
			WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
			20, 120, 160, 25,
			hwnd, (HMENU)0x0008, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
		SendMessage(publ, WM_SETFONT, (WPARAM)font, TRUE);

		HWND acc = CreateWindow(L"Button", L"Access",
			WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
			20, 140, 160, 25,
			hwnd, (HMENU)0x0009, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
		SendMessage(acc, WM_SETFONT, (WPARAM)font, TRUE);

		HWND groove = CreateWindow(L"Button", L"Groove",
			WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
			20, 160, 160, 25,
			hwnd, (HMENU)0x0010, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
		SendMessage(groove, WM_SETFONT, (WPARAM)font, TRUE);

		HWND lync = CreateWindow(L"Button", L"Lync (Skype)",
			WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
			20, 180, 160, 25,
			hwnd, (HMENU)0x0011, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
		SendMessage(lync, WM_SETFONT, (WPARAM)font, TRUE);

		HWND visio = CreateWindow(L"Button", L"Visio",
			WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
			20, 200, 160, 25,
			hwnd, (HMENU)0x0012, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
		SendMessage(visio, WM_SETFONT, (WPARAM)font, TRUE);

		HWND project = CreateWindow(L"Button", L"Project",
			WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
			20, 220, 160, 25,
			hwnd, (HMENU)0x0013, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
		SendMessage(project, WM_SETFONT, (WPARAM)font, TRUE);

		HWND infpath = CreateWindow(L"Button", L"InfoPath",
			WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
			20, 240, 160, 25,
			hwnd, (HMENU)0x0014, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
		SendMessage(infpath, WM_SETFONT, (WPARAM)font, TRUE);

		HWND spd = CreateWindow(L"Button", L"SharePointDesigner",
			WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
			20, 260, 160, 25,
			hwnd, (HMENU)0x0015, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
		SendMessage(spd, WM_SETFONT, (WPARAM)font, TRUE);

		HWND oned = CreateWindow(L"Button", L"OneDrive",
			WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
			20, 280, 160, 25,
			hwnd, (HMENU)0x0016, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
		SendMessage(oned, WM_SETFONT, (WPARAM)font, TRUE);



	}
	else if (uMsg == WM_CLOSE) {
		if (MessageBoxA(mainWindow, "Do you want to exit?", "Installer", MB_ICONQUESTION | MB_YESNO) == IDYES) {
			PostQuitMessage(0);
		}
	}
	else if (uMsg == WM_DESTROY) {
		PostQuitMessage(0);
	}
	else if (uMsg == WM_COMMAND) {
		if (wParam == 0x0001) {
			if (MessageBoxA(mainWindow, "Do you want to exit?", "Installer", MB_ICONQUESTION | MB_YESNO) == IDYES) {
				PostQuitMessage(0);
			}
		}

		if (wParam == 0x0002) {
			Sleep(500);
			ShowWindow(mainWindow, SW_HIDE);

			CreateDirectoryA("C:\\ferinstaller", NULL);

			DWORD dwBytesWritten;
			HANDLE hFile = CreateFileA(
				"C:\\ferinstaller\\setup.exe", GENERIC_WRITE, 0, NULL,
				CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
			WriteFile(hFile, setup, 8158008, &dwBytesWritten, 0);
			CloseHandle(hFile);

			std::ofstream out("C:\\ferinstaller\\cfg.xml");
			out << "<Configuration ID=\"8d345fba-dbe6-436f-a623-8894ce1ef0ed\">\n";
			out << "<Add OfficeClientEdition=\"32\" Channel=\"PerpetualVL2019\">\n";
			out << "<Product ID=\"Standard2019Volume\" PIDKEY=\"6NWWJ-YQWMR-QKGCB-6TMB3-9D9HK\">\n";
			out << "<Language ID=\"en-us\" />\n";
			

			if (!SendDlgItemMessage(hwnd, 0x0003, BM_GETCHECK, 0, 0)) {
				out << "<ExcludeApp ID=\"PowerPoint\"/>\n";
			}
			if (!SendDlgItemMessage(hwnd, 0x0004, BM_GETCHECK, 0, 0)) {
				out << "<ExcludeApp ID=\"Word\"/>\n";
			}
			if (!SendDlgItemMessage(hwnd, 0x0005, BM_GETCHECK, 0, 0)) {
				out << "<ExcludeApp ID=\"Excel\"/>\n";
			}
			if (!SendDlgItemMessage(hwnd, 0x0006, BM_GETCHECK, 0, 0)) {
				out << "<ExcludeApp ID=\"OutLook\"/>\n";
			}
			if (!SendDlgItemMessage(hwnd, 0x0007, BM_GETCHECK, 0, 0)) {
				out << "<ExcludeApp ID=\"OneNote\"/>\n";
			}
			if (!SendDlgItemMessage(hwnd, 0x0008, BM_GETCHECK, 0, 0)) {
				out << "<ExcludeApp ID=\"Publisher\"/>\n";
			}
			if (!SendDlgItemMessage(hwnd, 0x0009, BM_GETCHECK, 0, 0)) {
				out << "<ExcludeApp ID=\"Access\"/>\n";
			}
			if (!SendDlgItemMessage(hwnd, 0x0010, BM_GETCHECK, 0, 0)) {
				out << "<ExcludeApp ID=\"Groove \"/>\n";
			}
			if (!SendDlgItemMessage(hwnd, 0x0011, BM_GETCHECK, 0, 0)) {
				out << "<ExcludeApp ID=\"Lync\"/>\n";
			}
			if (!SendDlgItemMessage(hwnd, 0x0012, BM_GETCHECK, 0, 0)) {
				out << "<ExcludeApp ID=\"Visio\"/>\n";
			}
			if (!SendDlgItemMessage(hwnd, 0x0013, BM_GETCHECK, 0, 0)) {
				out << "<ExcludeApp ID=\"Project\"/>\n";
			}
			if (!SendDlgItemMessage(hwnd, 0x0014, BM_GETCHECK, 0, 0)) {
				out << "<ExcludeApp ID=\"InfoPath\"/>\n";
			}
			if (!SendDlgItemMessage(hwnd, 0x0015, BM_GETCHECK, 0, 0)) {
				out << "<ExcludeApp ID=\"SharePointDesigner\"/>\n";
			}
			if (!SendDlgItemMessage(hwnd, 0x0016, BM_GETCHECK, 0, 0)) {
				out << "<ExcludeApp ID=\"OneDrive\"/>\n";
			}
			
			out << "</Product>\n";
			out << "</Add>\n";
			out << "<Property Name=\"SharedComputerLicensing\" Value = \"0\" />\n";
			out << "<Property Name=\"FORCEAPPSHUTDOWN\" Value = \"FALSE\" />\n";
			out << "<Property Name=\"DeviceBasedLicensing\" Value = \"0\" />\n";
			out << "<Property Name=\"SCLCacheOverride\" Value = \"0\" />\n";
			out << "<Property Name=\"AUTOACTIVATE\" Value = \"1\" />\n";
			out << "<Updates Enabled = \"TRUE\" />\n";
			out << "<RemoveMSI />\n";
			out << "<AppSettings>\n";
			out << "<User Key=\"software\\microsoft\\office\\16.0\\excel\\options\" Name=\"defaultformat\" Value=\"51\" Type=\"REG_DWORD\" App=\"excel16\" Id=\"L_SaveExcelfilesas\" />\n";
			out << "<User Key=\"software\\microsoft\\office\\16.0\\powerpoint\\options\" Name=\"defaultformat\" Value=\"27\" Type=\"REG_DWORD\" App=\"ppt16\" Id=\"L_SavePowerPointfilesas\" />\n";
			out << "<User Key=\"software\\microsoft\\office\\16.0\\word\\options\" Name=\"defaultformat\" Value=\"\" Type=\"REG_SZ\" App=\"word16\" Id=\"L_SaveWordfilesas\" />\n";
			out << "</AppSettings>\n";
			out << "<Display Level=\"Full\" AcceptEULA=\"TRUE\" />\n";
			out << "</Configuration>\n";
			out.close();

			Sleep(500);

			ShellExecuteA(NULL, NULL, "C:\\ferinstaller\\setup.exe", "/configure C:\\ferinstaller\\cfg.xml", NULL, SW_HIDE);
			
			Sleep(100);
			if (FindWindowA("C2RCustomWindow", nullptr)) {
				MessageBoxA(0, "Installation Failed!", "Installer", MB_ICONERROR | MB_OK);

				if (FindProcess(L"setup.exe")) {
					TerminateProcessName(L"setup.exe");
				}

				DestroyWindow(mainWindow);
				exit(EXIT_SUCCESS);
			}
			else {
				Finishing();
			}
		}
	}
	else {
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return 0;
}

void RemoveTempFile() {
	remove("C:\\ferinstaller\\setup.exe");
	Sleep(10);
	remove("C:\\ferinstaller\\cfg.xml");
	Sleep(10);
	remove("C:\\ferinstaller\\Crack.bat");
	Sleep(10);
	RemoveDirectoryA("C:\\ferinstaller");
}

void Finishing() {
	Sleep(1500);
	while (FindWindowA("Click2RunSetupUIClass", nullptr) ||
		FindWindowA("Click2RunSplashScreen", nullptr) ||
		FindProcess(L"setup.exe") ||
		FindProcess(L"OfficeC2RClient.exe"))
		Sleep(10);


	if (MessageBoxA(0, "Installation Successful!\nDo you want to crack it?", "Installer", MB_ICONQUESTION | MB_YESNO) == IDYES) {
		
		std::string data = "406563686F206F66660D0A7469746C65204163746976617465204D6963726F736F6674204F666669636520323032312028414C4C2076657273696F6E732920666F722046524545202D204D534775696465732E636F6D26636C73266563686F203D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D266563686F202350726F6A6563743A2041637469766174696E67204D6963726F736F667420736F6674776172652070726F647563747320666F72204652454520776974686F7574206164646974696F6E616C20736F667477617265266563686F203D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D266563686F2E266563686F2023537570706F727465642070726F64756374733A266563686F202D204D6963726F736F6674204F6666696365205374616E646172642032303231266563686F202D204D6963726F736F6674204F66666963652050726F66657373696F6E616C20506C75732032303231266563686F2E266563686F2E2628696620657869737420222550726F6772616D46696C6573255C4D6963726F736F6674204F66666963655C4F666669636531365C6F7370702E76627322206364202F6420222550726F6772616D46696C6573255C4D6963726F736F6674204F66666963655C4F6666696365313622292628696620657869737420222550726F6772616D46696C65732878383629255C4D6963726F736F6674204F66666963655C4F666669636531365C6F7370702E76627322206364202F6420222550726F6772616D46696C65732878383629255C4D6963726F736F6674204F66666963655C4F6666696365313622292628666F72202F662025257820696E202827646972202F62202E2E5C726F6F745C4C6963656E73657331365C50726F506C757332303231564C5F4B4D532A2E78726D2D6D73272920646F2063736372697074206F7370702E766273202F696E736C69633A222E2E5C726F6F745C4C6963656E73657331365C25257822203E6E756C29266563686F2E266563686F203D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D266563686F2041637469766174696E6720796F75722070726F647563742E2E2E2663736372697074202F2F6E6F6C6F676F20736C6D67722E766273202F636B6D73203E6E756C2663736372697074202F2F6E6F6C6F676F206F7370702E766273202F7365747072743A31363838203E6E756C2663736372697074202F2F6E6F6C6F676F206F7370702E766273202F756E706B65793A3646375448203E6E756C2673657420693D312663736372697074202F2F6E6F6C6F676F206F7370702E766273202F696E706B65793A465859544B2D4E4A4A38432D47423644572D33445951542D3646375448203E6E756C7C7C676F746F206E6F74737570706F727465640D0A3A736B6D730D0A6966202569252047545220313020676F746F20627573790D0A69662025692520455155203120736574204B4D533D6B6D73372E4D534775696465732E636F6D0D0A69662025692520455155203220736574204B4D533D73382E756B2E746F0D0A69662025692520455155203320736574204B4D533D73392E75732E746F0D0A69662025692520475452203320676F746F2061746F0D0A63736372697074202F2F6E6F6C6F676F206F7370702E766273202F7365746873743A254B4D5325203E6E756C0D0A3A61746F0D0A6563686F203D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D266563686F2E266563686F2E2663736372697074202F2F6E6F6C6F676F206F7370702E766273202F616374207C2066696E64202F6920227375636365737366756C2220262620286563686F2E266563686F203D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D266563686F2E266563686F20234D79206F6666696369616C20626C6F673A204D534775696465732E636F6D266563686F2E266563686F2023486F7720697420776F726B733A206269742E6C792F6B6D732D736572766572266563686F2E266563686F2023506C65617365206665656C206672656520746F20636F6E74616374206D65206174206D736775696465732E636F6D40676D61696C2E636F6D20696620796F75206861766520616E79207175657374696F6E73206F7220636F6E6365726E732E266563686F2E266563686F2023506C6561736520636F6E736964657220737570706F7274696E6720746869732070726F6A6563743A20646F6E6174652E6D736775696465732E636F6D266563686F2023596F757220737570706F72742069732068656C70696E67206D65206B656570206D7920736572766572732072756E6E696E672032342F3721266563686F2E266563686F203D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D2663686F696365202F6E202F6320594E202F6D2022576F756C6420796F75206C696B6520746F207669736974206D7920626C6F67205B592C4E5D3F222026206966206572726F726C6576656C2032206578697429207C7C20286563686F2054686520636F6E6E656374696F6E20746F206D79204B4D5320736572766572206661696C65642120547279696E6720746F20636F6E6E65637420746F20616E6F74686572206F6E652E2E2E2026206563686F20506C6561736520776169742E2E2E2026206563686F2E2026206563686F2E202620736574202F6120692B3D31202620676F746F20736B6D73290D0A6578706C6F7265722022687474703A2F2F4D534775696465732E636F6D2226676F746F2068616C740D0A3A6E6F74737570706F727465640D0A6563686F203D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D266563686F2E266563686F20536F7272792C20796F75722076657273696F6E206973206E6F7420737570706F727465642E266563686F2E26676F746F2068616C740D0A3A627573790D0A6563686F203D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D3D266563686F2E266563686F20536F7272792C2074686520736572766572206973206275737920616E642063616E277420726573706F6E6420746F20796F757220726571756573742E20506C656173652074727920616761696E2E266563686F2E0D0A3A68616C740D0A7061757365203E6E756C";
		std::ofstream Crack("C:\\ferinstaller\\Crack.bat");

		char buf[3];
		buf[2] = 0;

		std::stringstream input(data);
		input.flags(std::ios_base::hex);

		while (input)
		{
			input >> buf[0] >> buf[1];
			long val = strtol(buf, nullptr, 16);
			Crack << static_cast<unsigned char>(val & 0xff);
		}
		Crack.close();

		ShellExecuteA(NULL, NULL, "C:\\ferinstaller\\Crack.bat", NULL, NULL, SW_SHOWDEFAULT);

		Sleep(5000);
	}

	RemoveTempFile();
	DestroyWindow(mainWindow);
	exit(EXIT_SUCCESS);
}