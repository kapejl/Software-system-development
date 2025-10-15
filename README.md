# Развертывание программы
Чтобы запустить программу необходимо:
1. Установить [Visual Studio 2022](https://visualstudio.microsoft.com/ru/vs/community/) или новее.
2. Установить Google Tests (можно в инсталлере вс или через консоль).
3. Скачать папку из ветки.
4. Запустить решение в ВС (выбрать подходящую версию SDK (10.0) и набор инструментов платформы (v143)).
5. Сбилдить консольное приложение и тесты.
6. Проверить работу.



git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat
.\vcpkg integrate install
.\vcpkg install gtest
