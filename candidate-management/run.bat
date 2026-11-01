@echo off
cls
echo =======================================================================
echo   BIEN DICH VA CHAY DU AN QUAN LY THI SINH (DE TAI SO 8 - CTDLGT)
echo =======================================================================
echo.
echo [1/2] Dang bien dich cac file ma nguon C++...
g++ -std=c++17 main.cpp Candidate.cpp LinkedList.cpp HashTable.cpp CandidateManager.cpp Sorter.cpp RoomAllocator.cpp Utils.cpp -o app.exe

if %ERRORLEVEL% EQU 0 (
    echo [2/2] Bien dich THANH CONG!
    echo.
    echo =======================================================================
    echo KHOI DONG CHUONG TRINH:
    echo =======================================================================
    echo.
    app.exe
) else (
    echo.
    echo [!] CO LOI BIEN DICH!
    echo Goi y: Hay kiem tra xem may ban da cai g++ MinGW chua.
    pause
)
