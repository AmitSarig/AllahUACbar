# AllahUACbar
`AllahUACbar` is a UAC (User Access Control) bypass tool that works on both Windows 7 and Windows 10.
This tool works by manipulating windows binaries with autoElevate=true by adding custom registry keys.

## Usage:
`AllahUACBar.exe [path to executable (default cmd.exe)]`

## Windows 7:
The CompMgmtLauncher.exe is one of an executable that is built in Windows 7 and has been configured to have the autoElevate setting to "true". CompMgmtLauncher.exe launches compmgmt.msc using ShellExecute. By creating a registry key in the following location in the registry "HKEY_CURRENT_USER\Software\Classes\mscfile\shell\open\command" which we can write to with non-elevated privileges, we can manipulate it to run any program as a high integrity process, bypassing the UAC prompt.

## Windows 10:
The sdclt.exe is one of the the Microsoft binaries that has been configured to have the autoElevate setting to "true". When sdclt.exe starts, the control panel is starting as well. It is also looking for the following registry path: "HKCU\Software\Microsoft\Windows\CurrentVersion\App Paths\control.exe". This location doesn't exist so we can place any executable in this registry location in order to execute it with admin privileges without showing the UAC window.




*This tool built for learning purposes, please use it only for legitimate reasons.
